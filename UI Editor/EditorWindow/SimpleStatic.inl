#ifndef SIMPLE_STATIC_INL
#define SIMPLE_STATIC_INL

#include "SimpleStatic.h"

namespace inner
{
	template <typename T>
	SimpleStatic<T>::SimpleStatic(SimpleWindow<T> * parent, int relX, int relY, int width, int height)
		: SimpleWindow<T>(parent, relX, relY, width, height)
	{
	}

	template <typename T>
	SimpleStatic<T>::~SimpleStatic()
	{
	}
}

#endif	// SIMPLE_STATIC_INL