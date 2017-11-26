#ifndef CURRENT_WINDOW_COMMAND_H
#define CURRENT_WINDOW_COMMAND_H

/*
 * 文件名：CurrentWindowCommand
 * 作用：设置当前编辑的控件
 * 说明：主编辑区始终会存在一个当前编辑的控件，该控件要么是用户创建的控件，要么是管理控件，
 * 其中管理控件不可以编辑属性
 */

#include <stdexcept>
#include <wx/cmdproc.h>
#include "../EditorWindow/EditorWindowInterface.h"

namespace Command
{
	template <typename T>
	class CurrentWindowCommand : public wxCommand
	{
	public:
		CurrentWindowCommand(T mgr, EditorAbstractWindow* newCurWnd)
			: wxCommand(true),
			m_mgr(mgr), m_toSetCurWnd(newCurWnd)
		{
			if (mgr == nullptr || newCurWnd == nullptr)
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
		// 用来记录将被设置为当前编辑的窗口
		EditorAbstractWindow* m_toSetCurWnd = nullptr;
	};

	template <typename T>
	bool CurrentWindowCommand<T>::Do()
	{
		return m_mgr->changeCurrentWnd(m_toSetCurWnd);
	}

	template <typename T>
	bool CurrentWindowCommand<T>::Undo()
	{
		return m_mgr->changeCurrentWnd(m_toSetCurWnd);
	}
}

#endif	// CURRENT_WINDOW_COMMAND_H