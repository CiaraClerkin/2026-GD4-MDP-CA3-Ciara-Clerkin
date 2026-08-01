class RoboCatClient : public RoboCat
{
public:
	static	GameObjectPtr	StaticCreate() { return GameObjectPtr(new RoboCatClient()); }

	virtual void Update();

	virtual void SetZombie();
	virtual bool GetZombie();

	virtual void HandleDying() override;

	virtual void	Read(InputMemoryBitStream& inInputStream) override;

	void DoClientSidePredictionAfterReplicationForLocalCat(uint32_t inReadState);
	void DoClientSidePredictionAfterReplicationForRemoteCat(uint32_t inReadState);

	void RestartClock();

protected:
	RoboCatClient();


private:
	void InterpolateClientSidePrediction(float inOldRotation, const Vector3& inOldLocation, const Vector3& inOldVelocity, bool inIsForRemoteCat);
	float				mTimeLocationBecameOutOfSync;
	float				mTimeVelocityBecameOutOfSync;

	SpriteComponentPtr	mSpriteComponent;
	std::string spriteName;

	bool isZombie;
	sf::Clock mClock;
};

