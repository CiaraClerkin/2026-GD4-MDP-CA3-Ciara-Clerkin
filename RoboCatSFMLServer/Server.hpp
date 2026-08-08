
class Server : public Engine
{
public:

	static bool StaticInit();

	virtual void DoFrame() override;

	virtual int Run();

	void HandleNewClient(ClientProxyPtr inClientProxy);
	void HandleLostClient(ClientProxyPtr inClientProxy);

	RoboCatPtr	GetCatForPlayer(int inPlayerId);
	void	SpawnCatForPlayer(int inPlayerId);

	//bool AreAllZombies();

	//void UnSetLatestPlayer();
	

private:
	Server();

	bool	InitNetworkManager();
	void	SetupWorld();

	bool	isFirstPlayer;
	//int		m_timer;

	const Vector3 spawnPositions[16]{
		{200, 200, 0},
		{800, 200, 0},
		{1400, 200, 0},
		{2000, 200, 0},
		{2600, 200, 0},
		{3200, 200, 0},
		{3900, 200, 0},
		{3900, 800, 0},
		{3900, 1400, 0},
		{3900, 2000, 0},
		{3200, 2000, 0},
		{2600, 2000, 0},
		{2000, 2000, 0},
		{1400, 2000, 0},
		{800,  2000, 0},
		{200,  2000, 0}
	};
};

