#ifndef CONDITION_VARIABLE_HPP
#define CONDITION_VARIABLE_HPP

#include "semaphore.hpp"
#include "mutex.hpp"
#include "semaphore_exceptions.hpp"
#include "mutex_exceptions.hpp"

namespace advcpp {

class ConditionVariable {
public:
    ConditionVariable();
    //~ConditionVariable = default;

    void Notify();
    void WaitToBeNotified(Mutex &a_lockedMutex);
private:
    ConditionVariable(const ConditionVariable&);
    ConditionVariable& operator=(const ConditionVariable&);

    Semaphore m_waitingSpace;
};

}//advcpp

#endif //CONDITION_VARIABLE_HPP
