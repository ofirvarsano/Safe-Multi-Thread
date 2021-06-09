#ifndef SEMAPHORE_EXCEPTIONS_HPP
#define SEMAPHORE_EXCEPTIONS_HPP

#include <exception>

namespace advcpp {

class SemaphoreOverFlow : public std::exception {
    virtual const char* what() const throw() {return "Semaphore overflow\n";}
};

class SemaphoreBlocked : public std::exception {
    virtual const char* what() const throw() {return "Semaphore is blocked\n";}
};

class SemaphoreTimedOut : public std::exception {
    virtual const char* what() const throw() {return "Semaphore timedout\n";}
};

} //advcpp

#endif //SEMAPHORE_EXCEPTIONS_HPP
