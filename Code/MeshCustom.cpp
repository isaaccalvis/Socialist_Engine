#include "Application.h"
#include "MeshCustom.h"

#include "Assimp/include/Importer.hpp"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"

MeshCustom::MeshCustom(const char* path) : Mesh()
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);
	if (!scene)
	{
		// TODO: PASAR AQUEST LOG A LOG DE CONSOLA INTERNA
		LOG("Mesh can not be loaded");
		return;
	}
	allInternalMeshes = new IndividualMesh[scene->mNumMeshes];
	num_Meshes = scene->mNumMeshes;
	for (int a = 0; a < scene->mNumMeshes; a++)
	{
		// Vertices
		allInternalMeshes[a].ind_vertices_array = new GLfloat[scene->mMeshes[a]->mNumVertices * 3];
		int auxCounterVertex = 0;
		for (int i = 0; i < scene->mMeshes[a]->mNumVertices; i++)
		{
			allInternalMeshes[a].ind_vertices_array[auxCounterVertex] = scene->mMeshes[a]->mVertices[i].x;
			auxCounterVertex++;
			allInternalMeshes[a].ind_vertices_array[auxCounterVertex] = scene->mMeshes[a]->mVertices[i].y;
			auxCounterVertex++;
			allInternalMeshes[a].ind_vertices_array[auxCounterVertex] = scene->mMeshes[a]->mVertices[i].z;
			auxCounterVertex++;
		}
		allInternalMeshes[a].verticesSize = scene->mMeshes[a]->mNumVertices;
		glGenBuffers(1, (GLuint*) &(allInternalMeshes[a].individualVertices));
		glBindBuffer(GL_ARRAY_BUFFER, allInternalMeshes[a].individualVertices);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * scene->mMeshes[a]->mNumVertices * 3, allInternalMeshes[a].ind_vertices_array, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Indices
		allInternalMeshes[a].ind_indices_array = new uint[scene->mMeshes[a]->mNumFaces * 3];
		int auxCounterIndex = 0;
		for (int i = 0; i < scene->mMeshes[a]->mNumFaces; i++)
		{
			allInternalMeshes[a].ind_indices_array[auxCounterIndex] = scene->mMeshes[a]->mFaces[i].mIndices[0];
			auxCounterIndex++;
			allInternalMeshes[a].ind_indices_array[auxCounterIndex] = scene->mMeshes[a]->mFaces[i].mIndices[1];
			auxCounterIndex++;
			allInternalMeshes[a].ind_indices_array[auxCounterIndex] = scene->mMeshes[a]->mFaces[i].mIndices[2];
			auxCounterIndex++;
		}
		allInternalMeshes[a].indicesSize = scene->mMeshes[a]->mNumFaces * 3;
		glGenBuffers(1, (GLuint*) &(allInternalMeshes[a].individualIndices));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, allInternalMeshes[a].individualIndices);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * scene->mMeshes[a]->mNumFaces * 3, allInternalMeshes[a].ind_indices_array, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	}
}

MeshCustom::~MeshCustom()
{

}

void MeshCustom::Render()
{
	for (int i = 0; i < num_Meshes; i++) {
		glEnableClientState(GL_VERTEX_ARRAY);

		glTranslatef(position.x, position.y, position.z);

		glBindBuffer(GL_ARRAY_BUFFER, allInternalMeshes[i].individualVertices);
		glVertexPointer(3, GL_FLOAT, 0, NULL);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, allInternalMeshes[i].individualIndices);
		glDrawElements(GL_TRIANGLES, allInternalMeshes[i].indicesSize, GL_UNSIGNED_INT, NULL);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}

MeshCustom::IndividualMesh::~IndividualMesh()
{
	glDeleteBuffers(1, (GLuint*)&individualVertices);
	glDeleteBuffers(1, (GLuint*)&individualIndices);
	glDeleteBuffers(1, (GLuint*)&individualTextureCoors);
	if (ind_vertices_array != nullptr)
		delete[] ind_vertices_array;
	if (ind_indices_array != nullptr)
		delete[] ind_indices_array;
}