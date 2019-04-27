#pragma once
#include <components/gameobject_components/behaviour.h>
#include "components/gameobject_components/sprite_animation_controller.h"
#include <components/gameobject_components/rect_collider.h>

namespace ns_HMGame
{
	class PlayerController : public ns_fretBuzz::ns_system::Behaviour
	{
	private:
		double m_dMouseX = 0.0;
		double m_dMouseY = 0.0;

		float m_fVelocity = 500.0f;

		bool m_bIsRunning = false;

		ns_fretBuzz::ns_system::SpriteAnimationController* m_pUpperSpriteAnimator = nullptr;
		ns_fretBuzz::ns_system::SpriteAnimationController* m_pLegsSpriteAnimator = nullptr;
		
		ns_fretBuzz::ns_system::RectCollider* m_pRectCollider = nullptr;

		ns_fretBuzz::ns_system::GameObject* m_pCamGameObj = nullptr;
		ns_fretBuzz::ns_system::GameObject* m_pPlayerUpperGameObj = nullptr;
		ns_fretBuzz::ns_system::GameObject* m_pGameObjCharacterLegs = nullptr;
		
		void manageInput();
	public:
		PlayerController(ns_fretBuzz::ns_system::GameObject& a_GameObject, ns_fretBuzz::ns_system::GameObject* a_pCamGameObject, ns_fretBuzz::ns_system::GameObject* a_pPlayerUpperGameObj, ns_fretBuzz::ns_system::GameObject* a_pLegsGameObject);

		virtual void update(float a_fDeltaTime) override;
	};
}