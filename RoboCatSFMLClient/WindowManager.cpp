#include "RoboCatClientPCH.hpp"

std::unique_ptr<sf::RenderWindow>	WindowManager::sInstance;

bool WindowManager::StaticInit()
{
	sInstance.reset(new sf::RenderWindow(sf::VideoMode(1280, 720), "RoboCatSFML!"));
	sInstance->setFramerateLimit(60);
	sInstance->setVerticalSyncEnabled(true);
	return true;
}


