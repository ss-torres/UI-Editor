#ifndef WINDOW_ATTRIBUTE_LOAD_H
#define WINDOW_ATTRIBUTE_LOAD_H

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
	WindowAttributeManager();
	~WindowAttributeManager();

	bool LoadAttributeFile(const wxString& winAttrFile);

	// 用来获取窗口名对应的窗口属性
	const std::vector<wxPGProperty*>& getWinAttr(const wxString& winName) const;

private:
	// 用来记录窗口属性信息
	std::map<wxString, std::vector<wxPGProperty*>> m_winAttrProperty;
	// 根据属性窗口wxPGProperty
	std::unique_ptr<PropertyFactory> m_propertyFacotry;
};

#endif		// WINDOW_ATTRIBUTE_LOAD_H