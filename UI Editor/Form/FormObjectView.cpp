#include "FormObjectView.h"
#include "FormObjectViewDefine.h"

FormObjectView::FormObjectView(wxAuiManager &manager, wxWindow * parent, int direction, const wxString & paneName)
	: FormToolWindow(manager, parent, direction, paneName)
{
	initSubWindows();
}

FormObjectView::~FormObjectView()
{

}

// 设置root节点对应的控件ID
void FormObjectView::setRootWindowId(ID_TYPE id)
{
	wxTreeListItem rootItem = m_objectView->GetRootItem();
	m_idToItems[id] = rootItem;
}

// 添加一个子节点用来标识一个控件
bool FormObjectView::addWindowItem(ID_TYPE parentId, ID_TYPE childId, const wxString &objectName, const wxString & winTypeName)
{
	wxTreeListItem parentItem = m_idToItems.at(parentId);
	wxTreeListItem childItem = m_objectView->AppendItem(parentItem, objectName, wxTreeListCtrl::NO_IMAGE, wxTreeListCtrl::NO_IMAGE, new EditorWindowID(childId));
	m_objectView->SetItemText(childItem, 1, winTypeName);
	m_idToItems[childId] = childItem;
	return true;
}

// 设置当前选中对象，会取消之前所有的选中
void FormObjectView::setCurSelect(ID_TYPE selectId) const
{
	m_objectView->UnselectAll();
	m_objectView->Select(m_idToItems.at(selectId));
}

// 添加选中对象
void FormObjectView::addSelect(ID_TYPE selectId) const
{
	m_objectView->Select(m_idToItems.at(selectId));
}

// 取消选中对象
void FormObjectView::unSelect(ID_TYPE unSelectId) const
{
	m_objectView->Unselect(m_idToItems.at(unSelectId));
}

// 获取当前所有选中
std::vector<ID_TYPE> FormObjectView::getSelections() const
{
	std::vector<ID_TYPE> selections;
	wxTreeListItems items;
	m_objectView->GetSelections(items);
	for (const auto& item : items)
	{
		auto data = dynamic_cast<EditorWindowID *>(m_objectView->GetItemData(item));
		selections.push_back(data->getEditorWinId());
	}

	return selections;
}

// 修改对象编辑器中的显示，当前只设计修改对象
void FormObjectView::changeWinAttr(ID_TYPE changeId, const wxString &attrName, const wxAny &toSetValue) const
{
	if (attrName == OBJECT_NAME)
	{
		wxTreeListItem item = m_idToItems.at(changeId);
		m_objectView->SetItemText(item, 0, toSetValue.As<wxString>());
	}
}

// 初始化子窗口
void FormObjectView::initSubWindows()
{
	m_objectView = new wxTreeListCtrl(getBench(), wxID_ANY, wxPoint(0, 0), wxSize(300, 600), wxTL_DEFAULT_STYLE | wxTL_CHECKBOX);
	m_objectView->AppendColumn(wxS("object"));
	m_objectView->AppendColumn(wxS("class"));
	//wxTreeListItem item = m_objectView->AppendItem(m_objectView->GetRootItem(), wxS("background"));
	//m_objectView->SetItemText(item, 1, wxS("EditorLabel"));

	wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);
	boxSizer->Add(m_objectView, 1, wxALL, 5);
	getBench()->SetSizerAndFit(boxSizer);
}

