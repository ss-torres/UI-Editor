#ifndef EDITOR_WINDOW_INTERFACE_H
#define EDITOR_WINDOW_INTERFACE_H

/*
 * 文件名：WindowInterface
 * 作用：用来定义编辑控件使用的接口
 */

#include "EditorAbstractWindow.h"
#include "EditorContainerWindow.h"

using EditorAbstractWindow = inner::SimpleWindow<inner::EditorFunc>;
using ContainterEditorWindow = inner::ContainerWindow<inner::EditorContainerFunc>;

#endif	// EDITOR_WINDOW_INTERFACE_H
