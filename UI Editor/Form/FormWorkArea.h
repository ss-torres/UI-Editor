#ifndef FORM_WORK_AREA_H
#define FORM_WORK_AREA_H

#include <memory>
#include <wx/msw/wrapwin.h>		// 在wxWidgets中替代<Windows.h>
#include <wx/panel.h>
#include <wx/dnd.h>
#include "WorkArea.h"
#include "../EditorWindow/EditorWindowInterface.h"

class DrawControlManager;
class CopyWindowInfo;
class wxMDIParentFrame;
class wxMDIChildFrame;

class FormWorkArea : public WorkArea
{
public:
	FormWorkArea(wxMDIParentFrame* parent, const wxString& captionName, const wxPoint& position, const wxSize &size);
	~FormWorkArea();

	// 获取该对象中的主窗口
	wxWindow* getBench() override;
	// 获取控件管理对象的ID
	ID_TYPE getManageWindowId() const;
	// 设置当前选中的控件
	void setCurrentWindow(EditorAbstractWindow* currentWnd) { m_currentWnd = currentWnd; }
	// 获取当前选中的控件
	EditorAbstractWindow* getCurrentWindow() const { return m_currentWnd; }
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
	// 用来处理场景更新的计算
	void updateScene(float dt);
	// 用来每帧绘制
	void drawScene(float dt);
	//绘制子控件
	void drawWindowRecur(EditorAbstractWindow* editorWindow, int absX, int absY);

	// 获取窗口句柄，该函数必须在初始化bench之后调用
	HWND getHandle();

private:
	// 查找指定位置接受消息的控件
	template <typename T = UiEditable<EditorAbstractWindow>>
	EditorAbstractWindow* findWnd(wxCoord x, wxCoord y);
	// 创建一个控件对象
	void createWndObject(EditorAbstractWindow* parent, int absX, int absY, const CopyWindowInfo& winValue);

	// 初始化显示窗口
	void initFrameWnd(wxMDIParentFrame* parent, const wxString& captionName, const wxPoint& position, const wxSize &size);
	// 初始化管理控件
	void initManageWnd();

private:
	wxPanel *m_bench;

	// 绘制该编辑区域控件的对象
	std::unique_ptr<DrawControlManager> m_drawManager;
	// 用来存储创建的控件
	EditorAbstractWindow* const m_winMgr = nullptr;
	// 当前选中的控件
	EditorAbstractWindow* m_currentWnd;
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