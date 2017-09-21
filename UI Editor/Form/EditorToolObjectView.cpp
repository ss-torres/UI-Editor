#include "EditorToolObjectView.h"

EditorToolObjectView::EditorToolObjectView(wxAuiManager &manager, wxWindow * parent, int direction, const wxString & paneName)
	: EditorToolWindow(manager, parent, direction, paneName)
{
	initSubWindows();
}

EditorToolObjectView::~EditorToolObjectView()
{

}

// 初始化子窗口
void EditorToolObjectView::initSubWindows()
{
	m_objectView = new wxTreeListCtrl(getBench(), wxID_ANY, wxPoint(0, 0), wxSize(300, 600), wxTL_DEFAULT_STYLE | wxTL_CHECKBOX);
	m_objectView->AppendColumn(wxS("object"));
	m_objectView->AppendColumn(wxS("class"));
	wxTreeListItem item = m_objectView->AppendItem(m_objectView->GetRootItem(), wxS("background"));
	m_objectView->SetItemText(item, 1, wxS("EditorLabel"));

	wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);
	boxSizer->Add(m_objectView, 1, wxALL, 5);
	getBench()->SetSizerAndFit(boxSizer);
}

