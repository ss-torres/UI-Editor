#ifndef EDITOR_TOOL_WIDGET_SELECT_DEFINE_H
#define EDITOR_TOOL_WIDGET_SELECT_DEFINE_H

#include <wx/treebase.h>
#include <wx/string.h>

/*
 * 文件名：EditorToolWidgetSelectDefine
 * 作用：（1）主要是为了EditorToolWidgetSelect定义各种窗口ID
 * （2）其他的一些宏定义，常量定义，简单函数定义等
 */

// 如下定义目前只是为了便于构建，之后可以考虑这部分构建也依赖于WindowAttribute.xml中的数据
// 窗口类型显示和窗口类型
const wxString EDITOR_STATIC_TYPE = wxT("GStatic");
const wxString EDITOR_STATIC_SHOW = wxT("Static");

const wxString EDITOR_BUTTON_TYPE = wxT("GButton");
const wxString EDITOR_BUTTON_SHOW = wxT("Button");

// 存储在窗口选择节点中的数据
class WidgetSelectItemName : public wxTreeItemData
{
public:
	WidgetSelectItemName(const wxString& widgetName)
		: m_widgetName(widgetName)
	{

	}

	~WidgetSelectItemName() override {}

	// 用来获取窗口对应的名字
	wxString getWidgetName() const { return m_widgetName;  }

private:
	wxString m_widgetName;
};

#endif	// EDITOR_TOOL_WIDGET_SELECT_DEFINE_H
