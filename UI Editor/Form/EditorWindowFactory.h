#ifndef EDITOR_WINDOW_FACTORY_H
#define EDITOR_WINDOW_FACTORY_H

#include "WorkAreaDefine.h"
#include "EditorToolWindow.h"

class EditorWorkArea;
class wxMDIParentFrame;

class EditorWindowFactory
{
public:
	EditorWindowFactory();
	~EditorWindowFactory();

	// 创建对应的ToolWindow
	EditorToolWindow* createToolWindow(ToolWindowType type, wxAuiManager &manager, wxWindow * parent, 
		int direction = wxLEFT, const wxString & paneName = wxEmptyString) const;
	// 销毁对应的ToolWindow
	void destroyToolWindow(EditorToolWindow* &toolWnd) const;

	// 创建主工作区
	EditorWorkArea* createWorkArea(wxMDIParentFrame* parent, 
		const wxString& captionName, const wxPoint& position, const wxSize &size) const;
	// 销毁主工作区
	void destroyWorkArea(EditorWorkArea* &workArea) const;

private:
	
};

#endif	// EDITOR_WINDOW_FACTORY_H