#include "EditorWindowFactory.h"
#include "EditorLabel.h"
#include "EditorButton.h"
#include "EditorManageWindow.h"

EditorAbstractWindowFactory* EditorWindowFactory::s_factoryInst = nullptr;

// 根据拷贝的控件数据，构造控件
EditorAbstractWindow * EditorWindowFactory::createCopyObjectWnd(CopyWindowInfo winObject,
	EditorAbstractWindow* parent, int relX, int relY, int width, int height)
{
	EditorAbstractWindow* editorWnd = WindowFactoryImpl::createEditorWnd(winObject.getWinName(),
		parent, relX, relY, width, height);
	// 先给默认的名称
	long winTypeNum = ++m_winTypeToNums[editorWnd->getWindowClassName()];
	wxString objectName = editorWnd->getWindowClassName() + (wxString() << winTypeNum);
	editorWnd->updateWinAttr(OBJECT_NAME, objectName);

	//editorWnd->resetWinAttrs();
	// 设置为拷贝对象的属性值
	auto& winAttrs = winObject.getWinAttrValues();
	for (const auto& value : winAttrs)
	{
		editorWnd->updateWinAttr(value.first, value.second);
	}

	return editorWnd;
}

// 创建一个管理控件
EditorAbstractWindow * EditorWindowFactory::createManageWnd(int width, int height)
{
	return new EditorManageWindow(0, 0, width, height);
}

// 根据控件名获取对应的控件对象
EditorAbstractWindow * WindowFactoryImpl::createEditorWnd(const wxString & winName,
	EditorAbstractWindow* parent, int relX, int relY, int width, int height)
{
	if (winName == EDITOR_LABEL_TYPE)
	{
		if (width < 0 || height < 0)
		{
			width = EDITOR_LABEL_WIDTH;
			height = EDITOR_LABEL_HEIGHT;
		}
		return new EditorLabel(parent, relX, relY, width, height);
	}
	else if (winName == EDITOR_BUTTON_TYPE)
	{
		if (width < 0 || height < 0)
		{
			width = EDITOR_BUTTON_WIDTH;
			height = EDITOR_BUTTON_HEIGHT;
		}
		return new EditorButton(parent, relX, relY, width, height);
	}

	if (width < 0 || height < 0)
	{
		width = EDITOR_WINDOW_WIDTH;
		height = EDITOR_WINDOW_HEIGHT;
	}

	return nullptr;
}
