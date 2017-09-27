#ifndef CONTAINER_WINDOW_INL
#define CONTAINER_WINDOW_INL

#include <cassert>
#include "ContainerWindow.h"
#include "../Util/ArithmeticUtil.h"

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
		for (auto value : m_children)
		{
			delete value;
		}
	}

	// 用来添加一个子窗口
	template <typename T>
	void ContainerWindow<T>::addChild(SimpleWindow<T>* child)
	{
		assert(child != nullptr);

		// 先从该窗口的父对象中移除这个子窗口
		if (child->hasParent())
		{
			child->getParent()->removeChild(child);
		}
		m_children.push_back(child);
		child->setParent(this);
		incrMsgRegion(child->getMsgRegion());
	}

	// 用来在某个窗口之前添加一个子窗口
	template <typename T>
	bool ContainerWindow<T>::insertChild(SimpleWindow<T>* child, const SimpleWindow<T>* before)
	{
		assert(child != nullptr);

		// 先从该窗口的父对象中移除这个子窗口
		if (child->hasParent())
		{
			child->getParent()->removeChild(child);
		}
		const auto it = std::find(m_children.cbegin(), m_children.cend(), before);
		if (it != m_children.cend())
		{
			m_children.insert(it, child);
			child->setParent(this);
			incrMsgRegion(child->getMsgRegion());
			return true;
		}

		return false;
	}

	// 用来移除一个子窗口
	template <typename T>
	bool ContainerWindow<T>::removeChild(SimpleWindow<T>* child)
	{
		assert(child != nullptr);

		for (auto it = m_children.cbegin(); it != m_children.cend(); ++it)
		{
			if (*it == child)
			{
				m_children.erase(it);
				child->setParent(nullptr);
				resetMsgRegion();
				return true;
			}
		}

		return false;
	}

	// 获取该窗口父对象的上一个子窗口，如果该窗口为第一个子窗口，则返回nullptr
	// complexity: linear
	template <typename T>
	inline SimpleWindow<T>* ContainerWindow<T>::getPrevSibling() const
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
	inline SimpleWindow<T>* ContainerWindow<T>::getNextSibling() const
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
	inline void ContainerWindow<T>::pushChild(SimpleWindow<T>* child)
	{
		assert(child != nullptr);

		m_children.push_back(child);
		incrMsgRegion(child->getMsgRegion());
	}

	// 更新父窗口判断消息的范围
	template<typename T>
	inline void ContainerWindow<T>::incrMsgRegion(const wxRegion& childRegion)
	{
		// 记录之前的范围
		auto oldRange = m_msgRegion;
		// 更新子窗口范围到当前坐标
		auto adjustRect = childRegion;
		adjustRect.Offset(narrow_cast<wxCoord>(m_relX), narrow_cast<wxCoord>(m_relY));

		// 子窗口范围不在父窗口之内
		m_msgRegion.Union(adjustRect);
		if (oldRange != m_msgRegion)
		{
			SimpleWindow<T>::incrMsgRegion(m_msgRegion);
		}
	}

	// 设置窗口消息范围为所有子窗口范围
	template<typename T>
	inline void ContainerWindow<T>::resetMsgRegion()
	{
		// 记录之前的范围
		auto oldRegion = m_msgRegion;
		// 以子窗口坐标系为参考
		wxRegion region;
		for (auto chp : m_children)
		{
			region.Union(chp->getMsgRegion());
		}
		region.Union(wxRect(0, 0, narrow_cast<wxCoord>(m_width), narrow_cast<wxCoord>(m_height)));
		m_msgRegion = std::move(region);
		// 偏移到当前坐标系
		m_msgRegion.Offset(narrow_cast<wxCoord>(m_relX), narrow_cast<wxCoord>(m_relY));
		// 如果两者范围不同，则向上传递
		if (oldRegion != m_msgRegion)
		{
			SimpleWindow<T>::resetMsgRegion();
		}
	}
}

#endif	// CONTAINER_WINDOW_INL