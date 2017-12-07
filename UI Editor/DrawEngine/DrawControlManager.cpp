#include "DrawControlManager.h"
#include "d3dEngine/d3dEngine.h"
#include "Controls/StaticControl.h"
#include "Controls/ButtonControl.h"

#include "../EditorWindow/EditorManageWindow.h"
#include "../EditorWindow/EditorLabel.h"
#include "../EditorWindow/EditorButton.h"
#include "../EditorWindow/EditorFrame.h"

const D3DCOLOR MANAGER_ENABLE_COLOR = D3DCOLOR_RGBA(0, 255, 0, 255);

const D3DCOLOR FRAME_ENABLE_COLOR = D3DCOLOR_RGBA(0, 200, 0, 255);

DrawControlManager::DrawControlManager(HWND mainWndId)
{
	initEngine(mainWndId);
	initControls();
}

DrawControlManager::~DrawControlManager()
{

}

// 用来设置渲染窗口大小
void DrawControlManager::handlgeSizeChange(UINT width, UINT height)
{
	m_engine->handlgeSizeChange(width, height);
}

// 绘制控件之前准备
void DrawControlManager::drawWindowsBefore()
{
	m_engine->RenderControlsBefore();
}

// 绘制控件之后处理
void DrawControlManager::drawWindowsAfter()
{
	m_engine->RenderControlsEnd();
}

// 绘制管理控件对象
void DrawControlManager::drawWindow(const EditorManageWindow* manageWindow, int absX, int absY)
{
	int width = manageWindow->getWidth();
	int height = manageWindow->getHeight();
	RECT drawRegion = { absX, absY, absX + width, absY + height };
	
	m_engine->DrawRectLine(&drawRegion, MANAGER_ENABLE_COLOR);
}

// 绘制Static对象
void DrawControlManager::drawWindow(const EditorLabel* label, int absX, int absY)
{
	resetControl(label, m_staticControl.get(), absX, absY);
	// 绘制该控件
	m_staticControl->Render(m_engine.get(), m_elapsedTime);
}

// 绘制Button对象
void DrawControlManager::drawWindow(const EditorButton* button, int absX, int absY)
{
	resetControl(button, m_buttonControl.get(), absX, absY);
	m_buttonControl->SetPressed(button->isPressed());
	m_buttonControl->SetMouseOver(button->isMouseOver());
	// 绘制该控件
	m_buttonControl->Render(m_engine.get(), m_elapsedTime);
}

// 绘制Frame对象
void DrawControlManager::drawWindow(const EditorFrame * frame, int absX, int absY)
{
	int width = frame->getWidth();
	int height = frame->getHeight();
	RECT drawRegion = { absX, absY, absX + width, absY + height };
	m_engine->DrawRectLine(&drawRegion, FRAME_ENABLE_COLOR);
}

// 初始化绘制用的Engine
void DrawControlManager::initEngine(HWND mainWndId)
{
	m_engine.reset(new D3DEngine(mainWndId, D3DDEVTYPE_HAL, D3DCREATE_HARDWARE_VERTEXPROCESSING));
}

// 初始化各种绘制用的控件
void DrawControlManager::initControls()
{
	m_staticControl.reset(new StaticControl());
	m_engine->InitControl(m_staticControl.get());
	m_buttonControl.reset(new ButtonControl());
	m_engine->InitControl(m_buttonControl.get());
}
