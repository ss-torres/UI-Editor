#ifndef WORK_AREA_HELP_H
#define WORK_AREA_HELP_H

/*
 * 文件名：EditorWorkAreaHelp
 * 作用：为FormWorkArea提供一些功能函数
 */

#include <type_traits>
#include "../EditorWindow/EditorWindowInterface.h"
#include "../EditorWindow/EditorWindowCheck.h"

namespace WorkAreaHelp
{
	// 判断时，需要父控件满足条件，才会判断子控件是否满足条件，如果父控件不满足，则子控件不判断
	// 该函数实现考虑了消息处理范围，如果查找点不在控件消息处理范围，则不处理
	// 传入的坐标为父控件参考坐标
	template <typename T = Check_UiEditable/*, bool = std::is_class<T>::value*/>
	const EditorAbstractWindow* getMatchWindow(const EditorAbstractWindow* searchWnd, wxCoord x, wxCoord y, T&& t = T());

	template <typename T = Check_UiEditable>
	EditorAbstractWindow* getMatchWindow(EditorAbstractWindow* searchWnd, wxCoord x, wxCoord y, T&& t = T())
	{
		const EditorAbstractWindow* ret = getMatchWindow(const_cast<const EditorAbstractWindow*>(searchWnd), x, y, t);
		return const_cast<EditorAbstractWindow*>(ret);
	}
}

template <typename T>
const EditorAbstractWindow* WorkAreaHelp::getMatchWindow(const EditorAbstractWindow* searchWnd, wxCoord x, wxCoord y, T&& t)
{
	x -= narrow_cast<wxCoord>(searchWnd->getRelX());
	y -= narrow_cast<wxCoord>(searchWnd->getRelY());
	// 如果该控件不可以编辑，则子控件都不可以编辑
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
	// 如果查找的窗口是Container控件，则先查看子控件
	if (searchWnd->isContainerWnd())
	{
		auto beg = searchWnd->getChildrenConstBeg();
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

#endif	// WORK_AREA_HELP_H
