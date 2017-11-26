#include "EditorFrame.h"
#include "../DrawEngine/DrawControlManager.h"

// 更新控件对象属性信息
void EditorFrame::updateWinAttr(const wxString & attrName, const wxAny & value)
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
void EditorFrame::editDraw(int absX, int absY, DrawControlManager * drawManager)
{
	drawManager->drawWindow(this, absX, absY);
}

const EditorFrame::ATTR_HANDLE_MAP &EditorFrame::getEditorAttrHandles()
{
	// 属性与属性处理函数Map
	static ATTR_HANDLE_MAP s_attrHandles = initEditorAttrHanldes();
	return s_attrHandles;
}

// 初始化属性处理函数Map
EditorFrame::ATTR_HANDLE_MAP EditorFrame::initEditorAttrHanldes()
{
	ATTR_HANDLE_MAP attrHandles;
	auto attrsRef = EditorFunc::getEditorAttrHandles();
	for (const auto& value : attrsRef)
	{
		attrHandles.insert(value);
	}
	return attrHandles;
}
