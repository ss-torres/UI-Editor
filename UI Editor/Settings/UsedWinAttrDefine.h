#ifndef USED_WIN_ATTR_DEFINE_H
#define USED_WIN_ATTR_DEFINE_H

/*
 * 文件名：UsedWinAttrDefine.h
 * 作用：用来定义编辑器中的各种窗口类型使用的属性名，可以用该属性名修改窗口的对应属性，
 * 这些属性与消息处理，窗口显示，渲染等有关
 * 说明：窗口类型参考"EditorToolWidgetSelectDefine.h"
 */

#include <wx/string.h>

// GWindow
// 窗口相对于父窗口位置
const wxString EDITOR_SHOW = wxS("editShow");
const wxString WIN_POSX = wxS("posX");
const wxString WIN_POSY = wxS("posY");
const wxString WIN_SIZEX = wxS("sizeX");
const wxString WIN_SIZEY = wxS("sizeY");

#endif	// USED_WIN_ATTR_DEFINE_H
