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

const int MANAGE_WINDOW_WIDTH = 1200;
const int MANAGE_WINDOW_HEIGHT = 900;

// ���Ƶ�ǰ���ڱ༭����ʹ�õ���ɫ
const D3DCOLOR CURRENT_WINDOW_COLOR = D3DCOLOR_RGBA(0, 0, 255, 255);

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
	
}

wxWindow * FormWorkArea::getBench()
{
	return m_bench;
}

// ��ȡ�ؼ����������ID
ID_TYPE FormWorkArea::getManageWindowId() const
{
	if (m_winMgr == nullptr)
	{
		throw ExtraExcept::unexpected_situation("FormWorkArea::getManageWindowId was been invoked when m_winMgr is nullptr");
	}

	return m_winMgr->getId();
}

// ���õ�ǰ�༭�Ŀؼ�ID
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

// ΪID�Ŀؼ�����һ���ӿؼ�
bool FormWorkArea::pushBackWindow(EditorAbstractWindow* parentWnd, EditorAbstractWindow *insertWnd)
{
	if (!parentWnd->isContainerWnd())
	{
		return false;
	}

	parentWnd->addChild(insertWnd);
	return true;
}

// ΪparentWnd��ָ��λ������һ���ӿؼ�
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

// ���ض�ID���ӿؼ��Ƴ�
bool FormWorkArea::removeWindow(EditorAbstractWindow* removeWnd)
{
	auto parenWnd = removeWnd->getParent();
	parenWnd->removeChild(removeWnd);
	return true;
}

// ����ÿ֡����
void FormWorkArea::updateFrame(float dt)
{
	// �鿴�豸�Ƿ�ʧ
	if (!m_drawManager->checkEveryFrame())
	{
		return;
	}

	updateScene(dt);
	drawScene(dt);
}

// ��������Drop�¼�
void FormWorkArea::onDrop(wxCoord x, wxCoord y, const CopyWindowInfo& winValue)
{
	// �鿴���ؼ�����
	EditorAbstractWindow* parentWnd = WorkAreaHelp::getMatchWindow(m_winMgr, x, y, Check_UiContainer());
	createWndObject(parentWnd, x, y, winValue);
}

// �����������ڱ�����
void FormWorkArea::handleActivate(wxActivateEvent & event)
{
	
}

// �������������Ĳ˵�
void FormWorkArea::handleContextMenu(wxContextMenuEvent & event)
{
	
}

// �����������������ļ��ڴ����д�
void FormWorkArea::handleDropFiles(wxDropFilesEvent & event)
{
	
}

// ����ΪFocus
void FormWorkArea::handleSetFocus(wxFocusEvent & event)
{
	event.Skip(true);
}

// ȡ��Focus
void FormWorkArea::handleKillFocus(wxFocusEvent & event)
{
	event.Skip(true);
}

// ����Idle��Ϣ
void FormWorkArea::handleIdle(wxIdleEvent & event)
{
	
}

// �������̰�����Ϣ
void FormWorkArea::handleKeyDown(wxKeyEvent & event)
{
	
}

// ���������ɿ���Ϣ
void FormWorkArea::handleKeyUp(wxKeyEvent & event)
{
	
}

// ��������������Ϣ
void FormWorkArea::handleChar(wxKeyEvent & event)
{
	
}

// ��������������
void FormWorkArea::handleLMouseDown(wxMouseEvent & event)
{
	// �鿴��갴��λ��
	wxCoord x = event.GetX();
	wxCoord y = event.GetY();
	// �鿴������Ϣ����
	auto editableWnd = WorkAreaHelp::getMatchWindow(m_winMgr, x, y, Check_Default());
	if (!editableWnd)
	{
		event.Skip();
		return;
	}
	using namespace Command;
	auto command = CommandFactory::instance()->createCurWindowSelectCommand(editableWnd);
	ChangeManager::instance()->getCommandStack().Submit(command);
}

// �����������ɿ�
void FormWorkArea::handleLMouseUp(wxMouseEvent & event)
{
	
}

// ��������ƶ�
void FormWorkArea::handleMouseMove(wxMouseEvent & event)
{
	
}

// �������ƣ����ﲻ��Ҫ�����������
void FormWorkArea::handlePaint(wxPaintEvent & event)
{
	event.Skip(true);
}

// �������ڴ�С�ı�
void FormWorkArea::handleSize(wxSizeEvent & event)
{
	wxSize size = event.GetSize();
	m_drawManager->handlgeSizeChange(size.x, size.y);
}

// ���������������µļ���
void FormWorkArea::updateScene(float dt)
{
	
}

// ����ÿ֡����
void FormWorkArea::drawScene(float dt)
{
	m_drawManager->drawWindowsBefore();
	drawWindowRecur(m_winMgr, 0, 0);
	// ���Ƶ�ǰ���ڱ༭����
	if (m_currentWnd)
	{
		m_drawManager->drawSelectWindow(m_currentWnd,
			m_currentWnd->getAbsX(), m_currentWnd->getAbsY(), CURRENT_WINDOW_COLOR);
	}
	m_drawManager->drawWindowsAfter();
}

//�����ӿؼ�
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

// ����һ���ؼ�����
void FormWorkArea::createWndObject(EditorAbstractWindow* parent, int absX, int absY, const CopyWindowInfo& winValue)
{
	EditorAbstractWindowFactory* wndFac = EditorWindowFactory::winFactoryInst();
	// ��ʱ������֮��Ὣnullptr�ж��Ƴ�
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


// ��ʼ����ʾ����
void FormWorkArea::initFrameWnd(wxMDIParentFrame* parent, const wxString& captionName, const wxPoint& position, const wxSize &size)
{
	wxMDIChildFrame* childFrame = new wxMDIChildFrame(parent, wxID_ANY, captionName, position, size);
	m_bench = new wxPanel(childFrame, -1, wxPoint(0,0), size);
	wxBoxSizer* vBoxSizer = new wxBoxSizer(wxVERTICAL);
	vBoxSizer->Add(m_bench, 1);
}

// ��ʼ�������ؼ�
void FormWorkArea::initManageWnd()
{
	setCurrentWindow(m_winMgr);
}

// ��ʼ����Ϣ����
void FormWorkArea::initMsgHandle()
{
	auto bench = getBench();
	// ���ڼ���
	bench->Bind(wxEVT_ACTIVATE, &FormWorkArea::handleActivate, this);
	// �����Ĳ˵�
	bench->Bind(wxEVT_CONTEXT_MENU, &FormWorkArea::handleContextMenu, this);
	// ���ɿ����ļ�
	bench->DragAcceptFiles(true);
	bench->Bind(wxEVT_DROP_FILES, &FormWorkArea::handleDropFiles, this);
	// ����ΪFocus
	bench->Bind(wxEVT_SET_FOCUS, &FormWorkArea::handleSetFocus, this);
	// ȡ��Focus
	bench->Bind(wxEVT_KILL_FOCUS, &FormWorkArea::handleKillFocus, this);
	// ����Idle��Ϣ
	bench->Bind(wxEVT_IDLE, &FormWorkArea::handleIdle, this);
	// �������̰���
	bench->Bind(wxEVT_KEY_DOWN, &FormWorkArea::handleKeyDown, this);
	// ���������ɿ�
	bench->Bind(wxEVT_KEY_UP, &FormWorkArea::handleKeyUp, this);
	// ������������
	bench->Bind(wxEVT_CHAR, &FormWorkArea::handleChar, this);
	// ��������������
	bench->Bind(wxEVT_LEFT_DOWN, &FormWorkArea::handleLMouseDown, this);
	// �����������ɿ�
	bench->Bind(wxEVT_LEFT_UP, &FormWorkArea::handleLMouseUp, this);
	// ��������ƶ�
	bench->Bind(wxEVT_MOTION, &FormWorkArea::handleMouseMove, this);
	// ��������
	bench->Bind(wxEVT_PAINT, &FormWorkArea::handlePaint, this);
	// �������ڴ�С�ı�
	bench->Bind(wxEVT_SIZE, &FormWorkArea::handleSize, this);
}