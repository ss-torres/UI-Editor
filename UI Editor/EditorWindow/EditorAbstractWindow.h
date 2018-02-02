#ifndef EDITOR_ABSTRACT_WINDOW_H
#define EDITOR_ABSTRACT_WINDOW_H

#include "EditorFunc.h"
#include "EditorWindowDefine.h"
#include "SimpleWindow/SimpleWindow.h"

class SaveInfo;

namespace inner
{
	template <>
	class SimpleWindow<EditorEditableFunc> : public SimpleWindow<EditorFunc>
	{
	public:
		using SELF_TYPE = SimpleWindow<EditorEditableFunc>;
	public:
		using SimpleWindow<EditorFunc>::SimpleWindow;
		~SimpleWindow<EditorEditableFunc>() override = default;

		// 将窗口信息保存到传入的容器中，如果replace为true，表示直接修改parentInfo，而不作为子对象
		void appendMySelf(SaveInfo& parentInfo, bool replace = false) const;

	protected:
		// 设置该控件是否编辑时显示
		void setEditShow(bool editShow) override;
		// 该控件是否处理控件消息
		bool isHandleMsg() const override { return getEditShow(); }
	};

	// 设置该控件是否编辑时显示
	inline void SimpleWindow<EditorEditableFunc>::setEditShow(bool editShow)
	{
		if (editShow != getEditShow())
		{
			// 设置编辑时是否可以显示
			EditorFunc::setEditShow(editShow);
			// 调整父控件的消息触发范围
			SimpleWindow<EditorFunc>::resetMsgRegion();
		}
	}
}

#endif	// EDITOR_ABSTRACT_WINDOW_H
