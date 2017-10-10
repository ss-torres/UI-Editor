#include "ChangeManager.h"
#include "../Form/EditorWorkArea.h"
#include "../Form/EditorToolObjectView.h"
#include "../Form/EditorToolPropertyEditor.h"
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

	// 添加一个窗口
	bool ChangeManager::pushBackWindow(AbstractEditorWindow * parentWnd, AbstractEditorWindow * insertWnd)
	{
		// 修改主工作区
		bool flag = m_workArea->pushBackWindow(parentWnd, insertWnd);
		flag = flag && m_objectView->addWindowItem(parentWnd->getId(), insertWnd->getId(),
			insertWnd->getWindowObjectName(), insertWnd->getWindowClassName());
		return flag;
	}

	// 插入一个窗口
	bool ChangeManager::insertWindow(AbstractEditorWindow * parentWnd, size_t idx, AbstractEditorWindow * insertWnd)
	{
		// 修改主工作区
		bool flag = m_workArea->insertWindow(parentWnd, idx, insertWnd);
		return flag;
	}

	// 移除一个窗口
	bool ChangeManager::removeWindow(AbstractEditorWindow * removeWnd)
	{
		// 修改主工作区
		bool flag = m_workArea->removeWindow(removeWnd);
		return flag;
	}

	// 修改当前选中的窗口
	void ChangeManager::changeSelectWnd(AbstractEditorWindow * lastCurWnd, AbstractEditorWindow * newCurWnd)
	{
		// 修改主工作区
		m_workArea->setCurrentWindow(newCurWnd);
		// 修改属性编辑框
		m_propertyEditor->resetAttrs(newCurWnd->getWindowClassName());
		// 先设置对应窗口属性的默认值
		const auto& winAttrDefValues = m_winAttrMgr->getWinDefValues(newCurWnd->getWindowClassName());
		m_propertyEditor->updateAttrs(winAttrDefValues);
		// 设置对应窗口的修改的属性值
		m_propertyEditor->updateAttrs(newCurWnd->getWinAttrs());
		// 修改对象查看中当前选中项

	}
}