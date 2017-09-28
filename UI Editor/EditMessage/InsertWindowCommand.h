#ifndef INSERT_WINDOW_COMMAND_H
#define INSERT_WINDOW_COMMAND_H

/*
 * 文件名：InsertWindowCommand
 * 作用：添加一个窗口对象
 */

#include <wx/cmdproc.h>
#include <stdexcept>
#include "../EditorWindow/WindowInterface.h"

namespace Command
{
	const int INSERT_POS_DEF_X = 5;
	const int INSERT_POS_DEF_Y = 5;
	const int INSERT_DEF_IDX = -1;		// 表示插入到最后

	template <typename T>
	class InsertWindowCommand : public wxCommand
	{
	public:
		InsertWindowCommand(T* winMgr, AbstractEditorWindow* insertWnd, AbstractEditorWindow* parentWnd)
			: m_winMgr(winMgr), m_insertWnd(insertWnd), m_parentWnd(parentWnd)
		{
			if (winMgr == NULL || insertWnd == NULL || parentWnd == NULL)
			{
				throw std::invalid_argument("InsertWindowCommand: winMgr, insertWnd and parentWnd shouldn't be nullptr");
			}
		}
		~InsertWindowCommand() override {}

		// 设置插入的位置
		void setInsertPos(int x, int y) { m_reX = x; m_relY = y; }
		// 设置插入的序号
		void setInsertIdx(size_t idx) { m_idx = idx; }

		// 是否可以回退
		bool CanUndo() const override { return true; }
		// 执行
		bool Do() override;
		// 回退
		bool Undo() override;

	protected:
		// 用来记录创建的窗口
		AbstractEditorWindow* m_insertWnd = nullptr;
		// 用来记录插入的父窗口
		AbstractEditorWindow* m_parentWnd = nullptr;
		// 插入的位置
		int m_relX = INSERT_POS_DEF_X;
		// 插入的位置
		int m_relY = INSERT_POS_DEF_Y;
		// 插入的序号
		size_t m_idx = INSERT_DEF_IDX;
		// 操作的窗口类
		T* m_winMgr = nullptr;
	};

	template <typename T>
	inline bool InsertWindowCommand<T>::Do()
	{
		if (m_idx == INSERT_DEF_IDX)
		{
			return m_winMgr->pushBackWindow(m_parentWnd, m_insertWnd);
		}
		else
		{
			return m_winMgr->insertWindow(m_parentWnd, m_idx, m_insertWnd);
		}
	}

	template <typename T>
	inline bool InsertWindowCommand<T>::Undo()
	{
		m_winMgr->removeWindow(m_insertWnd);
	}
}

#endif	// INSERT_WINDOW_COMMAND_H
