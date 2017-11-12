#ifndef EDITOR_LABEL_H
#define EDITOR_LABEL_H

/*
 * 文件名：EditorLabel
 * 作用：在SimpleLabel的基础上，实现用于编辑的相关功能
 * 调用函数修改该对象的属性，如果想同时修改属性列表中的值，需要使用updateWinAttr函数
 */

#include "SimpleWindow/SimpleLabel.h"
#include "EditorWindowInterface.h"


//using EditorLabel = inner::SimpleLabel<inner::EditorFunc>;


class EditorLabel : public inner::SimpleLabel<inner::EditorEditableFunc>
{
public:
	EditorLabel(SIMPLE_WINDOW_TYPE* parent, int relX, int relY, int width, int height);
	virtual ~EditorLabel();

	// 用来获取窗口类名字
	wxString getWindowClassName() const override { return EDITOR_LABEL_TYPE; }
	// 用来获取构建的窗口类型，继承的窗口返回自身
	EditorLabel* getConstructWindow() override { return this; }

	// 更新窗口对象属性信息
	void updateWinAttr(const wxString& attrName, const wxAny& value) override;

	//在编辑界面上绘制
	void editDraw(int absX, int absY, DrawControlManager* drawManager) override;

protected:
	// 定义处理消息的类型，返回值表示是否修改了属性，true表示修改，false表示未修改
	using CHANGE_ATTR_FUNC = std::function<bool(EditorLabel*, const wxAny&)>;
	using ATTR_HANDLE_MAP = std::map<const wxString, CHANGE_ATTR_FUNC>;
	// 获取属性与属性处理函数Map
	static const ATTR_HANDLE_MAP& getEditorAttrHandles();
	// 修改显示文字的函数
	bool ChangeText(const wxAny& value);

private:
	// 初始化属性处理函数Map
	static ATTR_HANDLE_MAP initEditorAttrHanldes();
};

#endif	// EDITOR_LABEL_H