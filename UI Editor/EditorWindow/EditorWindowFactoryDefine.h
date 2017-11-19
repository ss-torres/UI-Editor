#ifndef EDITOR_WINDOW_FACTORY_DEFINE_H
#define EDITOR_WINDOW_FACTORY_DEFINE_H

/*
 * 文件名：WindowFactoryDefine
 * 作用：定义与创建控件有关的数据
 */

#include <wx/string.h>

// 定义各种类型默认的宽和高

// EditorWindow
const int EDITOR_WINDOW_WIDTH = 30;
const int EDITOR_WINDOW_HEIGHT = 15;

// EditorLabel
const int EDITOR_LABEL_WIDTH = 30;
const int EDITOR_LABEL_HEIGHT = 15;

// EditorButton
const int EDITOR_BUTTON_WIDTH = 30;
const int EDITOR_BUTTON_HEIGHT = 15;

// 根据传入的信息，新建一个控件对象
class CopyWindowInfo
{
public:
	using WIN_ATTR_VALUE_LIST = std::map<wxString, wxAny>;
public:
	CopyWindowInfo(const wxString &winName = wxS(""))
		: m_winName(winName)
	{

	}
	~CopyWindowInfo() {}

	// 拷贝构造函数
	CopyWindowInfo(const CopyWindowInfo& right)
		: m_winName(right.m_winName), m_winAttrValues(right.m_winAttrValues)
	{

	}
	CopyWindowInfo(CopyWindowInfo&& right) noexcept(std::is_nothrow_move_constructible<wxString>::value
		&& std::is_nothrow_constructible<std::map<wxString, wxAny>>::value)
		: m_winName(std::move(right.m_winName)), m_winAttrValues(std::move(right.m_winAttrValues))
	{

	}
	// 赋值运算符
	CopyWindowInfo& operator=(const CopyWindowInfo& right)
	{
		m_winName = right.m_winName;
		m_winAttrValues = right.m_winAttrValues;
		return *this;
	}
	CopyWindowInfo& operator=(CopyWindowInfo&& right) noexcept(std::is_nothrow_move_assignable<wxString>::value
		&& std::is_nothrow_move_assignable<std::map<wxString, wxAny>>::value)
	{
		m_winName = std::move(right.m_winName);
		m_winAttrValues = std::move(right.m_winAttrValues);
		return *this;
	}
	// 设置控件名
	void setWinName(const wxString& winName) { m_winName = winName; }
	// 获取控件名
	const wxString& getWinName() const { return m_winName; }
	// 添加一条控件属性
	void add(const wxString winAttr, const wxAny& attrValue) { m_winAttrValues.insert(std::make_pair(winAttr, attrValue)); }
	// 获取控件属性
	const WIN_ATTR_VALUE_LIST& getWinAttrValues() const { return m_winAttrValues; }
	// 移动控件属性
	WIN_ATTR_VALUE_LIST&& moveWinAttrValues() { return std::move(m_winAttrValues); }
private:
	// 控件名
	wxString m_winName;
	// 控件属性值对
	std::map<wxString, wxAny> m_winAttrValues;
};

#endif	// WINDOW_FACTORY_DEFINE_H
