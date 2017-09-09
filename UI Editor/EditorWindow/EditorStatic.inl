#ifndef EDITOR_STATIC_INL
#define EDITOR_STATIC_INL

#include "EditorStatic.h"

namespace inner
{
	EditorStatic::EditorStatic(AbstractEditorWindow* parent, int relX, int relY, int width, int height)
		: SimpleStatic<EditorFunc>(parent, relX, relY, width, height)
	{
	}

	EditorStatic::~EditorStatic()
	{
	}
}

#endif	// EDITOR_STATIC_INL