#include <fretbuzz_pch.h>
#include "master_renderer.h"
#include "graphics/line_batch_renderer.h"
#include "graphics/sprite_batch_renderer.h"
#include "system/camera_manager.h"
#include <imgui/imgui.h>
#include <examples/imgui_impl_glfw.cpp>
#include <examples/imgui_impl_opengl3.cpp>
#include "../scene_manager.h"
#include "system.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		//singleton instance
		MasterRenderer* MasterRenderer::s_pInstance = nullptr;

		MasterRenderer* MasterRenderer::initialize(Window& a_Window)
		{
			if (s_pInstance != nullptr)
			{
				std::cout << "MasterRenderer::initialize:: Master Renderer already exists.\n";
				return nullptr;
			}
			s_pInstance = new MasterRenderer(a_Window);
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

		MasterRenderer::MasterRenderer(Window& a_Window)
		{
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			glFrontFace(GL_CCW);
			glEnable(GL_DEPTH_TEST);

			glDepthMask(GL_TRUE);
			glDepthFunc(GL_LESS);

			m_pBatchRendererManager = BatchRendererManager::intialize();
			m_pCameraManager = CameraManager::initialize();
			m_pLightManager = LightManager::initialize();
			m_pShaderManager = ShaderManager::initialize();
			//m_pPostProcessManager = PostProcessManager::initialize(a_iWidth, a_iHeight, Material::EDGE_DETECT);

			//m_pPostProcessManager->togglePostProcess(false);

#if _IS_DEBUG
			ImGui::CreateContext();
			ImGui::StyleColorsDark();
			ImGui_ImplGlfw_InitForOpenGL(a_Window.getGLFWWindow(), true);
			ImGui_ImplOpenGL3_Init();
#endif
		}

		MasterRenderer:: ~MasterRenderer()
		{
			m_pBatchRendererManager->destroy();
			//m_pPostProcessManager->destroy();
			m_pCameraManager->destroy();
			m_pLightManager->destroy();
			m_pShaderManager->destroy();
		}

		void MasterRenderer::render(ns_system::SceneManager& a_SceneManager, float a_fDeltaTime)
		{
			//Render Pass
			m_pCameraManager->updateViewMatrix();
			std::vector<Camera*>& l_vectCameras = m_pCameraManager->getCameras();
			size_t l_iCameraCount = l_vectCameras.size();
			for (size_t l_iCameraIndex = 0; l_iCameraIndex < l_iCameraCount; l_iCameraIndex++)
			{
				if (l_vectCameras[l_iCameraIndex]->isActiveAndEnabled())
				{
					//a_PostProcessManager.begin();
					m_pBatchRendererManager->beginBatches();

					Camera& l_CurrentCamera = *l_vectCameras[l_iCameraIndex];
					Window::get()->setViewport(l_CurrentCamera.getViewport());
					a_SceneManager.renderActiveScenes(l_CurrentCamera);

					m_pBatchRendererManager->endAndflushBatches();
					glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
					//a_PostProcessManager.draw(0, l_CurrentCamera);
				}
			}

#if _IS_DEBUG

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			m_pInspector->render(a_SceneManager, a_fDeltaTime);

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif
		}

		void MasterRenderer::closeWindow() const
		{
#if _IS_DEBUG
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
#endif
		}

#if _IS_DEBUG
		void MasterRenderer::setInspector(ns_editor::Inspector* a_pInspector)
		{
			m_pInspector = a_pInspector;
		}
#endif
	}
}