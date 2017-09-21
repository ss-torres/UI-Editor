#include "PropertyFactory.h"

#include "wx/fontdlg.h"
#include <wx/bitmap.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/property.h>
#include <wx/propgrid/props.h>
#include <wx/propgrid/advprops.h>

#include "../Settings/WindowAttributeDefine.h"
#include "../ErrorHandle/ErrorHandle.h"
#include "../Util/StringUtil.h"

PropertyFactory* PropertyFactory::s_propertyFactory = nullptr;


PropertyFactory::PropertyFactory()
{
	initXmlAttrTowxAttr();
}

const PropertyFactory * PropertyFactory::Instance()
{
	if (s_propertyFactory == nullptr)
	{
		wxPropertyGrid::RegisterAdditionalEditors();
		s_propertyFactory = new PropertyFactory;
	}

	return s_propertyFactory;
}


// 根据配置参数，获取一个wxPGProperty
wxPGProperty * PropertyFactory::createProperty(const AttributeProperty& attrProperty) const
{
	using namespace PropertyFactoryImpl;

	// 创建属性
	wxPGProperty* property = createPropertyFromName(attrProperty.propertyName, attrProperty.editorProperty);

	if (property == nullptr)
	{
		throw ExtraException::unexpected_situation("some Attribute's EditorProperty is wrong");
	}

	setPropertyEditor(property, attrProperty.editorName);
	setEditorValidator(property, attrProperty.editorValidator);
	//// 该函数需要在添加到wxPropertyGrid之后才能设置
	//property->SetMaxLength(attrProperty.editorMaxLength);
	setInitialValue(property, attrProperty.initialValue);
	setEditorAttributes(property, attrProperty.editorAttributeList);
	setPropertyAdditional(property, attrProperty.additionalInfos);

	return property;
}

// 销毁属性列表
void PropertyFactory::destroyProperty(wxPGProperty *& property)
{
	delete property;
	property = NULL;
}

// 设置编辑器的各种属性
void PropertyFactory::setEditorAttributes(wxPGProperty * property, const std::map<wxString, wxString>& editorAttrs) const
{
	// 查看通用属性设置
	for (auto it = editorAttrs.cbegin(); it != editorAttrs.cend(); ++it)
	{
		const auto wxAttr = getwxAttrFromXmlAttr(it->first);
		property->SetAttribute(wxAttr, it->second);
	}
}

// 初始化属性名对
void PropertyFactory::initXmlAttrTowxAttr()
{
	m_xmlAttrTowxAttr.emplace(XML_ATTR_DEFAULT_VALUE, 			wxPG_ATTR_DEFAULT_VALUE);
	m_xmlAttrTowxAttr.emplace(XML_ATTR_HINT,					wxPG_ATTR_HINT);
	m_xmlAttrTowxAttr.emplace(XML_ATTR_MAX,						wxPG_ATTR_MAX);
	m_xmlAttrTowxAttr.emplace(XML_ATTR_MIN,						wxPG_ATTR_MIN);
	m_xmlAttrTowxAttr.emplace(XML_ATTR_SPINCTRL_STEP,			wxPG_ATTR_SPINCTRL_STEP);
	m_xmlAttrTowxAttr.emplace(XML_ATTR_SPINCTRL_WRAP,			wxPG_ATTR_SPINCTRL_WRAP);
	m_xmlAttrTowxAttr.emplace(XML_ATTR_UNITS,					wxPG_ATTR_UNITS);
	m_xmlAttrTowxAttr.emplace(XML_BOOL_USE_CHECKBOX,			wxPG_BOOL_USE_CHECKBOX);
	m_xmlAttrTowxAttr.emplace(XML_BOOL_USE_DOUBLE_CLICK_CYCLING, wxPG_BOOL_USE_DOUBLE_CLICK_CYCLING);
	m_xmlAttrTowxAttr.emplace(XML_DIR_DIALOG_MESSAGE,			wxPG_DIR_DIALOG_MESSAGE);
	m_xmlAttrTowxAttr.emplace(XML_FILE_DIALOG_STYLE,			wxPG_FILE_DIALOG_STYLE);
	m_xmlAttrTowxAttr.emplace(XML_FILE_DIALOG_TITLE,			wxPG_FILE_DIALOG_TITLE);
	m_xmlAttrTowxAttr.emplace(XML_FILE_INITIAL_PATH,			wxPG_FILE_INITIAL_PATH);
	m_xmlAttrTowxAttr.emplace(XML_FILE_SHOW_FULL_PATH,			wxPG_FILE_SHOW_FULL_PATH);
	m_xmlAttrTowxAttr.emplace(XML_FILE_SHOW_RELATIVE_PATH,		wxPG_FILE_SHOW_RELATIVE_PATH);
	m_xmlAttrTowxAttr.emplace(XML_FILE_WILDCARD,				wxPG_FILE_WILDCARD);
	m_xmlAttrTowxAttr.emplace(XML_FLOAT_PRECISION,				wxPG_FLOAT_PRECISION);
	m_xmlAttrTowxAttr.emplace(XML_UINT_BASE,					wxPG_UINT_BASE);
	m_xmlAttrTowxAttr.emplace(XML_UINT_PREFIX,					wxPG_UINT_PREFIX);
}

// 根据属性名创建属性
wxPGProperty * PropertyFactoryImpl::createPropertyFromName(const wxString & propertyName, const wxString& editorProperty)
{
	wxPGProperty* property = NULL;
	if (editorProperty == STRING_PROPERTY)
	{
		property = new wxStringProperty(propertyName, wxPG_LABEL);
	}
	else if (editorProperty == INT_PROPERTY)
	{
		property = new wxIntProperty(propertyName, wxPG_LABEL);
	}
	else if (editorProperty == BOOL_PROPERTY)
	{
		property = new wxBoolProperty(propertyName, wxPG_LABEL);

	}
	else if (editorProperty == ENUM_PROPERTY)
	{
		property = new wxEnumProperty(propertyName, wxPG_LABEL);
	}

	return property;
}

// 根据编辑器描述设置编辑器
void PropertyFactoryImpl::setPropertyEditor(wxPGProperty* property, const wxString & editorName)
{
	if (editorName == TEXTCTRL_EDITOR)
	{
		property->SetEditor(wxPGEditor_TextCtrl);
	}
	else if (editorName == SPINCTRL_EDITOR)
	{
		property->SetEditor(wxPGEditor_SpinCtrl);
	}
	else if (editorName == CHECKBOX_EDITOR)
	{
		property->SetEditor(wxPGEditor_CheckBox);
	}
	else if (editorName == CHOICE_EDITOR)
	{
		property->SetEditor(wxPGEditor_Choice);
	}
}

// 设置属性编辑验证器
void PropertyFactoryImpl::setEditorValidator(wxPGProperty * property, const wxString & validatorName)
{
	if (validatorName == DEFAULT_VALIDATOR)
	{
		// 默认情况下不设置验证器
	}
}

// 设置初始值
void PropertyFactoryImpl::setInitialValue(wxPGProperty* property, const wxString& initialValue)
{
	if (initialValue.empty())
	{
		return;
	}

	wxVariant value;
	if (property->StringToValue(value, initialValue))
	{
		property->SetValue(value);
	}
}

// 设置属性的一些额外属性
void PropertyFactoryImpl::setPropertyAdditional(wxPGProperty * property, const std::map<wxString, wxString>& additionalInfos)
{
	// 判断是否为EnumProperty
	{
		auto enumProp = dynamic_cast<wxEnumProperty*>(property);
		if (enumProp)
		{
			SetEnumPropAdditional(enumProp, additionalInfos);
		}
	}
}

// 设置EnumProperty的一些额外属性
void PropertyFactoryImpl::SetEnumPropAdditional(wxEnumProperty * property, const std::map<wxString, wxString>& additionalInfos)
{
	// 查看设置的取值范围
	const auto it = additionalInfos.find(ENUM_RANGE);
	if (it != additionalInfos.cend())
	{
		std::vector<wxString> rangeValues = Util::splitStr(it->second, ",");
		wxPGChoices choices;
		for (auto iter = rangeValues.cbegin(); iter != rangeValues.cend(); ++iter)
		{
			choices.Add(*iter);
			property->SetChoices(choices);
		}
	}
}

