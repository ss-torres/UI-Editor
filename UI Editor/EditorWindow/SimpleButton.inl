#ifndef SIMPLE_BUTTON_INL
#define SIMPLE_BUTTON_INL

#include "SimpleButton.h"

namespace inner
{
	template <typename T>
	SimpleButton<T>::SimpleButton(SimpleWindow<T>* parent, int relX, int relY, int width, int height)
		: SimpleWindow<T>(parent, relX, relY, width, height)
	{

	}

	template <typename T>
	SimpleButton<T>::~SimpleButton()
	{

	}
}

#endif	// SIMPLE_BUTTON_INL