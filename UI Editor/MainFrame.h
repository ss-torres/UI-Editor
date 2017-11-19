#ifndef MAIN_FRAME_H
#define MAIN_FRAME_H

/*
 * 文件名：MainFrame
 * 作用：UI Editor的最外层窗口，管理整个UI Editor的窗口
 */

#include <memory>
#include <wx/wxprec.h>
#include <wx/aui/aui.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "Form/FormFactory.h"

class FormToolWindow;
class FormWidgetSelect;
class FormObjectView;
class FormPropertyEditor;
class FormWorkArea;
class WindowAttributeManager;

class MainFrame : public wxMDIParentFrame
{
public:
	MainFrame(const wxString& title);
	~MainFrame();

	// 每帧处理函数
	void updateFrame(float dt);
	// 重写销毁函数
	bool Destroy() override;
	// 获取功能窗口
	std::shared_ptr<FormObjectView> getObjectView() const { return m_tool_object_view; }
	std::shared_ptr<FormPropertyEditor> getPropertyEditor() const { return m_tool_property_editor; }
	std::shared_ptr<FormWorkArea> getWorkArea() const { return m_editWorkArea; }

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

	// 创建主工作区和功能区
	FormFactory m_manager;
	// 工具窗口
	// 控件类型选择
	std::shared_ptr<FormWidgetSelect> m_tool_widget_select;
	// 展示控件对象父子级关系
	std::shared_ptr<FormObjectView> m_tool_object_view;
	// 控件属性修改
	std::shared_ptr<FormPropertyEditor> m_tool_property_editor;

	// 主工作区
	std::shared_ptr<FormWorkArea> m_editWorkArea;

DECLARE_EVENT_TABLE()
};

// 增加一个窗口销毁的消息
wxDECLARE_EVENT(DESTROY_EVENT, wxNotifyEvent);

#endif	// MAIN_FRAME_H
