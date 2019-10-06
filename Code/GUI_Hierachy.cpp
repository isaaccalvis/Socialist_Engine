#include "Application.h"
#include "ModuleScene.h"
#include "GameObject.h"
#include "GUI_Hierachy.h"

#include "imgui\imgui.h"
#include "imgui\imgui_internal.h"

GUI_Hierachy::GUI_Hierachy(SDL_Scancode shortcut) : GUI_Panel(shortcut, GUI_WINDOWS::GUI_HIERACHY)
{

}

void GUI_Hierachy::Draw()
{
	ImGui::Begin("Hierachy", &active, ImGuiWindowFlags_NoFocusOnAppearing);
	RecursiveTakeChilds(App->scene->root);

	ImGui::End();
}

void GUI_Hierachy::RecursiveTakeChilds(GameObject* parent) const
{
	ImGuiTreeNodeFlags treeNodeFlags;

	for (int i = 0; i < parent->CountChild(); i++)
	{
		GameObject* child = parent->children[i];
		char name[256];
		sprintf_s(name, 256, child->name);
		if (child->CountChild() != 0)
		{
			treeNodeFlags = 0;
			treeNodeFlags |= ImGuiTreeNodeFlags_Leaf;

			if (App->scene->goSelected == child)
				treeNodeFlags |= ImGuiTreeNodeFlags_Selected;

			bool treeNodeOpened = false;
			if (ImGui::TreeNodeEx(name, treeNodeFlags))
				treeNodeOpened = true;

			if (ImGui::IsItemClicked() && (ImGui::GetMousePos().x - ImGui::GetItemRectMin().x) > ImGui::GetTreeNodeToLabelSpacing())
				App->scene->goSelected = child;
			GameObjectPopUp(child);

			if (treeNodeOpened)
			{
				RecursiveTakeChilds(child);
				ImGui::TreePop();
			}
		}
		else
		{
			treeNodeFlags = 0;
			treeNodeFlags |= ImGuiTreeNodeFlags_Leaf;

			if (App->scene->goSelected == child)
				treeNodeFlags |= ImGuiTreeNodeFlags_Selected;

			ImGui::TreeNodeEx(name, treeNodeFlags);
			ImGui::TreePop();
			if (ImGui::IsItemClicked() && (ImGui::GetMousePos().x - ImGui::GetItemRectMin().x) > ImGui::GetTreeNodeToLabelSpacing())
				App->scene->goSelected = child;
			GameObjectPopUp(child);
		}
	}
}

void GUI_Hierachy::GameObjectPopUp(GameObject* go) const
{
	if (ImGui::BeginPopupContextItem())
	{
		if (ImGui::Selectable("Create Empty"))
		{
			App->scene->CreateGameObject("Empty", go);
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
}