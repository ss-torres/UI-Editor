#ifndef SIMPLE_WINDOW_INL
#define SIMPLE_WINDOW_INL

#include "SimpleWindow.h"

namespace inner
{
	template <typename T>
	SimpleWindow<T>::SimpleWindow(SIMPLE_WINDOW_TYPE* parent, int relX, int relY, int width, int height)
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
			throw std::runtime_error("parent is not a Container window");
		}
		parent->pushChild(this);
	}

	template <typename T>
	SimpleWindow<T>::~SimpleWindow()
	{

	}

	// 用来添加一个子窗口
	template<typename T>
	inline void SimpleWindow<T>::addChild(SIMPLE_WINDOW_TYPE* child)
	{
		throw std::runtime_error(std::string("SimpleWindow can't invoke ") + __func__); 
	}

	// 用来在before窗口之前添加一个子窗口
	template <typename T>
	bool SimpleWindow<T>::insertChild(SIMPLE_WINDOW_TYPE* child, const SIMPLE_WINDOW_TYPE* before)
	{
		throw std::runtime_error(std::string("SimpleWindow can't invoke ") + __func__);
		return false;
	}

	// 用来在iter之前添加子窗口
	template<typename T>
	inline bool SimpleWindow<T>::insertChild(SIMPLE_WINDOW_TYPE * child, ConstChildIterator iter)
	{
		throw std::runtime_error(std::string("SimpleWindow can't invoke ") + __func__);
		return false;
	}

	// 用来移除一个子窗口
	template <typename T>
	bool SimpleWindow<T>::removeChild(SIMPLE_WINDOW_TYPE* child)
	{
		throw std::runtime_error(std::string("SimpleWindow can't invoke ") + __func__);
		return false;
	}

	// 获取该窗口父对象的上一个子窗口，如果该窗口为第一个子窗口，则返回nullptr
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

	// 获取该窗口父对象的下一个子窗口,如果该窗口为最后一个子窗口，则返回nullptr
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

	// 用来添加一个子窗口对象，该函数不会检测插入的对象是否已经有了父对象
	template<typename T>
	inline void SimpleWindow<T>::pushChild(SIMPLE_WINDOW_TYPE* child)
	{
		throw std::runtime_error(std::string("SimpleWindow can't invoke ") + __func__); 
	}

	// 获取子窗口列表
	template <typename T>
	const typename SimpleWindow<T>::CHILDREN_CONTAINER& SimpleWindow<T>::getConstChildren() const
	{
		return s_defChildrenRet;
	}


	// 需要子窗口列表相关的默认返回值
	template<typename T>
	const typename SimpleWindow<T>::CHILDREN_CONTAINER SimpleWindow<T>::s_defChildrenRet;
}

#endif		// SIMPLE_WINDOW_INL