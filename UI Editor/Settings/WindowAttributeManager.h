#ifndef WINDOW_ATTRIBUTE_LOAD_H
#define WINDOW_ATTRIBUTE_LOAD_H

/*
 * 文件名：WindowAttributeManager
 * 作用：用来管理控件与对应wxPGProperty之间的关系
 * 说明：该文件中存在两套wxPGProperty，一套wxPGProperty为从配置文件中读取的，对应着默认的值，
 * 另外一套对应着在编辑过程中使用的，其中的值会随着编辑过程不断改变
 */

#include <map>
#include <vector>
#include <memory>
#include <wx/wx.h>
#include "WinAttrAndNameProtocol.h"

class wxPGProperty;
class PropertyFactory;

class WindowAttributeManager
{
public:
	using EDIT_WIN_ATTR_ITERATOR = std::vector<wxPGProperty*>::iterator;
public:
	WindowAttributeManager();
	~WindowAttributeManager();

	bool LoadAttributeFile(const wxString& winAttrFile);

	// 用来获取控件名对应的默认控件属性
	const std::vector<wxPGProperty*>& getWinAttr(const wxString& winName) const;
	// 用来获取控件名对应的默认属性值
	const std::map<wxString, wxAny>& getWinDefValues(const wxString& winName) const;
	// 用来获取控件名对应的编辑属性值
	const std::vector<wxPGProperty*>& getEditWinAttr(const wxString& winName) const;
	//// 用来获取可以编辑的对应控件属性，通过使用iterator，可以只修改值，而不改变
	//// 以下函数需要logN的运行时间，所以请保存对应的ITERATOR
	//EDIT_WIN_ATTR_ITERATOR getEditWinAttrBeg(const wxString& winName);
	//EDIT_WIN_ATTR_ITERATOR getEditWinAttrEnd(const wxString& winName);

private:
	// 创建默认属性列表
	void createDefaultAttrs(const std::map<wxString, std::vector<WinAttrProperty>>& winAttrs);
	// 创建编辑用的属性列表
	void createEditAttrs(const std::map<wxString, std::vector<WinAttrProperty>>& winAttrs);

private:
	// 用来记录控件默认属性信息
	std::map<wxString, std::vector<wxPGProperty*>> m_winAttrProperty;
	// 用来记录控件默认属性信息
	std::map<wxString, std::map<wxString, wxAny>> m_winAttrDefValues;
	// 用来记录当前编辑的控件属性信息
	std::map<wxString, std::vector<wxPGProperty*>> m_winEditAttrProperty;
	// 根据属性控件wxPGProperty
	std::unique_ptr<PropertyFactory> m_propertyFacotry;
};

#endif		// WINDOW_ATTRIBUTE_LOAD_H