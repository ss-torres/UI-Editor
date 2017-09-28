#ifndef CONTAINER_WINDOW_H
#define CONTAINER_WINDOW_H

#include "SimpleWindow.h"

namespace inner
{
	template <typename T>
	class ContainerWindow : public SimpleWindow<T>
	{
	public:
		using SIMPLE_WINDOW_TYPE = typename SimpleWindow<T>::SIMPLE_WINDOW_TYPE;
	public:
		ContainerWindow(SIMPLE_WINDOW_TYPE* parent, int relX, int relY, int width, int height);
		~ContainerWindow() override;

		// 获取消息处理的范围
		wxRegion getMsgRegion() const override { return m_msgRegion; }

		// 获取窗口是否可以有子窗口对象
		bool isContainerWnd() const override { return true; }
		// 获取子窗口列表中cbegin对应的iterator
		virtual ConstChildIterator getChildrencConstBeg() const { return m_children.cbegin(); }
		// 获取子窗口列表中cend对应的iterator
		virtual ConstChildIterator getChildrenConstEnd() const { return m_children.cend(); }
		// 获取子窗口个数
		virtual ChildrenSize getChildrenSize() const { return m_children.size(); }
		// 用来添加一个子窗口
		void addChild(SIMPLE_WINDOW_TYPE* child) override;
		// 用来在before窗口之前添加一个子窗口
		bool insertChild(SIMPLE_WINDOW_TYPE* child, const SIMPLE_WINDOW_TYPE* before) override;
		// 用来在iter之前添加子窗口
		bool insertChild(SIMPLE_WINDOW_TYPE* child, ConstChildIterator iter) override;
		// 用来移除一个子窗口
		bool removeChild(SIMPLE_WINDOW_TYPE* child) override;

	protected:
		// 用来添加一个子窗口对象，该函数不会检测插入的对象是否已经有了父对象
		void pushChild(SIMPLE_WINDOW_TYPE* child) override;
		// 更新该窗口判断消息的范围，将childRect的消息处理范围添加到该窗口中
		void incrMsgRegion(const wxRegion& childRange) override;
		// 设置窗口消息范围为所有子窗口范围，用来子窗口发生变化，例如改变
		void resetMsgRegion() override;

		const CHILDREN_CONTAINER& getConstChildren() const override { return m_children; }
		// 获取子窗口列表
		CHILDREN_CONTAINER& getChildren() { return m_children; }
		const CHILDREN_CONTAINER& getChildren() const { return m_children; }

	protected:
		// 用来记录所有的子窗口
		CHILDREN_CONTAINER m_children;
		// 用来处理消息处理范围
		wxRegion m_msgRegion;
	};

	// 用在Editor模块中
	class EditorContainerFunc;
	template <>
	class ContainerWindow<EditorContainerFunc>;
}

#include "ContainerWindow.inl"

#endif	// CONTAINER_WINDOW_H
