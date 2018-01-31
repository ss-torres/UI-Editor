#include "MainFrame.h"

#include "Settings/WindowAttributeManager.h"
#include "Form/FormToolWindow.h"
#include "Form/FormWidgetSelect.h"
#include "Form/FormObjectView.h"
#include "Form/FormPropertyEditor.h"
#include "Form/FormWorkArea.h"
#include "EditMessage/ChangeManager.h"
#include "EditMessage/CommandFactory.h"

const wxString WIN_ATTR_FILE = "WindowAttribute.xml";

MainFrame::MainFrame(const wxString & title)
	: wxMDIParentFrame(NULL, wxID_ANY, title)
{
	loadWindowAttributes();
	initMessageHandle();
	addMenu();
	initSubWindows();
}

MainFrame::~MainFrame()
{
	m_auiManager->UnInit();
}

// 每帧处理函数
void MainFrame::updateFrame(float dt)
{
	m_editWorkArea->updateFrame(dt);
}

// 重写销毁函数
bool MainFrame::Destroy()
{
	bool destroyed = wxFrame::Destroy();
	if (destroyed)
	{
		wxNotifyEvent event(DESTROY_EVENT, GetId());
		event.SetEventObject(this);
		// Do send it.
		ProcessWindowEvent(event);

		return true;
	}

	return false;
}


wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_SIZE(MainFrame::OnSize)

	EVT_MENU(wxID_UNDO, MainFrame::OnUndoCommand)
	EVT_MENU(wxID_REDO, MainFrame::OnRedoCommand)
wxEND_EVENT_TABLE()

// 用来处理窗口大小改变
void MainFrame::OnSize(wxSizeEvent & event)
{
	if (m_auiManager)
	{
		m_auiManager->Update();
	}
}

// 用来处理取消之前的命令
void MainFrame::OnUndoCommand(wxCommandEvent & WXUNUSED(event))
{
	using namespace Command;
	ChangeManager::instance()->getCommandStack().Undo();
}

// 用来重新做之前的命令
void MainFrame::OnRedoCommand(wxCommandEvent & WXUNUSED(event))
{
	using namespace Command;
	ChangeManager::instance()->getCommandStack().Redo();
}

// 加载控件属性
void MainFrame::loadWindowAttributes()
{
	m_winAttrManager.reset(new WindowAttributeManager());
	m_winAttrManager->LoadAttributeFile(WIN_ATTR_FILE);
}

// 创建菜单栏
void MainFrame::addMenu()
{
	// 文件菜单
	wxMenu* fileMenu = new wxMenu;
	fileMenu->Append(wxID_NEW);
	fileMenu->Append(wxID_OPEN);
	fileMenu->Append(wxID_SAVE);
	fileMenu->Append(wxID_SAVEAS);
	fileMenu->Append(wxID_EXIT);

	// 编辑菜单
	wxMenu* editMenu = new wxMenu;
	editMenu->Append(wxID_UNDO);
	editMenu->Append(wxID_REDO);
	editMenu->Append(wxID_CUT);
	editMenu->Append(wxID_COPY);
	editMenu->Append(wxID_PASTE);
	editMenu->Append(wxID_FIND);

	// 帮助菜单
	wxMenu* helpMenu = new wxMenu;
	helpMenu->Append(wxID_HELP);
	helpMenu->Append(wxID_ABOUT);

	// 添加菜单栏
	wxMenuBar *menuBar = new wxMenuBar();
	menuBar->Append(fileMenu, "&File");
	menuBar->Append(editMenu, "&Edit");
	menuBar->Append(helpMenu, "&Help");

	using namespace Command;
	ChangeManager::instance()->getCommandStack().SetEditMenu(editMenu);

	SetMenuBar(menuBar);

	// 添加状态栏
	CreateStatusBar(1);
	SetStatusText("Welcome to UI Editor");
}

// 初始化命令相关的对象
void MainFrame::initMessageHandle()
{
	using namespace Command;
	ChangeManager::createInstance();
	CommandFactory::createInstance(ChangeManager::instance());

	ChangeManager::instance()->setWindowAttrMgr(m_winAttrManager);
}

// 初始化子窗口
void MainFrame::initSubWindows()
{
	wxSize clientSize = GetClientSize();

	m_auiManager = new wxAuiManager(this, wxAUI_MGR_DEFAULT);
	double width = 0.6;
	double height = 0.6;
	m_auiManager->SetDockSizeConstraint(width, height);

	auto funcWndsMgr = m_manager;
	auto tool_window_del_func = [funcWndsMgr](FormToolWindow* editWnd) {funcWndsMgr.destroyToolWindow(editWnd); };

	// 控件类型选择
	m_tool_widget_select.reset(dynamic_cast<FormWidgetSelect*>(
		m_manager.createToolWindow(ToolWindowType::WidgetSelect, *m_auiManager, this, wxLEFT, "Widget Select")),
		tool_window_del_func);
	wxAuiPaneInfo widgetSelectPaneInfo = m_tool_widget_select->getPaneInfo();
	widgetSelectPaneInfo.BestSize(100, clientSize.GetHeight());
	m_tool_widget_select->setPaneInfo(widgetSelectPaneInfo);
	// 查看控件对象父子级关系
	m_tool_object_view.reset(dynamic_cast<FormObjectView*>(
		m_manager.createToolWindow(ToolWindowType::ObjectView, *m_auiManager, this, wxRIGHT, "Object View")),
		tool_window_del_func);
	wxAuiPaneInfo objectViewPaneInfo = m_tool_object_view->getPaneInfo();
	objectViewPaneInfo.BestSize(300, clientSize.GetHeight());
	m_tool_object_view->setPaneInfo(objectViewPaneInfo);
	// 控件对象属性修改
	m_tool_property_editor.reset(dynamic_cast<FormPropertyEditor*>(
		m_manager.createToolWindow(ToolWindowType::PropertyEditor, *m_auiManager, this, wxRIGHT, "Property Editor")),
		tool_window_del_func);
	// 初始化不同控件类型对应的属性列表
	std::vector<wxString> winNames = m_tool_widget_select->getAllWinNames();
	m_tool_property_editor->initSubWindows(winNames);
	for (const auto& value : winNames)
	{
		m_tool_property_editor->insertWindowTypeAttrs(value, m_winAttrManager->getEditWinAttr(value));
	}
	wxAuiPaneInfo propertyEditorPaneInfo = m_tool_property_editor->getPaneInfo();
	propertyEditorPaneInfo.BestSize(300, clientSize.GetHeight());
	m_tool_property_editor->setPaneInfo(propertyEditorPaneInfo);

	m_auiManager->Update();

	auto work_area_del_func = [funcWndsMgr](FormWorkArea* editWnd) {funcWndsMgr.destroyWorkArea(editWnd); };
	// 添加主工作区
	m_editWorkArea.reset(
		m_manager.createWorkArea(this, "WorkArea", wxDefaultPosition, wxSize(500, 400)),
			work_area_del_func);

	// 设置主工作区与查看控件对象窗口之间的关联
	m_tool_object_view->setRootWindowId(m_editWorkArea->getManageWindowId());

	// 将主工作区和对应功能区添加到命令处理对象中
	using namespace Command;
	ChangeManager::instance()->setObjectView(m_tool_object_view);
	ChangeManager::instance()->setPropertyEditor(m_tool_property_editor);
	ChangeManager::instance()->setWorkArea(m_editWorkArea);
}

wxDEFINE_EVENT(DESTROY_EVENT, wxNotifyEvent);