#include "EditorFunc.h"
#include "SimpleWindow/SimpleWindow.h"
#include "EditorWindowCheck.h"

#include "../EditMessage/CommandFactory.h"
#include "../EditMessage/ChangeManager.h"

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

	// 用来查看对应ID的控件
	SimpleWindow<EditorFunc>* EditorFunc::findMatchWnd(ID_TYPE findId)
	{
		if (getId() == findId)
		{
			return getConstructWindow();
		}
		return nullptr;
	}

	// 修改编辑时是否显示
	bool EditorFunc::changeEditShow(const wxAny& value)
	{
		return ChangeWndAttrValue<bool>(value, &SimpleWindow<EditorFunc>::getEditShow,
			&SimpleWindow<EditorFunc>::setEditShow, __func__);
	}

	// 修改X坐标
	bool EditorFunc::changePosX(const wxAny & value)
	{
		return ChangeWndAttrValue<int>(value, &SimpleWindow<EditorFunc>::getRelX,
			&SimpleWindow<EditorFunc>::updateRelX, __func__);
	}

	// 修改Y坐标
	bool EditorFunc::changePosY(const wxAny &value)
	{
		return ChangeWndAttrValue<int>(value, &SimpleWindow<EditorFunc>::getRelY,
			&SimpleWindow<EditorFunc>::updateRelY, __func__);
	}

	// 修改sizeX
	bool EditorFunc::changeSizeX(const wxAny & value)
	{
		return ChangeWndAttrValue<int>(value, &SimpleWindow<EditorFunc>::getWidth,
			&SimpleWindow<EditorFunc>::updateWidth, __func__);
	}

	// 修改sizeY
	bool EditorFunc::changeSizeY(const wxAny & value)
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

	// 用来处理各种鼠标事件
	bool EditorFunc::handleLMouseDown(int x, int y)
	{
		if (Check_UiInMsgRegion(x, y)(getConstructWindow()))
		{
			using namespace Command;
			auto command = CommandFactory::instance()->createCurWindowSelectCommand(getConstructWindow());
			ChangeManager::instance()->getCommandStack().Submit(command);

			return true;
		}

		return false;
	}

	ID_TYPE EditorFunc::s_id_generator = ID_BEG;

	// 初始化属性处理函数Map
	EditorFunc::ATTR_HANDLE_MAP EditorFunc::initEditorAttrHanldes()
	{
		ATTR_HANDLE_MAP handles;
		handles.insert(std::make_pair(EDITOR_SHOW, &EditorFunc::changeEditShow));
		handles.insert(std::make_pair(WIN_POSX, &EditorFunc::changePosX));
		handles.insert(std::make_pair(WIN_POSY, &EditorFunc::changePosY));
		handles.insert(std::make_pair(WIN_SIZEX, &EditorFunc::changeSizeX));
		handles.insert(std::make_pair(WIN_SIZEY, &EditorFunc::changeSizeY));
		return handles;
	}
}