#include "EditorContainerWindow.h"
#include "EditorWindowCheck.h"

#include "../EditMessage/CommandFactory.h"
#include "../EditMessage/ChangeManager.h"

namespace inner
{
	// 用来查看对应ID的控件
	SimpleWindow<EditorFunc>* ContainerWindow<EditorContainerFunc>::findMatchWnd(ID_TYPE findId)
	{
		// 查看该控件ID是否满足
		if (getId() == findId)
		{
			return this;
		}
		// 查看子控件是否满足条件
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

	// 设置该控件是否编辑时显示，该实现可以优化，减少resetMsgRegion调用
	void ContainerWindow<EditorContainerFunc>::setEditShow(bool editShow)
	{
		//for (auto chp : getConstChildren())
		//{
		//	chp->setEditShow(editShow);
		//}

		ContainerWindow<EditorEditableFunc>::setEditShow(editShow);
	}

	// 处理鼠标按下
	bool ContainerWindow<EditorContainerFunc>::handleLMouseDown(int x, int y)
	{
		if (!Check_UiInMsgRegion(x, y)(this))
		{
			return false;
		}

		auto beg = getChildrenBeg();
		auto end = getChildrenEnd();
		for (; beg != end; ++beg)
		{
			auto childWnd = *beg;
			auto isHandle = childWnd->handleLMouseDown(x - childWnd->getRelX(), y - childWnd->getRelY());
			if (isHandle)
			{
				return isHandle;
			}
		}

		SIMPLE_WINDOW_TYPE::handleLMouseDown(x, y);

		return true;
	}
}