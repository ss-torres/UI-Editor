#ifndef SIMPLE_STATIC_INL
#define SIMPLE_STATIC_INL

#include "SimpleLabel.h"

namespace inner
{
	template <typename T>
	SimpleLabel<T>::SimpleLabel(SIMPLE_WINDOW_TYPE * parent, int relX, int relY, int width, int height)
		: SimpleWindow<T>(parent, relX, relY, width, height)
	{
	}

	template <typename T>
	SimpleLabel<T>::~SimpleLabel()
	{
	}
}

#endif	// SIMPLE_STATIC_INL