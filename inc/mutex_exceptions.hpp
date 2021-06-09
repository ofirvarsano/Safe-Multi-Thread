#ifndef MUTEX_EXCEPTIONS_HPP
#define MUTEX_EXCEPTIONS_HPP

#include <exception>

namespace advcpp {

class MutexLackResources : public std::exception {
    virtual const char* what() const throw() {return "Lack resources to create Mutex\n";}
};

class MutexLackMemory : public std::exception {
    virtual const char* what() const throw() {return "Lack memory to create Mutex\n";}
};

class MutexPremissionUnmatch : public std::exception {
    virtual const char* what() const throw() {return "Invalid premissions to create the Mutex\n";}
};

class MutexDestoryingBusyMutex : public std::exception {
    virtual const char* what() const throw() {return "Trying to destroy a busy Mutex\n";}
};

class MutexMaxNumRecursiveLocks : public std::exception {
    virtual const char* what() const throw() {return "Maximum number of recursive locks allready accuired\n";}
};

class MutexAllreadyLocked : public std::exception {
    virtual const char* what() const throw() {return "Trying to lock a locked Mutex\n";}
};

class MutexLockedByOtherThread : public std::exception {
    virtual const char* what() const throw() {return "Mutex is locked by other thread\n";}
};

class MutexAllreadyUnlocked : public std::exception {
    virtual const char* what() const throw() {return "Trying to unlock an unlocked Mutex\n";}
};

} //advcpp

#endif //MUTEX_EXCEPTIONS_HPP
