#ifndef DRAW_MANAGER_H
#define DRAW_MANAGER_H

/*
 * 文件名：DrawManager
 * 作用：用来连接绘制功能和窗口对象，实现窗口对象的绘制
 */

#include <memory>
#include "../EditorWindow/EditorWindowInterface.h"
#include "AbstractEngine.h"

class StaticControl;
class ButtonControl;

class DrawManager
{
public:
	DrawManager();
	~DrawManager();

private:
	// 初始化绘制用的Engine
	void initEngine();
	// 初始化各种绘制用的控件
	void initControls();
private:
	// 绘制用的Engine
	std::unique_ptr<AbstractEngine> m_engine;
	// 绘制用的各种控件
	std::unique_ptr<StaticControl> m_staticControl;
	std::unique_ptr<ButtonControl> m_buttonControl;
};

#endif	// DRAW_MANAGER_H
