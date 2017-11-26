#ifndef WIN_TYPE_NAME_PROTOCOL_H
#define WIN_TYPE_NAME_PROTOCOL_H

#include <wx/treebase.h>
#include <wx/string.h>

/*
 * 文件名：EditorToolWidgetSelectDefine
 * 作用：
 * （1）其他的一些宏定义，常量定义，简单函数定义等
 */

// 如下定义目前只是为了便于构建，之后可以考虑这部分构建也依赖于WindowAttribute.xml中的数据
// 控件类型显示和控件类型

const wxString EDITOR_WINDOW_TYPE = wxS("GWindow");		// 不可创建
const wxString EDITOR_WINDOW_SHOW = wxS("Window");

// 对应于EditorLabel
const wxString EDITOR_LABEL_TYPE = wxS("GLabel");		// 可以创建
const wxString EDITOR_LABEL_SHOW = wxS("Label");

// 对应于EditorButton
const wxString EDITOR_BUTTON_TYPE = wxS("GButton");		// 可以创建
const wxString EDITOR_BUTTON_SHOW = wxS("Button");

const wxString EDITOR_CONTAINER_TYPE = wxS("GContainerWindow");	// 不可创建
const wxString EDITOR_CONTAINER_SHOW = wxS("ContainerWindow");

// 对应于EditorFrame
const wxString EDITOR_FRAME_TYPE = wxS("GFrame");		// 可以创建
const wxString EDITOR_FRAME_SHOW = wxS("Frame");

#endif	// WIN_TYPE_NAME_PROTOCOL_H
