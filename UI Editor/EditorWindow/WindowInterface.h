#ifndef WINDOW_INTERFACE_H
#define WINDOW_INTERFACE_H

/*
 * 文件名：WindowInterface
 * 作用：用来定义编辑窗口使用的接口
 */

namespace inner
{
	class EditorFunc;
	template <typename T>
	class SimpleWindow;
}

using AbstractEditorWindow = inner::SimpleWindow<inner::EditorFunc>;


#endif	// WINDOW_INTERFACE_H
