#ifndef WINDOW_INTERFACE_H
#define WINDOW_INTERFACE_H

/*
 * 文件名：WindowInterface
 * 作用：用来定义编辑窗口使用的接口
 */

#include "EditorFunc.h"
#include "SimpleWindow.h"


using AbstractEditorWindow = inner::SimpleWindow<inner::EditorFunc>;


#endif	// WINDOW_INTERFACE_H
