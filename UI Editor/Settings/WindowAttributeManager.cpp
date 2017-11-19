#include <memory>
#include <stdexcept>
#include <wx/xml/xml.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/property.h>
#include "WindowAttributeManager.h"
#include "AttributeBuilder/XmlWinAttrBuilder.h"
#include "../Property/PropertyFactory.h"

WindowAttributeManager::WindowAttributeManager()
{
}

WindowAttributeManager::~WindowAttributeManager()
{
	for (auto it = m_winAttrProperty.begin(); it != m_winAttrProperty.end(); ++it)
	{
		auto& properties = it->second;
		for (auto iter = properties.begin(); iter != properties.end(); ++iter)
		{
			m_propertyFacotry->destroyProperty(*iter);
		}
	}
}

bool WindowAttributeManager::LoadAttributeFile(const wxString& winAttrFile)
{
	std::unique_ptr<AbstractWinAttrBuilder> winAttrBuilder(new XmlWinAttrBuilder(winAttrFile));
	if (winAttrBuilder->loadWinAttr())
	{
		// 加载属成功
		// 将xml中的属性描述，转变为wxPGProperty
		m_propertyFacotry.reset(new PropertyFactory());
		auto winAttrs = winAttrBuilder->getWinAttrs();

		createDefaultAttrs(winAttrs);
		createEditAttrs(winAttrs);
		return true;
	}

	return false;
}

// 用来获取控件名对应的默认控件属性
const std::vector<wxPGProperty*>& WindowAttributeManager::getWinAttr(const wxString& winName) const
{
	std::map<wxString, std::vector<wxPGProperty*>>::const_iterator it = m_winAttrProperty.find(winName);
	if (it != m_winAttrProperty.cend())
	{
		return it->second;
	}

	throw ExtraExcept::unexpected_situation("WindowAttributeManager::getWinAttr should find the winName.");

	static std::vector<wxPGProperty*> markAttr = std::vector<wxPGProperty*>();
	return markAttr;
}

// 用来获取控件名对应的默认属性值
const std::map<wxString, wxAny>& WindowAttributeManager::getWinDefValues(const wxString & winName) const
{
	auto it = m_winAttrDefValues.find(winName);
	if (it != m_winAttrDefValues.cend())
	{
		return it->second;
	}

	throw std::runtime_error("WindowAttributeManager::getWinDefValues can't find winName");
	static std::map<wxString, wxAny> errorRet;
	return errorRet;
}

// 用来获取控件名对应的编辑属性值
const std::vector<wxPGProperty*>& WindowAttributeManager::getEditWinAttr(const wxString& winName) const
{
	auto it = m_winEditAttrProperty.find(winName);
	if (it != m_winEditAttrProperty.cend())
	{
		return it->second;
	}

	throw std::runtime_error("WindowAttributeManager::getEditWinAttr can't find winName");
	static std::vector<wxPGProperty*> errorRet;
	return errorRet;
}

//// 用来获取可以编辑的对应控件属性，通过使用iterator，可以只修改值，而不改变
//WindowAttributeManager::EDIT_WIN_ATTR_ITERATOR WindowAttributeManager::getEditWinAttrBeg(const wxString & winName)
//{
//	auto it = m_winEditAttrProperty.find(winName);
//	if (it != m_winEditAttrProperty.cend())
//	{
//		return it->second.begin();
//	}
//	throw std::runtime_error("WindowAttributeManager::getEditWinAttrBeg can't find winName");
//	return EDIT_WIN_ATTR_ITERATOR();
//}
//
//WindowAttributeManager::EDIT_WIN_ATTR_ITERATOR WindowAttributeManager::getEditWinAttrEnd(const wxString & winName)
//{
//	auto it = m_winEditAttrProperty.find(winName);
//	if (it != m_winEditAttrProperty.cend())
//	{
//		return it->second.end();
//	}
//	throw std::runtime_error("WindowAttributeManager::getEditWinAttrEnd can't find winName");
//	return EDIT_WIN_ATTR_ITERATOR();
//}

// 创建默认属性列表
void WindowAttributeManager::createDefaultAttrs(const std::map<wxString, std::vector<WinAttrProperty>>& winAttrs)
{
	std::vector<wxPGProperty*> properties;
	std::map<wxString, wxAny> propertyValues;
	for (auto it = winAttrs.cbegin(); it != winAttrs.cend(); ++it)
	{
		properties.clear();
		auto& winAttr = it->second;
		for (auto iter = winAttr.cbegin(); iter != winAttr.cend(); ++iter)
		{
			wxPGProperty* pg = m_propertyFacotry->createDefaultProperty(*iter);
			if (pg == nullptr)
			{
				throw ExtraExcept::unexpected_situation("WindowAttributeManager::createDefaultAttrs: pg should not be nullptr");
			}
			properties.push_back(pg);
		}
		// 如果属性不为空
		if (!properties.empty())
		{
			// 初始化值
			propertyValues.clear();
			for (const auto prop : properties)
			{
				propertyValues.insert(std::make_pair(prop->GetName(), prop->GetValue()));
			}
			m_winAttrDefValues.emplace(it->first, std::move(propertyValues));
			m_winAttrProperty.emplace(it->first, std::move(properties));
		}
	}
}

// 创建编辑用的属性列表
void WindowAttributeManager::createEditAttrs(const std::map<wxString, std::vector<WinAttrProperty>>& winAttrs)
{
	std::vector<wxPGProperty*> properties;
	for (auto it = winAttrs.cbegin(); it != winAttrs.cend(); ++it)
	{
		properties.clear();
		auto& winAttr = it->second;
		for (auto iter = winAttr.cbegin(); iter != winAttr.cend(); ++iter)
		{
			wxPGProperty* pg = m_propertyFacotry->createProperty(*iter);
			if (pg == nullptr)
			{
				throw ExtraExcept::unexpected_situation("WindowAttributeManager::createEditAttrs: pg should not be nullptr");
			}
			properties.push_back(pg);
		}
		// 如果属性不为空
		if (!properties.empty())
		{
			m_winEditAttrProperty.emplace(it->first, std::move(properties));
		}
	}
}
