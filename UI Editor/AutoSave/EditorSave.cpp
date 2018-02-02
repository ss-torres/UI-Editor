#include <thread>
#include "EditorSave.h"


EditorSave* EditorSave::s_editor_save = nullptr;

EditorSave::EditorSave()
	: m_saveContinue(false)
{
}

// 进行窗口信息保存
bool EditorSave::operator()()
{
	std::this_thread::sleep_for(std::chrono::seconds(20));
	return false;
}
