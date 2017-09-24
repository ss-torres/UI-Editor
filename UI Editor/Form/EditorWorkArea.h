#ifndef EDITOR_WORK_AREA_H
#define EDITOR_WORK_AREA_H

#include "WorkArea.h"
#include <wx/msw/wrapwin.h>		// 在wxWidgets中替代<Windows.h>
#include <wx/mdi.h>
#include <wx/panel.h>
#include <wx/dnd.h>
#include "../EditorWindow/WindowInterface.h"

class D3DEngine;
class CopyWindowValue;
class wxMDIParentFrame;
class wxMDIChildFrame;

class EditorWorkArea : public WorkArea
{
public:
	EditorWorkArea(wxMDIParentFrame* parent, const wxString& captionName, const wxPoint& position, const wxSize &size);
	~EditorWorkArea();

	// 获取该对象中的主窗口
	wxWindow* getBench() override;

	// 用来每帧处理
	void updateFrame(float dt);

	// 用来处理Drop事件
	void onDrop(wxCoord x, wxCoord y, const CopyWindowValue& winValue);

private:
	// 用来处理场景更新的计算
	void updateScene(float dt);
	// 用来每帧绘制
	void drawScene();

	// 获取窗口句柄，该函数必须在初始化bench之后调用
	HWND getHandle();

	// 创建一个窗口对象
	void createWndObject(AbstractEditorWindow* parent, int absX, int absY, const CopyWindowValue& winValue);
	// 初始化D3D成员
	void initD3DMember();

private:
	wxMDIChildFrame *m_bench;

	// 绘制D3D的引擎
	D3DEngine* m_d3dEngine;
	//// 用来存储创建的窗口
	//AbstractEditorWindow* m_editorWins = nullptr;
};

// 获取窗口句柄，该函数必须在初始化bench之后调用
inline HWND EditorWorkArea::getHandle()
{ 
	return static_cast<HWND>(getBench()->GetHandle()); 
}

#endif	// EDITOR_WORK_AREA_H
