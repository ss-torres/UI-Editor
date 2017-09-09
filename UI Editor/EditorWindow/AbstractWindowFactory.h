#ifndef ABSTRACT_WINDOW_FACTORY_H
#define ABSTRACT_WINDOW_FACTORY_H

#include "SimpleWindow.h"

template <typename T>
class AbstractWindowFactory
{
public:
	AbstractWindowFactory() {}
	virtual ~AbstractWindowFactory() {}

	virtual inner::SimpleWindow<T>* createStatic() const = 0;
	//virtual SimpleWindow<T>* createButton() const = 0;
};

#endif	// ABSTRACT_WINDOW_FACTORY_H
