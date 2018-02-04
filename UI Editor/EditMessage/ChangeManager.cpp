#include "ChangeManager.h"
#include "WinAttrAndNameProtocol.h"
#include "../Form/FormWorkArea.h"
#include "../Form/FormObjectView.h"
#include "../Form/FormPropertyEditor.h"
#include "../Settings/WindowAttributeManager.h"

namespace Command
{
	const int MAX_COMMAND = 50;

	ChangeManager::ChangeManager()
		: m_commandStack(MAX_COMMAND)
	{
		
	}

	ChangeManager::~ChangeManager()
	{

	}

	ChangeManager* ChangeManager::s_changeManager = nullptr;

	// 添加一个控件
	bool ChangeManager::pushBackWindow(EditorAbstractWindow * parentWnd, EditorAbstractWindow * insertWnd)
	{
		// 修改主工作区
		bool flag = m_workArea->pushBackWindow(parentWnd, insertWnd);
		// 修改对象查看器
		if (flag)
		{
			flag = m_objectView->addWindowItem(parentWnd->getId(), insertWnd->getId(),
				insertWnd->getWinAttr(OBJECT_NAME).As<wxString>(), insertWnd->getWindowClassName());
		}

		return flag;
	}

	// 插入一个控件
	bool ChangeManager::insertWindow(EditorAbstractWindow * parentWnd, size_t idx, EditorAbstractWindow * insertWnd)
	{
		// 修改主工作区
		bool flag = m_workArea->insertWindow(parentWnd, idx, insertWnd);
		// 修改对象查看器
		if (flag)
		{

		}
		return flag;
	}

	// 移除一个控件
	bool ChangeManager::removeWindow(EditorAbstractWindow * removeWnd)
	{
		// 修改主工作区
		bool flag = m_workArea->removeWindow(removeWnd);
		// 修改对象查看器
		if (flag)
		{
			flag = m_objectView->delWindowItem(removeWnd->getId());
		}
		return flag;
	}

	// 修改当前编辑的控件，将之前的编辑控件保存到传参中
	bool ChangeManager::changeCurrentWnd(EditorAbstractWindow* &toSetCurWnd)
	{
		auto newCurWnd = toSetCurWnd;
		toSetCurWnd = m_workArea->getCurrentWindow();
		// 判断是否相同
		if (newCurWnd == toSetCurWnd)
		{
			return false;
		}
		// 修改主工作区
		m_workArea->setCurrentWindow(newCurWnd);
		// 对属性编辑器和对象查看的修改
		changeCurrentWndImpl(newCurWnd);

		return true;
	}

	// 修改当前编辑的控件，将之前的编辑控件ID保存到传参中
	bool ChangeManager::changeCurrentWnd(ID_TYPE &toSetCurWndId)
	{
		auto newCurWndId = toSetCurWndId;
		toSetCurWndId = m_workArea->getCurrentWindowId();
		// 判断是否相同
		if (newCurWndId == toSetCurWndId)
		{
			return false;
		}
		// 修改主工作区
		m_workArea->setCurrentWindowId(newCurWndId);
		// 对主工作区以外的工作区进行修改
		changeCurrentWndImpl(m_workArea->getCurrentWindow());

		return true;
	}

	// 修改当前编辑的控件属性，将原属性保存到传入的参数中
	void ChangeManager::changeSelectWndAttr(const wxString& attrName, wxAny& toSetValue)
	{
		auto curSelectWnd = m_workArea->getCurrentWindow();
		auto origValue = curSelectWnd->getWinAttr(attrName);
		// 如果窗口中没有属性
		if (origValue.IsNull())
		{
			// 如果在窗口属性中不存在，则使用默认属性
			auto attrValues = WindowAttributeManager::instance()->getWinDefValues(curSelectWnd->getWindowClassName());
			
			auto it = attrValues.find(attrName);
			if (it == attrValues.cend())
			{
				// 按照逻辑不应该出现的情况
				throw ExtraExcept::unexpected_situation("ChangeManager::changeSelectWndAttr can't find " + attrName.ToStdString());
			}
			else
			{
				origValue = it->second;
			}
		}
		// 在这里不判断新旧值是否相同，因为编辑过程中已经判断
		curSelectWnd->updateWinAttr(attrName, toSetValue);
		// 修改对象查看器的显示
		m_objectView->changeWinAttr(curSelectWnd->getId(), attrName, toSetValue);
		// 将之前的值复制给
		toSetValue = origValue;
	}

	// 修改当前选中的控件，将原来选中的所有控件ID保存
	bool ChangeManager::changeSelectWnds(std::unordered_set<ID_TYPE>& toSelectIds)
	{
		// 修改主工作区，修改完之后，toSelectIds指向的是之前选中的所有控件ID
		using std::swap;
		swap(toSelectIds, m_workArea->getSelectWndIds());
		// 修改对象查看中的选中项
		m_objectView->setSelections(m_workArea->getSelectWndIds());

		return true;
	}

	// 修改当前编辑窗口时，对主工作区以外的工作区进行修改
	void ChangeManager::changeCurrentWndImpl(EditorAbstractWindow * toSetCurWnd)
	{
		// 显示对应类型的属性编辑框
		if (!toSetCurWnd->isAttrEditable())
		{
			m_propertyEditor->clearAttrs();
		}
		else
		{
			m_propertyEditor->resetAttrs(toSetCurWnd->getWindowClassName());

			const auto& winAttrDefValues = WindowAttributeManager::instance()->getWinDefValues(toSetCurWnd->getWindowClassName());
			const auto& curAttrValues = toSetCurWnd->getWinAttrs();
			// 先设置对应控件属性的默认值
			if (winAttrDefValues.size() != curAttrValues.size())
			{
				m_propertyEditor->updateAttrs(winAttrDefValues);
			}
			// 设置对应控件的修改的属性值
			m_propertyEditor->updateAttrs(curAttrValues);
		}
	}
}