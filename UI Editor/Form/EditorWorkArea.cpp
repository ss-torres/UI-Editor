#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/mdi.h>
#include "EditorWorkArea.h"
#include "EditorWorkAreaHelp.h"
#include "../ErrorHandle/ErrorHandle.h"
#include "../CopyDrop/CopyWinObject.h"
#include "../EditorWindow/EditorWindowInterface.h"
#include "../EditorWindow/EditorWindowFactory.h"
#include "../EditMessage/CommandFactory.h"
#include "../EditMessage/ChangeManager.h"

#include "../EditorWindow/EditorManageWindow.h"
#include "../DrawEngine/DrawControlManager.h"

const int MANAGE_WINDOW_WIDTH = 1200;
const int MANAGE_WINDOW_HEIGHT = 900;

class DropWinTarget : public wxDropTarget
{
public:
	DropWinTarget(EditorWorkArea *workArea)
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
	EditorWorkArea* m_workArea;
};

EditorWorkArea::EditorWorkArea(wxMDIParentFrame* parent, const wxString& captionName = wxEmptyString, 
	const wxPoint& position = wxDefaultPosition, const wxSize &size = wxDefaultSize)
	: WorkArea(parent),
	m_winMgr(EditorWindowFactory::winFactoryInst()->createManageWnd(MANAGE_WINDOW_WIDTH, MANAGE_WINDOW_HEIGHT))
{
	initFrameWnd(parent, captionName, position, size);
	m_drawManager.reset(new DrawControlManager(getHandle()));
	initManageWnd();

	getBench()->SetDropTarget(new DropWinTarget(this));
}

EditorWorkArea::~EditorWorkArea()
{
	
}

wxWindow * EditorWorkArea::getBench()
{
	return m_bench;
}

// 获取窗口管理对象的ID
ID_TYPE EditorWorkArea::getManageWindowId() const
{
	if (m_winMgr == nullptr)
	{
		throw ExtraExcept::unexpected_situation("EditorWorkArea::getManageWindowId was been invoked when m_winMgr is nullptr");
	}

	return m_winMgr->getId();
}

// 为ID的窗口添加一个子窗口
bool EditorWorkArea::pushBackWindow(EditorAbstractWindow* parentWnd, EditorAbstractWindow *insertWnd)
{
	if (!parentWnd->isContainerWnd())
	{
		return false;
	}

	parentWnd->addChild(insertWnd);
	return true;
}

// 为parentWnd在指定位置添加一个子窗口
bool EditorWorkArea::insertWindow(EditorAbstractWindow* parentWnd, size_t idx, EditorAbstractWindow * insertWnd)
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

// 将特定ID的子窗口移除
bool EditorWorkArea::removeWindow(EditorAbstractWindow* removeWnd)
{
	auto parenWnd = removeWnd->getParent();
	parenWnd->removeChild(removeWnd);
	return true;
}

// 用来每帧处理
void EditorWorkArea::updateFrame(float dt)
{
	// 查看设备是否丢失
	if (!m_drawManager->checkEveryFrame())
	{
		return;
	}

	updateScene(dt);
	drawScene(dt);
}

// 用来处理Drop事件
void EditorWorkArea::onDrop(wxCoord x, wxCoord y, const CopyWindowInfo& winValue)
{
	// 查看父窗口对象
	EditorAbstractWindow* parentWnd = WorkAreaHelp::getMatchWindow(m_winMgr, x, y, Check_UiContainer());
	createWndObject(parentWnd, x, y, winValue);
}

// 用来处理场景更新的计算
void EditorWorkArea::updateScene(float dt)
{
	
}

// 用来每帧绘制
void EditorWorkArea::drawScene(float dt)
{
	m_drawManager->drawWindowsBefore();
	drawWindowRecur(m_winMgr, 0, 0);
	m_drawManager->drawWindowsAfter();
}

//绘制子窗口
void EditorWorkArea::drawWindowRecur(EditorAbstractWindow *editorWindow, int absX, int absY)
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

// 创建一个窗口对象
void EditorWorkArea::createWndObject(EditorAbstractWindow* parent, int absX, int absY, const CopyWindowInfo& winValue)
{
	AbstractWindowFactory* wndFac = EditorWindowFactory::winFactoryInst();
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
	auto dropWndCommand = CommandFactory::instance()->createDropWindowCommand(createdWnd, parent, getCurrentWindow());
	ChangeManager::instance()->getCommandStack().Submit(dropWndCommand);
}


// 初始化显示窗口
void EditorWorkArea::initFrameWnd(wxMDIParentFrame* parent, const wxString& captionName, const wxPoint& position, const wxSize &size)
{
	wxMDIChildFrame* childFrame = new wxMDIChildFrame(parent, wxID_ANY, captionName, position, size);
	m_bench = new wxPanel(childFrame, -1, wxPoint(0,0), size);
	wxBoxSizer* vBoxSizer = new wxBoxSizer(wxVERTICAL);
	vBoxSizer->Add(m_bench, 1);
}

// 初始化管理窗口
void EditorWorkArea::initManageWnd()
{
	setCurrentWindow(m_winMgr);
}
