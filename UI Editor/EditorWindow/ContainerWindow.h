#ifndef CONTAINER_WINDOW_H
#define CONTAINER_WINDOW_H

#include "SimpleWindow.h"

namespace inner
{
	template <typename T>
	class ContainerWindow : public SimpleWindow<T>
	{
	public:
		ContainerWindow(SimpleWindow<T>* parent, int relX, int relY, int width, int height);
		~ContainerWindow() override;

		// 获取窗口是否可以有子窗口对象
		bool isContainerWnd() const override { return true;  }
		//窗口遍历相关函数
		// 用来添加一个子窗口
		void addChild(SimpleWindow<T>* child);
		// 用来在before窗口之前添加一个子窗口
		bool insertChild(SimpleWindow<T>* child, const SimpleWindow<T>* before);
		// 用来移除一个子窗口
		bool removeChild(SimpleWindow<T>* child);
		// 获取该窗口父对象的上一个子窗口，如果该窗口为第一个子窗口，则返回nullptr
		// complexity: linear
		SimpleWindow<T>* getPrevSibling() const;
		// 获取该窗口父对象的下一个子窗口,如果该窗口为最后一个子窗口，则返回nullptr
		//	complexity: linear
		SimpleWindow<T>* getNextSibling() const;

	protected:
		// 用来添加一个子窗口对象，该函数不会检测插入的对象是否已经有了父对象
		void pushChild(SimpleWindow<T>* child) override;

	protected:
		std::vector<SimpleWindow*> m_children;
	};
}

#include "ContainerWindow.inl"

#endif	// CONTAINER_WINDOW_H
