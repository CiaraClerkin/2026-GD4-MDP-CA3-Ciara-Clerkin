typedef shared_ptr< sf::Texture > TexturePtr;
typedef shared_ptr<sf::Font> FontPtr;
typedef sf::Vector2<int> Vector2i;

class SpriteComponent
{
public:

	SpriteComponent(GameObject* inGameObject);
	~SpriteComponent();


	virtual void SetTexture(TexturePtr inTexture);
	//void SetTexture(TexturePtr inTexture, Vector2i size);
	virtual sf::Sprite& GetSprite();

	virtual void Update(Vector3 velocity);

	/*void frameRight();
	void frameLeft();
	void animate(float dt = 0.016667);

	void setFrameTimer(float frame_time);*/

private:
	sf::IntRect rectSourceSprite;
	sf::Clock clock;

protected:

	sf::Sprite m_sprite;

	//don't want circular reference...
	GameObject* mGameObject;

	Vector2i texCoord;
	int frameSize;

	float frameTimer;
	float frameTimerMax;

	void InitTimers();
};

typedef shared_ptr< SpriteComponent >	SpriteComponentPtr;

