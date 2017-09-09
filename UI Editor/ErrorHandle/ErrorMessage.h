#ifndef ERROR_MESSAGE_H
#define ERROR_MESSAGE_H

#include <wx/msgdlg.h> 

namespace EditorMessage
{
	inline void showErrorMessage(const wxString& errorMsg, const wxString& captionName = wxEmptyString);
}

void EditorMessage::showErrorMessage(const wxString& errorMsg, const wxString& captionName)
{
	wxMessageBox(errorMsg, captionName);
}

#endif	// ERROR_MESSAGE_H
