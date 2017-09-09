#ifndef EDITOR_TOOL_OBJECT_VIEW_H
#define EDITOR_TOOL_OBJECT_VIEW_H

/*
 * 文件名：EditorToolObjectView
 * 作用：用来查看当前创建的窗口父子级关系
 */

#include "EditorToolWindow.h"
#include <wx/treelist.h>

class EditorToolObjectView : public EditorToolWindow
{
public:
	EditorToolObjectView(wxAuiManager &manager, wxWindow * parent, int direction = wxLEFT, const wxString & paneName = wxEmptyString);
	~EditorToolObjectView() override;

private:
	// 初始化子窗口
	void initSubWindows();

private:
	wxTreeListCtrl* m_objectView;
};

#endif	// EDITOR_TOOL_OBJECT_VIEW_H
