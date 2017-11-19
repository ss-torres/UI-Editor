#include "AbstractWinAttrBuilder.h"

AbstractWinAttrBuilder::AbstractWinAttrBuilder()
{
}

AbstractWinAttrBuilder::~AbstractWinAttrBuilder()
{
}


// 获取加载的控件属性，在调用loadWinAttr后，只可调用一次
std::map<wxString, std::vector<WinAttrProperty>> AbstractWinAttrBuilder::getWinAttrs()
{
	return std::move(m_winAttrs);
}
