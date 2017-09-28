#ifndef WINDOW_INTERFACE_H
#define WINDOW_INTERFACE_H

/*
 * 文件名：WindowInterface
 * 作用：用来定义编辑窗口使用的接口
 */

#include "EditorFunc.h"
#include "AbstractEditorWindow.h"
#include "EditorContainerWindow.h"

using AbstractEditorWindow = inner::SimpleWindow<inner::EditorFunc>;
using ContainterEditorWindow = inner::ContainerWindow<inner::EditorContainerFunc>;

#endif	// WINDOW_INTERFACE_H
