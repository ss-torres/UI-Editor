#ifndef EDITOR_TOOL_PROPERTY_EDITOR_H
#define EDITOR_TOOL_PROPERTY_EDITOR_H

/*
 * 文件名：EditorToolPropertyEditor
 * 作用：用来编辑窗口的属性
 */

#include "EditorToolWindow.h"

class wxPropertyGrid;

class EditorToolPropertyEditor : public EditorToolWindow
{
public:
	EditorToolPropertyEditor(wxAuiManager &manager, wxWindow * parent, int direction = wxLEFT, const wxString & paneName = wxEmptyString);
	~EditorToolPropertyEditor() override;

private:
	// 初始化编辑属性窗口
	void initSubWindows();

private:
	// 用来显示属性的窗口
	wxPropertyGrid* m_propertyGrid;
};

#endif	// EDITOR_TOOL_PROPERTY_EDITOR_H
