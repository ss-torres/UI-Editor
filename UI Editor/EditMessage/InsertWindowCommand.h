#ifndef INSERT_WINDOW_COMMAND_H
#define INSERT_WINDOW_COMMAND_H

/*
 * 文件名：InsertWindowCommand
 * 作用：添加一个窗口对象
 * 说明：如果子窗口被添加到父窗口中，则父窗口负责管理子窗口的删除，
 * 否则该命令负责子窗口的删除，判断条件hasParent
 */

#include <wx/cmdproc.h>
#include <stdexcept>
#include "../EditorWindow/EditorWindowInterface.h"

namespace Command
{
	class ChangeManager;

	const size_t INSERT_DEF_IDX = -1;		// 表示插入到最后

	template <typename T>
	class InsertWindowCommand : public wxCommand
	{
	public:
		InsertWindowCommand(T winMgr, EditorAbstractWindow* insertWnd, EditorAbstractWindow* parentWnd)
			: m_winMgr(winMgr), m_insertWnd(insertWnd), m_parentWnd(parentWnd)
		{
			if (winMgr == NULL || insertWnd == NULL || parentWnd == NULL)
			{
				throw std::invalid_argument(__func__ + std::string(": winMgr, insertWnd and parentWnd shouldn't be nullptr"));
			}
		}
		~InsertWindowCommand() override;

		// 设置插入的序号
		void setInsertIdx(size_t idx) { m_idx = idx; }
		// 获取插入的序号
		size_t getInsertIdx() const { return m_idx; }

		// 是否可以回退
		bool CanUndo() const override { return true; }
		// 执行
		bool Do() override;
		// 回退
		bool Undo() override;

	protected:
		// 用来记录创建的窗口
		EditorAbstractWindow* m_insertWnd = nullptr;
		// 用来记录插入的父窗口
		EditorAbstractWindow* m_parentWnd = nullptr;
		// 插入的序号
		size_t m_idx = INSERT_DEF_IDX;
		// 操作的窗口类
		T m_winMgr;
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
		return m_winMgr->removeWindow(m_insertWnd);
	}


	template <typename T>
	InsertWindowCommand<T>::~InsertWindowCommand()
	{
		// 析构函数，如果插入的窗口为独立窗口，则可以删除
		if (!m_insertWnd->hasParent())
		{
			delete m_insertWnd;
			m_insertWnd = nullptr;
		}
	}
}

#endif	// INSERT_WINDOW_COMMAND_H
