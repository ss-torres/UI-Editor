#ifndef EDITOR_WORK_AREA_HELP_H
#define EDITOR_WORK_AREA_HELP_H

/*
 * 文件名：EditorWorkAreaHelp
 * 作用：为EditorWorkArea提供一些功能函数
 */

#include "../EditorWindow/WindowInterface.h"
#include "../EditorWindow/EditorWindowCheck.h"

namespace WorkAreaHelp
{
	template <typename T = UiEditable<AbstractEditorWindow>>
	AbstractEditorWindow* getMatchWindow(AbstractEditorWindow* searchWnd, int x, int y);
}

template <typename T>
AbstractEditorWindow* WorkAreaHelp::getMatchWindow(AbstractEditorWindow* searchWnd, int x, int y)
{
	// 如果父窗口不可以编辑，则子窗口都不可以编辑
	if (!T(searchWnd))
	{
		return nullptr;
	}
	// 如果查找的窗口是Container窗口，则先查看子窗口
	if (searchWnd->IsContainerWnd())
	{

	}
}

#endif	// EDITOR_WORK_AREA_HELP_H
