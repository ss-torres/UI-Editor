#ifndef COMMAND_FACTORY_H
#define COMMAND_FACTORY_H

#include "../EditorWindow/WindowInterface.h"
#include "ChangeManager.h"
#include "DropWindowCommand.h"

namespace Command
{
	class ChangeManager;

	class CommandFactory
	{
	public:
		CommandFactory(ChangeManager* chgMgr): m_chgMgr(chgMgr){ }
		~CommandFactory() {}

		static const CommandFactory* const createInstance(ChangeManager* chgMgr);
		static const CommandFactory* const instance() { return s_factory; }

		// 创建一个DropWindowCommand命令
		DropWindowCommand<ChangeManager*>* createDropWindowCommand(AbstractEditorWindow* insertWnd, 
			AbstractEditorWindow* parentWnd, AbstractEditorWindow* lastCurWnd) const;

	private:
		static CommandFactory* s_factory;
		ChangeManager* m_chgMgr;
	};

	inline const CommandFactory* const CommandFactory::createInstance(ChangeManager * chgMgr)
	{
		if (s_factory == nullptr)
		{
			s_factory = new CommandFactory(chgMgr);
		}

		return s_factory;
	}
}

#endif	// COMMAND_FACTORY_H
