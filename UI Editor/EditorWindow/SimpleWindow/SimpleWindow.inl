#ifndef SIMPLE_WINDOW_INL
#define SIMPLE_WINDOW_INL

#include "SimpleWindow.h"

namespace inner
{
	template <typename T>
	SimpleWindow<T>::SimpleWindow(SIMPLE_WINDOW_TYPE* parent, int relX, int relY, int width, int height)
		: T(),
		m_parent(parent), m_relX(relX), m_relY(relY), m_width(width), m_height(height),
		m_enable(true)
	{
		if (parent == nullptr)
		{
			return;
		}
		// 如果作为父对象的控件不能存储子控件
		if (!parent->isContainerWnd())
		{
			throw std::runtime_error("parent is not a Container window");
		}
		parent->pushChild(this);
	}

	template <typename T>
	SimpleWindow<T>::~SimpleWindow()
	{

	}

	// 用来添加一个子控件
	template<typename T>
	inline void SimpleWindow<T>::addChild(SIMPLE_WINDOW_TYPE* child)
	{
		throw std::runtime_error(std::string("SimpleWindow can't invoke ") + __func__); 
	}

	// 用来在before控件之前添加一个子控件
	template <typename T>
	bool SimpleWindow<T>::insertChild(SIMPLE_WINDOW_TYPE* child, const SIMPLE_WINDOW_TYPE* before)
	{
		throw std::runtime_error(std::string("SimpleWindow can't invoke ") + __func__);
		return false;
	}

	// 用来在iter之前添加子控件
	template<typename T>
	inline bool SimpleWindow<T>::insertChild(SIMPLE_WINDOW_TYPE * child, ConstChildIterator iter)
	{
		throw std::runtime_error(std::string("SimpleWindow can't invoke ") + __func__);
		return false;
	}

	// 用来移除一个子控件
	template <typename T>
	bool SimpleWindow<T>::removeChild(SIMPLE_WINDOW_TYPE* child)
	{
		throw std::runtime_error(std::string("SimpleWindow can't invoke ") + __func__);
		return false;
	}

	// 获取该控件父对象的上一个子控件，如果该控件为第一个子控件，则返回nullptr
	// complexity: linear
	template <typename T>
	inline typename SimpleWindow<T>::SIMPLE_WINDOW_TYPE* SimpleWindow<T>::getPrevSibling() const
	{
		auto parentWnd = getParent();
		if (parentWnd == nullptr)
		{
			return nullptr;
		}
		auto siblings = parentWnd->getConstChildren();
		auto myIt = std::find(siblings.cbegin(), siblings.cend(), this);
		// 在这里默认可以找到
		if (myIt != siblings.cbegin())
		{
			return *(--myIt);
		}

		return nullptr;
	}

	// 获取该控件父对象的下一个子控件,如果该控件为最后一个子控件，则返回nullptr
	//	complexity: linear
	template <typename T>
	inline typename SimpleWindow<T>::SIMPLE_WINDOW_TYPE* SimpleWindow<T>::getNextSibling() const
	{
		auto parentWnd = getParent();
		if (parentWnd == nullptr)
		{
			return nullptr;
		}
		auto siblings = parentWnd->getConstChildren();
		auto myIt = std::find(siblings.cbegin(), siblings.cend(), this);
		// 在这里默认可以找到
		if (myIt != (--siblings.cend()))
		{
			return *(++myIt);
		}

		return nullptr;
	}

	// 用来添加一个子控件对象，该函数不会检测插入的对象是否已经有了父对象
	template<typename T>
	inline void SimpleWindow<T>::pushChild(SIMPLE_WINDOW_TYPE* child)
	{
		throw std::runtime_error(std::string("SimpleWindow can't invoke ") + __func__); 
	}

	// 获取子控件列表
	template <typename T>
	const typename SimpleWindow<T>::CHILDREN_CONTAINER& SimpleWindow<T>::getConstChildren() const
	{
		return s_defChildrenRet;
	}

	// 需要子控件列表相关的默认返回值
	template<typename T>
	const typename SimpleWindow<T>::CHILDREN_CONTAINER SimpleWindow<T>::s_defChildrenRet;

	// 需要子控件列表相关的默认返回值
	template<typename T>
	typename SimpleWindow<T>::CHILDREN_CONTAINER SimpleWindow<T>::s_defChildrenRetV;


	// 设置该控件的父控件对象
	template <typename T>
	inline void SimpleWindow<T>::setParent(SIMPLE_WINDOW_TYPE* parent, SIMPLE_WINDOW_TYPE* child)
	{
		if (parent && !parent->isContainerWnd())
		{
			throw std::runtime_error("parent is not a Container window");
		}
		child->m_parent = parent;
	}


	// 更新相对坐标X
	template <typename T>
	inline void SimpleWindow<T>::updateRelX(int x)
	{
		// 先判断是否发生改变
		if (m_relX == x)
		{
			return;
		}

		m_relX = x;
		if (isHandleMsg())
		{
			// 非虚函数
			updateParentMsgRect();
		}
	}

	// 更新相对坐标Y
	template <typename T>
	inline void SimpleWindow<T>::updateRelY(int y)
	{
		// 先判断是否发生改变
		if (m_relY == y)
		{
			return;
		}

		m_relY = y;

		if (isHandleMsg())
		{
			// 非虚函数
			updateParentMsgRect();
		}
	}

	// 更新相对坐标X和Y
	template <typename T>
	inline void SimpleWindow<T>::updateRelPos(int x, int y)
	{
		// 先判断是否发生改变
		if (make_tuple(m_relX, m_relY) == make_tuple(x, y))
		{
			return;
		}

		m_relX = x;
		m_relY = y;
		if (isHandleMsg())
		{
			// 非虚函数
			updateParentMsgRect();
		}
	}

	// 获取绝对坐标X
	template <typename T>
	inline int SimpleWindow<T>::getAbsX() const
	{
		if (hasParent())
		{
			return getParent()->getAbsX() + getRelX();
		}
		return getRelX();
	}

	// 获取绝对坐标Y
	template <typename T>
	inline int SimpleWindow<T>::getAbsY() const
	{
		if (hasParent())
		{
			return getParent()->getAbsY() + getRelY();
		}
		return getRelY();
	}

	// 更新控件宽度大小
	template <typename T>
	inline void SimpleWindow<T>::updateWidth(int width)
	{
		// 先判断是否发生改变
		if (m_width == width)
		{
			return;
		}

		m_width = width;

		if (isHandleMsg())
		{
			// 非虚函数
			updateParentMsgRect();
		}
	}

	// 更新控件高度大小
	template <typename T>
	inline void SimpleWindow<T>::updateHeight(int height)
	{
		// 先判断是否发生改变
		if (m_height == height)
		{
			return;
		}

		m_height = height;

		if (isHandleMsg())
		{
			// 非虚函数
			updateParentMsgRect();
		}
	}

	// 更新控件大小
	template <typename T>
	inline void SimpleWindow<T>::updateSize(int width, int height)
	{
		// 先判断是否发生改变
		if (make_tuple(m_width, m_height) == make_tuple(width, height))
		{
			return;
		}

		m_width = width;
		m_height = height;

		if (isHandleMsg())
		{
			// 非虚函数
			updateParentMsgRect();
		}
	}

	// 更新控件范围
	template <typename T>
	inline void SimpleWindow<T>::updateRange(int x, int y, int width, int height)
	{
		// 先判断是否发生改变
		if (make_tuple(m_relX, m_relY, m_width, m_height)
			== make_tuple(x, y, width, height))
		{
			return;
		}

		m_relX = x;
		m_relY = y;
		m_width = width;
		m_height = height;

		if (isHandleMsg())
		{
			// 非虚函数
			updateParentMsgRect();
		}
	}

	// 获取消息处理的范围，相对范围，相对于自己
	template <typename T>
	inline wxRegion SimpleWindow<T>::getMsgRegion() const
	{
		if (isHandleMsg())
		{
			return wxRegion(0, 0, narrow_cast<wxCoord>(m_width), narrow_cast<wxCoord>(m_height));
		}
		else
		{
			return wxRegion();
		}
	}

	// 更新父控件消息处理范围
	template <typename T>
	inline void SimpleWindow<T>::updateParentMsgRect()
	{
		if (hasParent())
		{
			getParent()->resetMsgRegion();
		}
	}
}

#endif		// SIMPLE_WINDOW_INL