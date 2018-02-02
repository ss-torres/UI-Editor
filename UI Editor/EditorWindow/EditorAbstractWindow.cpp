#include "EditorAbstractWindow.h"
#include "EditorWindowCheck.h"

#include "../AutoSave/SaveInfo.h"


namespace inner
{
	void SimpleWindow<EditorEditableFunc>::appendMySelf(SaveInfo& parentInfo, bool replace) const
	{
		SaveInfo info;
		info.setWinType(getWindowClassName());
		info.setWinAttrs(getWinAttrs());
		if (isContainerWnd())
		{
			auto beg = getChildrenConstBeg();
			auto end = getChildrenConstEnd();
			for (; beg != end; ++beg)
			{
				auto child = dynamic_cast<SELF_TYPE*>(*beg);
				if (child)
				{
					child->appendMySelf(info, false);
				}
			}
		}
		
		if (!replace)
		{
			parentInfo.push_back(std::move(info));
		}
		else
		{
			parentInfo = std::move(info);
		}
	}
}