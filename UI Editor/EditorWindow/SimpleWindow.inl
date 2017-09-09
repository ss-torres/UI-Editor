#ifndef SIMPLE_WINDOW_INL
#define SIMPLE_WINDOW_INL

#include "SimpleWindow.h"

namespace inner
{
	template <typename T>
	SimpleWindow<T>::SimpleWindow(SimpleWindow<T>* parent, int relX, int relY, int width, int height)
		: m_parent(parent), m_relX(relX), m_relY(relY), m_width(width), m_height(height),
		m_enable(true),
		m_visible(true),
		m_visibleEnable(true)
	{

	}

	template <typename T>
	SimpleWindow<T>::~SimpleWindow()
	{

	}

	// 用来添加一个子窗口
	template <typename T>
	void SimpleWindow<T>::AddChild(SimpleWindow<T>* child)
	{
		m_children.push_back(child);
	}

	// 用来在某个窗口之前添加一个子窗口
	template <typename T>
	bool SimpleWindow<T>::InsertChild(SimpleWindow<T>* child, const SimpleWindow<T>* before)
	{
		const auto it = std::find(m_children.cbegin(), m_children.cend(), before);
		if (it != m_children.cend())
		{
			m_children.insert(it, child);
			return true;
		}

		return false;
	}

	// 用来移除一个子窗口
	template <typename T>
	bool SimpleWindow<T>::RemoveChild(SimpleWindow<T>* child)
	{
		for (auto it = m_children.cbegin(); it != m_children.cend(); ++it)
		{
			if (*it == child)
			{
				m_children.erase(it);
				return true;
			}
		}

		return false;
	}

	// 获取该窗口父对象的上一个子窗口，如果该窗口为第一个子窗口，则返回nullptr
	// complexity: linear
	template <typename T>
	SimpleWindow<T>* SimpleWindow<T>::getPrevSibling() const
	{
		auto parentWnd = getParent();
		if (parentWnd == nullptr)
		{
			return nullptr;
		}
		auto myIt = std::find(parentWnd->m_children.cbegin(), parentWnd->m_children.cend(), this);
		// 在这里默认可以找到
		if (myIt != parentWnd->m_children.cbegin())
		{
			return *(--myIt);
		}

		return nullptr;
	}

	// 获取该窗口父对象的下一个子窗口,如果该窗口为最后一个子窗口，则返回nullptr
	//	complexity: linear
	template <typename T>
	SimpleWindow<T>* SimpleWindow<T>::getNextSibling() const
	{
		auto parentWnd = getParent();
		if (parentWnd == nullptr)
		{
			return nullptr;
		}
		auto myIt = std::find(parentWnd->m_children.cbegin(), parentWnd->m_children.cend(), this);
		// 在这里默认可以找到
		if (myIt != (--parentWnd->m_children.cend()))
		{
			return *(++myIt);
		}

		return nullptr;
	}
}

#endif		// SIMPLE_WINDOW_INL