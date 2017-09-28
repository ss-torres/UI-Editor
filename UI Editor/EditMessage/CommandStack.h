#ifndef COMMAND_STACK_H
#define COMMAND_STACK_H

/*
 * 文件名：CommandStack
 * 作用：用来存储undo/redo的Command列表
 */

#include <wx/cmdproc.h>

namespace Command
{
	class CommandStack : public wxCommandProcessor
	{
	public:
		CommandStack(int maxCommands = -1);
		~CommandStack() override;

	private:

	};
}

#endif	// COMMAND_STACK_H
