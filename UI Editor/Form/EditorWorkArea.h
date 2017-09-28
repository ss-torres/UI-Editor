#ifndef EDITOR_WORK_AREA_H
#define EDITOR_WORK_AREA_H

#include "WorkArea.h"
#include <wx/msw/wrapwin.h>		// 在wxWidgets中替代<Windows.h>
#include <wx/mdi.h>
#include <wx/panel.h>
#include <wx/dnd.h>
#include "../EditorWindow/WindowInterface.h"
#include "../EditorWindow/EditorWindowCheck.h"

class D3DEngine;
class CopyWindowInfo;
class wxMDIParentFrame;
class wxMDIChildFrame;

class EditorWorkArea : public WorkArea
{
public:
	EditorWorkArea(wxMDIParentFrame* parent, const wxString& captionName, const wxPoint& position, const wxSize &size);
	~EditorWorkArea();

	// 获取该对象中的主窗口
	wxWindow* getBench() override;
	// 为ID的窗口添加一个子窗口
	bool pushBackWindow(ID_TYPE parentId, AbstractEditorWindow* insertWnd);
	// 将特定ID的子窗口移除
	bool removeWindow(ID_TYPE removeId);

public:
	// 用来每帧处理
	void updateFrame(float dt);

	// 用来处理Drop事件
	void onDrop(wxCoord x, wxCoord y, const CopyWindowInfo& winValue);

private:
	// 用来处理场景更新的计算
	void updateScene(float dt);
	// 用来每帧绘制
	void drawScene();

	// 获取窗口句柄，该函数必须在初始化bench之后调用
	HWND getHandle();

private:
	// 查找指定位置接受消息的窗口
	template <typename T = UiEditable<AbstractEditorWindow>>
	AbstractEditorWindow* findWnd(wxCoord x, wxCoord y);
	// 创建一个窗口对象
	void createWndObject(AbstractEditorWindow* parent, int absX, int absY, const CopyWindowInfo& winValue);
	// 初始化管理窗口
	void initManageWnd();

private:
	wxMDIChildFrame *m_bench;

	// 绘制D3D的引擎
	D3DEngine* m_d3dEngine;
	// 用来存储创建的窗口
	AbstractEditorWindow* m_editorWins = nullptr;
};

// 获取窗口句柄，该函数必须在初始化bench之后调用
inline HWND EditorWorkArea::getHandle()
{ 
	return static_cast<HWND>(getBench()->GetHandle()); 
}

// 查找指定位置接受消息的窗口
template<typename T>
inline AbstractEditorWindow * EditorWorkArea::findWnd(wxCoord x, wxCoord y)
{
	int relX = narrow_cast<int>(x);
	int relY = narrow_cast<int>(y);
}

#endif	// EDITOR_WORK_AREA_H