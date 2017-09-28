#ifndef EDITOR_WINDOW_CHECK_H
#define EDITOR_WINDOW_CHECK_H

/*
 * 文件名：EditorWindowCheck
 * 作用：用来在查找时提供各种比较条件
 */

#include "WindowInterface.h"

// 总是成功的判断
template <typename T>
class UiNoCheck
{
public:
	UiNoCheck() = default;
	~UiNoCheck() = default;

	bool operator()(T* window) { return true; }
};

// 判断在编辑器中是否可以编辑
template <typename T>
class UiEditable
{
public:
	UiEditable() = default;
	~UiEditable() {}

	bool operator()(T* window) { return window->isUiEditable(); }
};

// 判断在编辑器中是否为：可编辑而且可以有子对象
template <typename T>
class UiEditableContainer
{
public:
	UiEditableContainer() = default;
	~UiEditableContainer() {}

	bool operator()(T* window) { return window->isUiEditable() && window->isContainerWnd(); }
};

#endif	// EDITOR_WINDOW_CHECK_H
