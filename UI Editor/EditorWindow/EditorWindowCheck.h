#ifndef EDITOR_WINDOW_CHECK_H
#define EDITOR_WINDOW_CHECK_H

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
	UiNoCheck() = default;
	~UiNoCheck() = default;

	constexpr bool operator()(const UiCheckType* window) const { return true; }
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

	bool operator()(const UiCheckType* window) const { return window->getId() == m_id && DecoType::DecoType()(window); }

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

	bool operator()(const UiCheckType* window) const { return window->isUiShow() && DecoType::DecoType()(window); }
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

	bool operator()(const UiCheckType* window) const { return window->isContainerWnd() && DecoType::DecoType()(window); }
};


// 定义一些常用类型
using Check_Default = UiNoCheck<>;
using Check_UiEditable = UiShow<UiNoCheck<>>;
using Check_UiContainer = UiContainer<UiNoCheck<>>;
using Check_UiIdEqual = UiIdEqualCheck<UiNoCheck<>, ID_TYPE>;

#endif	// EDITOR_WINDOW_CHECK_H
