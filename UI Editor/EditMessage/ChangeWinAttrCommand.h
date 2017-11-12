#ifndef CHANGE_WIN_ATTR_COMMAND_H
#define CHANGE_WIN_ATTR_COMMAND_H

/*
 * 文件名：ChangeWinAttrCommand
 * 作用：修改当前窗口(EditorAbstractWindow系列)的属性值
 * 说明：将当前窗口的属性值修改为newValue，同时将之前的值保存，用于实现Undo操作
 */

#include <wx/cmdproc.h>
#include <stdexcept>
#include "../EditorWindow/EditorWindowInterface.h"

namespace Command
{
	template <typename T>
	class ChangeWinAttrCommand : public wxCommand
	{
	public:
		ChangeWinAttrCommand(T mgr, wxString attrName, wxAny newValue)
			: wxCommand(true),
			m_mgr(mgr),
			m_attrName(attrName),
			m_toSetValue(newValue)
		{
			if (mgr == nullptr)
			{
				throw std::invalid_argument(__func__ + std::string(": winMgr, lastCurWnd and newCurWnd shouldn't be nullptr"));
			}
		}
		~ChangeWinAttrCommand() {}

		// 重构执行函数
		bool Do() override;
		// 重构取消执行函数
		bool Undo() override;

	private:
		T m_mgr;
		// 当前窗口要被设置的属性
		wxString m_attrName;
		// 当前窗口要被设置的值
		wxAny m_toSetValue;
	};

	// 重构执行函数
	template<typename T>
	inline bool ChangeWinAttrCommand<T>::Do()
	{
		m_mgr->changeSelectWndAttr(m_attrName, m_toSetValue);
		return true;
	}

	// 重构取消执行函数
	template<typename T>
	inline bool ChangeWinAttrCommand<T>::Undo()
	{
		m_mgr->changeSelectWndAttr(m_attrName, m_toSetValue);
		return true;
	}
}

#endif	// CHANGE_WIN_ATTR_COMMAND_H