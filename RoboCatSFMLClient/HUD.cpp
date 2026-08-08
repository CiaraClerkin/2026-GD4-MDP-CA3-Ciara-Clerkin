#include "RoboCatClientPCH.hpp"

std::unique_ptr< HUD >	HUD::sInstance;

HUD::HUD() :
	mScoreBoardOrigin(50.f + WindowManager::sInstance->getView().getCenter().x, 60.f + WindowManager::sInstance->getView().getCenter().y, 0.0f),
	mBandwidthOrigin(50.f + WindowManager::sInstance->getView().getCenter().x, + WindowManager::sInstance->getView().getCenter().y, 0.0f),
	mRoundTripTimeOrigin(580.f + WindowManager::sInstance->getView().getCenter().x, 10.f + WindowManager::sInstance->getView().getCenter().y, 0.0f),
	mScoreOffset(0.f + WindowManager::sInstance->getView().getCenter().x, 10.f + WindowManager::sInstance->getView().getCenter().y, 0.0f),
	mHealthOffset(1000 + WindowManager::sInstance->getView().getCenter().x, 10.f + WindowManager::sInstance->getView().getCenter().y, 0.0f),
	mHealth(0),
	mEndText("Running"),
	mTimer(6)
{
}

void HUD::StaticInit()
{
	sInstance.reset(new HUD());
}

void HUD::Render()
{
	//RenderBandWidth();
	//RenderRoundTripTime();
	//RenderScoreBoard();
	//RenderHealth();
	RenderTimer();
	if (mEndText != "Running")
	{
		RenderEndScreen();
	}
}

void HUD::RenderHealth()
{
	if (mHealth > 0)
	{
		string healthString = StringUtils::Sprintf("Health %d", mHealth);
		RenderText(healthString, { 600.f + WindowManager::sInstance->getView().getCenter().x, +WindowManager::sInstance->getView().getCenter().y - 350, 0.0f }, Colors::Red);
	}
}

void HUD::RenderBandWidth()
{
	string bandwidth = StringUtils::Sprintf("In %d  Bps, Out %d Bps",
		static_cast<int>(NetworkManagerClient::sInstance->GetBytesReceivedPerSecond().GetValue()),
		static_cast<int>(NetworkManagerClient::sInstance->GetBytesSentPerSecond().GetValue()));
	RenderText(bandwidth, { -400.f + WindowManager::sInstance->getView().getCenter().x, +WindowManager::sInstance->getView().getCenter().y - 350, 0.0f }, Colors::White);
}

void HUD::RenderRoundTripTime()
{
	float rttMS = NetworkManagerClient::sInstance->GetAvgRoundTripTime().GetValue() * 1000.f;

	string roundTripTime = StringUtils::Sprintf("RTT %d ms", (int)rttMS);
	RenderText(roundTripTime, { 150.f + WindowManager::sInstance->getView().getCenter().x, +WindowManager::sInstance->getView().getCenter().y - 350, 0.0f }, Colors::White);
}

void HUD::RenderScoreBoard()
{
	const vector< ScoreBoardManager::Entry >& entries = ScoreBoardManager::sInstance->GetEntries();
	Vector3 offset = { -600 + WindowManager::sInstance->getView().getCenter().x, +WindowManager::sInstance->getView().getCenter().y - 350, 0.0f };

	for (const auto& entry : entries)
	{
		RenderText(entry.GetFormattedNameScore(), offset, entry.GetColor());
		//offset.mX += mScoreOffset.mX;
		offset.mY += 50.f;
	}

}

/*void HUD::SetTimerText(std::string inString)
{
	RenderText("Game Over", { 200.f, 60.f, 0.0f }, Colors::White);
}*/

void HUD::RenderTimer()
{
	RenderText(std::to_string(mTimer), { WindowManager::sInstance->getView().getCenter().x - (25 * std::to_string(mTimer).length()) / 2, +WindowManager::sInstance->getView().getCenter().y - 350, 0.0f }, Colors::White);
	//NetworkManager::
	//if (mTimer > 120)
	//{
		//RenderText("Game Over", { 200.f, 60.f, 0.0f }, Colors::White);
	//}
	//else
	//{
		//RenderText(std::to_string(mTimer.getElapsedTime().asSeconds()), { 200.f, 60.f, 0.0f }, Colors::White);
	//}
}

void HUD::RenderEndScreen()
{
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(WindowManager::sInstance->getSize().x, WindowManager::sInstance->getSize().y));
	rect.setFillColor(sf::Color(0, 0, 30, 80));
	rect.setPosition(WindowManager::sInstance->getView().getCenter().x - WindowManager::sInstance->getSize().x/2, WindowManager::sInstance->getView().getCenter().y - WindowManager::sInstance->getSize().y/2);
	WindowManager::sInstance->draw(rect);
	RenderText(mEndText, { WindowManager::sInstance->getView().getCenter().x - (50 * mEndText.length())/2, +WindowManager::sInstance->getView().getCenter().y - 50, 0.0f}, Colors::White, 100);
}

void HUD::RenderText(const string& inStr, const Vector3& origin, const Vector3& inColor, const int size)
{
	sf::Text text;
	text.setString(inStr);
	text.setFillColor(sf::Color(inColor.mX, inColor.mY, inColor.mZ, 255));
	text.setCharacterSize(size);
	text.setPosition(origin.mX, origin.mY);
	text.setFont(*FontManager::sInstance->GetFont("carlito"));
	WindowManager::sInstance->draw(text);
}
