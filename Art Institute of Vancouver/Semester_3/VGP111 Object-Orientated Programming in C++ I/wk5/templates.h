#ifndef __TEMPLATES_H
#define __TEMPLATES_H

template<typename T>
class cCalculator
{
public:
	T Add(T a, T b);
	T Sub(T a, T b);
};

#include "templates.inl"

#endif //__TEMPLATES_H