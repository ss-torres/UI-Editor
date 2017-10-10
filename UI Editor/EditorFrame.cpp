#include "EditorFrame.h"

#include "Settings/WindowAttributeManager.h"
#include "Form/EditorToolWindow.h"
#include "Form/EditorToolWidgetSelect.h"
#include "Form/EditorToolObjectView.h"
#include "Form/EditorToolPropertyEditor.h"
#include "Form/EditorWorkArea.h"
#include "EditMessage/ChangeManager.h"
#include "EditMessage/CommandFactory.h"

const wxString WIN_ATTR_FILE = "WindowAttribute.xml";

EditorFrame::EditorFrame(const wxString & title)
	: wxMDIParentFrame(NULL, wxID_ANY, title)
{
	loadWindowAttributes();
	addMenu();
	initSubWindows();
}

EditorFrame::~EditorFrame()
{
	m_auiManager->UnInit();
}

// 每帧处理函数
void EditorFrame::updateFrame(float dt)
{
	m_editWorkArea->updateFrame(dt);
}

// 重写销毁函数
bool EditorFrame::Destroy()
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


wxBEGIN_EVENT_TABLE(EditorFrame, wxFrame)
	EVT_SIZE(EditorFrame::OnSize)
wxEND_EVENT_TABLE()

// 创建菜单栏
void EditorFrame::addMenu()
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
	
	SetMenuBar(menuBar);

	// 添加状态栏
	CreateStatusBar(1);
	SetStatusText("Welcome to UI Editor");
}

// 用来处理窗口大小改变
void EditorFrame::OnSize(wxSizeEvent & event)
{
	if (m_auiManager)
	{
		m_auiManager->Update();
	}
}

// 加载窗口属性
void EditorFrame::loadWindowAttributes()
{
	m_winAttrManager.reset(new WindowAttributeManager());
	m_winAttrManager->LoadAttributeFile(WIN_ATTR_FILE);
}

// 初始化子窗口
void EditorFrame::initSubWindows()
{
	wxSize clientSize = GetClientSize();

	m_auiManager = new wxAuiManager(this, wxAUI_MGR_DEFAULT);
	double width = 0.6;
	double height = 0.6;
	m_auiManager->SetDockSizeConstraint(width, height);

	auto funcWndsMgr = m_manager;
	auto tool_window_del_func = [funcWndsMgr](EditorToolWindow* editWnd) {funcWndsMgr.destroyToolWindow(editWnd); };

	// 窗口类型选择
	m_tool_widget_select.reset(dynamic_cast<EditorToolWidgetSelect*>(
		m_manager.createToolWindow(ToolWindowType::WidgetSelect, *m_auiManager, this, wxLEFT, "Widget Select")),
		tool_window_del_func);
	wxAuiPaneInfo widgetSelectPaneInfo = m_tool_widget_select->getPaneInfo();
	widgetSelectPaneInfo.BestSize(100, clientSize.GetHeight());
	m_tool_widget_select->setPaneInfo(widgetSelectPaneInfo);
	// 查看窗口对象父子级关系
	m_tool_object_view.reset(dynamic_cast<EditorToolObjectView*>(
		m_manager.createToolWindow(ToolWindowType::ObjectView, *m_auiManager, this, wxRIGHT, "Object View")),
		tool_window_del_func);
	wxAuiPaneInfo objectViewPaneInfo = m_tool_object_view->getPaneInfo();
	objectViewPaneInfo.BestSize(300, clientSize.GetHeight());
	m_tool_object_view->setPaneInfo(objectViewPaneInfo);
	// 窗口对象属性修改
	m_tool_property_editor.reset(dynamic_cast<EditorToolPropertyEditor*>(
		m_manager.createToolWindow(ToolWindowType::PropertyEditor, *m_auiManager, this, wxRIGHT, "Property Editor")),
		tool_window_del_func);
	// 初始化不同窗口类型对应的属性列表
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

	auto work_area_del_func = [funcWndsMgr](EditorWorkArea* editWnd) {funcWndsMgr.destroyWorkArea(editWnd); };
	// 添加工作窗口
	m_editWorkArea.reset(
		m_manager.createWorkArea(this, "WorkArea", wxDefaultPosition, wxSize(500, 400)),
			work_area_del_func);

	// 设置工作窗口与查看对象窗口之间的关联
	m_tool_object_view->setRootWindowId(m_editWorkArea->getManageWindowId());

	using namespace Command;
	ChangeManager::createInstance();
	CommandFactory::createInstance(ChangeManager::instance());
	// 将主工作区和工具窗口添加到改变处理对象中
	ChangeManager::instance()->setObjectView(m_tool_object_view);
	ChangeManager::instance()->setPropertyEditor(m_tool_property_editor);
	ChangeManager::instance()->setWorkArea(m_editWorkArea);

	ChangeManager::instance()->setWindowAttrMgr(m_winAttrManager);
}

wxDEFINE_EVENT(DESTROY_EVENT, wxNotifyEvent);