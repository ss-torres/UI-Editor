#ifndef WINDOW_ATTRIBUTE_LOAD_H
#define WINDOW_ATTRIBUTE_LOAD_H

/*
 * 文件名：WindowAttributeManager
 * 作用：用来管理窗口与对应wxPGProperty之间的关系
 * 说明：该文件中存在两套wxPGProperty，一套wxPGProperty为从配置文件中读取的，对应着默认的值，
 * 另外一套对应着在编辑过程中使用的，其中的值会随着编辑过程不断改变
 */

#include <wx/wx.h>
#include <map>
#include <vector>
#include <memory>

#include "WindowAttributeDefine.h"

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

	// 用来获取窗口名对应的窗口属性
	const std::vector<wxPGProperty*>& getWinAttr(const wxString& winName) const;
	// 用来获取可以编辑的对应窗口属性，通过使用iterator，可以只修改值，而不改变
	// 以下函数需要logN的运行时间，所以请保存对应的ITERATOR
	EDIT_WIN_ATTR_ITERATOR getEditWinAttrBeg(const wxString& winName);
	EDIT_WIN_ATTR_ITERATOR getEditWinAttrEnd(const wxString& winName);

private:
	// 创建默认属性列表
	void createDefaultAttrs(const std::map<wxString, std::vector<AttributeProperty>>& winAttrs);
	// 创建编辑用的属性列表
	void createEditAttrs(const std::map<wxString, std::vector<AttributeProperty>>& winAttrs);

private:
	// 用来记录窗口默认属性信息
	std::map<wxString, std::vector<wxPGProperty*>> m_winAttrProperty;
	// 用来记录当前编辑的窗口属性信息
	std::map<wxString, std::vector<wxPGProperty*>> m_winEditAttrProperty;
	// 根据属性窗口wxPGProperty
	std::unique_ptr<PropertyFactory> m_propertyFacotry;
};

#endif		// WINDOW_ATTRIBUTE_LOAD_H