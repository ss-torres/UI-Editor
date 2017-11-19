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
		wxRegion getMsgRegion() const override;

		// 获取控件是否可以有子控件对象
		bool isContainerWnd() const override { return true; }
		// 获取子控件列表中cbegin对应的iterator
		virtual ConstChildIterator getChildrenConstBeg() const { return m_children.cbegin(); }
		// 获取子控件列表中cend对应的iterator
		virtual ConstChildIterator getChildrenConstEnd() const { return m_children.cend(); }
		// 获取子控件个数
		virtual ChildrenSize getChildrenSize() const { return m_children.size(); }
		// 用来添加一个子控件
		void addChild(SIMPLE_WINDOW_TYPE* child) override;
		// 用来在before控件之前添加一个子控件
		bool insertChild(SIMPLE_WINDOW_TYPE* child, const SIMPLE_WINDOW_TYPE* before) override;
		// 用来在iter之前添加子控件
		bool insertChild(SIMPLE_WINDOW_TYPE* child, ConstChildIterator iter) override;
		// 用来移除一个子控件
		bool removeChild(SIMPLE_WINDOW_TYPE* child) override;

		// 重载绘制函数
		void draw(int x, int y) const override {}

	protected:
		// 用来添加一个子控件对象，该函数不会检测插入的对象是否已经有了父对象
		void pushChild(SIMPLE_WINDOW_TYPE* child) override;
		// 更新该控件判断消息的范围，将childRange添加到该控件的消息处理范围，调用该函数不判断该控件是否处理消息，
		// 会判断子控件是否处理消息
		void incrMsgRegion(const wxRegion& childRange);
		// 设置控件消息范围为所有子控件范围，用来子控件发生变化，调用该函数不判断该控件是否处理消息，
		// 会判断子控件是否处理消息
		void resetMsgRegion() override;

		const CHILDREN_CONTAINER& getConstChildren() const override { return m_children; }
		// 获取子控件列表
		CHILDREN_CONTAINER& getChildren() { return m_children; }
		const CHILDREN_CONTAINER& getChildren() const { return m_children; }

	protected:
		// 用来记录所有的子控件
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
