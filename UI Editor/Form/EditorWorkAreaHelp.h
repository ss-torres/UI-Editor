#ifndef EDITOR_WORK_AREA_HELP_H
#define EDITOR_WORK_AREA_HELP_H

/*
 * 文件名：EditorWorkAreaHelp
 * 作用：为EditorWorkArea提供一些功能函数
 */

#include <type_traits>
#include "../EditorWindow/EditorWindowInterface.h"
#include "../EditorWindow/EditorWindowCheck.h"

namespace WorkAreaHelp
{
	// 判断时，需要父窗口满足条件，才会判断子窗口是否满足条件，如果父窗口不满足，则子窗口不判断
	// 该函数实现考虑了消息处理范围，如果查找点不在窗口消息处理范围，则不处理
	// 传入的坐标为父窗口参考坐标
	template <typename T = Check_UiEditable/*, bool = std::is_class<T>::value*/>
	EditorAbstractWindow* getMatchWindow(EditorAbstractWindow* searchWnd, wxCoord x, wxCoord y, T&& t = T());
}

template <typename T>
EditorAbstractWindow* WorkAreaHelp::getMatchWindow(EditorAbstractWindow* searchWnd, wxCoord x, wxCoord y, T&& t)
{
	x -= narrow_cast<wxCoord>(searchWnd->getRelX());
	y -= narrow_cast<wxCoord>(searchWnd->getRelY());
	// 如果该窗口不可以编辑，则子窗口都不可以编辑
	if (!t(searchWnd))
	{
		return nullptr;
	}
	// 判断是否在消息范围内
	wxRegion msgRegion = searchWnd->getMsgRegion();
	if (!msgRegion.Contains(x, y))
	{
		return nullptr;
	}
	// 如果查找的窗口是Container窗口，则先查看子窗口
	if (searchWnd->isContainerWnd())
	{
		auto beg = searchWnd->getChildrencConstBeg();
		auto end = searchWnd->getChildrenConstEnd();
		for (; beg != end; ++beg)
		{
			auto ret = getMatchWindow(*beg, x, y, std::forward<T>(t));
			if (ret != nullptr)
			{
				return ret;
			}
		}
	}
	return searchWnd;
}

#endif	// EDITOR_WORK_AREA_HELP_H
