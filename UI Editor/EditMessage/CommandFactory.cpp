#include "CommandFactory.h"
#include "ChangeManager.h"

namespace Command
{
	CommandFactory* CommandFactory::s_factory = nullptr;

	DropWindowCommand<ChangeManager*> * CommandFactory::createDropWindowCommand(EditorAbstractWindow * insertWnd,
		EditorAbstractWindow * parentWnd) const
	{
		return new DropWindowCommand<ChangeManager*>(ChangeManager::instance(), insertWnd, parentWnd);
	}

	// 创建一个ChangeWinAttrCommand命令
	ChangeWinAttrCommand<ChangeManager*>* CommandFactory::createChangeWinAttrCommand(const wxString& attrName, const wxAny& toSetValue) const
	{
		return new ChangeWinAttrCommand<ChangeManager*>(ChangeManager::instance(), attrName, toSetValue);
	}

	// 创建一个选择当前控件命令
	CurrentWindowCommand<ChangeManager*>* CommandFactory::createCurrentWindowCommand(EditorAbstractWindow * curWnd) const
	{
		return new CurrentWindowCommand<ChangeManager*>(ChangeManager::instance(), curWnd);
	}

	// 创建一个选择当前控件ID命令
	CurrentWindowIdCommand<ChangeManager*>* CommandFactory::createCurrentWindowIdCommand(ID_TYPE curWndId) const
	{
		return new CurrentWindowIdCommand<ChangeManager*>(ChangeManager::instance(), curWndId);
	}

	// 创建一个选择当前控件并且设置为唯一选择的命令
	CurWindowSelectCommand<ChangeManager*>* CommandFactory::createCurWindowSelectCommand(EditorAbstractWindow * curWnd) const
	{
		return new CurWindowSelectCommand<ChangeManager*>(ChangeManager::instance(), curWnd);
	}
}

