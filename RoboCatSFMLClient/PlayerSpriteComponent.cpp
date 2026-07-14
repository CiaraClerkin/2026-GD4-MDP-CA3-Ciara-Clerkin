#include "RoboCatClientPCH.hpp"
#include <iostream>


PlayerSpriteComponent::PlayerSpriteComponent(GameObject* inGameObject) :
	SpriteComponent(inGameObject)
{}

sf::Sprite& PlayerSpriteComponent::GetSprite()
{
	// Update the sprite based on the game object stuff.
	auto pos = mGameObject->GetLocation();
	auto rot = mGameObject->GetRotation();
	m_sprite.setPosition(pos.mX, pos.mY);
	m_sprite.setRotation(rot);
	RoboCat* player = dynamic_cast<RoboCat*>(mGameObject);
	Vector3 playerColor = player->GetColor();
	m_sprite.setColor(sf::Color(playerColor.mX, playerColor.mY, playerColor.mZ, 255));

	return m_sprite;
}

void PlayerSpriteComponent::SetTexture(TexturePtr inTexture)
{
	//auto tSize = inTexture->getSize();
	sf::Vector2i tSize = {24, 24};
	m_sprite.setTexture(*inTexture);
	rectSourceSprite = sf::IntRect(0, 24, 24, 24);
	m_sprite.setTextureRect(rectSourceSprite);
	m_sprite.setOrigin(tSize.x / 2, tSize.y / 2);
	m_sprite.setScale(sf::Vector2f(6.f * mGameObject->GetScale(), 6.f * mGameObject->GetScale()));
}

void PlayerSpriteComponent::Update(Vector3 velocity)
{
	if (clock.getElapsedTime().asSeconds() > 0.2f)
	{
		std::cout << velocity.mX << std::endl;

		if (velocity.mX == 0 && velocity.mY == 0)
		{
			spriteStart.x = 0;
			spriteStart.y = 24;
		}
		else 
		{
			if (velocity.mX == 0 || velocity.mY == 0)
			{
				if (velocity.mX > 0)
				{
					m_sprite.setScale(6.0f, 6.0f);
					spriteStart.x = 24 * 8;
					spriteStart.y = 24 * 2;
				}
				else if (velocity.mX < 0)
				{
					m_sprite.setScale(-6.0f, 6.0f);
					spriteStart.x = 24 * 8;
					spriteStart.y = 24 * 2;
				}

				if (velocity.mY > 0)
				{
					spriteStart.x = 0;
					spriteStart.y = 24 * 2;
				}
				else if (velocity.mY < 0)
				{
					spriteStart.x = 24 * 16;
					spriteStart.y = 24 * 2;
				}
			}
			else 
			{
				if (velocity.mY > 0)
				{
					if (velocity.mX > 0)
					{
						m_sprite.setScale(6.0f, 6.0f);
						spriteStart.x = 24 * 4;
						spriteStart.y = 24 * 2;
					}
					else 
					{
						m_sprite.setScale(-6.0f, 6.0f);
						spriteStart.x = 24 * 4;
						spriteStart.y = 24 * 2;
					}
				}
				else
				{
					if (velocity.mX > 0)
					{
						m_sprite.setScale(6.0f, 6.0f);
						spriteStart.x = 24 * 12;
						spriteStart.y = 24 * 2;
					}
					else
					{
						m_sprite.setScale(-6.0f, 6.0f);
						spriteStart.x = 24 * 12;
						spriteStart.y = 24 * 2;
					}
				}
			}
		}

		if (m_sprite.getTextureRect().left < spriteStart.x)
		{
			rectSourceSprite.left = spriteStart.x;
			rectSourceSprite.top = spriteStart.y;
			m_sprite.setTextureRect(rectSourceSprite);
		}

		//m_sprite.getTextureRect().left
		if (m_sprite.getTextureRect().left > spriteStart.x + (24 * 2))
		{
			rectSourceSprite.left = spriteStart.x;
			rectSourceSprite.top = spriteStart.y;
		}
		else
		{
			rectSourceSprite.left += 24;
		}

		m_sprite.setTextureRect(rectSourceSprite);
		clock.restart();
	}
}