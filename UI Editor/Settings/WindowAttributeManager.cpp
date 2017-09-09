#include "WindowAttributeManager.h"
#include <wx/xml/xml.h>
#include <memory>
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
					throw ExtraException::unexpected_situation("WindowAttributeManager::LoadAttributeFile: pg should not be nullptr");
				}
				properties.push_back(pg);
			}
			// 如果属性不为空
			if (!properties.empty())
			{
				m_winAttrProperty.emplace(it->first, std::move(properties));
			}
		}
		return true;
	}

	return false;
}

// 用来获取窗口名对应的窗口属性
const std::vector<wxPGProperty*>& WindowAttributeManager::getWinAttr(const wxString& winName) const
{
	std::map<wxString, std::vector<wxPGProperty*>>::const_iterator it = m_winAttrProperty.find(winName);
	if (it != m_winAttrProperty.cend())
	{
		return it->second;
	}

	throw ExtraException::unexpected_situation("WindowAttributeManager::getWinAttr should find the winName.");

	static std::vector<wxPGProperty*> markAttr = std::vector<wxPGProperty*>();
	return markAttr;
}
