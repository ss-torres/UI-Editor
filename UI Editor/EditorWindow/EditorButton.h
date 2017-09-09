#ifndef EDITOR_BUTTON_H
#define EDITOR_BUTTON_H

/*
* 文件名：EditorButton
* 作用：在SimpleButton的基础上，实现用于编辑的相关功能
*/

#include "SimpleButton.h"
#include "EditorFunc.h"
#include "WindowInterface.h"

namespace inner
{
	class EditorButton : SimpleButton<EditorFunc>
	{
	public:
		EditorButton(AbstractEditorWindow* parent, int relX, int relY, int width, int height);
		~EditorButton();


	};
}

#include "EditorButton.inl"

#endif	// EDITOR_BUTTON_H
