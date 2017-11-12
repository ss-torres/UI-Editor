#include "CommandFactory.h"
#include "ChangeManager.h"

namespace Command
{
	CommandFactory* CommandFactory::s_factory = nullptr;

	DropWindowCommand<ChangeManager*> * CommandFactory::createDropWindowCommand(EditorAbstractWindow * insertWnd,
		EditorAbstractWindow * parentWnd, EditorAbstractWindow * lastCurWnd) const
	{
		return new DropWindowCommand<ChangeManager*>(ChangeManager::instance(), insertWnd, parentWnd, lastCurWnd);
	}

	// 创建一个ChangeWinAttrCommand命令
	ChangeWinAttrCommand<ChangeManager*>* CommandFactory::createChangeWinAttrCommand(const wxString& attrName, const wxAny& toSetValue) const
	{
		return new ChangeWinAttrCommand<ChangeManager*>(ChangeManager::instance(), attrName, toSetValue);
	}
}

