#ifndef EDITOR_WINDOW_H
#define EDITOR_WINDOW_H

/*
 * 文件名：EditorWindow
 * 作用：用来实现控件的基本功能
 * 说明：
 * 1.控件的消息响应范围由该控件是否可以编辑决定，不受控件是否激活影响
 * 2.响应消息时，从父控件到子控件判断，如果父控件不处理消息，或者处理消息范围不满足条件，则不判断子控件是否处理
 * 3.如果父控件隐藏，则子控件也一起隐藏
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
		using ChildrenSize = typename CHILDREN_CONTAINER::size_type;
	public:
		SimpleWindow(SIMPLE_WINDOW_TYPE* parent, int relX, int relY, int width, int height);
		virtual ~SimpleWindow();

		// forbidden the copy constructor and copy assignment
		SimpleWindow(const SimpleWindow<T>& right) = delete;
		SimpleWindow<T>& operator=(const SimpleWindow<T>& right) = delete;

		// 获取控件是否可以有子控件对象
		virtual bool isContainerWnd() const { return false; }
		// 获取该控件的父控件
		SIMPLE_WINDOW_TYPE* getParent() const { return m_parent; }
		// 标识控件没有父控件，简化判断
		bool hasParent() const { return m_parent != nullptr; }

		// 用来添加一个子控件
		virtual void addChild(SIMPLE_WINDOW_TYPE* child);
		// 用来在before控件之前添加一个子控件
		virtual bool insertChild(SIMPLE_WINDOW_TYPE* child, const SIMPLE_WINDOW_TYPE* before);
		// 用来在iter之前添加子控件
		virtual bool insertChild(SIMPLE_WINDOW_TYPE* child, ConstChildIterator iter);
		// 用来移除一个子控件
		virtual bool removeChild(SIMPLE_WINDOW_TYPE* child);
		// 获取子控件列表中cbegin对应的iterator
		virtual ConstChildIterator getChildrenConstBeg() const { return s_defChildrenRet.cbegin(); }
		// 获取子控件列表中cend对应的iterator
		virtual ConstChildIterator getChildrenConstEnd() const { return s_defChildrenRet.cend(); }
		// 获取子控件个数
		virtual ChildrenSize getChildrenSize() const { return 0; }


		// 获取该控件父对象的上一个子控件，如果该控件为第一个子控件，则返回nullptr
		// complexity: linear
		SIMPLE_WINDOW_TYPE* getPrevSibling() const;
		// 获取该控件父对象的下一个子控件,如果该控件为最后一个子控件，则返回nullptr
		//	complexity: linear
		SIMPLE_WINDOW_TYPE* getNextSibling() const;

		// 控件的基本属性

		// 编辑控件范围
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
		// 更新控件宽度大小
		void updateWidth(int width);
		// 获取控件宽度大小
		int getWidth() const { return m_width;  }
		// 更新控件高度大小
		void updateHeight(int height);
		// 获取高度大小
		int getHeight() const { return m_height;  }
		// 更新控件大小
		void updateSize(int width, int height);
		// 更新控件范围
		void updateRange(int x, int y, int width, int height);

		// 设置是否激活
		void setEnable(bool enable) { m_enable = enable; }
		// 获取是否激活
		bool getEnable() const { return m_enable; }

		// 在界面上绘制
		virtual void draw(int x, int y) const = 0;

		// 获取消息处理的范围，相对范围，相对于自己
		virtual wxRegion getMsgRegion() const;
		// 该控件是否处理控件消息
		virtual bool isHandleMsg() const { return true; }

	protected:
		// 设置该控件的父控件对象，该函数调用不会改变父控件的消息响应范围
		void setParent(SIMPLE_WINDOW_TYPE* parent, SIMPLE_WINDOW_TYPE* child);
		// 用来添加一个子控件对象，该函数不会检测插入的对象是否已经有了父对象
		virtual void pushChild(SIMPLE_WINDOW_TYPE* child);
		// 更新该控件判断消息的范围，将childRect的消息处理范围添加到该控件中
		virtual void incrMsgRegion(const wxRegion& childRect) { if (hasParent()) { getParent()->incrMsgRegion(childRect); } }
		// 设置控件消息范围为所有子控件范围，用来处理子控件发生变化，例如改变
		virtual void resetMsgRegion() { if (hasParent()) { getParent()->resetMsgRegion(); } }

		// 获取子控件列表
		virtual const CHILDREN_CONTAINER& getConstChildren() const;
		// 获取子控件列表中begin对应的iterator
		virtual ChildIterator getChildrenBeg() { return s_defChildrenRetV.begin(); }
		// 获取子控件列表中end对应的iterator
		virtual ChildIterator getChildrenEnd() { return s_defChildrenRetV.end(); }

	protected:
		// 控件的父对象
		SIMPLE_WINDOW_TYPE* m_parent;

		// 控件属性
		// 控件范围
		int m_relX;
		int m_relY;
		int m_width;
		int m_height;

		// 是否处于激活状态
		bool m_enable;

		const static CHILDREN_CONTAINER s_defChildrenRet;
		static CHILDREN_CONTAINER s_defChildrenRetV;

	private:
		// 更新父控件消息处理范围
		void updateParentMsgRect();
	};

	// 用在Editor模块中
	class EditorEditableFunc;
	template <>
	class SimpleWindow<EditorEditableFunc>;
}

#include "SimpleWindow.inl"

#endif	// EDITOR_WINDOW_H
