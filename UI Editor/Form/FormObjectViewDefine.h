#ifndef FORM_OBJECT_VIEW_DEFINE_H
#define FORM_OBJECT_VIEW_DEFINE_H

#include <wx/clntdata.h>
#include "../EditorWindow/EditorFunc.h"

class EditorWindowID : public wxClientData
{
public:
	EditorWindowID(ID_TYPE editorWinId)
		: m_editorWinId(editorWinId)
	{

	}
	~EditorWindowID() override { }

	// 获取节点对应的控件ID
	ID_TYPE getEditorWinId() const { return m_editorWinId; }
private:
	ID_TYPE m_editorWinId;
};

#endif	// FORM_OBJECT_VIEW_DEFINE_H
