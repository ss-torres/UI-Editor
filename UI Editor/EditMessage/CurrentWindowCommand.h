#ifndef CURRENT_WINDOW_COMMAND_H
#define CURRENT_WINDOW_COMMAND_H

/*
 * 文件名：CurrentWindowCommand
 * 作用：设置当前选中的控件
 * 说明：主编辑区始终会存在一个当前选中的控件，该控件要么是用户创建的控件，要么是管理控件，
 * 其中管理控件不可以编辑属性
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
		CurrentWindowCommand(T mgr, EditorAbstractWindow* lastCurWnd, EditorAbstractWindow* newCurWnd)
			: wxCommand(true),
			m_mgr(mgr), m_lastCurWnd(lastCurWnd), m_newCurWnd(newCurWnd)
		{
			if (mgr == nullptr || lastCurWnd == nullptr || newCurWnd == nullptr)
			{
				throw std::invalid_argument(__func__ + std::string(": winMgr, lastCurWnd and newCurWnd shouldn't be nullptr"));
			}
		}
		~CurrentWindowCommand() { }

		// 重构执行函数
		bool Do() override;
		// 重构取消执行函数
		bool Undo() override;

	private:
		T m_mgr;
		EditorAbstractWindow* m_lastCurWnd = nullptr;
		EditorAbstractWindow* m_newCurWnd = nullptr;
	};

	template <typename T>
	bool CurrentWindowCommand<T>::Do()
	{
		m_mgr->changeSelectWnd(m_lastCurWnd, m_newCurWnd);
		return true;
	}

	template <typename T>
	bool CurrentWindowCommand<T>::Undo()
	{
		m_mgr->changeSelectWnd(m_newCurWnd, m_lastCurWnd);
		return true;
	}
}

#endif	// CURRENT_WINDOW_COMMAND_H