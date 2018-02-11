#include <thread>
#include "EditorSave.h"

EditorSave::EditorSave()
	: m_saveContinue(true)
{
	m_xmlSaver = new EditorUiXmlSaver();
}

// 进行窗口信息保存
bool EditorSave::operator()()
{
	auto node = m_xmlSaver->addRootWindow(m_info.getWinType(), m_info.getWinAttrs());
	for (auto it = m_info.getChildConstBeg(); it != m_info.getChildConstEnd(); ++it)
	{
		// 如果主线程取消，则返回
		if (!m_saveContinue.load(std::memory_order_relaxed))
		{
			return false;
		}

		appendNodeInfo(*it, node);
	}
	// 如果主线程取消，则返回
	if (!m_saveContinue.load(std::memory_order_relaxed))
	{
		return false;
	}

	m_xmlSaver->saveWindow(m_saveFileName);
	return true;
}

// 将存储的窗口信息保存到文件
void EditorSave::appendNodeInfo(const SaveInfo & info, wxXmlNode *parent)
{
	// 如果主线程设置取消保存过程，则直接返回
	if (!m_saveContinue.load(std::memory_order_relaxed))
	{
		return;
	}

	auto node = m_xmlSaver->appendChildWindow(info.getWinType(), info.getWinAttrs(), parent);
	for (auto it = info.getChildConstBeg(); it != info.getChildConstEnd(); ++it)
	{
		appendNodeInfo(*it, node);
	}
}