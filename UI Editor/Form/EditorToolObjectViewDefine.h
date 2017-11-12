#ifndef EDITOR_TOOL_OBJECT_VIEW_DEFINE_H
#define EDITOR_TOOL_OBJECT_VIEW_DEFINE_H

#include <wx/clntdata.h>
#include "../EditorFuncDefine.h"

class EditorWindowID : public wxClientData
{
public:
	EditorWindowID(ID_TYPE editorWinId)
		: m_editorWinId(editorWinId)
	{

	}
	~EditorWindowID() override { }

	// 获取节点对应的窗口ID
	ID_TYPE getEditorWinId() const { return m_editorWinId; }
private:
	ID_TYPE m_editorWinId;
};

#endif	// EDITOR_TOOL_OBJECT_VIEW_DEFINE_H
