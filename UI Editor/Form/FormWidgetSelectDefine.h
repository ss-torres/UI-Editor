#ifndef FORM_WIDGET_SELECT_DEFINE_H
#define FORM_WIDGET_SELECT_DEFINE_H

#include <wx/treebase.h>
#include <wx/string.h>

/*
 * 文件名：EditorToolWidgetSelectDefine
 * 作用：
 * （1）节点类型定义
 */


// 存储在控件选择节点中的数据
class WidgetSelectItemName : public wxTreeItemData
{
public:
	WidgetSelectItemName(const wxString& widgetName)
		: m_widgetName(widgetName)
	{

	}

	~WidgetSelectItemName() override {}

	// 用来获取控件类型名
	wxString getWidgetName() const { return m_widgetName;  }

private:
	wxString m_widgetName;
};

#endif	// FORM_WIDGET_SELECT_DEFINE_H
