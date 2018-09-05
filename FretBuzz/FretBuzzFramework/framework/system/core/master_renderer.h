#pragma once

#include "window.h"
#include "../timer/timerFPS.h"
#include "../../components/camera.h"
#include "../../graphics/sprite_batch_renderer.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class Game;
		class MasterRenderer
		{
		private:
			static MasterRenderer* s_pInstance;

			Window* m_pWindow = nullptr;
			TimerFPS* m_pTimer = nullptr;

			Camera* m_pMainCamera;

			ns_graphics::SpriteBatchRenderer* m_pSpriteBatchRenderer = nullptr;

		public:
			MasterRenderer(int a_iWidth, int a_iHeight, std::string a_strWindowName, bool a_bLogFPS = false);
			~MasterRenderer();

			GLFWwindow* getGLFWWindow() const;
			bool isWindowClosed() const;

			void beginFrame();
			float render(Game& m_Game);

			void closeWindow() const;
		};
	}
}