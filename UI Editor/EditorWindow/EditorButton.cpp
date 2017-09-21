#include "EditorButton.h"

namespace inner
{
	EditorButton::EditorButton(AbstractEditorWindow* parent, int relX, int relY, int width, int height)
		: SimpleButton<EditorFunc>(parent, relX, relY, width, height)
	{
	}

	EditorButton::~EditorButton()
	{

	}

	// 更新窗口对象属性信息
	void EditorButton::updateWinAttr(const wxString& attrName, const wxAny &value)
	{
		EditorFunc::updateWinAttr(attrName, value);
		// 查看是否与编辑时处理和显示相关，如果是，则单独处理
		auto attrsRef = getEditorAttrHandles();
		const auto &it = attrsRef.find(attrName);
		if (it != attrsRef.cend())
		{
			(it->second)(this, value);
		}
	}

	// 获取属性与属性处理函数Map
	const EditorButton::ATTR_HANDLE_MAP & EditorButton::getEditorAttrHandles()
	{
		// 属性与属性处理函数Map
		static ATTR_HANDLE_MAP s_attrHandles = initEditorAttrHanldes();
		return s_attrHandles;
	}

	// 初始化属性处理函数Ma
	EditorButton::ATTR_HANDLE_MAP EditorButton::initEditorAttrHanldes()
	{
		ATTR_HANDLE_MAP attrHandles;
		auto attrsRef = EditorFunc::getEditorAttrHandles();
		for (const auto& value : attrsRef)
		{
			attrHandles.insert(value);
		}
		return attrHandles;
	}
}