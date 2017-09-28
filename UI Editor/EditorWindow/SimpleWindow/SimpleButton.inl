#ifndef SIMPLE_BUTTON_INL
#define SIMPLE_BUTTON_INL

#include "SimpleButton.h"

namespace inner
{
	template <typename T>
	SimpleButton<T>::SimpleButton(SIMPLE_WINDOW_TYPE* parent, int relX, int relY, int width, int height)
		: SimpleWindow<T>(parent, relX, relY, width, height)
	{

	}

	template <typename T>
	SimpleButton<T>::~SimpleButton()
	{

	}
}

#endif	// SIMPLE_BUTTON_INL