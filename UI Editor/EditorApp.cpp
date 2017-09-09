#include "EditorApp.h"
#include "EditorFrame.h"
#include "DrawEngine\GameTimer.h"

// 重载程序初始化函数
bool EditorApp::OnInit()
{
	// 调用父类的初始化函数
	if (!wxApp::OnInit())
		return false;

	m_editorFrame = new EditorFrame("UI Editor");
	m_editorFrame->SetSize(1080, 810);
	m_editorFrame->Center();

	// 显示主界面
	m_editorFrame->Show(true);
	// 绑定消息，获取Frame销毁消息
	Bind(DESTROY_EVENT, &EditorApp::handleFrameDestroy, this, m_editorFrame->GetId());

	// 初始化时间
	m_timer = new GameTimer();
	m_timer->reset();

	return true;
}

// 重载程序退出函数
int EditorApp::OnExit()
{
	delete m_timer;
	return 0;
}

// this method is called by the active event loop when there are no events
// to process
bool EditorApp::ProcessIdle()
{
	bool ret = wxApp::ProcessIdle();
	// 如果不需要额外的Idle事件，则处理D3D相关内容
	if (!ret)
	{
		do
		{
			// 查看该程序是否为前台程序
			if (!IsActive())
			{
				Sleep(20);
				break;
			}
			m_timer->tick();
			if (m_editorFrame)
			{
				m_editorFrame->updateFrame(m_timer->deltaTime());
			}
		} while (0);
	}

	return ret;
}

// 用来获取Frame窗口已经被销毁的消息
void EditorApp::handleFrameDestroy(wxNotifyEvent & event)
{
	m_editorFrame = NULL;
}
