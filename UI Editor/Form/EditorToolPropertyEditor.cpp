#include "EditorToolPropertyEditor.h"

#include <wx/propgrid/propgrid.h>
#include "../Property/ImageProperty.h"

EditorToolPropertyEditor::EditorToolPropertyEditor(wxAuiManager & manager, wxWindow * parent, int direction, const wxString & paneName)
	: EditorToolWindow(manager, parent, direction, paneName)
{
	initSubWindows();
}

EditorToolPropertyEditor::~EditorToolPropertyEditor()
{
}

// 初始化编辑属性窗口
void EditorToolPropertyEditor::initSubWindows()
{
	m_propertyGrid = new wxPropertyGrid(getBench(), wxID_ANY, wxPoint(0, 0), wxSize(300, 600));
	ImageProperty* imgProp = new ImageProperty("NormalImage", wxPG_LABEL);
	m_propertyGrid->Append(imgProp);

	wxBoxSizer* vBoxSizer = new wxBoxSizer(wxVERTICAL);
	vBoxSizer->Add(m_propertyGrid, 1, wxALL, 5);
	getBench()->SetSizerAndFit(vBoxSizer);
}
