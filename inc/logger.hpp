#ifndef LOGGER_H
#define LOGGER_H

#include "mutex.hpp"
#include "uncopyable.hpp"

#include <iostream>

namespace advcpp {

class Logger : private Uncopyable {
public:
	explicit Logger(std::ostream& os = std::cerr);
	// ~Logger(); = default
	
	void exception(std::exception const& ex);
	void log(const std::string& a_message);
	
	
private:
	void write(const std::string& a_message);

private:
	std::ostream& m_outStream;
	Mutex m_mutex;
};

Logger& GetLogger();
//extern Logger logger;

} //advcpp

#endif // LOGGER_H
