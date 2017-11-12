#ifndef EDITOR_TOOL_PROPERTY_EDITOR_H
#define EDITOR_TOOL_PROPERTY_EDITOR_H

/*
 * 文件名：EditorToolPropertyEditor
 * 作用：用来编辑窗口的属性
 */

#include "EditorToolWindow.h"
#include <map>
#include <vector>

class wxPropertyGrid;
class wxPGProperty;
class wxBoxSizer;
class wxPropertyGridEvent;

class EditorToolPropertyEditor : public EditorToolWindow
{
public:
	EditorToolPropertyEditor(wxAuiManager &manager, wxWindow * parent, int direction = wxLEFT, const wxString & paneName = wxEmptyString);
	~EditorToolPropertyEditor() override;

	// 初始化编辑属性窗口
	void initSubWindows(const std::vector<wxString>& windowTypes);
	// 修改对应窗口的属性列表
	void insertWindowTypeAttrs(const wxString& winType, const std::vector<wxPGProperty*>& attrs);

	// 显示对应类型的编辑框
	void resetAttrs(const wxString& winTypeName);
	// 设置属性列表的值
	void updateAttrs(const std::map<wxString, wxAny>& propAttrs);
private:
	// 用来处理属性改变
	void OnPropertyGridChanged(wxPropertyGridEvent& event);
private:
	// 用来设置窗口属性的编辑器列表
	std::map<wxString, wxPropertyGrid*> m_propertyGrids;
	// 布局管理器
	wxBoxSizer* m_sizer;
	// 当前编辑的属性类型
	wxString m_curEditWinType;
	// 当前用来编辑窗口属性的编辑器
	wxPropertyGrid* m_curPropertyGrid = nullptr;
};

#endif	// EDITOR_TOOL_PROPERTY_EDITOR_H
