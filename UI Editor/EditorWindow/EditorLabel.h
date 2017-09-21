#ifndef EDITOR_LABEL_H
#define EDITOR_LABEL_H

/*
 * 文件名：EditorLabel
 * 作用：在SimpleLabel的基础上，实现用于编辑的相关功能
 */

#include "SimpleLabel.h"
#include "EditorFunc.h"
#include "WindowInterface.h"


//using EditorLabel = inner::SimpleLabel<inner::EditorFunc>;


namespace inner
{
	class EditorLabel : public SimpleLabel<EditorFunc>
	{
	public:
		EditorLabel(AbstractEditorWindow* parent, int relX, int relY, int width, int height);
		virtual ~EditorLabel();

		// 用来获取构建的窗口类型，继承的窗口返回自身
		SimpleLabel<EditorFunc>* getConstructWindow() override { return this;  }

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

#endif	// EDITOR_LABEL_H