#ifndef EDITOR_WINDOW_H
#define EDITOR_WINDOW_H

/*
 * 文件名：EditorWindow
 * 作用：用来实现窗口的基本功能
 */

#include <vector>
#include <iterator>
#include <wx/string.h>
#include <wx/region.h>
#include <stdexcept>
#include "../../Util/ArithmeticUtil.h"

namespace inner
{
	template <typename T>
	class SimpleWindow : public T
	{
	public:
		// 增加一个类型标识符
		using FuncType = typename T::FuncBaseType;
		using SIMPLE_WINDOW_TYPE = SimpleWindow<FuncType>;
		using CHILDREN_CONTAINER = std::vector<SIMPLE_WINDOW_TYPE*>;
		using ConstChildIterator = typename CHILDREN_CONTAINER::const_iterator;
		using ChildIterator = typename CHILDREN_CONTAINER::iterator;
	public:
		SimpleWindow(SIMPLE_WINDOW_TYPE* parent, int relX, int relY, int width, int height);
		virtual ~SimpleWindow();

		// forbidden the copy constructor and copy assignment
		SimpleWindow(const SimpleWindow<T>& right) = delete;
		SimpleWindow<T>& operator=(const SimpleWindow<T>& right) = delete;

		// 获取窗口是否可以有子窗口对象
		virtual bool isContainerWnd() const { return false; }
		// 获取该窗口的父窗口
		SIMPLE_WINDOW_TYPE* getParent() const { return m_parent; }
		// 标识窗口没有父窗口，简化判断
		bool hasParent() const { return m_parent != nullptr; }
		// 设置该窗口的父窗口对象
		void setParent(SIMPLE_WINDOW_TYPE* parent);

		// 用来添加一个子窗口
		virtual void addChild(SIMPLE_WINDOW_TYPE* child);
		// 用来在before窗口之前添加一个子窗口
		virtual bool insertChild(SIMPLE_WINDOW_TYPE* child, const SIMPLE_WINDOW_TYPE* before);
		// 用来移除一个子窗口
		virtual bool removeChild(SIMPLE_WINDOW_TYPE* child);
		// 获取子窗口列表中cbegin对应的iterator
		virtual ConstChildIterator getChildrencConstBeg() const { return s_defChildrenRet.cbegin(); }
		// 获取子窗口列表中cend对应的iterator
		virtual ConstChildIterator getChildrenConstEnd() const { return s_defChildrenRet.cend(); }


		// 获取该窗口父对象的上一个子窗口，如果该窗口为第一个子窗口，则返回nullptr
		// complexity: linear
		SIMPLE_WINDOW_TYPE* getPrevSibling() const;
		// 获取该窗口父对象的下一个子窗口,如果该窗口为最后一个子窗口，则返回nullptr
		//	complexity: linear
		SIMPLE_WINDOW_TYPE* getNextSibling() const;

		// 窗口的基本属性
		// 设置窗口对象的名字
		void setWindowObjectName(const wxString& objectName) { m_windowObjectName = objectName; }
		// 用来获取窗口对象名字
		wxString getWindowObjectName() { return m_windowObjectName; }
		// 用来获取窗口类名字
		virtual wxString getWindowClassName() const { return wxS("SimpleWindow"); }

		// 编辑窗口范围
		// 更新相对坐标X
		void updateRelX(int x);
		// 获取相对坐标X
		int getRelX() const { return m_relX;  }
		// 获取绝对坐标X
		int getAbsX() const;
		// 更新相对坐标Y
		void updateRelY(int y);
		// 获取相对坐标Y
		int getRelY() const { return m_relY;  }
		// 获取绝对坐标Y
		int getAbsY() const;
		// 更新相对坐标X和Y
		void updateRelPos(int x, int y);
		// 更新窗口宽度大小
		void updateWidth(int width);
		// 获取窗口宽度大小
		int getWidth() const { return m_width;  }
		// 更新窗口高度大小
		void updateHeight(int height);
		// 获取高度大小
		int getHeight() const { return m_height;  }
		// 更新窗口大小
		void updateSize(int width, int height);
		// 更新窗口范围
		void updateRange(int x, int y, int width, int height);

		// 设置窗口是否为Enable
		void setEnable(bool enable) { m_enable = enable; }
		// 设置窗口是否可见
		void setVisible(bool visible) { m_visible = visible; }
		// 设置窗口是否能够可见
		void setVisibleEnable(bool visibleEnable) { m_visibleEnable = visibleEnable; }

		// 在界面上绘制
		virtual void draw() = 0;

		// 获取消息处理的范围，相对范围
		virtual wxRegion getMsgRegion() const;


	protected:
		// 用来添加一个子窗口对象，该函数不会检测插入的对象是否已经有了父对象
		virtual void pushChild(SIMPLE_WINDOW_TYPE* child);
		// 更新该窗口判断消息的范围，将childRect的消息处理范围添加到该窗口中
		virtual void incrMsgRegion(const wxRegion& childRect) { if (hasParent()) { getParent()->incrMsgRegion(childRect); } }
		// 设置窗口消息范围为所有子窗口范围，用来子窗口发生变化，例如改变
		virtual void resetMsgRegion() { if (hasParent()) { getParent()->resetMsgRegion(); } }

		// 获取子窗口列表
		virtual const CHILDREN_CONTAINER& getConstChildren() const;

	protected:
		// 窗口的父对象
		SIMPLE_WINDOW_TYPE* m_parent;

		// 窗口对象名字
		wxString m_windowObjectName;

		// 窗口属性
		// 窗口范围
		int m_relX;
		int m_relY;
		int m_width;
		int m_height;

		// 窗口是否Enable
		bool m_enable;
		// 设置窗口是否可见
		bool m_visible;
		// 设置窗口是否能够可见
		bool m_visibleEnable;

		const static CHILDREN_CONTAINER s_defChildrenRet;

	private:
		// 更新父窗口消息处理范围
		void updateParentMsgRect();
	};

	// 设置该窗口的父窗口对象
	template <typename T>
	inline void SimpleWindow<T>::setParent(SIMPLE_WINDOW_TYPE* parent)
	{
		if (!parent->isContainerWnd())
		{
			throw std::runtime_error("parent is not a Container window");
		}
		m_parent = parent;
	}


	// 更新相对坐标X
	template <typename T>
	inline void SimpleWindow<T>::updateRelX(int x)
	{
		m_relX = x;
		updateParentMsgRect();
	}

	// 更新相对坐标Y
	template <typename T>
	inline void SimpleWindow<T>::updateRelY(int y)
	{
		m_relY = y;
		updateParentMsgRect();
	}

	// 更新相对坐标X和Y
	template <typename T>
	inline void SimpleWindow<T>::updateRelPos(int x, int y)
	{
		m_relX = x;
		m_relY = y;
		updateParentMsgRect();
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

	// 更新窗口宽度大小
	template <typename T>
	inline void SimpleWindow<T>::updateWidth(int width)
	{
		m_width = width;
		updateParentMsgRect();
	}

	// 更新窗口高度大小
	template <typename T>
	inline void SimpleWindow<T>::updateHeight(int height)
	{
		m_height = height;
		updateParentMsgRect();
	}

	// 更新窗口大小
	template <typename T>
	inline void SimpleWindow<T>::updateSize(int width, int height)
	{
		m_width = width;
		m_height = height;
		updateParentMsgRect();
	}

	// 更新窗口范围
	template <typename T>
	inline void SimpleWindow<T>::updateRange(int x, int y, int width, int height)
	{
		m_relX = x;
		m_relY = y;
		m_width = width;
		m_height = height;
		updateParentMsgRect();
	}

	// 获取消息处理的范围，相对范围
	template <typename T>
	inline wxRegion SimpleWindow<T>::getMsgRegion() const 
	{
		return wxRegion(
			narrow_cast<wxCoord>(m_relX), narrow_cast<wxCoord>(m_relY),
			narrow_cast<wxCoord>(m_width), narrow_cast<wxCoord>(m_height));
	}

	// 更新父窗口消息处理范围
	template <typename T>
	inline void SimpleWindow<T>::updateParentMsgRect()
	{
		if (hasParent())
		{
			getParent()->incrMsgRegion(getMsgRegion());
		}
	}


	// 用在Editor模块中
	class EditorEditableFunc;
	template <>
	class SimpleWindow<EditorEditableFunc>;
}

#include "SimpleWindow.inl"

#endif	// EDITOR_WINDOW_H
