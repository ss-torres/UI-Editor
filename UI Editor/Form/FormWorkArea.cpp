#include <ctime>
#include <sstream>
#include <iomanip>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/mdi.h>
#include "FormWorkArea.h"
#include "WorkAreaHelp.h"
#include "../ErrorHandle/ErrorHandle.h"
#include "../CopyDrop/CopyWinObject.h"
#include "../EditorWindow/EditorWindowInterface.h"
#include "../EditorWindow/EditorWindowFactory.h"
#include "../EditMessage/CommandFactory.h"
#include "../EditMessage/ChangeManager.h"

#include "../EditorWindow/EditorManageWindow.h"
#include "../DrawEngine/DrawControlManager.h"

#include "../AutoSave/SaveInfo.h"
#include "../AutoSave/EditorSave.h"

const int MANAGE_WINDOW_WIDTH = 1200;
const int MANAGE_WINDOW_HEIGHT = 900;

// 绘制当前正在编辑窗口使用的颜色
const D3DCOLOR CURRENT_WINDOW_COLOR = D3DCOLOR_RGBA(0, 0, 255, 255);

const char* const FILE_NO_NAME_SHOW = "untitled_ui";
const char* const BACK_UP_DIR = "./backup/";

class DropWinTarget : public wxDropTarget
{
public:
	DropWinTarget(FormWorkArea *workArea)
		: wxDropTarget(new CopyWinObject(getCopyDataFormat()))
	{
		m_workArea = workArea;
	}

	~DropWinTarget(){ }

	wxDragResult OnEnter(wxCoord x, wxCoord y, wxDragResult defResult) override
	{
		return defResult;
	}

	wxDragResult OnDragOver(wxCoord x, wxCoord y, wxDragResult defResult) override
	{
		return defResult;
	}

	wxDragResult OnData(wxCoord x, wxCoord y, wxDragResult defResult) override
	{
		if (!GetData())
		{
			return wxDragNone;
		}

		auto rcvObj = dynamic_cast<CopyWinObject*>(GetDataObject());

		if (rcvObj == nullptr)
		{
			return wxDragNone;
		}

		m_workArea->onDrop(x, y, rcvObj->getWinValue());

		return defResult;
	}
private:
	FormWorkArea* m_workArea;
};

FormWorkArea::FormWorkArea(wxMDIParentFrame* parent, const wxString& captionName = wxEmptyString, 
	const wxPoint& position = wxDefaultPosition, const wxSize &size = wxDefaultSize)
	: WorkArea(parent),
	m_winMgr(EditorWindowFactory::winFactoryInst()->createManageWnd(MANAGE_WINDOW_WIDTH, MANAGE_WINDOW_HEIGHT))
{
	initFrameWnd(parent, captionName, position, size);
	m_drawManager.reset(new DrawControlManager(getHandle()));
	initManageWnd();
	initMsgHandle();

	getBench()->SetDropTarget(new DropWinTarget(this));
}

FormWorkArea::~FormWorkArea()
{
	// 如果保存ui线程有效，则等待其结束
	if (m_saveThread.valid())
	{
		if (m_saveThread.wait_for(std::chrono::seconds(0)) != std::future_status::deferred)
		{
			m_saveThread.wait();
		}
	}

	if (m_editorSave)
	{
		delete m_editorSave;
		m_editorSave = nullptr;
	}
}

wxWindow * FormWorkArea::getBench()
{
	return m_bench;
}

// 获取控件管理对象的ID
ID_TYPE FormWorkArea::getManageWindowId() const
{
	if (m_winMgr == nullptr)
	{
		throw ExtraExcept::unexpected_situation("FormWorkArea::getManageWindowId was been invoked when m_winMgr is nullptr");
	}

	return m_winMgr->getId();
}

wxString FormWorkArea::getManageWindowName() const
{
	if (m_winMgr == nullptr)
	{
		throw ExtraExcept::unexpected_situation("FormWorkArea::getManageWindowId was been invoked when m_winMgr is nullptr");
	}

	return m_winMgr->getWinAttr(OBJECT_NAME).As<wxString>();
}

// 设置当前编辑的控件ID
bool FormWorkArea::setCurrentWindowId(ID_TYPE curWndId)
{
	EditorAbstractWindow* curWnd = WorkAreaHelp::getAvailWindow(m_winMgr, Check_UiIdEqual(curWndId));
	if (curWnd != nullptr)
	{
		setCurrentWindow(curWnd);
		return true;
	}

	return false;
}

// 为ID的控件添加一个子控件
bool FormWorkArea::pushBackWindow(EditorAbstractWindow* parentWnd, EditorAbstractWindow *insertWnd)
{
	if (!parentWnd->isContainerWnd())
	{
		return false;
	}

	parentWnd->addChild(insertWnd);
	return true;
}

// 为parentWnd在指定位置添加一个子控件
bool FormWorkArea::insertWindow(EditorAbstractWindow* parentWnd, size_t idx, EditorAbstractWindow * insertWnd)
{
	if (!parentWnd->isContainerWnd())
	{
		return false;
	}
	
	if (idx > parentWnd->getChildrenSize())
	{
		return false;
	}
	auto iter = parentWnd->getChildrenConstBeg() + idx;
	parentWnd->insertChild(insertWnd, iter);
	return true;
}

// 将特定ID的子控件移除
bool FormWorkArea::removeWindow(EditorAbstractWindow* removeWnd)
{
	auto parenWnd = removeWnd->getParent();
	parenWnd->removeChild(removeWnd);
	return true;
}

// 用来每帧处理
void FormWorkArea::updateFrame(float dt)
{
	// 查看设备是否丢失
	if (!m_drawManager->checkEveryFrame())
	{
		return;
	}

	updateScene(dt);
	drawScene();
}

// 用来处理Drop事件
void FormWorkArea::onDrop(wxCoord x, wxCoord y, const CopyWindowInfo& winValue)
{
	// 查看父控件对象
	EditorAbstractWindow* parentWnd = WorkAreaHelp::getMatchWindow(m_winMgr, x, y, Check_UiContainer());
	createWndObject(parentWnd, x, y, winValue);
}

// 用来处理窗口被激活
void FormWorkArea::handleActivate(wxActivateEvent & event)
{
	
}

// 用来处理上下文菜单
void FormWorkArea::handleContextMenu(wxContextMenuEvent & event)
{
	
}

// 用来处理将拖拉的文件在窗口中打开
void FormWorkArea::handleDropFiles(wxDropFilesEvent & event)
{
	
}

// 设置为Focus
void FormWorkArea::handleSetFocus(wxFocusEvent & event)
{
	event.Skip(true);
}

// 取消Focus
void FormWorkArea::handleKillFocus(wxFocusEvent & event)
{
	event.Skip(true);
}

// 处理Idle消息
void FormWorkArea::handleIdle(wxIdleEvent & event)
{
	
}

// 处理键盘按下消息
void FormWorkArea::handleKeyDown(wxKeyEvent & event)
{
	
}

// 处理键盘松开消息
void FormWorkArea::handleKeyUp(wxKeyEvent & event)
{
	
}

// 处理输入文字消息
void FormWorkArea::handleChar(wxKeyEvent & event)
{
	
}

// 处理鼠标左键按下
void FormWorkArea::handleLMouseDown(wxMouseEvent & event)
{
	m_mouseDown = true;
	// 查看鼠标按下位置
	wxCoord x = event.GetX();
	wxCoord y = event.GetY();

	if (m_winMgr == nullptr || !m_winMgr->handleLMouseDown(narrow_cast<int>(x), narrow_cast<int>(y)))
	{
		event.Skip();
	}
}

// 处理鼠标左键松开
void FormWorkArea::handleLMouseUp(wxMouseEvent & event)
{
	m_mouseDown = false;
}

// 处理鼠标移动
void FormWorkArea::handleMouseMove(wxMouseEvent & event)
{
	
}

// 处理绘制，这里不需要处理这个函数
void FormWorkArea::handlePaint(wxPaintEvent & event)
{
	event.Skip(true);
}

// 处理窗口大小改变
void FormWorkArea::handleSize(wxSizeEvent & event)
{
	wxSize size = event.GetSize();
	m_drawManager->handlgeSizeChange(size.x, size.y);
}

// 用来处理场景更新的计算
void FormWorkArea::updateScene(float dt)
{
	m_calcTime += dt;

	if (m_calcTime > m_backupTime)
	{
		saveWndBacks();
		// 重新统计
		m_calcTime = 0;
	}
}

// 用来每帧绘制
void FormWorkArea::drawScene()
{
	m_drawManager->drawWindowsBefore();
	drawWindowRecur(m_winMgr, 0, 0);
	// 绘制当前正在编辑窗口
	if (m_currentWnd)
	{
		m_drawManager->drawSelectWindow(m_currentWnd,
			m_currentWnd->getAbsX(), m_currentWnd->getAbsY(), CURRENT_WINDOW_COLOR);
	}
	m_drawManager->drawWindowsAfter();
}

//绘制子控件
void FormWorkArea::drawWindowRecur(EditorAbstractWindow *editorWindow, int absX, int absY)
{
	absX += editorWindow->getRelX();
	absY += editorWindow->getRelY();

	editorWindow->editDraw(absX, absY, m_drawManager.get());
	
	auto end = editorWindow->getChildrenConstEnd();
	for (auto beg = editorWindow->getChildrenConstBeg(); beg != end; ++beg)
	{
		drawWindowRecur(*beg, absX, absY);
	}
}

// 创建一个控件对象
void FormWorkArea::createWndObject(EditorAbstractWindow* parent, int absX, int absY, const CopyWindowInfo& winValue)
{
	EditorAbstractWindowFactory* wndFac = EditorWindowFactory::winFactoryInst();
	// 暂时处理，之后会将nullptr判断移除
	int relX = absX;
	int relY = absY;
	if (parent != nullptr)
	{
		relX -= parent->getAbsX();
		relY -= parent->getAbsY();
	}
	auto createdWnd = wndFac->createCopyObjectWnd(winValue, parent, relX, relY);
	using namespace Command;
	auto dropWndCommand = CommandFactory::instance()->createDropWindowCommand(createdWnd, parent);
	ChangeManager::instance()->getCommandStack().Submit(dropWndCommand);
}

// 获取保存窗口信息的对象
EditorSave * FormWorkArea::getEditorSave()
{
	if (m_editorSave == nullptr)
	{
		m_editorSave = new EditorSave();
	}

	return m_editorSave;
}

// 将窗口保存到文件中，同步操作
void FormWorkArea::saveWnds()
{
	handleLastBack();

	SaveInfo info;
	m_winMgr->appendMySelf(info, true);

	if (m_editFile.empty())
	{
		getEditorSave()->setSaveFileName(FILE_NO_NAME_SHOW);
	}
	else
	{
		getEditorSave()->setSaveFileName(m_editFile);
	}
	getEditorSave()->setSaveInfo(std::move(info));

	m_saveThread = std::async(std::ref(*getEditorSave()));
	m_saveThread.get();
}

// 将窗口信息保存到文件中，异步操作
void FormWorkArea::saveWndBacks()
{
	handleLastBack();

	SaveInfo info;
	m_winMgr->appendMySelf(info, true);

	// 保存窗口信息到文件中
	auto t = std::time(nullptr);
	std::ostringstream out;
	out << std::put_time(std::localtime(&t), "_%Y%m%d_%H%M%S");
	wxString backupFileName;
	if (m_editFile.empty())
	{
		backupFileName = wxString(BACK_UP_DIR) + wxString(FILE_NO_NAME_SHOW) + out.str().c_str();
	}
	else
	{
		backupFileName = wxString(BACK_UP_DIR) + m_editFile + out.str().c_str();
	}
	getEditorSave()->setSaveFileName(std::move(backupFileName));
	getEditorSave()->setSaveInfo(std::move(info));

	m_saveThread = std::async(std::ref(*getEditorSave()));
}

// 处理上一次保存窗口信息过程
bool FormWorkArea::handleLastBack()
{
	// 处理保存窗口信息线程，确保其安全退出
	if (m_saveThread.valid())
	{
		std::future_status curStatus;
		if ((curStatus = m_saveThread.wait_for(std::chrono::seconds(0))) == std::future_status::ready)
		{	// 保存窗口信息过程已完成
			return m_saveThread.get();
		}
		else if (curStatus == std::future_status::timeout)
		{	// 保存窗口信息过程正在进行，取消保存
			getEditorSave()->setSaveContinue(false);
			bool ret = m_saveThread.get();
			getEditorSave()->setSaveContinue(true);
			return false;
		}
		else
		{
			return false;
			// 保存窗口信息过程未开始，则直接跳过
		}
	}

	return false;
}

// 初始化显示窗口
void FormWorkArea::initFrameWnd(wxMDIParentFrame* parent, const wxString& captionName, const wxPoint& position, const wxSize &size)
{
	wxMDIChildFrame* childFrame = new wxMDIChildFrame(parent, wxID_ANY, captionName, position, size);
	m_bench = new wxPanel(childFrame, -1, wxPoint(0,0), size);
	wxBoxSizer* vBoxSizer = new wxBoxSizer(wxVERTICAL);
	vBoxSizer->Add(m_bench, 1);
}

// 初始化管理控件
void FormWorkArea::initManageWnd()
{
	setCurrentWindow(m_winMgr);
}

// 初始化消息处理
void FormWorkArea::initMsgHandle()
{
	auto bench = getBench();
	// 窗口激活
	bench->Bind(wxEVT_ACTIVATE, &FormWorkArea::handleActivate, this);
	// 上下文菜单
	bench->Bind(wxEVT_CONTEXT_MENU, &FormWorkArea::handleContextMenu, this);
	// 打开松开的文件
	bench->DragAcceptFiles(true);
	bench->Bind(wxEVT_DROP_FILES, &FormWorkArea::handleDropFiles, this);
	// 设置为Focus
	bench->Bind(wxEVT_SET_FOCUS, &FormWorkArea::handleSetFocus, this);
	// 取消Focus
	bench->Bind(wxEVT_KILL_FOCUS, &FormWorkArea::handleKillFocus, this);
	// 处理Idle消息
	bench->Bind(wxEVT_IDLE, &FormWorkArea::handleIdle, this);
	// 处理键盘按下
	bench->Bind(wxEVT_KEY_DOWN, &FormWorkArea::handleKeyDown, this);
	// 处理键盘松开
	bench->Bind(wxEVT_KEY_UP, &FormWorkArea::handleKeyUp, this);
	// 处理输入文字
	bench->Bind(wxEVT_CHAR, &FormWorkArea::handleChar, this);
	// 处理鼠标左键按下
	bench->Bind(wxEVT_LEFT_DOWN, &FormWorkArea::handleLMouseDown, this);
	// 处理鼠标左键松开
	bench->Bind(wxEVT_LEFT_UP, &FormWorkArea::handleLMouseUp, this);
	// 处理鼠标移动
	bench->Bind(wxEVT_MOTION, &FormWorkArea::handleMouseMove, this);
	// 处理绘制
	bench->Bind(wxEVT_PAINT, &FormWorkArea::handlePaint, this);
	// 处理窗口大小改变
	bench->Bind(wxEVT_SIZE, &FormWorkArea::handleSize, this);
}
