#include "CommandStack.h"

namespace Command
{
	CommandStack::CommandStack(int maxCommands)
		: wxCommandProcessor(maxCommands)
	{

	}

	CommandStack::~CommandStack()
	{

	}
}