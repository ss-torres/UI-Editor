#ifndef ABSTRACT_WIN_ATTR_BUILDER_H
#define ABSTRACT_WIN_ATTR_BUILDER_H

#include <map>
#include <vector>
#include "WinAttrAndNameProtocol.h"

class AbstractWinAttrBuilder
{
public:
	AbstractWinAttrBuilder();
	virtual ~AbstractWinAttrBuilder();

	// 加载各类控件对应的属性
	virtual bool loadWinAttr() = 0;

	// 获取加载的控件属性，在调用loadWinAttr后，只可调用一次
	std::map<wxString, std::vector<WinAttrProperty>> getWinAttrs();

protected:
	std::map<wxString, std::vector<WinAttrProperty>> m_winAttrs;
};


#endif	// ABSTRACT_WIN_ATTR_BUILDER_H
