#ifndef INSERT_WINDOW_COMMAND_H
#define INSERT_WINDOW_COMMAND_H

/*
 * 文件名：InsertWindowCommand
 * 作用：添加一个控件对象
 * 说明：如果子控件被添加到父控件中，则父控件负责管理子控件的删除，
 * 否则该命令负责子控件的删除，判断条件hasParent
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
		InsertWindowCommand(T mgr, EditorAbstractWindow* insertWnd, EditorAbstractWindow* parentWnd)
			: wxCommand(true),
			m_mgr(mgr), m_insertWnd(insertWnd), m_parentWnd(parentWnd)
		{
			if (mgr == NULL || insertWnd == NULL || parentWnd == NULL)
			{
				throw std::invalid_argument(__func__ + std::string(": winMgr, insertWnd and parentWnd shouldn't be nullptr"));
			}
		}
		~InsertWindowCommand() override;

		// 设置插入的序号
		void setInsertIdx(size_t idx) { m_idx = idx; }
		// 获取插入的序号
		size_t getInsertIdx() const { return m_idx; }

		// 执行
		bool Do() override;
		// 回退
		bool Undo() override;

	protected:
		// 用来记录创建的控件
		EditorAbstractWindow* m_insertWnd = nullptr;
		// 用来记录插入的父控件
		EditorAbstractWindow* m_parentWnd = nullptr;
		// 插入的序号
		size_t m_idx = INSERT_DEF_IDX;
		// 操作的管理类
		T m_mgr;
	};

	template <typename T>
	inline bool InsertWindowCommand<T>::Do()
	{
		if (m_idx == INSERT_DEF_IDX)
		{
			return m_mgr->pushBackWindow(m_parentWnd, m_insertWnd);
		}
		else
		{
			return m_mgr->insertWindow(m_parentWnd, m_idx, m_insertWnd);
		}
	}

	template <typename T>
	inline bool InsertWindowCommand<T>::Undo()
	{
		return m_mgr->removeWindow(m_insertWnd);
	}


	template <typename T>
	InsertWindowCommand<T>::~InsertWindowCommand()
	{
		// 析构函数，如果插入的控件为独立控件，则可以删除
		if (!m_insertWnd->hasParent())
		{
			delete m_insertWnd;
			m_insertWnd = nullptr;
		}
	}
}

#endif	// INSERT_WINDOW_COMMAND_H
