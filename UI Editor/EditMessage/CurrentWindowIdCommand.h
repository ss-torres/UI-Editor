#ifndef CURRENT_WINDOW_ID_COMMAND_H
#define CURRENT_WINDOW_ID_COMMAND_H

/*
* 文件名：CurrentWindowIdCommand
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
	class CurrentWindowIdCommand : public wxCommand
	{
	public:
		CurrentWindowIdCommand(T mgr, ID_TYPE newCurWndId)
			: wxCommand(true),
			m_mgr(mgr), m_toSetCurWndId(newCurWndId)
		{
			if (mgr == nullptr)
			{
				throw std::invalid_argument(__func__ + std::string(": winMgr shouldn't be nullptr"));
			}
		}
		~CurrentWindowIdCommand() { }

		// 重构执行函数
		bool Do() override;
		// 重构取消执行函数
		bool Undo() override;

	private:
		T m_mgr;
		// 用来记录将被设置为当前编辑的窗口
		ID_TYPE m_toSetCurWndId;
	};

	template <typename T>
	bool CurrentWindowIdCommand<T>::Do()
	{
		return m_mgr->changeCurrentWnd(m_toSetCurWndId);
	}

	template <typename T>
	bool CurrentWindowIdCommand<T>::Undo()
	{
		return m_mgr->changeCurrentWnd(m_toSetCurWndId);
	}
}

#endif	// CURRENT_WINDOW_ID_COMMAND_H