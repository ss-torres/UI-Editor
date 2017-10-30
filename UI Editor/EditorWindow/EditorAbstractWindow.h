#ifndef EDITOR_ABSTRACT_WINDOW_H
#define EDITOR_ABSTRACT_WINDOW_H

#include "EditorFunc.h"
#include "SimpleWindow/SimpleWindow.h"

namespace inner
{
	template <>
	class SimpleWindow<EditorEditableFunc> : public SimpleWindow<EditorFunc>
	{
	public:
		using SimpleWindow<EditorFunc>::SimpleWindow;
		~SimpleWindow<EditorEditableFunc>() override = default;

	protected:
		// 设置该窗口是否编辑时显示
		void setEditShow(bool editShow) override;
		// 该窗口是否处理窗口消息
		bool isHandleMsg() const override { return getEditShow(); }
	};

	// 设置该窗口是否编辑时显示
	inline void SimpleWindow<EditorEditableFunc>::setEditShow(bool editShow)
	{
		// 设置编辑时是否可以显示
		EditorFunc::setEditShow(editShow);
		// 调整父窗口的消息触发范围
		SimpleWindow<EditorFunc>::resetMsgRegion();
	}
}

#endif	// EDITOR_ABSTRACT_WINDOW_H
