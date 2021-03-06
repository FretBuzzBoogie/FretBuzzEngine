#pragma once
#include "../sprite_animator.h"
#include "sprite_renderer.h"

namespace FRETBUZZ
{
	class  SpriteAnimationController : public IComponent
	{
	private:

		SpriteAnimator* m_pSpriteAnimator = nullptr;

		Sprite* m_pCurrentSprite = nullptr;
		SpriteRenderer* m_pSpriteRenderer = nullptr;
		std::vector<Sprite>* m_pCurrentSpriteSheet = nullptr;

		AnimationState* m_pAnimState = nullptr;

		bool m_bIsCurrentAnimationLooped = false;
		int m_iSpriteCount = 0;
		float m_fTimePassedInCurrentSprite = 0.0f;
		float m_fTimePerSprite = 0.0f;
		int m_iCurrentSpriteIndex = 0;

		std::string m_strCurrentonCompleteTrigger;

		std::string m_strDefaultStateID;

		void playStateID(std::string a_strAnimationID);

	protected:
		~SpriteAnimationController();

	public:
		SpriteAnimationController(GameObject* a_GameObj, std::string a_strAnimatorId);

		void play(std::string a_strAnimationID);

		virtual void update(const float& a_fDeltaTime) override;
	};
}