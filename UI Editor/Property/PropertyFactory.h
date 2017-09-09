#ifndef PROPERTY_FACTORY_H
#define PROPERTY_FACTORY_H

#include <map>
#include <wx/string.h>
#include "../ErrorHandle/ErrorHandle.h"

struct AttributeProperty;
class wxPGProperty;
class wxEnumProperty;

class PropertyFactory
{
public:
	PropertyFactory();
	~PropertyFactory() {}

	// 静态函数
	static const PropertyFactory* Instance();

	// 根据配置参数，获取一个wxPGProperty
	wxPGProperty* createProperty(const AttributeProperty& attrProperty) const;
	// 销毁属性列表
	void destroyProperty(wxPGProperty* &property);

private:
	// 设置编辑器的各种属性
	void setEditorAttributes(wxPGProperty* property, const std::map<wxString, wxString>& editorAttrs) const;
	// 根据传入的xml中属性名，获取wxWidgets中对应属性名
	const wxString& getwxAttrFromXmlAttr(const wxString& xmlAttr) const;
	// 初始化属性名对
	void initXmlAttrTowxAttr();

private:
	static PropertyFactory *s_propertyFactory;
	// 记录XML中Attribute与wxWidgets中属性的关系
	std::map<wxString, wxString> m_xmlAttrTowxAttr;
};

namespace PropertyFactoryImpl
{
	// 根据属性名创建属性
	wxPGProperty* createPropertyFromName(const wxString& propertyName, const wxString& editorProperty);
	// 根据编辑器描述设置编辑器
	void setPropertyEditor(wxPGProperty* property, const wxString& editorName);
	// 设置属性编辑验证器
	void setEditorValidator(wxPGProperty* property, const wxString& validatorName);
	// 设置属性的一些额外属性
	void SetPropertyAdditional(wxPGProperty* property, const std::map<wxString, wxString>& additionalInfos);
	// 设置EnumProperty的一些额外属性
	void SetEnumPropAdditional(wxEnumProperty* property, const std::map<wxString, wxString>& additionalInfos);
}

// 根据传入的xml中属性名，获取wxWidgets中对应属性名
inline const wxString& PropertyFactory::getwxAttrFromXmlAttr(const wxString& xmlAttr) const
{
	const auto it = m_xmlAttrTowxAttr.find(xmlAttr);
	if (it != m_xmlAttrTowxAttr.cend())
	{
		return it->second;
	}

	throw ExtraException::unexpected_situation("PropertyFactory::getwxAttrFromXmlAttr: wxAttr should be found.");
	thread_local wxString errorRet = wxString("");
	return errorRet;
}

#endif	// PROPERTY_FACTORY_H