#include <wx/image.h>
#include "FormFactory.h"
#include "FormWidgetSelect.h"
#include "FormObjectView.h"
#include "FormPropertyEditor.h"
#include "FormWorkArea.h"
#include "../ErrorHandle/ErrorHandle.h"

FormFactory::FormFactory()
{
	// 初始化贴图加载
	if (wxImage::FindHandler(wxBITMAP_TYPE_PNG) == nullptr)
	{
		wxImage::AddHandler(new wxPNGHandler);
	}
}

FormFactory::~FormFactory()
{
	wxImage::CleanUpHandlers();
}

FormToolWindow * FormFactory::createToolWindow(ToolWindowType type, wxAuiManager &manager, wxWindow * parent,
	int direction, const wxString & paneName) const
{
	switch (type)
	{
	case ToolWindowType::WidgetSelect:
		return new FormWidgetSelect(manager, parent, direction, paneName);

	case ToolWindowType::ObjectView:
		return new FormObjectView(manager, parent, direction, paneName);

	case ToolWindowType::PropertyEditor:
		return new FormPropertyEditor(manager, parent, direction, paneName);

	default:
		throw ExtraExcept::unexpected_situation("createToolWindow'default is a branch that should not be invoked.");
		break;
	}
}

// 销毁对应的ToolWindow
void FormFactory::destroyToolWindow(FormToolWindow* &toolWnd) const
{
	delete toolWnd;
	toolWnd = NULL;
}

// 创建主工作区
FormWorkArea * FormFactory::createWorkArea(wxMDIParentFrame* parent,
	const wxString& captionName, const wxPoint& position, const wxSize& size) const
{
	return new FormWorkArea(parent, captionName, position, size);
}

// 销毁主工作区
void FormFactory::destroyWorkArea(FormWorkArea* &workArea) const
{
	delete workArea;
	workArea = NULL;
}
