#include <assert.h>
#include "waitingQueue.hpp"
#include "semaphore_exceptions.hpp"
#include "mutex_exceptions.hpp"

namespace advcpp {

template<class ValueT>
WaitingQueue<ValueT>::WaitingQueue()
: m_queue()
//, m_enqWaiting()
, m_deqWaiting()
, m_queueLock()
{
    assert(m_queue.empty());
}

template<class ValueT>
WaitingQueue<ValueT>::~WaitingQueue() 
{}

template<class ValueT>
void WaitingQueue<ValueT>::Enqueue(const ValueT& a_val) {
	
    m_queueLock.Lock();
    m_queue.push(a_val);
    m_queueLock.UnLock();
    m_deqWaiting.Notify();
}

template<class ValueT>
void WaitingQueue<ValueT>::Dequeue(ValueT& a_returnVal) {

    m_queueLock.Lock();
    while(m_queue.empty()) {
        m_deqWaiting.WaitToBeNotified(m_queueLock);
    }
    a_returnVal = m_queue.front();
    m_queue.pop();
    m_queueLock.UnLock();
}
  
} //advcpp
