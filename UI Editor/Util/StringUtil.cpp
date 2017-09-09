#include "StringUtil.h"

std::vector<wxString> Util::splitStr(const wxString& splittedStr, const wxString& delimiter)
{
	std::vector<wxString> ret;

	size_t begPos = 0;
	size_t endPos = splittedStr.find(delimiter, begPos);
	while (endPos != wxNOT_FOUND)
	{
		ret.push_back(splittedStr.Mid(begPos, endPos - begPos));
		begPos = endPos + delimiter.size();
		endPos = splittedStr.find(delimiter, begPos);
	}
	if (begPos < splittedStr.size())
	{
		ret.push_back(splittedStr.Mid(begPos));
	}

	return ret;
}
