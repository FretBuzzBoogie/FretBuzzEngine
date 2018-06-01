#pragma once
#include "system.h"
#include <iostream>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		System* System::s_pInstance = nullptr;

		System::System()
		{
			m_pFPStimer = new TimerFPS(true);
		}

		bool System::initialize()
		{
			s_pInstance = new System();
			s_pInstance->m_pWindow = new Window(800, 600, "FretBuzz");
			
			return s_pInstance->m_pWindow->isInitialized();
		}

		System::~System()
		{
			if (m_pWindow != nullptr)
			{
				delete m_pWindow;
				m_pWindow = nullptr;
			}

			if (m_pFPStimer != nullptr)
			{
				delete m_pFPStimer;
				m_pFPStimer = nullptr;
			}

			s_pInstance = nullptr;
		}

		void System::Run()
		{
			if (s_pInstance != nullptr)
			{
				return;
			}

			if (!initialize())
			{
				destroy();
				return;
			}

			Window& l_Window = *(s_pInstance->m_pWindow);
			TimerFPS& l_FPSTimer = *(s_pInstance->m_pFPStimer);

			while (!l_Window.isWindowClosed())
			{
				l_Window.clear();


				l_Window.update();
				l_FPSTimer.update();
			}

			destroy();
		}

		void System::destroy()
		{
			if (s_pInstance != nullptr)
			{
				delete s_pInstance;
				s_pInstance = nullptr;
			}
		}
	}
}