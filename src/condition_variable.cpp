#include <assert.h>
#include "condition_variable.hpp"

namespace advcpp {

ConditionVariable::ConditionVariable()
: m_waitingSpace()
{}

void ConditionVariable::WaitToBeNotified(Mutex &a_lockedMutex) {
    try {
        a_lockedMutex.UnLock();
    }
    catch(const std::exception &a_ex) {
        assert(!a_ex.what());
    }
    m_waitingSpace.Acquire();
    try {
        a_lockedMutex.Lock();
    }
    catch(const std::exception &a_ex) {
        assert(!a_ex.what());
    }
}

void ConditionVariable::Notify() {
    m_waitingSpace.Release();
}

} //advcpp
