#ifndef FORM_WORK_AREA_H
#define FORM_WORK_AREA_H

#include <memory>
#include <future>
#include <unordered_set>
#include <wx/msw/wrapwin.h>		// 在wxWidgets中替代<Windows.h>
#include <wx/panel.h>
#include <wx/dnd.h>
#include "WorkArea.h"
#include "../EditorWindow/EditorWindowInterface.h"

class DrawControlManager;
class CopyWindowInfo;
class wxMDIParentFrame;
class wxMDIChildFrame;
class EditorSave;

class FormWorkArea : public WorkArea
{
public:
	FormWorkArea(wxMDIParentFrame* parent, const wxString& captionName, const wxPoint& position, const wxSize &size);
	~FormWorkArea();

	// 获取该对象中的主窗口
	wxWindow* getBench() override;
	// 获取控件管理对象的ID
	ID_TYPE getManageWindowId() const;
	// 获取控件管理对象的名字
	wxString getManageWindowName() const;
	// 设置当前编辑的控件
	void setCurrentWindow(EditorAbstractWindow* currentWnd) { m_currentWnd = currentWnd; }
	// 设置当前编辑的控件ID
	bool setCurrentWindowId(ID_TYPE curWndId);
	// 获取当前编辑的控件
	EditorAbstractWindow* getCurrentWindow() const { return m_currentWnd; }
	// 获取当前编辑的控件ID
	ID_TYPE getCurrentWindowId() const { return m_currentWnd->getId(); }
	// 获取当前所有选中的窗口ID
	const std::unordered_set<ID_TYPE>& getSelectWndIds() const { return m_selectWndIds; }
	// 获取当前所有选中的窗口ID
	std::unordered_set<ID_TYPE>& getSelectWndIds() { return m_selectWndIds; }
	// 设置当前选中的所有窗口ID
	void setSelectWndIds(std::unordered_set<ID_TYPE> selectWndIds) { m_selectWndIds = std::move(selectWndIds); }
	// 为parentWnd添加一个子控件
	bool pushBackWindow(EditorAbstractWindow* parenWnd, EditorAbstractWindow* insertWnd);
	// 为parentWnd在指定位置添加一个子控件
	bool insertWindow(EditorAbstractWindow* parentWnd, size_t idx, EditorAbstractWindow* insertWnd);
	// 将特定ID的子控件移除
	bool removeWindow(EditorAbstractWindow* removeWnd);

public:
	// 用来每帧处理
	void updateFrame(float dt);

	// 用来处理Drop事件
	void onDrop(wxCoord x, wxCoord y, const CopyWindowInfo& winValue);

private:
	// 用来处理各种消息
	// 用来处理窗口被激活
	void handleActivate(wxActivateEvent& event);
	// 用来处理上下文菜单
	void handleContextMenu(wxContextMenuEvent& event);
	// 用来处理将拖拉的文件在窗口中打开
	void handleDropFiles(wxDropFilesEvent& event);
	// 设置为Focus
	void handleSetFocus(wxFocusEvent& event);
	// 取消Focus
	void handleKillFocus(wxFocusEvent& event);
	// 处理Idle消息
	void handleIdle(wxIdleEvent& event);
	// 处理键盘按下消息
	void handleKeyDown(wxKeyEvent& event);
	// 处理键盘松开消息
	void handleKeyUp(wxKeyEvent& event);
	// 处理输入文字消息
	void handleChar(wxKeyEvent& event);
	// 处理鼠标左键按下
	void handleLMouseDown(wxMouseEvent& event);
	// 处理鼠标左键松开
	void handleLMouseUp(wxMouseEvent& event);
	// 处理鼠标移动
	void handleMouseMove(wxMouseEvent& event);
	// 处理绘制，这里不需要处理这个函数
	void handlePaint(wxPaintEvent& event);
	// 处理窗口大小改变
	void handleSize(wxSizeEvent& event);

private:
	// 获取窗口句柄，该函数必须在初始化bench之后调用
	HWND getHandle();
	// 用来处理场景更新的计算
	void updateScene(float dt);
	// 用来每帧绘制
	void drawScene();
	//绘制子控件
	void drawWindowRecur(EditorAbstractWindow* editorWindow, int absX, int absY);

private:
	// 查找指定位置接受消息的控件
	template <typename T = UiEditable<EditorAbstractWindow>>
	EditorAbstractWindow* findWnd(wxCoord x, wxCoord y);
	// 创建一个控件对象
	void createWndObject(EditorAbstractWindow* parent, int absX, int absY, const CopyWindowInfo& winValue);

	// 获取保存窗口信息的对象
	EditorSave* getEditorSave();
	// 将窗口保存到文件中，同步操作
	void saveWnds();
	// 将窗口信息保存到备份文件中，异步操作
	void saveWndBacks();
	// 处理上一次保存窗口信息过程，返回保存过程是否成功
	bool handleLastBack();

	// 初始化显示窗口
	void initFrameWnd(wxMDIParentFrame* parent, const wxString& captionName, const wxPoint& position, const wxSize &size);
	// 初始化管理控件
	void initManageWnd();
	// 初始化消息处理
	void initMsgHandle();

private:
	wxPanel *m_bench;

	// 绘制该编辑区域控件的对象
	std::unique_ptr<DrawControlManager> m_drawManager;
	// 用来存储创建的控件
	EditorAbstractWindow* const m_winMgr = nullptr;
	// 当前编辑的控件
	EditorAbstractWindow* m_currentWnd = nullptr;
	// 当前所有选中的控件ID
	std::unordered_set<ID_TYPE> m_selectWndIds;

private:
	// 消息处理记录
	bool m_mouseDown = false;

	// 时间统计，如果超过约定的时间，就开始备份
	float m_calcTime = 0;
	// 限定的时间
	float m_backupTime = 10;
	// 保存的文件名
	wxString m_editFile;
	// 用来记录保存的线程信息
	std::future<bool> m_saveThread;
	// 用来保持用于保存的对象
	EditorSave* m_editorSave = nullptr;
};

// 获取窗口句柄，该函数必须在初始化bench之后调用
inline HWND FormWorkArea::getHandle()
{ 
	return static_cast<HWND>(getBench()->GetHandle()); 
}

// 查找指定位置接受消息的控件
template<typename T>
inline EditorAbstractWindow * FormWorkArea::findWnd(wxCoord x, wxCoord y)
{
	int relX = narrow_cast<int>(x);
	int relY = narrow_cast<int>(y);
}

#endif	// FORM_WORK_AREA_H