#ifndef XML_WIN_ATTR_BUILDER_H
#define XML_WIN_ATTR_BUILDER_h

#include "AbstractWinAttrBuilder.h"

class wxXmlNode;

class XmlWinAttrBuilder : public AbstractWinAttrBuilder
{
public:
	XmlWinAttrBuilder(const wxString& xmlName);
	~XmlWinAttrBuilder();

	// 加载窗口属性
	bool loadWinAttr() override;

private:
	// 加载一个节点
	void loadXmlNode(wxXmlNode* node, std::vector<AttributeProperty> winAttrs);
	// 分析一个Attribute的数据
	void AnalyzeNode(wxXmlNode* node, AttributeProperty& attrProperty);

private:
	wxString m_xmlName;
};

#endif	// XML_WIN_ATTR_BUILDER_H
