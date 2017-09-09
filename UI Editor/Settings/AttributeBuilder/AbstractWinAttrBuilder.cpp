#include "AbstractWinAttrBuilder.h"

AbstractWinAttrBuilder::AbstractWinAttrBuilder()
{
}

AbstractWinAttrBuilder::~AbstractWinAttrBuilder()
{
}


// 获取加载的窗口属性，获取后，除非重新加载，否则不可使用
std::map<wxString, std::vector<AttributeProperty>> AbstractWinAttrBuilder::getWinAttrs()
{
	return std::move(m_winAttrs);
}
