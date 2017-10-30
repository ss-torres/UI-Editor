#ifndef CURRENT_WINDOW_COMMAND_H
#define CURRENT_WINDOW_COMMAND_H

/*
 * 文件名：CurrentWindowCommand
 * 作用：设置当前选中的窗口
 * 说明：主编辑区始终会存在一个当前选中的窗口，该窗口要么是用户创建的窗口，要么是管理窗口，
 * 其中管理窗口不可以编辑属性
 */

#include <wx/cmdproc.h>
#include <stdexcept>
#include "../EditorWindow/EditorWindowInterface.h"

namespace Command
{
	template <typename T>
	class CurrentWindowCommand : public wxCommand
	{
	public:
		CurrentWindowCommand(T winMgr, EditorAbstractWindow* lastCurWnd, EditorAbstractWindow* newCurWnd)
			: m_winMgr(winMgr), m_lastCurWnd(lastCurWnd), m_newCurWnd(newCurWnd)
		{
			if (winMgr == nullptr || lastCurWnd == nullptr || newCurWnd == nullptr)
			{
				throw std::invalid_argument(__func__ + std::string(": winMgr, lastCurWnd and newCurWnd shouldn't be nullptr"));
			}
		}
		~CurrentWindowCommand() { }

		// 是否可以回退
		bool CanUndo() const override { return true; }

		// 重构执行函数
		bool Do() override;
		// 重构取消函数
		bool Undo() override;

	private:
		T m_winMgr;
		EditorAbstractWindow* m_lastCurWnd = nullptr;
		EditorAbstractWindow* m_newCurWnd = nullptr;
	};

	template <typename T>
	bool CurrentWindowCommand<T>::Do()
	{
		m_winMgr->changeSelectWnd(m_lastCurWnd, m_newCurWnd);
		return true;
	}

	template <typename T>
	bool CurrentWindowCommand<T>::Undo()
	{
		m_winMgr->changeSelectWnd(m_newCurWnd, m_lastCurWnd);
		return true;
	}
}

#endif	// CURRENT_WINDOW_COMMAND_H