#pragma once
#include "master_renderer.h"
#include "../game.h"
#include "../../graphics/line_batch_renderer.h"
#include "../../graphics/sprite_batch_renderer.h"
#include "../../system/camera_manager.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		//singleton instance
		MasterRenderer* MasterRenderer::s_pInstance = nullptr;

		MasterRenderer* MasterRenderer::initialize(int a_iWidth, int a_iHeight, std::string a_strWindowName, bool a_bLogFPS)
		{
			if (s_pInstance != nullptr)
			{
				std::cout << "MasterRenderer::initialize:: Master Renderer already exists.\n";
				return nullptr;
			}
			s_pInstance = new MasterRenderer(a_iWidth, a_iHeight, a_strWindowName, a_bLogFPS);
			return s_pInstance;
		}

		void MasterRenderer::destroy()
		{
			delete s_pInstance;
			s_pInstance = nullptr;	
		}

		const MasterRenderer* MasterRenderer::get()
		{
			return s_pInstance;
		}

		MasterRenderer::MasterRenderer(int a_iWidth, int a_iHeight, std::string a_strWindowName, bool a_bLogFPS)
		{
			m_pWindow = Window::initialize(a_iWidth, a_iHeight, a_strWindowName);
			Window::registerWindowResizeCallback(windowResizeCallback);

			m_pBatchRendererManager = ns_graphics::BatchRendererManager::intialize();
			m_pCameraManager = CameraManager::initialize();
			m_pLightManager = ns_graphics::LightManager::initialize();

			m_pTimer = new TimerFPS(a_bLogFPS);
		}

		MasterRenderer:: ~MasterRenderer()
		{
			m_pBatchRendererManager->destroy();

			if (m_pTimer != nullptr)
			{
				delete m_pTimer;
				m_pTimer = nullptr;
			}
			
			m_pCameraManager->destroy();
			m_pLightManager->destroy();

			Window::unregisterWindowResizeCallback(windowResizeCallback);
			m_pWindow->destroy();
		}

		float MasterRenderer::render(Game& m_Game)
		{
			m_pWindow->clear();

			m_pBatchRendererManager->beginBatches();

			m_pCameraManager->updateViewMatrix();
			m_pCameraManager->renderFrame(m_Game);

			m_pBatchRendererManager->endAndflushBatches();

			m_pWindow->update();
			m_pTimer->update();
			return m_pTimer->getDeltaTime();
		}

		bool MasterRenderer::isWindowClosed() const
		{
			return m_pWindow->isWindowClosed();
		}

		GLFWwindow* MasterRenderer::getGLFWWindow() const
		{
			return m_pWindow->getGLFWWindow();
		}

		void MasterRenderer::closeWindow() const
		{
			m_pWindow->closeWindow();
		}

		void MasterRenderer::windowResizeCallback()
		{
			s_pInstance->m_pCameraManager->windowResize();
		}
	}
}