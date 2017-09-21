#ifndef COPY_WIN_OBJECT_H
#define COPY_WIN_OBJECT_H

/*
 * 文件名：CopyWinObject
 * 作用：Drag & Drop中用来传递窗口属性值的数据
 * 注意事项：当前只考虑一个应用直接的拷贝，如果需要可以修改来实现不同项目之间的考虑
 */

#include <vector>
#include <type_traits>
#include <wx/string.h>
#include <wx/dataobj.h>

const wxString COPY_DATA_FORMAT = wxS("CopyWinValue");

class CopyWindowValue
{
public:
	using WIN_ATTR_VALUE_LIST = std::vector<std::pair<wxString, wxAny>>;
public:
	CopyWindowValue(const wxString &winName = wxS(""))
		: m_winName(winName)
	{

	}
	~CopyWindowValue() {}
	
	// 拷贝构造函数
	CopyWindowValue(const CopyWindowValue& right)
		: m_winName(right.m_winName), m_winAttrValues(right.m_winAttrValues)
	{

	}
	CopyWindowValue(CopyWindowValue&& right) noexcept(std::is_nothrow_move_constructible<wxString>::value
		&& std::is_nothrow_constructible<std::vector<std::pair<wxString, wxAny>>>::value)
		: m_winName(std::move(right.m_winName)), m_winAttrValues(std::move(right.m_winAttrValues))
	{

	}
	// 赋值运算符
	CopyWindowValue& operator=(const CopyWindowValue& right)
	{
		m_winName = right.m_winName;
		m_winAttrValues = right.m_winAttrValues;
		return *this;
	}
	CopyWindowValue& operator=(CopyWindowValue&& right) noexcept(std::is_nothrow_move_assignable<wxString>::value
		&& std::is_nothrow_move_assignable<std::vector<std::pair<wxString, wxAny>>>::value)
	{
		m_winName = std::move(right.m_winName);
		m_winAttrValues = std::move(right.m_winAttrValues);
		return *this;
	}
	// 设置窗口名
	void setWinName(const wxString& winName) { m_winName = winName;  }
	// 获取窗口名
	const wxString& getWinName() const { return m_winName; }
	// 添加一条窗口属性
	void add(const wxString winAttr, const wxAny& attrValue) { m_winAttrValues.push_back(std::make_pair(winAttr, attrValue)); }
	// 获取窗口属性
	const WIN_ATTR_VALUE_LIST& getWinAttrValues() const { return m_winAttrValues; }
private:
	// 窗口名
	wxString m_winName;
	// 窗口属性值对
	std::vector<std::pair<wxString, wxAny>> m_winAttrValues;
};

// 获取一个自定义的DataFormat
inline wxDataFormat getCopyDataFormat()
{
	wxDataFormat format;
	format.SetId(COPY_DATA_FORMAT);
	return format;
}

class CopyWinObject : public wxDataObjectSimple
{
public:
	CopyWinObject(const wxDataFormat& format = wxFormatInvalid)
		: wxDataObjectSimple(format)
	{

	}

	// 该函数默认传入的结构体为CopyWindowValue
	bool GetDataHere(void *buf) const override;
	
	size_t GetDataSize() const override;
	// 设置的结构体默认为CopyWindowValue
	bool SetData(size_t len, const void* buf) override;

	// 用来获取存储的窗口属性信息
	const CopyWindowValue& getWinValue() const { return m_data; }

private:
	CopyWindowValue m_data;
};

#endif	// COPY_WIN_OBJECT_H