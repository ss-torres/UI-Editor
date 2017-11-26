#ifndef EDITOR_MANAGE_WINDOW_H
#define EDITOR_MANAGE_WINDOW_H

/*
 * 文件名：EditorManageWindow
 * 作用：用在FormWorkArea上，作为最上层的控件，用来简化处理
 */


#include "SimpleWindow/ContainerWindow.h"
#include "EditorWindowInterface.h"

class EditorManageWindow : public inner::ContainerWindow<inner::EditorContainerFunc>
{
public:
	EditorManageWindow(int relX, int relY, int width, int height);
	~EditorManageWindow();

	// 设置属性是否可以编辑
	bool isAttrEditable() override { return false; }
	// 用来获取构建的控件类型，继承的控件返回自身
	EditorManageWindow* getConstructWindow() override { return this; }
	// 获取消息处理的范围，获取自身设置的范围，超过该范围的消息不处理，相对范围，相对于自己
	wxRegion getMsgRegion() const override;
	// 设置控件在编辑时是否显示
	void setEditShow(bool editShow) override { EditorFunc::setEditShow(editShow); }

	// 用来获取控件类名字
	virtual wxString getWindowClassName() const { return wxS("EditorManageWindow"); }

	//在编辑界面上绘制
	void editDraw(int absX, int absY, DrawControlManager* drawManager) override;

protected:
	// 更新该控件判断消息的范围，将childRect的消息处理范围添加到该控件中
	void incrMsgRegion(const wxRegion& childRange) override {}
	// 设置控件消息范围为所有子控件范围，用来子控件发生变化，例如改变
	void resetMsgRegion() override {}

	// 该控件是否处理控件消息
	bool isHandleMsg() const override { return true; }
};

// 获取消息处理的范围，相对范围，相对于自己
inline wxRegion EditorManageWindow::getMsgRegion() const
{
	return wxRegion(narrow_cast<wxCoord>(getRelX()), narrow_cast<wxCoord>(getRelY()),
		narrow_cast<wxCoord>(getWidth()), narrow_cast<wxCoord>(getHeight()));
}

#endif	// EDITOR_MANAGE_WINDOW_H
