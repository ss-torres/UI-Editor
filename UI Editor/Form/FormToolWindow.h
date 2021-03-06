#ifndef FORM_TOOL_WINDOW_H
#define FORM_TOOL_WINDOW_H

#include <memory>
#include <wx/aui/aui.h>
#include "WorkArea.h"

class WindowAttributeManager;

class FormToolWindow : public WorkArea
{
public:
	FormToolWindow(wxAuiManager& manager, wxWindow* parent, int direction = wxLEFT, const wxString & paneName = wxEmptyString);
	virtual ~FormToolWindow();

	// 获取该工作区的主窗口对象
	wxWindow* getBench() override { return m_bench; }

	// 用来设置停靠方向
	void setDirection(int direction);
	// 用来设置标题
	void setCaption(const wxString& captionName);
	// 用来设置各种停靠属性
	void setPaneInfo(const wxAuiPaneInfo& paneInfo);
	// 获取各种停靠属性
	wxAuiPaneInfo& getPaneInfo();

private:
	wxAuiManager& m_auiManager;
	// 用来记录该区域管理的窗口类
	wxPanel* m_bench;
};

#endif		// FORM_TOOL_WINDOW_H