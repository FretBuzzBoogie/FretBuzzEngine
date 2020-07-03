#pragma once
#include <fretbuzz_pch.h>
#include <system/game_startup.h>
//#include "game/scenes/gameplay_scene.h"

extern void SetStartupData(ns_fretBuzz::GameStartup& a_GameStartupData);

int main(int argc, char** argv)
{
	ns_fretBuzz::GameStartup m_GameStartupData;
	SetStartupData(m_GameStartupData);
	m_GameStartupData.run();
	return 0;
}