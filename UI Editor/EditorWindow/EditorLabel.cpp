#include "EditorLabel.h"

namespace inner
{
	EditorLabel::EditorLabel(SIMPLE_WINDOW_TYPE* parent, int relX, int relY, int width, int height)
		: SimpleLabel<EditorEditableFunc>(parent, relX, relY, width, height)
	{
	}

	EditorLabel::~EditorLabel()
	{
	}

	// 更新窗口对象属性信息
	void EditorLabel::updateWinAttr(const wxString& attrName, const wxAny &value)
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
	const EditorLabel::ATTR_HANDLE_MAP & EditorLabel::getEditorAttrHandles()
	{
		// 属性与属性处理函数Map
		static ATTR_HANDLE_MAP s_attrHandles = initEditorAttrHanldes();
		return s_attrHandles;
	}

	// 初始化属性处理函数Ma
	EditorLabel::ATTR_HANDLE_MAP EditorLabel::initEditorAttrHanldes()
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