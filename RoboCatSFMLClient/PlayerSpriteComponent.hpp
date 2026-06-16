#pragma once
class PlayerSpriteComponent : public SpriteComponent
{
public:
	PlayerSpriteComponent(GameObject* inGameObject);
	virtual sf::Sprite& GetSprite() override;
	virtual void SetTexture(TexturePtr inTexture) override;
	virtual void Update(Vector3 velocity);
private:
	sf::IntRect rectSourceSprite;
	sf::Vector2i spriteStart;
	sf::Clock clock;
};

typedef shared_ptr<PlayerSpriteComponent >	PlayerSpriteComponentPtr;

