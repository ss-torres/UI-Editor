#ifndef INSERT_WINDOW_COMMAND_H
#define INSERT_WINDOW_COMMAND_H

/*
 * 文件名：InsertWindowCommand
 * 作用：添加一个窗口对象
 */

#include <wx/cmdproc.h>
#include "../EditorWindow/WindowInterface.h"

namespace Command
{
	template <typename T>
	class InsertWindowCommand : public wxCommand
	{
	public:
		InsertWindowCommand(T* winMgr) : m_winMgr(winMgr) {}
		InsertWindowCommand(AbstractEditorWindow* insertWnd, ID_TYPE id)
			: m_insertWnd(insertWnd), m_id(id) {}
		~InsertWindowCommand() override {}

		// 是否可以回退
		bool CanUndo() const override { return true; }
		// 执行
		bool Do() override;
		// 回退
		bool Undo() override;

	protected:
		// 用来记录创建的窗口
		AbstractEditorWindow* m_insertWnd = nullptr;
		// 用来记录窗口ID，Do时，表示父窗口的ID，Undo的时候，用来记录子窗口的ID
		ID_TYPE m_id = -1;
		// 操作的窗口类
		T* m_winMgr = nullptr;
	};

	template <typename T>
	inline bool InsertWindowCommand<T>::Do()
	{
		m_winMgr->pushBackWindow(m_id, m_insertWnd);
		m_id = m_insertWnd->getId();
	}

	template <typename T>
	inline bool InsertWindowCommand<T>::Undo()
	{
		return false;
	}
}

#endif	// INSERT_WINDOW_COMMAND_H
