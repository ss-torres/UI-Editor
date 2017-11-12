#ifndef EDITOR_FUNC_DEFINE_H
#define EDITOR_FUNC_DEFINE_H

#include <wx/string.h>

#define WCHAR_LABEL_TYPE	1

// 用来指示窗口的类型
enum EditorWindowType
{
	EDITOR_DEFAULT_WINDOW = 0,		// 保留的窗口类型
	EDITOR_MANAGER_WINDOW,			// EditorManagerWindow
	EDITOR_CONTAINER_WINDOW,		// EditorContainerWindow
	EDITOR_LABEL,					// EditorLabel
	EDITOR_BUTTON,					// EditorButton
};

using ID_TYPE = int;

// 编辑窗口的起始ID
const ID_TYPE ID_BEG = 100;

#if WCHAR_LABEL_TYPE
using LABEL_TYPE = std::wstring;
using LABEL_CHAR = wchar_t;

inline LABEL_TYPE wxStrToStdStr(const wxString& str)
{
	return str.ToStdWstring();
}

// 需要调用的str在使用返回值的情况下一直存在
inline const LABEL_CHAR* wxStrToCStr(const wxString& str)
{
	return str.wc_str();
}
#else
// 定义文本编辑器类型
using LABEL_TYPE = std::string;
using LABEL_CHAR = char;

inline LABEL_TYPE wxStrToStdStr(const wxString& str)
{
	return str.ToStdString();
}

// 需要调用的str在使用返回值的情况下一直存在
inline const LABEL_CHAR* wxStrToCStr(const wxString& str)
{
	return str.c_str();
}
#endif

#endif	// EDITOR_FUNC_DEFINE_H