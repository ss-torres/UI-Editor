#ifndef EDITOR_WINDOW_H
#define EDITOR_WINDOW_H

/*
 * 文件名：EditorWindow
 * 作用：用来实现窗口的基本功能
 */

#include <vector>
#include <wx/string.h>

namespace inner
{
	template <typename T>
	class SimpleWindow : public T
	{
	public:
		// 增加一个类型标识符
		using FuncType = T;
		//using ConstChildIterator = std::list<SimpleWindow*>::const_iter;
		//using ChildIterator = std::list<SimpleWindow*>::iterator;
	public:
		SimpleWindow(SimpleWindow<T>* parent, int relX, int relY, int width, int height);
		virtual ~SimpleWindow();

		//窗口遍历相关函数
		// 获取该窗口的父窗口
		SimpleWindow<T>* getParent() const { return m_parent; }
		// 用来添加一个子窗口
		void AddChild(SimpleWindow<T>* child);
		// 用来在before窗口之前添加一个子窗口
		bool InsertChild(SimpleWindow<T>* child, const SimpleWindow<T>* before);
		// 用来移除一个子窗口
		bool RemoveChild(SimpleWindow<T>* child);
		// 获取该窗口父对象的上一个子窗口，如果该窗口为第一个子窗口，则返回nullptr
		// complexity: linear
		SimpleWindow<T>* getPrevSibling() const;
		// 获取该窗口父对象的下一个子窗口,如果该窗口为最后一个子窗口，则返回nullptr
		//	complexity: linear
		SimpleWindow<T>* getNextSibling() const;

		// 窗口的基本属性
		// 设置窗口对象的名字
		void setWindowObjectName(const wxString& objectName) { m_windowObjectName = objectName; }
		// 用来获取窗口对象名字
		wxString getWindowObjectName() { return m_windowObjectName; }
		// 用来获取窗口类名字
		virtual wxString getWindowClassName() { return "EditorWindow"; }

		// 编辑窗口范围
		// 更新相对坐标X
		void updateRelX(int x) { m_relX = x; }
		// 更新相对坐标Y
		void updateRelY(int y) { m_relY = y; }
		// 更新相对坐标X和Y
		void updateRelPos(int x, int y) { m_relX = x, m_relY = y; }
		// 更新窗口宽度大小
		void updateWidth(int width) { m_width = width; }
		// 更新窗口高度大小
		void updateHeight(int height) { m_height = height; }
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
		// 窗口的父子级
		SimpleWindow* m_parent;
		std::vector<SimpleWindow*> m_children;

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
