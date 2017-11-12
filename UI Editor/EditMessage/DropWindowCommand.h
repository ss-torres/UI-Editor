#ifndef DROP_WINDOW_COMMAND_H
#define DROP_WINDOW_COMMAND_H

/*
 * 文件名: DropWindowCommand
 * 作用：在主工作区添加一个窗口，并将该窗口设置为当前窗口
 */

#include "InsertWindowCommand.h"
#include "CurrentWindowCommand.h"

namespace Command
{
	template <typename T>
	class DropWindowCommand : public wxCommand
	{
	public:
		DropWindowCommand(T t, EditorAbstractWindow* insertWnd, EditorAbstractWindow* parentWnd, EditorAbstractWindow* lastCurWnd)
			: wxCommand(true),
			m_insertCommand(t, insertWnd, parentWnd), m_curWinCommand(t, lastCurWnd, insertWnd)
		{

		}
		~DropWindowCommand() override {}

		// 重构执行
		bool Do() override;
		// 重构取消执行
		bool Undo() override;

	private:
		InsertWindowCommand<T> m_insertCommand;
		CurrentWindowCommand<T> m_curWinCommand;
	};

	template <typename T>
	bool DropWindowCommand<T>::Do()
	{
		bool flag = m_insertCommand.Do();
		flag = flag && m_curWinCommand.Do();
		return flag;
	}

	template <typename T>
	bool DropWindowCommand<T>::Undo()
	{
		bool flag = m_curWinCommand.Undo();
		flag = flag && m_insertCommand.Do();
		return flag;
	}
}

#endif	// DROP_WINDOW_COMMAND_H
