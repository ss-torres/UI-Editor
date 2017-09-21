#ifndef EDITOR_WINDOW_H
#define EDITOR_WINDOW_H

/*
 * 文件名：EditorWindow
 * 作用：用来实现窗口的基本功能
 */

#include <vector>
#include <iterator>
#include <wx/string.h>

namespace inner
{
	template <typename T>
	class SimpleWindow : public T
	{
	public:
		// 增加一个类型标识符
		using FuncType = T;
		using ConstChildIterator = typename std::vector<SimpleWindow<T>*>::const_iterator;
		using ChildIterator = typename std::vector<SimpleWindow*>::iterator;
	public:
		SimpleWindow(SimpleWindow<T>* parent, int relX, int relY, int width, int height);
		virtual ~SimpleWindow();

		// forbidden the copy constructor and copy assignment
		SimpleWindow(const SimpleWindow<T>& right) = delete;
		SimpleWindow<T>& operator=(const SimpleWindow<T>& right) = delete;

		// 获取窗口是否可以有子窗口对象
		virtual bool isContainerWnd() const { return false; }

		// 窗口的基本属性
		// 设置窗口对象的名字
		void setWindowObjectName(const wxString& objectName) { m_windowObjectName = objectName; }
		// 用来获取窗口对象名字
		wxString getWindowObjectName() { return m_windowObjectName; }
		// 用来获取窗口类名字
		virtual wxString getWindowClassName() { return "SimpleWindow"; }

		// 编辑窗口范围
		// 更新相对坐标X
		void updateRelX(int x) { m_relX = x; }
		// 获取相对坐标X
		int getRelX() const { return m_relX;  }
		// 更新相对坐标Y
		void updateRelY(int y) { m_relY = y; }
		// 获取相对坐标Y
		int getRelY() const { return m_relY;  }
		// 更新相对坐标X和Y
		void updateRelPos(int x, int y) { m_relX = x, m_relY = y; }
		// 更新窗口宽度大小
		void updateWidth(int width) { m_width = width; }
		// 获取窗口宽度大小
		int getWidth() const { return m_width;  }
		// 更新窗口高度大小
		void updateHeight(int height) { m_height = height; }
		// 获取高度大小
		int getHeight() const { return m_height;  }
		// 更新窗口范围
		void updateRange(int x, int y, int width, int height) { m_relX = x; m_relY = y; m_width = width; m_height = height; }

		// 设置窗口是否为Enable
		void setEnable(bool enable) { m_enable = enable; }
		// 设置窗口是否可见
		void setVisible(bool visible) { m_visible = visible; }
		// 设置窗口是否能够可见
		void setVisibleEnable(bool visibleEnable) { m_visibleEnable = visibleEnable; }

		// 用来在界面上绘制的函数
		virtual void draw() = 0;

	protected:
		// 获取该窗口的父窗口
		SimpleWindow<T>* getParent() const { return m_parent; }
		// 设置该窗口的父窗口对象
		void setParent(SimpleWindow<T>* parent) { m_parent = parent; }
		// 用来添加一个子窗口对象，该函数不会检测插入的对象是否已经有了父对象
		virtual void pushChild(SimpleWindow<T>* child);

	protected:
		// 窗口的父对象
		SimpleWindow* m_parent;

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
	};

}

#include "SimpleWindow.inl"

#endif	// EDITOR_WINDOW_H
