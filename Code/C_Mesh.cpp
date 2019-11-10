#include "Application.h"

#include "C_Mesh.h"
#include "C_Material.h"
#include "C_Transform.h"

C_Mesh::C_Mesh(GameObject* parent) : Component(parent, COMPONENT_TYPE::COMPONENT_MESH)
{
	isUnique = true;
}

C_Mesh::~C_Mesh()
{
	App->renderer3D->DeleteMesh(mesh);
	mesh = nullptr;
}

void C_Mesh::Update(float dt)
{
	if (mesh != nullptr)
	{
		parent->GetComponent(COMPONENT_TRANSFORM)->GetComponentAsTransform()->globalMatrix.Decompose(mesh->position, mesh->rotation, mesh->scale);

		if (parent->GetComponent(COMPONENT_TYPE::COMPONENT_MATERIAL)->GetComponentAsMaterial() != nullptr
			&& parent->GetComponent(COMPONENT_TYPE::COMPONENT_MATERIAL)->GetComponentAsMaterial()->texture != nullptr)
		{
			mesh->Render(parent->GetComponent(COMPONENT_TYPE::COMPONENT_MATERIAL)->GetComponentAsMaterial()->texture);
		}
		else
		{
			mesh->Render();
		}
	}
}

void C_Mesh::SetMesh(Mesh* mesh)
{
	this->mesh = mesh;
	parent->UpdateAABB();
}

Mesh* C_Mesh::GetMesh()
{
	return mesh;
}