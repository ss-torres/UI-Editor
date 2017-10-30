#ifndef EDITOR_WINDOW_CHECK_H
#define EDITOR_WINDOW_CHECK_H

/*
 * 文件名：EditorWindowCheck
 * 作用：用来在查找时提供各种比较条件
 */

#include "EditorWindowInterface.h"

// 总是成功的判断
template <typename CheckType = EditorAbstractWindow>
class UiNoCheck
{
public:
	UiNoCheck() = default;
	~UiNoCheck() = default;

	bool operator()(CheckType* window) { return true; }
};

// 判断在编辑器中是否可以编辑
template <typename DecoType, typename CheckType = EditorAbstractWindow>
class UiEditable : public DecoType
{
public:
	UiEditable() = default;
	~UiEditable() {}

	bool operator()(CheckType* window) { return window->isUiEditable() && DecoType::DecoType()(window); }
};

// 判断是否可以有子对象
template <typename DecoType, typename CheckType = EditorAbstractWindow>
class UiContainer : public DecoType
{
public:
	UiContainer() = default;
	~UiContainer() = default;

	bool operator()(CheckType* window) { return window->isContainerWnd() && DecoType::DecoType()(window); }
};

// 定义一些常用类型
using Check_UiEditable = UiEditable<UiNoCheck<>>;
using Check_UiContainer = UiContainer<UiNoCheck<>>;

#endif	// EDITOR_WINDOW_CHECK_H
