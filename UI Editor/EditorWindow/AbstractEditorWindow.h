#ifndef ABSTRACT_EDITOR_WINDOW_H
#define ABSTRACT_EDITOR_WINDOW_H

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

		// 设置该窗口是否编辑时显示

	};
}

#endif	// ABSTRACT_EDITOR_WINDOW_H
