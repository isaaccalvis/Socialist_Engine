#include <iostream>
#include "Mesh.h"
#include "Application.h"
#include "par_shapes.h"

Mesh::Mesh()
{}

Mesh::Mesh(MESH_TYPE type)
{
	verticesSize = 0;
	indicesSize = 0;
	par_shapes_mesh* primitive;
	switch (type)
	{
	case MESH_TYPE::PRIMITIVE_CUBE:
		primitive = par_shapes_create_cube();
		break;
	case MESH_TYPE::PRIMITIVE_PLANE:
		primitive = par_shapes_create_plane(5, 5);
		break;
	case MESH_TYPE::PRIMITIVE_FRUSTRUM:
	{
		verticesSize = 24;
		verticesArray = new GLfloat[verticesSize]{
			-0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.25f, 0.5f, -0.25f,
			 0.25f, 0.5f, -0.25f,
			 0.25f, 0.5f,  0.25f,
			-0.25f, 0.5f,  0.25f
		};

		indicesSize = 36;
		indicesArray = new unsigned int[indicesSize] {
			2, 1, 0,
				3, 2, 0,
				2, 5, 1,
				5, 2, 6,
				3, 7, 2,
				2, 7, 6,
				5, 6, 4,
				6, 7, 4,
				3, 0, 4,
				7, 3, 4,
				0, 1, 4,
				1, 5, 4
		};
	}
	break;
	case MESH_TYPE::PRIMITIVE_CYLINDER:
		primitive = par_shapes_create_cylinder(16, 8);
		break;
	case MESH_TYPE::PRIMITIVE_SPHERE:
		primitive = par_shapes_create_subdivided_sphere(3);
		break;
	}

	verticesSize = primitive->npoints * 3;
	verticesArray = new GLfloat[verticesSize];
	for (int i = 0; i < verticesSize; i++)
	{
		verticesArray[i] = primitive->points[i];
	}

	indicesSize = primitive->ntriangles * 3;
	indicesArray = new unsigned int[indicesSize];
	for (int i = 0; i < indicesSize; i++)
	{
		indicesArray[i] = primitive->triangles[i];
	}

	textureCoords = new GLfloat[primitive->npoints * 2];
	textureCoords = primitive->tcoords;

	vertices = 0u;
	glGenBuffers(1, (GLuint*) &(vertices));
	glBindBuffer(GL_ARRAY_BUFFER, vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * verticesSize, verticesArray, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	indices = 0u;
	glGenBuffers(1, (GLuint*) &(indices));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indicesSize, indicesArray, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Bounding Box
	//boundingBox.SetNegativeInfinity();
	//boundingBox.Enclose((const math::float3*)verticesArray, verticesSize);
	//boundingBoxCube = new DebugCube(boundingBox.CenterPoint(), boundingBox.Size());
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, (GLuint*)&vertices);
	glDeleteBuffers(1, (GLuint*)&indices);
	glDeleteBuffers(1, (GLuint*)&textureIndex);
	if (verticesArray != nullptr)
		delete[] verticesArray;
	if (indicesArray != nullptr)
		delete[] indicesArray;
	if (textureCoords != nullptr)
		delete[] textureCoords;
	if (normals != nullptr)
		delete[] normals;
	if (boundingBoxCube != nullptr)
		delete boundingBoxCube;
}

void Mesh::Render(Texture* texture)
{
	glPushMatrix();

	// Draw Geometry
	if (texture != nullptr)
	{
		glBindTexture(GL_TEXTURE_2D, texture->GetBufferPos());
	}
	glEnableClientState(GL_VERTEX_ARRAY);

	glTranslatef(position.x, position.y, position.z);
	glRotated(rotation.Angle() * RADTODEG, rotation.x, rotation.y, rotation.z);
	glScalef(scale.x, scale.y, scale.z);

	glBindBuffer(GL_ARRAY_BUFFER, vertices);
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	if (textureCoords != nullptr)
	{
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, textureIndex);
		glTexCoordPointer(2, GL_FLOAT, 0, NULL);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices);
	glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	// Draw Normals
	if (App->renderer3D->renderNormals)
	{
		for (int i = 0; i < verticesSize; i++)
		{
			if (normals != nullptr)
				normals[i].Render();
		}
	}

	if (App->renderer3D->renderBoudingBox)
	{
		if (boundingBoxCube != nullptr)
			boundingBoxCube->Render();
	}

	glPopMatrix();
}

void Mesh::SetPosition(math::float3 nPosition)
{
	this->position = nPosition;
}

void Mesh::SetRotation(const math::Quat nRotation)
{
	this->rotation = nRotation;
}

void Mesh::SetScale(math::float3 nScale)
{
	this->scale = nScale;
}

math::float3 Mesh::GetPosition() const
{
	return position;
}

math::float3 Mesh::GetScale() const
{
	return scale;
}

unsigned int Mesh::GetIndicesSize() const
{
	return indicesSize;
}

unsigned int Mesh::GetVerticesSize() const
{
	return verticesSize;
}

AABB Mesh::GetBoundingBox()
{
	return boundingBox;
}