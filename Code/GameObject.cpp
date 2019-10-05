#include "Application.h"
#include "GameObject.h"
#include "C_Transform.h"
#include "C_Mesh.h"
#include "C_Material.h"

GameObject::GameObject()
{

}

GameObject::GameObject(std::string name, GameObject* parent)
{
	this->name = name.c_str();
	if (parent == nullptr)
		parent = App->scene->root;
	else
		this->parent = parent;
}

GameObject::~GameObject()
{
	
}

void GameObject::Update(float dt)
{

}

Component* GameObject::CreateComponent(COMPONENT_TYPE type, const char* name)
{
	Component* component = nullptr;
	switch (type)
	{
	case COMPONENT_TYPE::COMPONENT_TRANSFORM:
	{
		component = new C_Transform(this);
	}
	break;
	case COMPONENT_TYPE::COMPONENT_MESH:
	{
		component = new C_Mesh(this);
	}
	break;
	case COMPONENT_TYPE::COMPONENT_MATERIAL:
	{
		component = new C_Material(this);
	}
	break;
	}
	component->parent = this;
	components.push_back(component);
	return component;
}

Component* GameObject::GetComponent(COMPONENT_TYPE type, const char* name)
{
	return nullptr;
}

GameObject* GameObject::GetParent() const
{
	return parent;
}

void GameObject::SetParent(GameObject* parent)
{
	this->parent = parent;
}