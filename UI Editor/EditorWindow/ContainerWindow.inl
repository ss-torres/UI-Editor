#ifndef CONTAINER_WINDOW_INL
#define CONTAINER_WINDOW_INL

#include "ContainerWindow.h"

namespace inner
{
	template<typename T>
	ContainerWindow<T>::ContainerWindow(SimpleWindow<T>* parent, int relX, int relY, int width, int height)
		: SimpleWindow<T>(parent, relX, relY, width, height)
	{
	}

	template <typename T>
	ContainerWindow<T>::~ContainerWindow()
	{

	}

	// 用来添加一个子窗口
	template <typename T>
	void ContainerWindow<T>::addChild(SimpleWindow<T>* child)
	{
		std::assert(child != nullptr);
		// 先从该窗口的父对象中移除这个子窗口
		if (child->getParent() != nullptr)
		{
			child->getParent()->removeChild(child);
		}
		m_children.push_back(child);
		child->setParent(this);
	}

	// 用来在某个窗口之前添加一个子窗口
	template <typename T>
	bool ContainerWindow<T>::insertChild(SimpleWindow<T>* child, const SimpleWindow<T>* before)
	{
		std::assert(child != nullptr);
		// 先从该窗口的父对象中移除这个子窗口
		if (child->getParent() != nullptr)
		{
			child->getParent()->removeChild(child);
		}
		const auto it = std::find(m_children.cbegin(), m_children.cend(), before);
		if (it != m_children.cend())
		{
			m_children.insert(it, child);
			child->setParent(this);
			return true;
		}

		return false;
	}

	// 用来移除一个子窗口
	template <typename T>
	bool ContainerWindow<T>::removeChild(SimpleWindow<T>* child)
	{
		for (auto it = m_children.cbegin(); it != m_children.cend(); ++it)
		{
			if (*it == child)
			{
				m_children.erase(it);
				child->setParent(nullptr);
				return true;
			}
		}

		return false;
	}

	// 获取该窗口父对象的上一个子窗口，如果该窗口为第一个子窗口，则返回nullptr
	// complexity: linear
	template <typename T>
	SimpleWindow<T>* ContainerWindow<T>::getPrevSibling() const
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
	SimpleWindow<T>* ContainerWindow<T>::getNextSibling() const
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

	// 用来添加一个子窗口对象，该函数不会检测插入的对象是否已经有了父对象
	template<typename T>
	void ContainerWindow<T>::pushChild(SimpleWindow<T>* child)
	{
		m_children.push_back(child);
	}
}

#endif	// CONTAINER_WINDOW_INL