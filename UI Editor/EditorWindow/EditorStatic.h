#ifndef EDITOR_STATIC_H
#define EDITOR_STATIC_H

/*
 * 文件名：EditorStatic
 * 作用：在SimpleStatic的基础上，实现用于编辑的相关功能
 */

#include "SimpleStatic.h"
#include "EditorFunc.h"
#include "WindowInterface.h"


//using EditorStatic = inner::SimpleStatic<inner::EditorFunc>;


namespace inner
{
	class EditorStatic : public SimpleStatic<EditorFunc>
	{
	public:
		EditorStatic(AbstractEditorWindow* parent, int relX, int relY, int width, int height);
		virtual ~EditorStatic();

		// 用来获取构建的窗口类型，继承的窗口返回自身
		SimpleStatic<EditorFunc>* getConstructWindow() override { return this;  }

	};
}

#include "SimpleStatic.inl"

#endif	// EDITOR_STATIC_H