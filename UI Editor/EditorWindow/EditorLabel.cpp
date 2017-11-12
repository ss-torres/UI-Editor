#include "EditorLabel.h"
#include "../DrawEngine/DrawControlManager.h"
#include "../Settings/UsedWinAttrDefine.h"

EditorLabel::EditorLabel(SIMPLE_WINDOW_TYPE* parent, int relX, int relY, int width, int height)
	: SimpleLabel<inner::EditorEditableFunc>(parent, relX, relY, width, height)
{
	// 临时用于测试
	updateWinAttr(LABEL_TEXT, wxString(L"label"));
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

//在编辑界面上绘制
void EditorLabel::editDraw(int absX, int absY, DrawControlManager * drawManager)
{
	drawManager->drawWindow(this, absX, absY);
}

// 获取属性与属性处理函数Map
const EditorLabel::ATTR_HANDLE_MAP & EditorLabel::getEditorAttrHandles()
{
	// 属性与属性处理函数Map
	static ATTR_HANDLE_MAP s_attrHandles = initEditorAttrHanldes();
	return s_attrHandles;
}

// 修改显示文字的函数
bool EditorLabel::ChangeText(const wxAny & value)
{
	if (value.CheckType<wxString>())
	{
		auto v = wxStrToStdStr(value.As<wxString>());
		if (v != getText())
		{
			setText(v);
			return true;
		}
	}
	else
	{
		throw std::runtime_error("ChangeText" + std::string("'s parameter is not ") + typeid(wxString).name());
	}

	return false;
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
	attrHandles.insert(std::make_pair(LABEL_TEXT, &EditorLabel::ChangeText));
	return attrHandles;
}