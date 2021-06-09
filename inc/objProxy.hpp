#ifndef CLONING_PROXY_HPP
#define CLONING_PROXY_HPP

#include "semaphore.hpp"

namespace advcpp {

template<typename T>
class CloningProxy {
public:
    explicit CloningProxy(const T& a_obj);
    ~CloningProxy();
    
    T* Clone() const;
    void Wait();
    void Notify();
    
private:
	const T& m_object;
	Semaphore m_sem;
};

template<typename T>
CloningProxy<T>::CloningProxy(const T& a_obj)
: m_object(a_obj)
, m_sem(1)
{}
    
template<typename T>
CloningProxy<T>::~CloningProxy() {}    

template<typename T>
T* CloningProxy<T>::Clone() const
{
	return m_object.Clone();
}

template<typename T>
void CloningProxy<T>::Wait()
{
	m_sem.Acquire();
}

template<typename T>  
void CloningProxy<T>::Notify()
{
	m_sem.Release();
}

}//advcpp

#endif // CLONING_PROXY_HPP
