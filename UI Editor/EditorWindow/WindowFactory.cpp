#include "WindowFactory.h"
#include "../Form/EditorToolWidgetSelectDefine.h"
#include "EditorLabel.h"
#include "EditorButton.h"

// 根据拷贝的窗口数据，构造窗口
AbstractEditorWindow * WindowFactory::createCopyObjectWnd(const CopyWindowValue& winObject,
	AbstractEditorWindow* parent, int relX, int relY, int width, int height)
{
	AbstractEditorWindow* editorWnd = createEditorWnd(winObject.getWinName(),
		parent, relX, relY, width, height);

	return editorWnd;
}

// 根据窗口名获取对应的窗口对象
AbstractEditorWindow * WindowFactory::createEditorWnd(const wxString & winName, 
	AbstractEditorWindow* parent, int relX, int relY, int width, int height) const
{
	if (winName == EDITOR_LABEL_TYPE)
	{
		return new inner::EditorLabel(parent, relX, relY, width, height);
	}
	else if (winName == EDITOR_BUTTON_TYPE)
	{
		return new inner::EditorButton(parent, relX, relY, width, height);
	}

	return nullptr;
}
