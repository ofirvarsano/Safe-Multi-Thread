#ifndef RUNNABLE_HPP
#define RUNNABLE_HPP

namespace advcpp {

class Runnable {
public:
    Runnable();
    virtual ~Runnable() = 0;
    virtual void operator()() = 0;
    virtual Runnable* Clone() const = 0;
};

}//advcpp

#endif //RUNNABLE_HPP
