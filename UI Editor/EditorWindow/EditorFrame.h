#ifndef EDITOR_FRAME_H
#define EDITOR_FRAME_H

/*
 * 文件名：EditorFrame
 * 作用：用来实现一个简单的控件容器，该控件容器用来管理控件，同时显示出控件容器范围
 */

#include "EditorContainerWindow.h"

class EditorFrame : public inner::ContainerWindow<inner::EditorContainerFunc>
{
public:
	using ContainerWindow<inner::EditorContainerFunc>::ContainerWindow;
	~EditorFrame() override {}

	// 用来获取控件类名字
	wxString getWindowClassName() const override { return EDITOR_FRAME_TYPE; }
	// 用来获取构建的控件类型，继承的控件返回自身
	EditorFrame* getConstructWindow() override { return this; }

	// 更新控件对象属性信息
	void updateWinAttr(const wxString& attrName, const wxAny& value) override;

	//在编辑界面上绘制
	void editDraw(int absX, int absY, DrawControlManager* drawManager) override;

protected:
	// 定义处理消息的类型，返回值表示是否修改了属性，true表示修改，false表示未修改
	using CHANGE_ATTR_FUNC = std::function<bool(EditorFrame*, const wxAny&)>;
	using ATTR_HANDLE_MAP = std::map<const wxString, CHANGE_ATTR_FUNC>;
	// 获取属性与属性处理函数Map
	static const ATTR_HANDLE_MAP& getEditorAttrHandles();
private:
	// 初始化属性处理函数Map
	static ATTR_HANDLE_MAP initEditorAttrHanldes();
};

#endif	// EDITOR_FRAME_H
