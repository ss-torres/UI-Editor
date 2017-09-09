#include "EditorToolWindow.h"
#include "../ErrorHandle/ErrorHandle.h"
#include <wx/frame.h>
#include <cassert>

EditorToolWindow::EditorToolWindow(wxAuiManager &manager, wxWindow * parent, int direction, const wxString & paneName)
	: WorkArea(parent),
	m_auiManager(manager)
{
	// 要求aui管理的窗口，与传入的父窗口为同一个对象
	assert((m_auiManager.GetManagedWindow() == parent) && "the window managed by aui should be same with parent ");
	// 在调用其他函数前，需要初始化m_bench，为m_bench创建窗口
	m_bench = new wxPanel(parent);
	m_auiManager.AddPane(m_bench, direction, paneName);
}

EditorToolWindow::~EditorToolWindow()
{
	assert(getBench() != nullptr);
}

// 用来设置停靠方向
void EditorToolWindow::setDirection(int direction)
{
	wxAuiPaneInfo& myPaneInfo = m_auiManager.GetPane(getBench());
	if (myPaneInfo.IsOk())
	{
		myPaneInfo.Direction(direction);
		m_auiManager.Update();
	}
	else
	{
		throw ExtraException::unexpected_situation("myPaneInfo's IsOk() should be true.");
	}
}

// 用来设置标题
void EditorToolWindow::setCaption(const wxString & captionName)
{
	wxAuiPaneInfo& myPaneInfo = m_auiManager.GetPane(getBench());
	if (myPaneInfo.IsOk())
	{
		myPaneInfo.Caption(captionName);
		m_auiManager.Update();
	}
	else
	{
		throw ExtraException::unexpected_situation("myPaneInfo's IsOk() should be true.");
	}
}

// 用来设置各种停靠属性
void EditorToolWindow::setPanelInfo(const wxAuiPaneInfo & paneInfo)
{
	wxAuiPaneInfo& myPaneInfo = m_auiManager.GetPane(getBench());
	if (myPaneInfo.IsOk())
	{
		myPaneInfo = paneInfo;
		m_auiManager.Update();
	}
	else
	{
		throw ExtraException::unexpected_situation("myPaneInfo's IsOk() should be true.");
	}
}

wxAuiPaneInfo & EditorToolWindow::getPanelInfo()
{
	wxAuiPaneInfo& myPaneInfo = m_auiManager.GetPane(getBench());
	if (myPaneInfo.IsOk())
	{
		return myPaneInfo;
	}
	else
	{
		throw ExtraException::unexpected_situation("myPaneInfo's IsOk() should be true.");
		return myPaneInfo;
	}
}