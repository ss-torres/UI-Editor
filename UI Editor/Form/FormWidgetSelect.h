#ifndef FORM_WIDGET_SELECT_H
#define FORM_WIDGET_SELECT_H

/*
 * 文件名：FormWidgetSelect
 * 作用：用来拖拉在绘制区创建需要绘制的控件类型
 */

#include <vector>
#include <wx/treectrl.h>
#include "FormToolWindow.h"

class FormWidgetSelect : public FormToolWindow
{
public:
	FormWidgetSelect(wxAuiManager &manager, wxWindow * parent, int direction = wxLEFT, const wxString & paneName= wxEmptyString);
	~FormWidgetSelect() override;

	// 用来获取所有能创建的控件类型名
	std::vector<wxString> getAllWinNames() const;

private:
	// 用来处理拖拉控件类型图标
	void OnDragWidgetIcon(wxTreeEvent& event);
private:
	// 用来初始化窗口
	void initSubWindows();

private:
	wxTreeCtrl* m_widget_tree;
};

#endif	// FORM_WIDGET_SELECT_H
