#ifndef THREAD_EXCEPTIONS
#define THREAD_EXCEPTIONS

#include <exception>

namespace advcpp {

class ThreadLackResourcesException : public std::exception {
    virtual const char* what() const throw();
};

class ThreadInvalidPremissionsException : public std::exception {
    virtual const char* what() const throw();
};

class ThreadJoiningEachOtherException : public std::exception {
    virtual const char* what() const throw();
};

class ThreadAlreadyJoinedException : public std::exception {
    virtual const char* what() const throw();
};

} //advcpp

#endif // THREAD_EXCEPTIONS
