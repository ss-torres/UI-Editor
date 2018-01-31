#ifndef EDITOR_WINDOW_CHECK_H
#define EDITOR_WINDOW_CHECK_H

#include "EditorWindowInterface.h"

/*
 * 文件名：EditorWindowCheck
 * 作用：用来在查找时提供各种比较条件
 */

// 总是成功的判断
template <typename CheckType = EditorAbstractWindow>
class UiNoCheck
{
public:
	using UiCheckType = CheckType;
public:
	constexpr UiNoCheck() = default;
	~UiNoCheck() = default;

	constexpr bool operator()(const UiCheckType* window) const { return true; }
};

// 坐标满足条件
template <typename DecoType>
class UiMsgInRegion : public DecoType
{
public:
	using UiCheckType = typename DecoType::UiCheckType;
public:
	constexpr UiMsgInRegion(int x, int y)
		: m_x(x), m_y(y) { }
	~UiMsgInRegion() = default;

	bool operator()(const UiCheckType* window) const			// inline implicit
	{ 
		return window->getMsgRegion().Contains(m_x, m_y) && DecoType::DecoType()(window);
	}

private:
	int m_x;	// x 坐标
	int m_y;	// y 坐标
};

// 用来判断ID相同
template <typename DecoType, typename IDType>
class UiIdEqualCheck : public DecoType
{
public:
	using UiCheckType = typename DecoType::UiCheckType;
public:
	UiIdEqualCheck(IDType id)
		: m_id(id)
	{

	}
	~UiIdEqualCheck() = default;

	bool operator()(const UiCheckType* window) const			// inline implicit
	{
		return window->getId() == m_id && DecoType::DecoType()(window); 
	}

private:
	IDType m_id;
};

// 判断在编辑器中是否可以编辑
template <typename DecoType>
class UiShow : public DecoType
{
public:
	using UiCheckType = typename DecoType::UiCheckType;
public:
	UiShow() = default;
	~UiShow() = default;

	bool operator()(const UiCheckType* window) const		// inline implicit 
	{
		return window->isUiShow() && DecoType::DecoType()(window); 
	}
};

// 判断是否可以有子对象
template <typename DecoType>
class UiContainer : public DecoType
{
public:
	using UiCheckType = typename DecoType::UiCheckType;
public:
	UiContainer() = default;
	~UiContainer() = default;

	bool operator()(const UiCheckType* window) const		// inline implicit
	{
		return window->isContainerWnd() && DecoType::DecoType()(window); 
	}
};


// 定义一些常用类型
using Check_Default = UiNoCheck<>;
using Check_UiInMsgRegion = UiMsgInRegion<UiNoCheck<>>;
using Check_UiEditable = UiShow<UiNoCheck<>>;
using Check_UiContainer = UiContainer<UiNoCheck<>>;
using Check_UiIdEqual = UiIdEqualCheck<UiNoCheck<>, ID_TYPE>;

#endif	// EDITOR_WINDOW_CHECK_H
