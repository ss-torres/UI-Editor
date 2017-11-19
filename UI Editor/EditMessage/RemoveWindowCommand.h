#ifndef REMOVE_WINDOW_COMMAND_H
#define REMOVE_WINDOW_COMMAND_H

/*
 * 文件名：RemoveWindowCommand
 * 作用：用来实现移除一个控件的作用
 * 说明：如果子控件被插入到父控件中，则父控件负责子控件的删除
 * 否则该命令负责子控件的删除
 */

#include "InsertWindowCommand.h"

namespace Command
{
	template <typename T>
	class RemoveWindowCommand : public InsertWindowCommand<T>
	{
	public:
		RemoveWindowCommand(T* mgr, EditorAbstractWindow* removeWnd, EditorAbstractWindow* parentWnd)
			: InsertWindowCommand<T>(mgr, removeWnd, parentWnd) { }
		~RemoveWindowCommand() override {}


		// 重构Do函数，与InsertWindowCommand正好相反
		bool Do() override;
		// 重构Undo函数，与InsertWindowCommand正好相反
		bool Undo() override;

	};

	template <typename T>
	inline bool RemoveWindowCommand<T>::Do()
	{
		return InsertWindowCommand<T>::Undo();
	}

	template<typename T>
	inline bool RemoveWindowCommand<T>::Undo()
	{
		return InsertWindowCommand<T>::Do();
	}
}

#endif	// REMOVE_WINDOW_COMMAND_H
