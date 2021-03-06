#include <fretbuzz_pch.h>
#include "sprite.h"

namespace FRETBUZZ
{
	SpriteGroup::SpriteGroup(Texture* a_pTexture, std::vector<Sprite> a_vectSpriteData)
		: m_vectSpriteData{a_vectSpriteData},
		m_pTexture{a_pTexture },
			IManagedResource()
	{
	}

	SpriteGroup::SpriteGroup(SpriteGroup& a_Sprite)
		: m_vectSpriteData{ a_Sprite.m_vectSpriteData },
		m_pTexture{ a_Sprite.m_pTexture },
		IManagedResource()
	{
		
	}

	SpriteGroup::SpriteGroup(SpriteGroup&& a_Sprite)
		: m_vectSpriteData{ a_Sprite.m_vectSpriteData },
		m_pTexture{ a_Sprite.m_pTexture },
			IManagedResource()
	{
		
	}

	void SpriteGroup::operator=(SpriteGroup& a_Sprite)
	{
		m_pTexture = a_Sprite.m_pTexture;
		m_vectSpriteData = a_Sprite.m_vectSpriteData;
	}

	void SpriteGroup::operator=(SpriteGroup&& a_Sprite)
	{
		m_pTexture = a_Sprite.m_pTexture;
		m_vectSpriteData = a_Sprite.m_vectSpriteData;
	}

	SpriteGroup::~SpriteGroup()
	{
		
	}

	void SpriteGroup::destroyResource()
	{
		m_pTexture = nullptr;
	}

	std::vector<Sprite>* SpriteGroup::getSprites()
	{
		return &m_vectSpriteData;
	}

	Sprite* SpriteGroup::getSprite(int l_iSpriteIndex)
	{
		return &m_vectSpriteData[l_iSpriteIndex];
	}

	Sprite* SpriteGroup::getSpriteByID(std::string l_strSpriteID)
	{
		for (std::vector<Sprite>::iterator l_Iterator = m_vectSpriteData.begin(),
			l_IteratorEnd = m_vectSpriteData.end();
			l_Iterator != l_IteratorEnd;
			l_Iterator++)
		{
			if (l_Iterator->getID().compare(l_strSpriteID) == 0)
			{
				return &(*l_Iterator);
			}
		}
		return nullptr;
	}
}