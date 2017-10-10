#ifndef EDITOR_MANAGE_WINDOW_H
#define EDITOR_MANAGE_WINDOW_H

/*
 * 文件名：EditorManageWindow
 * 作用：用在EditorWorkArea上，作为最上层的窗口，用来简化处理
 */

#include "WindowInterface.h"
#include "SimpleWindow/ContainerWindow.h"

class EditorManageWindow : public inner::ContainerWindow<inner::EditorContainerFunc>
{
public:
	EditorManageWindow(int relX, int relY, int width, int height);
	~EditorManageWindow();

	// 设置属性是否可以编辑
	bool isAttrEditable() override { return false; }
	// 用来获取构建的窗口类型，继承的窗口返回自身
	virtual SimpleWindow<EditorFunc>* getConstructWindow() { return this; }
	// 获取消息处理的范围，获取自身设置的范围，超过该范围的消息不处理
	wxRegion getMsgRegion() const override;
	// 设置窗口在编辑时是否显示
	void setEditShow(bool editShow) override { EditorFunc::setEditShow(editShow); }

	// 用来获取窗口类名字
	virtual wxString getWindowClassName() const { return wxS("EditorManageWindow"); }

	// 在界面上绘制
	void draw() override {}

protected:
	// 更新该窗口判断消息的范围，将childRect的消息处理范围添加到该窗口中
	void incrMsgRegion(const wxRegion& childRange) override {}
	// 设置窗口消息范围为所有子窗口范围，用来子窗口发生变化，例如改变
	void resetMsgRegion() override {}

	// 该窗口是否处理窗口消息
	bool isHandleMsg() const override { return true; }
};

// 获取消息处理的范围
inline wxRegion EditorManageWindow::getMsgRegion() const
{
	return wxRegion(narrow_cast<wxCoord>(getRelX()), narrow_cast<wxCoord>(getRelY()),
		narrow_cast<wxCoord>(getWidth()), narrow_cast<wxCoord>(getHeight()));
}

#endif	// EDITOR_MANAGE_WINDOW_H
