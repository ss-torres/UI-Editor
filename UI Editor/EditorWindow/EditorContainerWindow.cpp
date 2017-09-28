#include "EditorContainerWindow.h"

namespace inner
{
	// 用来查看对应ID的窗口
	SimpleWindow<EditorFunc>* ContainerWindow<EditorContainerFunc>::findMatchWnd(ID_TYPE findId)
	{
		// 查看该窗口ID是否满足
		if (getId() == findId)
		{
			return this;
		}
		// 查看子窗口是否满足条件
		for (const auto& value : getConstChildren())
		{
			const auto wnd = value->findMatchWnd(findId);
			if (wnd != nullptr)
			{
				return wnd;
			}
		}

		return nullptr;
	}
}