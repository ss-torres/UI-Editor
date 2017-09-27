#include "EditorFunc.h"
#include <stdexcept>
#include "../Settings/UsedWinAttrDefine.h"
#include "SimpleWindow.h"

namespace inner
{
	EditorFunc::EditorFunc()
		: m_editShow(true),
		m_id(getNewId())
	{
	
	}

	EditorFunc::~EditorFunc()
	{
	}

	// 修改编辑时是否显示
	bool EditorFunc::ChangeEditShow(const wxAny& value)
	{
		return ChangeWndAttrValue<bool>(value, &SimpleWindow<EditorFunc>::getEditShow,
			&SimpleWindow<EditorFunc>::setEditShow, __func__);
	}

	// 修改X坐标
	bool EditorFunc::ChangePosX(const wxAny & value)
	{
		return ChangeWndAttrValue<int>(value, &SimpleWindow<EditorFunc>::getRelX,
			&SimpleWindow<EditorFunc>::updateRelX, __func__);
	}

	// 修改Y坐标
	bool EditorFunc::ChangePosY(const wxAny &value)
	{
		return ChangeWndAttrValue<int>(value, &SimpleWindow<EditorFunc>::getRelY,
			&SimpleWindow<EditorFunc>::updateRelY, __func__);
	}

	// 修改sizeX
	bool EditorFunc::ChangeSizeX(const wxAny & value)
	{
		return ChangeWndAttrValue<int>(value, &SimpleWindow<EditorFunc>::getWidth,
			&SimpleWindow<EditorFunc>::updateWidth, __func__);
	}

	// 修改sizeY
	bool EditorFunc::ChangeSizeY(const wxAny & value)
	{
		return ChangeWndAttrValue<int>(value, &SimpleWindow<EditorFunc>::getHeight,
			&SimpleWindow<EditorFunc>::updateHeight, __func__);
	}

	// 获取属性与属性处理函数Map
	const EditorFunc::ATTR_HANDLE_MAP& EditorFunc::getEditorAttrHandles()
	{
		// 属性与属性处理函数Map
		static auto s_attrHandles = initEditorAttrHanldes();
		return s_attrHandles;
	}

	ID_TYPE EditorFunc::s_id_generator = ID_BEG;

	// 初始化属性处理函数Map
	EditorFunc::ATTR_HANDLE_MAP EditorFunc::initEditorAttrHanldes()
	{
		ATTR_HANDLE_MAP handles;
		handles.insert(std::make_pair(EDITOR_SHOW, &EditorFunc::ChangeEditShow));
		return handles;
	}
}
