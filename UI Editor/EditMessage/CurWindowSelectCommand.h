#ifndef CUR_WINDOW_SELECT_COMMAND_H
#define CUR_WINDOW_SELECT_COMMAND_H

/*
 * 文件名：CurWindowSelectCommand
 * 作用：选中新的窗口为当前编辑窗口，并且将该窗口设置为唯一选中窗口
 * 说明：使用CurWindowCommand和SelectWindowsCommand实现
 */

#include "CurrentWindowCommand.h"
#include "SelectWindowsCommand.h"

namespace Command
{
	template <typename T>
	class CurWindowSelectCommand : public wxCommand
	{
	public:
		CurWindowSelectCommand(T t, EditorAbstractWindow* curWindow)
			: wxCommand(true), m_curWinCommand(t, curWindow),
			m_selWindowsCommand(t, std::unordered_set<ID_TYPE>{curWindow->getId()})
		{

		}
		~CurWindowSelectCommand() override {}

		// 重构执行
		bool Do() override;
		// 重构取消执行
		bool Undo() override;

	private:
		CurrentWindowCommand<T> m_curWinCommand;
		SelectWindowsCommand<T> m_selWindowsCommand;
	};

	// 执行
	template<typename T>
	inline bool CurWindowSelectCommand<T>::Do()
	{
		bool flag = m_curWinCommand.Do();
		if (flag)
		{
			flag = m_selWindowsCommand.Do();
		}
		return flag;
	}

	// 取消执行
	template<typename T>
	inline bool CurWindowSelectCommand<T>::Undo()
	{
		bool flag = m_selWindowsCommand.Undo();
		if (flag)
		{
			flag = m_curWinCommand.Undo();
		}
		return flag;
	}
}

#endif	// CUR_WINDOW_SELECT_COMMAND_H