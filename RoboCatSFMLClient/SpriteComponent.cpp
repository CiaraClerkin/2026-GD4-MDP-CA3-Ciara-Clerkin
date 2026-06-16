#include "RoboCatClientPCH.hpp"


SpriteComponent::SpriteComponent(GameObject* inGameObject) :
	mGameObject(inGameObject)
{
	//and add yourself to the rendermanager...
	RenderManager::sInstance->AddComponent(this);
}

SpriteComponent::~SpriteComponent()
{
	//don't render me, I'm dead!
	RenderManager::sInstance->RemoveComponent(this);
}

void SpriteComponent::SetTexture(TexturePtr inTexture)
{
	auto tSize = inTexture->getSize();
	//rectSourceSprite = sf::IntRect(0, 0, 24, 24);
	//m_sprite.setTextureRect(rectSourceSprite);
	m_sprite.setTexture(*inTexture);
	//m_sprite.setOrigin(tSize.x / 2, tSize.y / 2);
	m_sprite.setScale(sf::Vector2f(1.f * mGameObject->GetScale(), 1.f * mGameObject->GetScale()));
}

/*void SpriteComponent::SetTexture(TexturePtr inTexture, Vector2i size)
{
	InitTimers();
	
	texCoord = size;
	auto tSize = inTexture->getSize();
	m_sprite.setTexture(*inTexture);
	m_sprite.setOrigin(tSize.x / 2, tSize.y / 2);
	m_sprite.setScale(sf::Vector2f(1.f * mGameObject->GetScale(), 1.f * mGameObject->GetScale()));
	m_sprite.setTextureRect({ size, sf::Vector2i(tSize) });
}*/

sf::Sprite& SpriteComponent::GetSprite()
{
	// Update the sprite based on the game object stuff.
	auto pos = mGameObject->GetLocation();
	auto rot = mGameObject->GetRotation();
	m_sprite.setPosition(pos.mX, pos.mY);
	m_sprite.setRotation(rot);

	return m_sprite;
}

void SpriteComponent::Update(Vector3 velocity)
{
}

/*void SpriteComponent::InitTimers()
{
	frameTimer = 0.0f;
	frameTimerMax = 0.0f;
}

void SpriteComponent::frameRight()
{
	this->texCoord.x += textures->getFrameSize().x;
	if (this->texCoord.x >= textures->getSize().x)
	{
		this->texCoord.x = 0;
	}
}

void SpriteComponent::frameLeft()
{
	this->texCoord.x -= textures->getFrameSize().x;
	if (this->texCoord.x < 0) 
	{
		this->texCoord.x = textures->getSize().x - textures->getFrameSize().x;
	}
}

void SpriteComponent::animate(float dt)
{
	frameTimer += dt;
	if (frameTimer >= frameTimerMax)
	{
		frameRight();
		this->setTextureRect(sf::IntRect(texCoord, sf::Vector2i(textures->getFrameSize())));
	}
}

void SpriteComponent::setFrameTimer(float frame_time)
{
	frameTimerMax = frame_time;
}*/