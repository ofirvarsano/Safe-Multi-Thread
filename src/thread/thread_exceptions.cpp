#include "thread_exceptions.hpp"

namespace advcpp {

const char* ThreadLackResourcesException::what() const throw() {
	return "Lack resources to create Thread\n";
}

const char* ThreadInvalidPremissionsException::what() const throw() {
	return "Invalid premissions to create the Thread\n";
}

const char* ThreadJoiningEachOtherException::what() const throw() {
    return "Two threads trying to join each other\n";
}

const char* ThreadAlreadyJoinedException::what() const throw() {
    return "Thread was already joined / detached\n";
}

} //advcpp
