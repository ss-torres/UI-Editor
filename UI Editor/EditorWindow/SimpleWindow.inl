#ifndef SIMPLE_WINDOW_INL
#define SIMPLE_WINDOW_INL

#include "SimpleWindow.h"

namespace inner
{
	template <typename T>
	SimpleWindow<T>::SimpleWindow(SimpleWindow<T>* parent, int relX, int relY, int width, int height)
		: T(),
		m_parent(parent), m_relX(relX), m_relY(relY), m_width(width), m_height(height),
		m_enable(true),
		m_visible(true),
		m_visibleEnable(true)
	{
		if (parent == nullptr)
		{
			return;
		}
		// 如果作为父对象的窗口不能存储子窗口
		if (!parent->isContainerWnd())
		{
			throw std::runtime_error("parnet is not a Container window");
		}
		parent->pushChild(this);
	}

	template <typename T>
	SimpleWindow<T>::~SimpleWindow()
	{

	}

	// 用来添加一个子窗口对象，该函数不会检测插入的对象是否已经有了父对象
	template<typename T>
	inline void SimpleWindow<T>::pushChild(SimpleWindow<T>* child)
	{
	}
}

#endif		// SIMPLE_WINDOW_INL