#ifndef EDITOR_SAVE_H
#define EDITOR_SAVE_H

/*
 * 用于文件保存的模块
 */

#include <atomic>
#include "SaveInfo.h"
#include "EditorUiXmlSaver.h"

class wxXmlNode;

class EditorSave
{
public:
	EditorSave();
	~EditorSave() = default;

	// 设置存储的文件信息
	void setSaveInfo(const SaveInfo& info) = delete;
	void setSaveInfo(SaveInfo&& info) { m_info = std::move(info); }
	// 设置存储文件名称
	void setSaveFileName(const wxString& fileName) { m_saveFileName = fileName; }
	void setSaveFileName(wxString&& fileName) { m_saveFileName = std::move(fileName); }
	// 用来设置是否继续保存操作
	// 线程安全函数
	void setSaveContinue(bool cont) { m_saveContinue.store(cont, std::memory_order_release); }
	// 进行窗口信息保存
	bool operator()();

private:
	// 将存储的窗口信息保存到文件
	void appendNodeInfo(const SaveInfo& info, wxXmlNode* parent);

	// 需要存储的窗口信息
	SaveInfo m_info;
	// 存储到的文件名称
	wxString m_saveFileName;
	// 用来判断主线程是否取消保存
	std::atomic<bool> m_saveContinue;

	// 用于保存窗口UI的功能类
	EditorUiXmlSaver* m_xmlSaver = nullptr;
};

#endif	// EDITOR_SAVE_H
