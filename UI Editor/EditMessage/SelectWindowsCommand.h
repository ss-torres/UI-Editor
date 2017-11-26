#ifndef SELECT_WINDOWS_COMMAND_H
#define SELECT_WINDOWS_COMMAND_H

/*
 * 文件名：SelectWindowsCommand
 * 作用：设置当前选中的控件
 * 说明：主编辑区始终会存在一个或者多个当前选中的控件，如果只存在一个当前选择控件，那么该控件为当前编辑控件，
 * 该控件要么是用户创建的控件，要么是管理控件，其中管理控件不可以编辑属性
 */

#include <unordered_set>
#include <stdexcept>
#include <wx/cmdproc.h>
#include "../EditorWindow/EditorWindowInterface.h"

namespace Command
{
	template <typename T>
	class SelectWindowsCommand : public wxCommand
	{
	public:
		SelectWindowsCommand(T mgr, std::unordered_set<ID_TYPE> selectIds)
			: m_mgr(mgr), m_selectIds(std::move(selectIds))
		{
			if (mgr == nullptr)
			{
				throw std::invalid_argument(__func__ + std::string(": winMgr shouldn't be nullptr"));
			}
		}
		~SelectWindowsCommand() override {}

		// 重构执行函数
		bool Do() override;
		// 重构取消执行函数
		bool Undo() override;


	private:
		T m_mgr;
		// 设置选中的所有控件ID
		std::unordered_set<ID_TYPE> m_selectIds;
	};


	// 重构执行函数
	template<typename T>
	inline bool SelectWindowsCommand<T>::Do()
	{
		return m_mgr->changeSelectWnds(m_selectIds);
	}

	// 重构取消执行函数
	template<typename T>
	inline bool SelectWindowsCommand<T>::Undo()
	{
		return m_mgr->changeSelectWnds(m_selectIds);
	}
}

#endif	// SELECT_WINDOWS_COMMAND_H