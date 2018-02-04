#ifndef SAVE_INFO_H
#define SAVE_INFO_H

#include <map>
#include <vector>
#include <wx/string.h>
#include <wx/any.h>

/*
 * 用来存入文件的每个窗口信息，当前信息包括：
 * （1）该窗口的属性信息
 * （2）该窗口的子窗口信息
 */

class SaveInfo
{
public:
	using WIN_ATTR_MAP = std::map<wxString, wxAny>;
	using CONST_CHILD_ITERATOR = std::vector<SaveInfo>::const_iterator;
public:
	SaveInfo() = default;
	~SaveInfo() = default;
	
	// 拷贝构造函数和移动构造函数
	SaveInfo(const SaveInfo& info) = delete;
	SaveInfo(SaveInfo&& info) = default;

	SaveInfo& operator=(const SaveInfo& info) = delete;
	SaveInfo& operator=(SaveInfo&& info) = default;

	// 设置窗口类型名
	void setWinType(const wxString& winType) { m_winType = winType; }
	// 设置该窗口的所有属性
	void setWinAttrs(const WIN_ATTR_MAP& winAttrs) { m_allWinAttrs = winAttrs; }

	// 将子窗口信息存储到该对象中
	void push_back(const SaveInfo& info) = delete;
	void push_back(SaveInfo&& info) { m_childrens.push_back(std::move(info)); }

	//获取窗口类型
	const wxString& getWinType() const { return m_winType; }
	// 用来获取窗口属性
	const WIN_ATTR_MAP& getWinAttrs() const { return m_allWinAttrs; }

	CONST_CHILD_ITERATOR getChildConstBeg() const { return m_childrens.cbegin(); }
	CONST_CHILD_ITERATOR getChildConstEnd() const { return m_childrens.cend(); }

private:
	// 该窗口的类型名称
	wxString m_winType;
	// 该窗口的所有属性
	WIN_ATTR_MAP m_allWinAttrs;
	// 该窗口的子窗口
	std::vector<SaveInfo> m_childrens;
};

#endif	// SAVE_INFO_H