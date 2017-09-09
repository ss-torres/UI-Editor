#ifndef EDITOR_TOOL_WIDGET_SELECT_H
#define EDITOR_TOOL_WIDGET_SELECT_H

/*
 * 文件名：EditorToolWidgetSelect
 * 作用：用来拖拉在绘制区创建需要绘制的窗口类型
 */

#include "EditorToolWindow.h"
#include <wx/treectrl.h>

class EditorToolWidgetSelect : public EditorToolWindow
{
public:
	EditorToolWidgetSelect(wxAuiManager &manager, wxWindow * parent, int direction = wxLEFT, const wxString & paneName= wxEmptyString);
	~EditorToolWidgetSelect() override;


private:
	// 用来处理拖拉窗口类型图标
	void OnDragWidgetIcon(wxTreeEvent& event);
private:
	// 用来初始化窗口
	void initSubWindows();

private:
	wxTreeCtrl* m_widget_tree;
};

#endif	// EDITOR_TOOL_WIDGET_SELECT_H
