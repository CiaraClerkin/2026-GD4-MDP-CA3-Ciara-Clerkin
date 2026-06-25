#include "RoboCatClientPCH.hpp"

std::unique_ptr< RenderManager >	RenderManager::sInstance;

RenderManager::RenderManager()
{
	view.reset(sf::FloatRect(0, 0, 1280, 720));
	WindowManager::sInstance->setView(view);
}


void RenderManager::StaticInit()
{
	sInstance.reset(new RenderManager());
}


void RenderManager::AddComponent(SpriteComponent* inComponent)
{
	mComponents.emplace_back(inComponent);
}

void RenderManager::RemoveComponent(SpriteComponent* inComponent)
{
	int index = GetComponentIndex(inComponent);

	if (index != -1)
	{
		int lastIndex = mComponents.size() - 1;
		if (index != lastIndex)
		{
			mComponents[index] = mComponents[lastIndex];
		}
		mComponents.pop_back();
	}
}

int RenderManager::GetComponentIndex(SpriteComponent* inComponent) const
{
	for (int i = 0, c = mComponents.size(); i < c; ++i)
	{
		if (mComponents[i] == inComponent)
		{
			return i;
		}
	}

	return -1;
}

//this part that renders the world is really a camera-
//in a more detailed engine, we'd have a list of cameras, and then render manager would
//render the cameras in order
void RenderManager::RenderComponents()
{
	// We sort the Sprite Components by the ZOrder of their Game Object so that we can draw them on screen in the right order.
	// My Google search for Z-Order in SFML came up with AI code for this and I used it as a reference and adapted it to the project, so technically AI usage here.
	std::sort(mComponents.begin(), mComponents.end(), [](SpriteComponent*& a, SpriteComponent*& b) { return a->GetGameObject()->GetZOrder() > b->GetGameObject()->GetZOrder(); });
	
	//Get the logical viewport so we can pass this to the SpriteComponents when it's draw time
	for (SpriteComponent* c : mComponents)
	{
		WindowManager::sInstance->draw(c->GetSprite());
		if (dynamic_cast<RoboCat*>(c->GetGameObject()))
		{
			// wherever player movement happens?
			if (dynamic_cast<RoboCat*>(c->GetGameObject())->GetPlayerId() == NetworkManagerClient::sInstance->GetPlayerId())
			{
				//view.setCenter(std::round(c->GetGameObject()->GetLocation().mX), std::round(c->GetGameObject()->GetLocation().mY));
				view.setCenter(c->GetGameObject()->GetLocation().mX, c->GetGameObject()->GetLocation().mY);
				WindowManager::sInstance->setView(view);
			}
		}
	}
}

void RenderManager::Render()
{
	//
	// Clear the back buffer
	//
	WindowManager::sInstance->clear(sf::Color(100, 149, 237, 255));

	RenderManager::sInstance->RenderComponents();

	HUD::sInstance->Render();

	//
	// Present our back buffer to our front buffer
	//
	WindowManager::sInstance->display();

}
