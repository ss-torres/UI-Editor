#include "XmlWinAttrBuilder.h"
#include <wx/xml/xml.h>

const wxString ROOT_NAME = "UIAttribute";

XmlWinAttrBuilder::XmlWinAttrBuilder(const wxString & xmlName)
	: m_xmlName(xmlName)
{
}

XmlWinAttrBuilder::~XmlWinAttrBuilder()
{
}

bool XmlWinAttrBuilder::loadWinAttr()
{
	wxXmlDocument doc;
	if (!doc.Load(m_xmlName))
		return false;

	// 检查文件标识
	wxXmlNode* rootNode = doc.GetRoot();
	if (rootNode->GetName() != ROOT_NAME)
	{
		return false;
	}

	// 查看UI属性版本
	const wxString& versionValue = rootNode->GetAttribute("version", "0");
	long version = 0;
	if (!versionValue.ToLong(&version) || (version == 0))
	{
		return false;
	}
	// 加载不同类型窗口的属性
	std::vector<AttributeProperty> attrs;
	wxXmlNode* winNode = rootNode->GetChildren();
	for (; winNode != nullptr; winNode = winNode->GetNext())
	{
		if (winNode->GetName() != "Window")
		{
			continue;
		}

		loadXmlNode(winNode, attrs);
	}

	return true;
}

void XmlWinAttrBuilder::loadXmlNode(wxXmlNode * node, std::vector<AttributeProperty> winAttrs)
{
	// 不同窗口的属性
	wxString winName = node->GetAttribute("name", "");
	if (winName.empty())
	{
		return;
	}

	// 遍历窗口的所有属性
	wxXmlNode* attrNode = node->GetChildren();
	AttributeProperty attrProperty;
	wxString nodeValue;
	for (; attrNode != nullptr; attrNode = attrNode->GetNext())
	{
		if (attrNode->GetName() != "Attribute")
		{
			continue;
		}

		nodeValue = attrNode->GetAttribute("name", "");

		// 属性不能为空
		if (nodeValue.empty())
		{
			continue;
		}

		attrProperty.propertyName = nodeValue;

		AnalyzeNode(attrNode, attrProperty);

		winAttrs.push_back(std::move(attrProperty));
	}

	// 遍历窗口的子窗口类型（derived class）
	wxXmlNode* winNode = node->GetChildren();
	for (; winNode != nullptr; winNode = winNode->GetNext())
	{
		if (winNode->GetName() != "Window")
		{
			continue;
		}

		loadXmlNode(winNode, winAttrs);
	}

	// 已经获取了所有的属性，保存对应属性
	if (!winAttrs.empty())
	{
		m_winAttrs.emplace(std::move(winName), std::move(winAttrs));
	}
}

// 分析一个Attribute的数据
void XmlWinAttrBuilder::AnalyzeNode(wxXmlNode *node, AttributeProperty & attrProperty)
{
	attrProperty.editorProperty = node->GetAttribute(SET_PROPERTY_TYPE, "");
	if (attrProperty.editorProperty.empty())
	{
		attrProperty.editorProperty = STRING_PROPERTY;
	}
	attrProperty.editorName = node->GetAttribute(SET_EDITOR_NAME, "");
	attrProperty.editorValidator = node->GetAttribute(SET_EDITOR_VALIDATOR, "");

	wxString lengthDesc = node->GetAttribute(SET_EDITOR_MAX_LEN, "");
	long lengthValue = 0;
	lengthDesc.ToLong(&lengthValue);
	if (lengthValue <= 0)
	{
		lengthValue = DEF_MAX_LENGTH;
	}
	attrProperty.editorMaxLength = lengthValue;
	attrProperty.initialValue = node->GetAttribute(SET_INITIAL_VALUE, "");

	wxXmlNode* subNode = node->GetChildren();
	for (; subNode != nullptr; subNode = subNode->GetNext())
	{
		if (subNode->GetName() == wxS("EditorAttributeList"))
		{
			wxXmlNode* thirdNode = subNode->GetChildren();
			for (; thirdNode != nullptr; thirdNode = thirdNode->GetNext())
			{
				attrProperty.editorAttributeList.emplace(thirdNode->GetAttribute("name", ""),
					thirdNode->GetAttribute("value", ""));
			}
		}
		else if (subNode->GetName() == wxS("PropertyAdditional"))
		{
			wxXmlNode* thirdNode = subNode->GetChildren();
			for (; thirdNode != nullptr; thirdNode = thirdNode->GetNext())
			{
				attrProperty.additionalInfos.emplace(thirdNode->GetAttribute("name", ""),
					thirdNode->GetAttribute("value", ""));
			}
		}
	}
}
