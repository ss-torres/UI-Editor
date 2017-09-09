#ifndef EDITOR_BUTTON_INL
#define EDITOR_BUTTON_INL

#include "EditorButton.h"

namespace inner
{
	EditorButton::EditorButton(AbstractEditorWindow* parent, int relX, int relY, int width, int height)
		: SimpleButton<EditorFunc>(parent, relX, relY, width, height)
	{
	}

	EditorButton::~EditorButton()
	{

	}
}

#endif	// EDITOR_BUTTON_INL