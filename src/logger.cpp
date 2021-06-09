#include "logger.hpp"
#include <pthread.h>

namespace advcpp {

Logger::Logger(std::ostream& os)
: m_outStream(os)
{}

void Logger::exception(std::exception const& ex)
{
	write(ex.what());
}

void Logger::log(const std::string& a_message)
{
	write(a_message);
}

void Logger::write(const std::string& a_message)
{
	m_mutex.Lock();
	m_outStream << "[TID: " << pthread_self() << "]\n";
	m_outStream << a_message << std::endl;
	m_mutex.UnLock();
}

Logger& GetLogger()
{
	static Mutex mutex;
	mutex.Lock();
	try {
		static Logger* logg = new Logger;
		mutex.UnLock();
		return *logg;
	}
	catch(...) {
		mutex.UnLock();
		throw;
	}
}

//Logger logger = GetLogger();

} //advcpp
