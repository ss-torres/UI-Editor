#include "DrawManager.h"
#include "d3dEngine/d3dEngine.h"
#include "Controls/StaticControl.h"
#include "Controls/ButtonControl.h"

DrawManager::DrawManager()
{
	initControls();
}

DrawManager::~DrawManager()
{

}

// 初始化绘制用的Engine
void DrawManager::initEngine()
{
	
}

// 初始化各种绘制用的控件
void DrawManager::initControls()
{
	m_staticControl.reset(new StaticControl());
	m_buttonControl.reset(new ButtonControl());
}
