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
		flag = flag && m_objectView->addWindowItem(parentWnd->getId(), insertWnd->getId(),
			insertWnd->getWinAttr(OBJECT_NAME).As<wxString>(), insertWnd->getWindowClassName());
		return flag;
	}

	// 插入一个控件
	bool ChangeManager::insertWindow(EditorAbstractWindow * parentWnd, size_t idx, EditorAbstractWindow * insertWnd)
	{
		// 修改主工作区
		bool flag = m_workArea->insertWindow(parentWnd, idx, insertWnd);
		return flag;
	}

	// 移除一个控件
	bool ChangeManager::removeWindow(EditorAbstractWindow * removeWnd)
	{
		// 修改主工作区
		bool flag = m_workArea->removeWindow(removeWnd);
		return flag;
	}

	// 修改当前选中的控件
	void ChangeManager::changeSelectWnd(EditorAbstractWindow * lastCurWnd, EditorAbstractWindow * newCurWnd)
	{
		// 修改主工作区
		m_workArea->setCurrentWindow(newCurWnd);
		// 显示对应类型的属性编辑框
		m_propertyEditor->resetAttrs(newCurWnd->getWindowClassName());
		// 先设置对应控件属性的默认值
		const auto& winAttrDefValues = m_winAttrMgr->getWinDefValues(newCurWnd->getWindowClassName());
		m_propertyEditor->updateAttrs(winAttrDefValues);
		// 设置对应控件的修改的属性值
		m_propertyEditor->updateAttrs(newCurWnd->getWinAttrs());
		// 修改对象查看中当前选中项
		m_objectView->setCurSelect(newCurWnd->getId());
	}

	// 修改当前选中的控件属性，将原属性保存到传入的参数中
	void ChangeManager::changeSelectWndAttr(const wxString& attrName, wxAny& toSetValue)
	{
		auto curSelectWnd = m_workArea->getCurrentWindow();
		wxAny origValue = curSelectWnd->getWinAttr(attrName);
		// 在这里不判断新旧值是否相同，因为编辑过程中已经判断
		curSelectWnd->updateWinAttr(attrName, toSetValue);
		// 修改对象查看器的显示
		m_objectView->changeWinAttr(curSelectWnd->getId(), attrName, toSetValue);
		// 将之前的值复制给
		toSetValue = origValue;
	}
}