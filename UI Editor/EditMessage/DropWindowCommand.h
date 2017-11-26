#ifndef DROP_WINDOW_COMMAND_H
#define DROP_WINDOW_COMMAND_H

/*
 * 文件名: DropWindowCommand
 * 作用：在主工作区添加一个控件，并将该控件设置为当前控件
 */

#include "InsertWindowCommand.h"
#include "CurrentWindowCommand.h"
#include "SelectWindowsCommand.h"

namespace Command
{
	template <typename T>
	class DropWindowCommand : public wxCommand
	{
	public:
		DropWindowCommand(T t, EditorAbstractWindow* insertWnd, EditorAbstractWindow* parentWnd)
			: wxCommand(true),
			m_insertCommand(t, insertWnd, parentWnd), m_curWinCommand(t, insertWnd),
			m_selWindowsCommand(t, std::unordered_set<ID_TYPE>{insertWnd->getId()})
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
		SelectWindowsCommand<T> m_selWindowsCommand;
	};

	template <typename T>
	bool DropWindowCommand<T>::Do()
	{
		bool flag = m_insertCommand.Do();
		if (flag)
		{
			flag = m_curWinCommand.Do();
		}
		if (flag)
		{
			flag = m_selWindowsCommand.Do();
		}
		return flag;
	}

	template <typename T>
	bool DropWindowCommand<T>::Undo()
	{
		bool flag = m_selWindowsCommand.Undo();
		if (flag)
		{
			flag = m_curWinCommand.Undo();
		}
		if (flag)
		{
			flag = m_insertCommand.Undo();
		}
		return flag;
	}
}

#endif	// DROP_WINDOW_COMMAND_H
