#include "ModuleScene.h"

ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleScene::~ModuleScene()
{

}

update_status ModuleScene::Update(float dt)
{

	return update_status::UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp()
{

	return true;
}

void ModuleScene::AddGameObject(GameObject* go)
{
	if (go != nullptr)
	{
		gameObjects.push_back(go);
	}
}

GameObject* ModuleScene::CreateGameObject(std::string name, GameObject* parent)
{
	GameObject* go = new GameObject(name);
	if (parent != nullptr)
	{
		go->SetParent(go);
	}
	AddGameObject(go);
	return go;
}

void ModuleScene::DeleteGameObject(GameObject* go)
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects[i] == go)
		{
			gameObjects.erase(gameObjects.begin() + i);
		}
	}
}

GameObject* ModuleScene::SearchGameObject(std::string name)
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects[i]->GetName() == name)
		{
			return gameObjects[i];
		}
	}
}