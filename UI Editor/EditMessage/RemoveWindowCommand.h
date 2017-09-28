#ifndef REMOVE_WINDOW_COMMAND_H
#define REMOVE_WINDOW_COMMAND_H

/*
 * 文件名：RemoveWindowCommand
 * 作用：用来实现移除一个窗口的作用
 */

#include "InsertWindowCommand.h"

namespace Command
{
	template <typename T>
	class RemoveWindowCommand : public InsertWindowCommand<T>
	{
	public:
		RemoveWindowCommand(T* winMgr):InsertWindowCommand<T>(winMgr) {}
		~RemoveWindowCommand() override {}

		// 重构Do函数，与InsertWindowCommand正好相反
		bool Do() override { return false; }
		// 重构Undo函数，与InsertWindowCommand正好相反
		bool Undo() override { return false; }

	};
}

#endif	// REMOVE_WINDOW_COMMAND_H
