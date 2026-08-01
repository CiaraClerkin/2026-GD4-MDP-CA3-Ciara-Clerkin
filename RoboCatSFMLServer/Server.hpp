
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
};

