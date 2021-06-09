#ifndef WAITING_QUEUE_HPP
#define WAITING_QUEUE_HPP

#include <assert.h>

#include "condition_variable.hpp"
#include "mutex.hpp"
#include "uncopyable.hpp"
#include <queue>

namespace advcpp {

template <class ValueT>
class WaitingQueue : private Uncopyable {
public:
     explicit WaitingQueue(size_t a_capacity = 0);
    ~WaitingQueue();

    void Enqueue(const ValueT& a_val);
    void Dequeue(ValueT& a_returnVal);
    
    void LockQueue();
    void UnLockQueue();
    
    bool IsEmpty() const;
    bool IsFull() const;

private:
	bool privateIsEmpty() const;
    bool privateIsFull() const;
    
    std::queue<ValueT> m_queue;
    ConditionVariable m_enqWaiting;
    ConditionVariable m_deqWaiting;
    mutable Mutex m_queueLock;
    size_t m_capacity;
};

#include "waiting_queue_inl.hxx"

} //experis

#endif //WAITING_QUEUE_HPP
