#ifndef EDITOR_BUTTON_H
#define EDITOR_BUTTON_H

/*
 * 文件名：EditorButton
 * 作用：在SimpleButton的基础上，实现用于编辑的相关功能
 * 调用函数修改该对象的属性，如果想同时修改属性列表中的值，需要使用updateWinAttr函数
 */

#include "SimpleWindow/SimpleButton.h"
#include "EditorWindowInterface.h"


class EditorButton : public inner::SimpleButton<inner::EditorEditableFunc>
{
public:
	EditorButton(SIMPLE_WINDOW_TYPE* parent, int relX, int relY, int width, int height);
	~EditorButton() override;

	// 用来获取窗口类名字
	virtual wxString getWindowClassName() const { return EDITOR_BUTTON_TYPE; }
	// 用来获取构建的窗口类型，继承的窗口返回自身
	EditorButton* getConstructWindow() override { return this; }

	// 更新窗口对象属性信息
	void updateWinAttr(const wxString& attrName, const wxAny& value) override;

	// 获取窗口是否处于按下状态
	bool isPressed() const { return m_state == EDITOR_STATE_PRESSED; }
	// 获取鼠标是否在窗口上
	bool isMouseOver() const { return m_state == EDITOR_STATE_MOUSE_OVER; }

	//在编辑界面上绘制
	void editDraw(int absX, int absY, DrawControlManager* drawManager) override;

protected:
	// 定义处理消息的类型，返回值表示是否修改了属性，true表示修改，false表示未修改
	using CHANGE_ATTR_FUNC = std::function<bool(EditorButton*, const wxAny&)>;
	using ATTR_HANDLE_MAP = std::map<const wxString, CHANGE_ATTR_FUNC>;
	// 获取属性与属性处理函数Map
	static const ATTR_HANDLE_MAP& getEditorAttrHandles();

private:
	// 初始化属性处理函数Map
	static ATTR_HANDLE_MAP initEditorAttrHanldes();

	// 记录窗口的鼠标状态
	EDITOR_WINDOW_STATE m_state;
};

#endif	// EDITOR_BUTTON_H
