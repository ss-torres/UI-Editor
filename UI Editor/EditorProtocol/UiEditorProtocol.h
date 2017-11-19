#ifndef UI_EDITOR_PROTOCOL_H
#define UI_EDITOR_PROTOCOL_H


/*
 * 文件名：UiEditorProtocol
 * 作用：一些重要的设定，现在的设定内容包括
 * 1.设定是使用多字节还是UNICODE
 */

#include <wx/string.h>

#define WCHAR_LABEL_TYPE	1

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

#endif	// UI_EDITOR_PROTOCOL_H