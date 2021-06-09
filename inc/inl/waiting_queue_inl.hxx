#ifndef WAITING_QUEUE_INL_HPP
#define WAITING_QUEUE_INL_HPP

#include <assert.h>
#include "waitingQueue.hpp"
#include "semaphore_exceptions.hpp"
#include "mutex_exceptions.hpp"

template<class ValueT>
WaitingQueue<ValueT>::WaitingQueue(size_t a_capacity)
: m_queue()
, m_enqWaiting()
, m_deqWaiting()
, m_queueLock()
, m_capacity(a_capacity)
{}

template<class ValueT>
WaitingQueue<ValueT>::~WaitingQueue() 
{}

template<class ValueT>
void WaitingQueue<ValueT>::Enqueue(const ValueT& a_val)
{
	LockQueue();
	
    if(m_capacity)
    {
    	while(m_capacity == m_queue.size()) {
        	m_enqWaiting.WaitToBeNotified(m_queueLock);
    	}
    }
    try {
        m_queue.push(a_val);
    }
    catch(...) {
        UnLockQueue();
        throw;
    }
    UnLockQueue();
    m_deqWaiting.Notify();
}

template<class ValueT>
void WaitingQueue<ValueT>::Dequeue(ValueT& a_returnVal)
{
	LockQueue();
	
    while(m_queue.empty()) {
        m_deqWaiting.WaitToBeNotified(m_queueLock);
    }
    try {
        a_returnVal = m_queue.front();
    	m_queue.pop();
    }
    catch(...) {
        UnLockQueue();
        throw;
    }
    UnLockQueue();
    m_enqWaiting.Notify();
}

template<class ValueT>
void WaitingQueue<ValueT>::LockQueue()
{
	try {
        m_queueLock.Lock();
    }
    catch(const std::exception &a_ex) {
        assert(!a_ex.what());
    }
}

template<class ValueT>
void WaitingQueue<ValueT>::UnLockQueue()
{
	try {
        m_queueLock.UnLock();
    }
    catch(const std::exception &a_ex) {
        assert(!a_ex.what());
    }
}

template<class ValueT>
bool WaitingQueue<ValueT>::IsEmpty() const
{
	LockQueue();
	return m_queue.empty();
}

template<class ValueT>
bool WaitingQueue<ValueT>::IsFull() const
{
	LockQueue();
	if (m_capacity) {
        return m_capacity == m_queue.size();
    }
    return false;
}

template<class ValueT>
bool WaitingQueue<ValueT>::privateIsEmpty() const
{
	return m_queue.empty();
}

template<class ValueT>
bool WaitingQueue<ValueT>::privateIsFull() const
{
	if (m_capacity) {
        return m_capacity == m_queue.size();
    }
    return false;
}

#endif // WAITING_QUEUE_INL_HPP
