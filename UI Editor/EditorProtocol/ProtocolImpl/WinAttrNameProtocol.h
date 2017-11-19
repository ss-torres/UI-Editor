#ifndef WIN_ATTR_NAME_PROTOCOL_H
#define WIN_ATTR_NAME_PROTOCOL_H

/*
 * 文件名：WinAttrNameProtocol.h
 * 作用：用来定义编辑器中的各种控件类型使用的属性名，可以用该属性名修改控件的对应属性，
 * 这些属性与消息处理，控件显示，渲染等有关
 */

#include <wx/string.h>

// GWindow
const wxString EDITOR_SHOW = wxS("editShow");
const wxString OBJECT_NAME = wxS("objectName");
// 控件相对于父控件位置
const wxString WIN_POSX = wxS("posX");
const wxString WIN_POSY = wxS("posY");
const wxString WIN_SIZEX = wxS("sizeX");
const wxString WIN_SIZEY = wxS("sizeY");

// GLabel
const wxString LABEL_TEXT = wxS("text");

// GButton
const wxString BUTTON_TEXT = wxS("text");

#endif	// WIN_ATTR_NAME_PROTOCOL_H
