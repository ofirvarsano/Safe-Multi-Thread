#ifndef UNCOPYABLE_H
#define UNCOPYABLE_H

namespace advcpp {

class Uncopyable {
protected:
	explicit Uncopyable();
private:
	Uncopyable(Uncopyable const&); // no copy
};

} //advcpp

#endif // UNCOPYABLE_H
