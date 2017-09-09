#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <vector>
#include <wx/string.h>

namespace Util
{
	std::vector<wxString> splitStr(const wxString& splittedStr, const wxString& delimiter = " ");
}

#endif	// STRING_UTIL_H
