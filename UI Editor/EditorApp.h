#ifndef EDITOR_APP_H
#define EDITOR_APP_H

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class GameTimer;
class EditorFrame;

class EditorApp : public wxApp
{
public:
	// 重载程序初始化函数
	bool OnInit() override;
	// 重载程序退出函数
	int OnExit() override;

	// this method is called by the active event loop when there are no events
	// to process
	bool ProcessIdle() override;

private:
	// 用来获取Frame窗口已经被销毁的消息
	void handleFrameDestroy(wxNotifyEvent& event);

private:
	// 用于计算D3D渲染事件
	GameTimer* m_timer;
	// 程序主窗口
	EditorFrame* m_editorFrame;
};

#endif	// EDITOR_APP_H
