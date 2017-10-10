#ifndef EDITOR_BUTTON_H
#define EDITOR_BUTTON_H

/*
* 文件名：EditorButton
* 作用：在SimpleButton的基础上，实现用于编辑的相关功能
*/

#include "SimpleWindow/SimpleButton.h"
#include "WindowInterface.h"

namespace inner
{
	class EditorButton : public SimpleButton<EditorEditableFunc>
	{
	public:
		EditorButton(SIMPLE_WINDOW_TYPE* parent, int relX, int relY, int width, int height);
		~EditorButton() override;

		// 用来获取窗口类名字
		virtual wxString getWindowClassName() const { return EDITOR_BUTTON_TYPE; }
		// 用来获取构建的窗口类型，继承的窗口返回自身
		SimpleButton<EditorEditableFunc>* getConstructWindow() override { return this; }

		// 更新窗口对象属性信息
		void updateWinAttr(const wxString& attrName, const wxAny& value) override;

	protected:
		// 获取属性与属性处理函数Map
		static const ATTR_HANDLE_MAP& getEditorAttrHandles();

	private:
		// 初始化属性处理函数Map
		static ATTR_HANDLE_MAP initEditorAttrHanldes();
	};
}

#endif	// EDITOR_BUTTON_H
