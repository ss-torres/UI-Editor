#ifndef EDITOR_FUNC_DEFINE_H
#define EDITOR_FUNC_DEFINE_H

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

#endif	// EDITOR_FUNC_DEFINE_H