#include "EditorManageWindow.h"
#include "../DrawEngine/DrawControlManager.h"

EditorManageWindow::EditorManageWindow(int relX, int relY, int width, int height)
	: inner::ContainerWindow<inner::EditorContainerFunc>(nullptr, relX, relY, width, height)
{
	
}

EditorManageWindow::~EditorManageWindow()
{
}


//在编辑界面上绘制
void EditorManageWindow::editDraw(int absX, int absY, DrawControlManager* drawManager)
{
	drawManager->drawWindow(this, absX, absY);
}