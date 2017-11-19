#ifndef CONTAINER_WINDOW_INL
#define CONTAINER_WINDOW_INL

#include <cassert>
#include "ContainerWindow.h"
#include "../Util/ArithmeticUtil.h"

namespace inner
{
	template<typename T>
	ContainerWindow<T>::ContainerWindow(SIMPLE_WINDOW_TYPE* parent, int relX, int relY, int width, int height)
		: SimpleWindow<T>(parent, relX, relY, width, height)
	{
	}

	// 获取消息处理的范围
	template<typename T>
	inline wxRegion ContainerWindow<T>::getMsgRegion() const
	{
		if (isHandleMsg())
		{
			return m_msgRegion;
		}
		else
		{
			return wxRegion();
		}
	}

	template <typename T>
	ContainerWindow<T>::~ContainerWindow()
	{
		for (auto value : m_children)
		{
			delete value;
		}
	}

	// 用来添加一个子控件
	template <typename T>
	void ContainerWindow<T>::addChild(SIMPLE_WINDOW_TYPE* child)
	{
		assert(child != nullptr);

		// 先从该控件的父对象中移除这个子控件
		if (child->hasParent())
		{
			// 存在子控件，则一定是ContainerWindow
			child->getParent()->removeChild(child);
		}
		m_children.push_back(child);
		setParent(this, child);

		incrMsgRegion(child->getMsgRegion());
	}

	// 用来在某个控件之前添加一个子控件
	template <typename T>
	bool ContainerWindow<T>::insertChild(SIMPLE_WINDOW_TYPE* child, const SIMPLE_WINDOW_TYPE* before)
	{
		assert(child != nullptr);

		// 先从该控件的父对象中移除这个子控件
		if (child->hasParent())
		{
			// 存在子控件，则一定是ContainerWindow
			child->getParent()->removeChild(child);
		}
		const auto it = std::find(m_children.cbegin(), m_children.cend(), before);
		if (it != m_children.cend())
		{
			return insertChild(child, it);
		}

		return false;
	}

	// 用来在iter之前添加子控件
	template<typename T>
	inline bool ContainerWindow<T>::insertChild(SIMPLE_WINDOW_TYPE* child, ConstChildIterator iter)
	{
		m_children.insert(iter, child);
		setParent(this, child);

		incrMsgRegion(child->getMsgRegion());

		return true;
	}

	// 用来移除一个子控件
	template <typename T>
	bool ContainerWindow<T>::removeChild(SIMPLE_WINDOW_TYPE* child)
	{
		assert(child != nullptr);

		for (auto it = m_children.cbegin(); it != m_children.cend(); ++it)
		{
			if (*it == child)
			{
				m_children.erase(it);
				setParent(nullptr, child);
				if (child->isHandleMsg())
				{
					resetMsgRegion();
				}
				return true;
			}
		}

		return false;
	}

	// 用来添加一个子控件对象，该函数不会检测插入的对象是否已经有了父对象
	template<typename T>
	inline void ContainerWindow<T>::pushChild(SIMPLE_WINDOW_TYPE* child)
	{
		assert(child != nullptr);

		m_children.push_back(child);

		incrMsgRegion(child->getMsgRegion());
	}

	// 更新该控件判断消息的范围，将childRange添加到该控件的消息处理范围，调用该函数不判断该控件是否处理消息，
	// 会判断子控件是否处理消息
	template<typename T>
	inline void ContainerWindow<T>::incrMsgRegion(const wxRegion& childRegion)
	{
		// 记录之前的范围
		auto oldRange = m_msgRegion;
		// 更新子控件范围到当前坐标
		auto adjustRect = childRegion;
		adjustRect.Offset(narrow_cast<wxCoord>(m_relX), narrow_cast<wxCoord>(m_relY));

		m_msgRegion.Union(adjustRect);
		// 该控件范围因为增加了childRegion而发生了改变
		if (oldRange != m_msgRegion)
		{
			SimpleWindow<T>::incrMsgRegion(m_msgRegion);
		}
	}

	// 设置控件消息范围为所有子控件范围，用来子控件发生变化，调用该函数不判断该控件是否处理消息
	// 会判断子控件是否处理消息
	template<typename T>
	inline void ContainerWindow<T>::resetMsgRegion()
	{
		// 记录之前的范围
		auto oldRegion = m_msgRegion;
		// 以子控件坐标系为参考
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