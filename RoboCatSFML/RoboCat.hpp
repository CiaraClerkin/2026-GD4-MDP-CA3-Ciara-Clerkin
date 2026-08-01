class RoboCat : public GameObject
{
public:
	CLASS_IDENTIFICATION('RCAT', GameObject)

	enum ECatReplicationState
	{
		ECRS_Pose = 1 << 0,
		ECRS_Color = 1 << 1,
		ECRS_PlayerId = 1 << 2,
		ECRS_Health = 1 << 3,
		ECRS_Zombie = 1 << 4,

		ECRS_AllState = ECRS_Pose | ECRS_Color | ECRS_PlayerId | ECRS_Health | ECRS_Zombie
	};


	static	GameObject* StaticCreate() { return new RoboCat(); }

	virtual uint32_t GetAllStateMask()	const override { return ECRS_AllState; }

	virtual	RoboCat* GetAsCat() override { return this; }

	virtual void Update() override;

	void ProcessInput(float inDeltaTime, const InputState& inInputState);
	void SimulateMovement(float inDeltaTime);

	void ProcessCollisions();
	void ProcessCollisionsWithScreenWalls();

	void		SetPlayerId(uint32_t inPlayerId) { mPlayerId = inPlayerId; }
	uint32_t	GetPlayerId()						const { return mPlayerId; }

	void			SetVelocity(const Vector3& inVelocity) { mVelocity = inVelocity; }
	const Vector3& GetVelocity()						const { return mVelocity; }

	bool GetIsZombie() { return mIsZombie; }
	void SetIsZombie() { mIsZombie = true; }

	//void SetTimer(float timer) { time = timer; }
	//sf::Clock GetTimer() { return m_GameTimer; }

	void SetIsLatestPlayer(bool inLatestPlayer) { mLatestPlayer = inLatestPlayer; }
	bool GetIsLatestPlayer() { return mLatestPlayer; }

	void SetLatestPlayer();

	bool AreAllZombies();

	void SetFirstTime(bool inFirstTime) { firstTime = inFirstTime; }
	bool GetFirstTime() { return firstTime; }

	void SetClockFirstTime(bool inFirstTime) { clockFirstTime = inFirstTime; }
	bool GetClockFirstTime() { return clockFirstTime; }

	void SetIsClockPendingRestart(bool inPending) { mIsClockPendingRestart = inPending; }
	bool GetIsClockPendingRestart() { return mIsClockPendingRestart; }

	void AlertRestartClocks();

	virtual uint32_t	Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const override;

protected:
	RoboCat();

private:


	void	AdjustVelocityByThrust(float inDeltaTime);

	Vector3				mVelocity;


	float				mMaxLinearSpeed;
	float				mMaxRotationSpeed;

	//bounce fraction when hitting various things
	float				mWallRestitution;
	float				mCatRestitution;


	uint32_t			mPlayerId;

	mutable bool		firstTime;
	mutable bool		mLatestPlayer;
	mutable bool		mIsClockPendingRestart;
	mutable bool		clockFirstTime;

protected:

	///move down here for padding reasons...

	float				mLastMoveTimestamp;

	float				mThrustDir;
	float				mThrustSide;
	int					mHealth;

	bool				mIsShooting;

	bool				mIsZombie;
	bool				mAreAllZombies;
};

typedef shared_ptr< RoboCat >	RoboCatPtr;

