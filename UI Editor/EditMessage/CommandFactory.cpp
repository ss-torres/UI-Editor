#include "CommandFactory.h"
#include "DropWindowCommand.h"
#include "ChangeManager.h"

namespace Command
{
	CommandFactory* CommandFactory::s_factory = nullptr;

	DropWindowCommand<ChangeManager*> * CommandFactory::createDropWindowCommand(EditorAbstractWindow * insertWnd,
		EditorAbstractWindow * parentWnd, EditorAbstractWindow * lastCurWnd) const
	{
		return new DropWindowCommand<ChangeManager*>(ChangeManager::instance(), insertWnd, parentWnd, lastCurWnd);
	}
}

