#include "WindowFactory.h"
#include "../Form/EditorToolWidgetSelectDefine.h"
#include "WindowFactoryDefine.h"
#include "EditorFunc.h"
#include "EditorLabel.h"
#include "EditorButton.h"

AbstractWindowFactory* WindowFactory::s_factoryInst = nullptr;

// 根据拷贝的窗口数据，构造窗口
AbstractEditorWindow * WindowFactory::createCopyObjectWnd(CopyWindowValue winObject,
	AbstractEditorWindow* parent, int relX, int relY, int width, int height)
{
	AbstractEditorWindow* editorWnd = WindowFactoryImpl::createEditorWnd(winObject.getWinName(),
		parent, relX, relY, width, height);

	editorWnd->resetWinAttrs();
	auto& winAttrs = winObject.getWinAttrValues();
	for (const auto& value : winAttrs)
	{
		editorWnd->updateWinAttr(value.first, value.second);
	}

	return editorWnd;
}

// 根据窗口名获取对应的窗口对象
AbstractEditorWindow * WindowFactoryImpl::createEditorWnd(const wxString & winName,
	AbstractEditorWindow* parent, int relX, int relY, int width, int height)
{
	if (winName == EDITOR_LABEL_TYPE)
	{
		if (width < 0 || height < 0)
		{
			width = EDITOR_LABEL_WIDTH;
			height = EDITOR_LABEL_HEIGHT;
		}
		return new inner::EditorLabel(parent, relX, relY, width, height);
	}
	else if (winName == EDITOR_BUTTON_TYPE)
	{
		if (width < 0 || height < 0)
		{
			width = EDITOR_BUTTON_WIDTH;
			height = EDITOR_BUTTON_HEIGHT;
		}
		return new inner::EditorButton(parent, relX, relY, width, height);
	}

	if (width < 0 || height < 0)
	{
		width = EDITOR_WINDOW_WIDTH;
		height = EDITOR_WINDOW_HEIGHT;
	}

	return nullptr;
}
