#ifndef DRAW_CONTROL_MANAGER_H
#define DRAW_CONTROL_MANAGER_H

/*
 * 文件名：DrawManager
 * 作用：用来管理创建的Control，创建的Control用在主工作区中进行控件的渲染
 */

#include <memory>
#include "UiEditorProtocol.h"
#include "../EditorWindow/EditorWindowInterface.h"
#include "AbstractEngine.h"

class StaticControl;
class ButtonControl;

class EditorManageWindow;
class EditorLabel;
class EditorButton;

class DrawControlManager
{
public:
	DrawControlManager(HWND mainWndId);
	~DrawControlManager();

	// 设置时间间隔
	void setElapsedTime(float elapsedTime) { m_elapsedTime = elapsedTime; }

	// 绘制控件之前准备
	void drawWindowsBefore();
	// 绘制控件之后处理
	void drawWindowsAfter();
	// 每帧检测，如果为true，则说明检测通过
	bool checkEveryFrame() const { return m_engine->checkEveryFrame(); }
	// 绘制控件对象
	template <typename T>
	void drawWindow(const T* window, int absX, int absY) { }
	// 绘制管理控件对象
	void drawWindow(const EditorManageWindow* manageWindow, int absX, int absY);
	// 绘制Static对象
	void drawWindow(const EditorLabel* label, int absX, int absY);
	// 绘制Button对象
	void drawWindow(const EditorButton* button, int absX, int absY);

private:
	// 重设control的一些属性
	template <typename EditorWindowType, typename ControlType>
	void resetControl(const EditorWindowType* editorWindow, ControlType* control, int absX, int absY);
private:
	// 初始化绘制用的Engine
	void initEngine(HWND mainWndId);
	// 初始化各种绘制用的控件
	void initControls();
private:
	// 每帧间隔
	float m_elapsedTime = 0.05f;
	// 绘制用的Engine
	std::unique_ptr<AbstractEngine> m_engine;
	// 绘制用的各种控件
	std::unique_ptr<StaticControl> m_staticControl;
	std::unique_ptr<ButtonControl> m_buttonControl;
};

// 重设control的一些属性
template <typename EditorWindowType, typename ControlType>
inline void DrawControlManager::resetControl(const EditorWindowType* editorWindow, ControlType* control, int absX, int absY)
{
	// 设置范围
	control->SetX(absX);
	control->SetY(absY);
	control->SetWidth(editorWindow->getWidth());
	control->SetHeight(editorWindow->getHeight());
	// 设置Control是否激活
	control->SetEnable(editorWindow->getEnable());
	control->SetText(&(editorWindow->getText()));
}

#endif	// DRAW_CONTROL_MANAGER_H
