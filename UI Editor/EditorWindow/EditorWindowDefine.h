#ifndef EDITOR_WINDOW_DEFINE_H
#define EDITOR_WINDOW_DEFINE_H

/*
 * 文件名：EditorWindowType
 * 作用：添加一些用于Editor系列窗口的辅助常量，类等
 */

// Enable状态，是否显示，以及是否为focus有额外的对象标识
enum EDITOR_WINDOW_STATE
{
	EDITOR_STATE_NORMAL = 0,			// 正常状态，标识鼠标不在窗口上
	EDITOR_STATE_MOUSE_OVER = 1,		// 鼠标在窗口上
	EDITOR_STATE_PRESSED = 2,			// 鼠标在窗口上按下
};


#endif	// EDITOR_WINDOW_DEFINE_H
