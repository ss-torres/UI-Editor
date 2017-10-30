#ifndef EDITOR_FRAME_H
#define EDITOR_FRAME_H

/*
 * 文件名：EditorFrame
 * 作用：UI Editor的最外层窗口，管理整个UI Editor的窗口
 */

#include <wx/wxprec.h>
#include <wx/aui/aui.h>
#include <memory>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "Form/EditorFormFactory.h"

class EditorToolWindow;
class EditorToolWidgetSelect;
class EditorToolObjectView;
class EditorToolPropertyEditor;
class EditorWorkArea;
class WindowAttributeManager;

class EditorFrame : public wxMDIParentFrame
{
public:
	EditorFrame(const wxString& title);
	~EditorFrame();

	// 每帧处理函数
	void updateFrame(float dt);
	// 重写销毁函数
	bool Destroy() override;
	// 获取功能窗口
	std::shared_ptr<EditorToolObjectView> getObjectView() const { return m_tool_object_view; }
	std::shared_ptr<EditorToolPropertyEditor> getPropertyEditor() const { return m_tool_property_editor; }
	std::shared_ptr<EditorWorkArea> getWorkArea() const { return m_editWorkArea; }

private:
	// 加载窗口属性
	void loadWindowAttributes();
	// 初始化子窗口
	void initSubWindows();
	// 创建菜单栏
	void addMenu();

private:
	// 用来处理窗口大小改变
	void OnSize(wxSizeEvent& event);

private:
	wxAuiManager* m_auiManager;
	// 管理窗口属性
	std::shared_ptr<WindowAttributeManager> m_winAttrManager;

	// 创建主工作区和工具窗口
	EditorFormFactory m_manager;
	// 工具窗口
	// 窗口类型选择
	std::shared_ptr<EditorToolWidgetSelect> m_tool_widget_select;
	// 创建窗口对象父子级关系
	std::shared_ptr<EditorToolObjectView> m_tool_object_view;
	// 窗口属性修改
	std::shared_ptr<EditorToolPropertyEditor> m_tool_property_editor;

	// 工作区窗口
	std::shared_ptr<EditorWorkArea> m_editWorkArea;

DECLARE_EVENT_TABLE()
};

// 增加一个窗口销毁的消息
wxDECLARE_EVENT(DESTROY_EVENT, wxNotifyEvent);

#endif	// EDITOR_FRAME_H
