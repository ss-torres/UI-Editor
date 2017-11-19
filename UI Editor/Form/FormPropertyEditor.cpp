#include <wx/propgrid/propgrid.h>
#include <wx/log.h>
#include "FormPropertyEditor.h"
#include "../Property/ImageProperty.h"
#include "../ErrorHandle/ErrorHandle.h"
#include "../EditMessage/CommandFactory.h"
#include "../EditMessage/ChangeManager.h"

const int PROPERTY_EDITOR_WIDTH = 300;
const int PROPERTY_EDITOR_HEIGHT = 600;

FormPropertyEditor::FormPropertyEditor(wxAuiManager & manager, wxWindow * parent, int direction, const wxString & paneName)
	: FormToolWindow(manager, parent, direction, paneName)
{
	
}

FormPropertyEditor::~FormPropertyEditor()
{
}

// 显示对应类型的编辑框
void FormPropertyEditor::resetAttrs(const wxString& winTypeName)
{
	// 如果当前打开的和之前的一致，则不操作
	if (winTypeName == m_curEditWinType)
	{
		return;
	}
	// 显示对应控件的编辑器
	m_curPropertyGrid->Hide();
	auto it = m_propertyGrids.find(winTypeName);
	if (it != m_propertyGrids.cend())
	{
		it->second->Show();
		m_curPropertyGrid = it->second;
		m_curEditWinType = winTypeName;
		m_sizer->Layout();

		return;
	}

	// 没有查找到，异常
	throw ExtraExcept::unexpected_situation("FormPropertyEditor::resetAttrs: can't find winTypeName in m_propertyGrids");
	return;
}

// 设置属性列表的值
void FormPropertyEditor::updateAttrs(const std::map<wxString, wxAny>& propAttrs)
{
	const char* const PRE_FUNC_NAME = "FormPropertyEditor::resetAttrs";
	const char* const CUR_FUNC_NAME = "FormPropertyEditor::updateAttrs";

	if (m_curPropertyGrid == nullptr)
	{
		throw ExtraExcept::wrong_invoke_seq(PRE_FUNC_NAME, CUR_FUNC_NAME);
	}

	for (const auto& attr : propAttrs)
	{
		auto prop = m_curPropertyGrid->GetProperty(attr.first);
		if (prop == nullptr)
		{
			throw ExtraExcept::wrong_invoke_seq(PRE_FUNC_NAME, CUR_FUNC_NAME);
		}
		// 修改属性值
		prop->SetValue(attr.second);
	}
	// 刷新属性列表
	m_curPropertyGrid->Update();
}

// 用来处理属性改变
void FormPropertyEditor::OnPropertyGridChanged(wxPropertyGridEvent & event)
{
	wxPGProperty* prop = event.GetProperty();

	if (prop->GetGrid() != m_curPropertyGrid)
	{
		throw ExtraExcept::unexpected_situation("The wxPGProperty changed is not in current wxPropertyGrid");
	}
	using namespace Command;
	auto changeWinAttrCmd = CommandFactory::instance()->createChangeWinAttrCommand(
		event.GetPropertyName(), event.GetPropertyValue());
	ChangeManager::instance()->getCommandStack().Submit(changeWinAttrCmd);
}

// 初始化编辑属性窗口
void FormPropertyEditor::initSubWindows(const std::vector<wxString>& windowTypes)
{
	wxBoxSizer* vBoxSizer = new wxBoxSizer(wxVERTICAL);
	m_sizer = vBoxSizer;

	for (auto const& winType : windowTypes)
	{
		auto propertyGrid = new wxPropertyGrid(getBench(), wxID_ANY, wxPoint(0, 0), 
			wxSize(PROPERTY_EDITOR_WIDTH, PROPERTY_EDITOR_HEIGHT), 
			wxPG_DEFAULT_STYLE | wxPG_SPLITTER_AUTO_CENTER |wxPG_HIDE_MARGIN);
		propertyGrid->SetColumnProportion(0, 4);
		propertyGrid->SetColumnProportion(1, 6);
		propertyGrid->Hide();
		//ImageProperty* imgProp = new ImageProperty("NormalImage", wxPG_LABEL);
		//propertyGrid->Append(imgProp);

		vBoxSizer->Add(propertyGrid, 1, wxALL, 5);
		// 添加控件名和编辑界面的map
		m_propertyGrids.insert(std::make_pair(winType, propertyGrid));

		propertyGrid->Bind(wxEVT_PG_CHANGED, &FormPropertyEditor::OnPropertyGridChanged, this);
	}
	// 查看是否存在可以编辑的控件类型
	if (m_propertyGrids.empty())
	{
		throw ExtraExcept::unexpected_situation("FormPropertyEditor::initSubWindows: m_propertyGrids can't be empty");
	}
	// 初始化值
	m_curEditWinType = m_propertyGrids.begin()->first;
	m_curPropertyGrid = m_propertyGrids.begin()->second;
	m_curPropertyGrid->Show();
	getBench()->SetSizerAndFit(vBoxSizer);
}

// 修改对应控件的属性列表
void FormPropertyEditor::insertWindowTypeAttrs(const wxString& winType, const std::vector<wxPGProperty*>& attrs)
{
	auto it = m_propertyGrids.find(winType);

	if (it == m_propertyGrids.cend())
	{
		throw std::runtime_error("FormPropertyEditor::insertWindowTypeAttrs: m_properGrids can't find " + winType);
	}

	auto propertyGrid = it->second;
	for (auto prop : attrs)
	{
		propertyGrid->Append(prop);
	}
	propertyGrid->ResetColumnSizes();
	getBench()->SetSizerAndFit(m_sizer);
}
