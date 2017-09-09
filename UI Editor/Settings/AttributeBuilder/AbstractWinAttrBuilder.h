#ifndef ABSTRACT_WIN_ATTR_BUILDER_H
#define ABSTRACT_WIN_ATTR_BUILDER_H

#include <map>
#include <vector>
#include "../WindowAttributeDefine.h"

class AbstractWinAttrBuilder
{
public:
	AbstractWinAttrBuilder();
	virtual ~AbstractWinAttrBuilder();

	// 加载各类窗口对应的属性
	virtual bool loadWinAttr() = 0;

	// 获取加载的窗口属性，获取后，除非重新加载，否则不可使用
	std::map<wxString, std::vector<AttributeProperty>> getWinAttrs();

protected:
	std::map<wxString, std::vector<AttributeProperty>> m_winAttrs;
};


#endif	// ABSTRACT_WIN_ATTR_BUILDER_H
