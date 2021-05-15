#include "HUDContent.h"
#include <cstddef>
#include "HUD.h"

HUDContent* HUDContent::__instance = NULL;

HUDContent* HUDContent::GetInstance()
{
	if (__instance == NULL) __instance = new HUDContent();
	return __instance;
}

void HUDContent::SetUpContent()
{
	world = new CText(Content::World, HUD_ALIGN_LEFT, HUD_ALIGN_TOP);
	live = new CText(Content::Live, HUD_ALIGN_LEFT, HUD_ALIGN_BOTTOM);
	time = new CText(Content::Time, HUD_ALIGN_RIGHT, HUD_ALIGN_BOTTOM);
}

void HUDContent::Update()
{
	world->Update();
	live->Update();
	time->Update();
}

void HUDContent::Render()
{
	world->RenderText();
	live->RenderText();
	time->RenderText();
}