#ifndef FORM_FACTORY_H
#define FORM_FACTORY_H

#include "WorkAreaDefine.h"
#include "FormToolWindow.h"

class FormWorkArea;
class wxMDIParentFrame;

class FormFactory
{
public:
	FormFactory();
	~FormFactory();

	// 创建对应的ToolWindow
	FormToolWindow* createToolWindow(ToolWindowType type, wxAuiManager &manager, wxWindow * parent, 
		int direction = wxLEFT, const wxString & paneName = wxEmptyString) const;
	// 销毁对应的ToolWindow
	void destroyToolWindow(FormToolWindow* &toolWnd) const;

	// 创建主工作区
	FormWorkArea* createWorkArea(wxMDIParentFrame* parent, 
		const wxString& captionName, const wxPoint& position, const wxSize &size) const;
	// 销毁主工作区
	void destroyWorkArea(FormWorkArea* &workArea) const;

private:
	
};

#endif	// FORM_FACTORY_H