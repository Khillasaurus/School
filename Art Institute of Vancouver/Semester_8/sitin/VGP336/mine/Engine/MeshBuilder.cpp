//====================================================================================================
// Filename:	MeshBuilder.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "MeshBuilder.h"

#include "Heightmap.h"

//====================================================================================================
// Local Definitions
//====================================================================================================

namespace
{
	std::vector<Mesh::Vertex> s_vertices;
	std::vector<u16> s_indices;
}

//====================================================================================================
// Class Definitions
//====================================================================================================

void MeshBuilder::StartMesh()
{
	s_vertices.clear();
	s_indices.clear();
}

//----------------------------------------------------------------------------------------------------

u32 MeshBuilder::AddVertexToMesh(const Mesh::Vertex& vertex)
{
	s_vertices.push_back(vertex);
	return s_vertices.size() - 1;
}

//----------------------------------------------------------------------------------------------------

void MeshBuilder::AddFaceToMesh(u32 a, u32 b, u32 c)
{
	s_indices.push_back(a);
	s_indices.push_back(b);
	s_indices.push_back(c);
}

//----------------------------------------------------------------------------------------------------

void MeshBuilder::FinalizeMesh(Mesh& mesh)
{
	GenerateMesh(mesh, &s_vertices[0], s_vertices.size(), &s_indices[0], s_indices.size());
}

//----------------------------------------------------------------------------------------------------

void MeshBuilder::GenerateMesh(Mesh& mesh, const Mesh::Vertex* vertexData, u32 numVertices, const u16* indexData, u32 numIndices)
{
	// Free any existing data
	mesh.Destroy();
	
	// Allocate memory
	Mesh::Vertex* vertices = new Mesh::Vertex[numVertices];
	u16* indices = new u16[numIndices];

	// Copy data
	memcpy(vertices, vertexData, numVertices * sizeof(Mesh::Vertex));
	memcpy(indices, indexData, numIndices * sizeof(u16));

	// Bind new data
	mesh.mpVertices = vertices;
	mesh.mpIndices = indices;
	mesh.mNumVertices = numVertices;
	mesh.mNumIndices = numIndices;
}

//----------------------------------------------------------------------------------------------------

void MeshBuilder::CreateQuad(Mesh& mesh)
{
	const Mesh::Vertex kVertices[] =
	{
		Mesh::Vertex( Math::Vector3(-1.0f, -1.0f, 0.0f), Math::Vector3(0.0f, 0.0f, -1.0f), Math::Vector3(1.0f, 0.0f, 0.0f), Color::White(), Math::Vector2(0.0f, 1.0f) ),
		Mesh::Vertex( Math::Vector3(-1.0f,  1.0f, 0.0f), Math::Vector3(0.0f, 0.0f, -1.0f), Math::Vector3(1.0f, 0.0f, 0.0f), Color::White(), Math::Vector2(0.0f, 0.0f) ),
		Mesh::Vertex( Math::Vector3( 1.0f,  1.0f, 0.0f), Math::Vector3(0.0f, 0.0f, -1.0f), Math::Vector3(1.0f, 0.0f, 0.0f), Color::White(), Math::Vector2(1.0f, 0.0f) ),
		Mesh::Vertex( Math::Vector3( 1.0f, -1.0f, 0.0f), Math::Vector3(0.0f, 0.0f, -1.0f), Math::Vector3(1.0f, 0.0f, 0.0f), Color::White(), Math::Vector2(1.0f, 1.0f) ),
	};

	const u16 kIndices[] =
	{
		0, 1, 2, 0, 2, 3
	};
	
	const u32 kNumVertices = ARRAYSIZE(kVertices);
	const u32 kNumIndices = ARRAYSIZE(kIndices);

	GenerateMesh(mesh, kVertices, kNumVertices, kIndices, kNumIndices);
}

//----------------------------------------------------------------------------------------------------

void MeshBuilder::CreateCube(Mesh& mesh)
{
	const Mesh::Vertex kVertices[] =
	{
		// Pos X
		Mesh::Vertex( Math::Vector3(1.0f, -1.0f, -1.0f), Math::Vector3(1.0f, 0.0f, 0.0f), Math::Vector3(0.0f, 0.0f, 1.0f), Color::White(), Math::Vector2(0.0f, 1.0f) ),
		Mesh::Vertex( Math::Vector3(1.0f,  1.0f, -1.0f), Math::Vector3(1.0f, 0.0f, 0.0f), Math::Vector3(0.0f, 0.0f, 1.0f), Color::White(), Math::Vector2(0.0f, 0.0f) ),
		Mesh::Vertex( Math::Vector3(1.0f,  1.0f,  1.0f), Math::Vector3(1.0f, 0.0f, 0.0f), Math::Vector3(0.0f, 0.0f, 1.0f), Color::White(), Math::Vector2(1.0f, 0.0f) ),
		Mesh::Vertex( Math::Vector3(1.0f, -1.0f,  1.0f), Math::Vector3(1.0f, 0.0f, 0.0f), Math::Vector3(0.0f, 0.0f, 1.0f), Color::White(), Math::Vector2(1.0f, 1.0f) ),

		// Neg X
		Mesh::Vertex( Math::Vector3(-1.0f, -1.0f,  1.0f), Math::Vector3(-1.0f, 0.0f, 0.0f), Math::Vector3(0.0f, 0.0f, -1.0f), Color::White(), Math::Vector2(0.0f, 1.0f) ),
		Mesh::Vertex( Math::Vector3(-1.0f,  1.0f,  1.0f), Math::Vector3(-1.0f, 0.0f, 0.0f), Math::Vector3(0.0f, 0.0f, -1.0f), Color::White(), Math::Vector2(0.0f, 0.0f) ),
		Mesh::Vertex( Math::Vector3(-1.0f,  1.0f, -1.0f), Math::Vector3(-1.0f, 0.0f, 0.0f), Math::Vector3(0.0f, 0.0f, -1.0f), Color::White(), Math::Vector2(1.0f, 0.0f) ),
		Mesh::Vertex( Math::Vector3(-1.0f, -1.0f, -1.0f), Math::Vector3(-1.0f, 0.0f, 0.0f), Math::Vector3(0.0f, 0.0f, -1.0f), Color::White(), Math::Vector2(1.0f, 1.0f) ),

		// Pos Y
		Mesh::Vertex( Math::Vector3(-1.0f, 1.0f, -1.0f), Math::Vector3(0.0f, 1.0f, 0.0f), Math::Vector3(1.0f, 0.0f, 0.0f), Color::White(), Math::Vector2(0.0f, 1.0f) ),
		Mesh::Vertex( Math::Vector3(-1.0f, 1.0f,  1.0f), Math::Vector3(0.0f, 1.0f, 0.0f), Math::Vector3(1.0f, 0.0f, 0.0f), Color::White(), Math::Vector2(0.0f, 0.0f) ),
		Mesh::Vertex( Math::Vector3( 1.0f, 1.0f,  1.0f), Math::Vector3(0.0f, 1.0f, 0.0f), Math::Vector3(1.0f, 0.0f, 0.0f), Color::White(), Math::Vector2(1.0f, 0.0f) ),
		Mesh::Vertex( Math::Vector3( 1.0f, 1.0f, -1.0f), Math::Vector3(0.0f, 1.0f, 0.0f), Math::Vector3(1.0f, 0.0f, 0.0f), Color::White(), Math::Vector2(1.0f, 1.0f) ),

		// Neg Y
		Mesh::Vertex( Math::Vector3(-1.0f, -1.0f,  1.0f), Math::Vector3(0.0f, -1.0f, 0.0f), Math::Vector3(1.0f, 0.0f, 0.0f), Color::White(), Math::Vector2(0.0f, 1.0f) ),
		Mesh::Vertex( Math::Vector3(-1.0f, -1.0f, -1.0f), Math::Vector3(0.0f, -1.0f, 0.0f), Math::Vector3(1.0f, 0.0f, 0.0f), Color::White(), Math::Vector2(0.0f, 0.0f) ),
		Mesh::Vertex( Math::Vector3( 1.0f, -1.0f, -1.0f), Math::Vector3(0.0f, -1.0f, 0.0f), Math::Vector3(1.0f, 0.0f, 0.0f), Color::White(), Math::Vector2(1.0f, 0.0f) ),
		Mesh::Vertex( Math::Vector3( 1.0f, -1.0f,  1.0f), Math::Vector3(0.0f, -1.0f, 0.0f), Math::Vector3(1.0f, 0.0f, 0.0f), Color::White(), Math::Vector2(1.0f, 1.0f) ),

		// Pos Z
		Mesh::Vertex( Math::Vector3( 1.0f, -1.0f, 1.0f), Math::Vector3(0.0f, 0.0f, 1.0f), Math::Vector3(-1.0f, 0.0f, 0.0f), Color::White(), Math::Vector2(0.0f, 1.0f) ),
		Mesh::Vertex( Math::Vector3( 1.0f,  1.0f, 1.0f), Math::Vector3(0.0f, 0.0f, 1.0f), Math::Vector3(-1.0f, 0.0f, 0.0f), Color::White(), Math::Vector2(0.0f, 0.0f) ),
		Mesh::Vertex( Math::Vector3(-1.0f,  1.0f, 1.0f), Math::Vector3(0.0f, 0.0f, 1.0f), Math::Vector3(-1.0f, 0.0f, 0.0f), Color::White(), Math::Vector2(1.0f, 0.0f) ),
		Mesh::Vertex( Math::Vector3(-1.0f, -1.0f, 1.0f), Math::Vector3(0.0f, 0.0f, 1.0f), Math::Vector3(-1.0f, 0.0f, 0.0f), Color::White(), Math::Vector2(1.0f, 1.0f) ),

		// Neg Z
		Mesh::Vertex( Math::Vector3(-1.0f, -1.0f, -1.0f), Math::Vector3(0.0f, 0.0f, -1.0f), Math::Vector3(1.0f, 0.0f, 0.0f), Color::White(), Math::Vector2(0.0f, 1.0f) ),
		Mesh::Vertex( Math::Vector3(-1.0f,  1.0f, -1.0f), Math::Vector3(0.0f, 0.0f, -1.0f), Math::Vector3(1.0f, 0.0f, 0.0f), Color::White(), Math::Vector2(0.0f, 0.0f) ),
		Mesh::Vertex( Math::Vector3( 1.0f,  1.0f, -1.0f), Math::Vector3(0.0f, 0.0f, -1.0f), Math::Vector3(1.0f, 0.0f, 0.0f), Color::White(), Math::Vector2(1.0f, 0.0f) ),
		Mesh::Vertex( Math::Vector3( 1.0f, -1.0f, -1.0f), Math::Vector3(0.0f, 0.0f, -1.0f), Math::Vector3(1.0f, 0.0f, 0.0f), Color::White(), Math::Vector2(1.0f, 1.0f) ),
	};

	const u16 kIndices[] =
	{
		0, 1, 2, 0, 2, 3,
		4, 5, 6, 4, 6, 7,
		8, 9, 10, 8, 10, 11,
		12, 13, 14, 12, 14, 15,
		16, 17, 18, 16, 18, 19,
		20, 21, 22, 20, 22, 23
	};
	
	const u32 kNumVertices = ARRAYSIZE(kVertices);
	const u32 kNumIndices = ARRAYSIZE(kIndices);

	GenerateMesh(mesh, kVertices, kNumVertices, kIndices, kNumIndices);
}

//----------------------------------------------------------------------------------------------------

void MeshBuilder::CreateSkybox(Mesh& mesh)
{
	const Mesh::Vertex kVertices[] =
	{
		// Pos X
		Mesh::Vertex( Math::Vector3(1.0f, -1.0f,  1.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Color::White(), Math::Vector2(0.0f, 1.0f) ),
		Mesh::Vertex( Math::Vector3(1.0f,  1.0f,  1.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Color::White(), Math::Vector2(0.0f, 0.0f) ),
		Mesh::Vertex( Math::Vector3(1.0f,  1.0f, -1.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Color::White(), Math::Vector2(1.0f, 0.0f) ),
		Mesh::Vertex( Math::Vector3(1.0f, -1.0f, -1.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Color::White(), Math::Vector2(1.0f, 1.0f) ),

		// Neg X
		Mesh::Vertex( Math::Vector3(-1.0f, -1.0f, -1.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Color::White(), Math::Vector2(0.0f, 1.0f) ),
		Mesh::Vertex( Math::Vector3(-1.0f,  1.0f, -1.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Color::White(), Math::Vector2(0.0f, 0.0f) ),
		Mesh::Vertex( Math::Vector3(-1.0f,  1.0f,  1.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Color::White(), Math::Vector2(1.0f, 0.0f) ),
		Mesh::Vertex( Math::Vector3(-1.0f, -1.0f,  1.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Color::White(), Math::Vector2(1.0f, 1.0f) ),

		// Pos Y
		Mesh::Vertex( Math::Vector3(-1.0f, 1.0f,  1.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Color::White(), Math::Vector2(0.0f, 1.0f) ),
		Mesh::Vertex( Math::Vector3(-1.0f, 1.0f, -1.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Color::White(), Math::Vector2(0.0f, 0.0f) ),
		Mesh::Vertex( Math::Vector3( 1.0f, 1.0f, -1.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Color::White(), Math::Vector2(1.0f, 0.0f) ),
		Mesh::Vertex( Math::Vector3( 1.0f, 1.0f,  1.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Color::White(), Math::Vector2(1.0f, 1.0f) ),

		// Neg Y
		Mesh::Vertex( Math::Vector3(-1.0f, -1.0f, -1.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Color::White(), Math::Vector2(0.0f, 1.0f) ),
		Mesh::Vertex( Math::Vector3(-1.0f, -1.0f,  1.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Color::White(), Math::Vector2(0.0f, 0.0f) ),
		Mesh::Vertex( Math::Vector3( 1.0f, -1.0f,  1.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Color::White(), Math::Vector2(1.0f, 0.0f) ),
		Mesh::Vertex( Math::Vector3( 1.0f, -1.0f, -1.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Color::White(), Math::Vector2(1.0f, 1.0f) ),

		// Pos Z
		Mesh::Vertex( Math::Vector3(-1.0f, -1.0f, 1.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Color::White(), Math::Vector2(0.0f, 1.0f) ),
		Mesh::Vertex( Math::Vector3(-1.0f,  1.0f, 1.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Color::White(), Math::Vector2(0.0f, 0.0f) ),
		Mesh::Vertex( Math::Vector3( 1.0f,  1.0f, 1.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Color::White(), Math::Vector2(1.0f, 0.0f) ),
		Mesh::Vertex( Math::Vector3( 1.0f, -1.0f, 1.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Color::White(), Math::Vector2(1.0f, 1.0f) ),

		// Neg Z
		Mesh::Vertex( Math::Vector3( 1.0f, -1.0f, -1.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Color::White(), Math::Vector2(0.0f, 1.0f) ),
		Mesh::Vertex( Math::Vector3( 1.0f,  1.0f, -1.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Color::White(), Math::Vector2(0.0f, 0.0f) ),
		Mesh::Vertex( Math::Vector3(-1.0f,  1.0f, -1.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Color::White(), Math::Vector2(1.0f, 0.0f) ),
		Mesh::Vertex( Math::Vector3(-1.0f, -1.0f, -1.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Math::Vector3(0.0f, 0.0f, 0.0f), Color::White(), Math::Vector2(1.0f, 1.0f) ),
	};

	const u16 kIndices[] =
	{
		0, 1, 2, 0, 2, 3,
		4, 5, 6, 4, 6, 7,
		8, 9, 10, 8, 10, 11,
		12, 13, 14, 12, 14, 15,
		16, 17, 18, 16, 18, 19,
		20, 21, 22, 20, 22, 23
	};
	
	const u32 kNumVertices = ARRAYSIZE(kVertices);
	const u32 kNumIndices = ARRAYSIZE(kIndices);
	
	GenerateMesh(mesh, kVertices, kNumVertices, kIndices, kNumIndices);
}

//----------------------------------------------------------------------------------------------------

void MeshBuilder::CreateSphere(Mesh& mesh, u32 slices, u32 rings)
{
	const u32 kNumVertices = (slices + 1) * rings;
	const u32 kNumIndices = slices * (rings - 1) * 6;
	const f32 kSliceStep = Math::kTwoPi / slices;
	const f32 kRingStep = Math::kPi / (rings - 1);
	
	// Allocate memory
	Mesh::Vertex* vertices = new Mesh::Vertex[kNumVertices];
	u16* indices = new u16[kNumIndices];
	
	// Fill vertex data
	f32 uStep = 1.0f / slices;
	f32 vStep = 1.0f / rings;
	u32 index = 0;
	for (u32 j = 0; j < rings; ++j)
	{
		const f32 phi = j * kRingStep;
		for (u32 i = 0; i <= slices; ++i)
		{
			const f32 theta = i * kSliceStep;
			const f32 y = cos(phi);
			const f32 r = sqrt(1.0f - (y * y));
			const f32 s = sin(theta);
			const f32 c = cos(theta);
			const f32 x = r * c;
			const f32 z = r * s;
			vertices[index].position = Math::Vector3(x, y, z);
			vertices[index].normal = Math::Vector3(x, y, z);
			vertices[index].tangent = Math::Vector3(-s, 0.0f, c);
			vertices[index].color = Color::White();
			vertices[index].texcoord = Math::Vector2(i * uStep, j * vStep);
			++index;
		}
	}

	// Fill index data
	index = 0;
	for (u32 j = 0; j < rings - 1; ++j)
	{
		for (u32 i = 0; i < slices; ++i)
		{
			const u32 a = i % (slices + 1);
			const u32 b = (i + 1) % (slices + 1);
			const u32 c = j * (slices + 1);
			const u32 d = (j + 1) * (slices + 1);

			//     a     b
			//   c +-----+
			//     |     |
			//     |     |
			//   d +-----+
			//
			indices[index++] = a + c;
			indices[index++] = b + c;
			indices[index++] = a + d;

			indices[index++] = b + c;
			indices[index++] = b + d;
			indices[index++] = a + d;
		}
	}

	GenerateMesh(mesh, vertices, kNumVertices, indices, kNumIndices);
}

//----------------------------------------------------------------------------------------------------

void MeshBuilder::CreateCylinder(Mesh& mesh, f32 radius, u32 slices, u32 rings)
{
	const u32 kNumVertices = (slices + 1) * rings;
	const u32 kNumIndices = slices * (rings - 1) * 6;
	const f32 kSliceStep = Math::kTwoPi / slices;
	const f32 kRingStep = 2.0f / (rings - 1);
	
	// Allocate memory
	Mesh::Vertex* vertices = new Mesh::Vertex[kNumVertices];
	u16* indices = new u16[kNumIndices];
	
	// Fill vertex data
	f32 uStep = 1.0f / slices;
	f32 vStep = 1.0f / rings;
	u32 index = 0;
	for (u32 j = 0; j < rings; ++j)
	{
		for (u32 i = 0; i <= slices; ++i)
		{
			const f32 theta = i * kSliceStep;
			const f32 y = 1.0f - (j * kRingStep);
			const f32 s = sin(theta);
			const f32 c = cos(theta);
			const f32 x = radius * c;
			const f32 z = radius * s;
			vertices[index].position = Math::Vector3(x, y, z);
			vertices[index].normal = Math::Vector3(x, 0.0f, z);
			vertices[index].tangent = Math::Vector3(-s, 0.0f, c);
			vertices[index].color = Color::White();
			vertices[index].texcoord = Math::Vector2(i * uStep, j * vStep);
			++index;
		}
	}

	// Fill index data
	index = 0;
	for (u32 j = 0; j < rings - 1; ++j)
	{
		for (u32 i = 0; i < slices; ++i)
		{
			const u32 a = i % (slices + 1);
			const u32 b = (i + 1) % (slices + 1);
			const u32 c = j * (slices + 1);
			const u32 d = (j + 1) * (slices + 1);

			//     a     b
			//   c +-----+
			//     |     |
			//     |     |
			//   d +-----+
			//
			indices[index++] = a + c;
			indices[index++] = b + c;
			indices[index++] = a + d;

			indices[index++] = b + c;
			indices[index++] = b + d;
			indices[index++] = a + d;
		}
	}

	GenerateMesh(mesh, vertices, kNumVertices, indices, kNumIndices);
}

//----------------------------------------------------------------------------------------------------

void MeshBuilder::CreateTorus(Mesh& mesh, f32 radius, f32 ringRadius, u32 sides, u32 rings)
{
	const u32 kNumVerticesPerRow = sides + 1;
	const u32 kNumVerticesPerColumn = rings + 1;
	const u32 kNumVertices = kNumVerticesPerRow * kNumVerticesPerColumn;
	const u32 kNumIndices = sides * rings * 6;
	const f32 kPhiStep = Math::kTwoPi / sides;
	const f32 kThetaStep = Math::kTwoPi / rings;
	const f32 kUStep = 1.0f / rings;
	const f32 kVStep = 1.0f / sides;
	
	// Allocate memory
	Mesh::Vertex* vertices = new Mesh::Vertex[kNumVertices];
	u16* indices = new u16[kNumIndices];

	u32 index = 0;
	f32 theta = 0.0f;
	f32 phi = 0.0f;

	// Fill vertices
	for (u32 i = 0; i < kNumVerticesPerColumn; ++i)
	{
		theta = kThetaStep * i;

		for (u32 j = 0; j < kNumVerticesPerRow; ++j)
		{
			phi = kPhiStep * j;

			const f32 cosPhi = cos(phi);
			const f32 sinPhi = sin(phi);
			const f32 cosTheta = cos(theta);
			const f32 sinTheta = sin(theta);

			const f32 arm = ringRadius * cosPhi;
			const f32 x = cosTheta * (radius + arm);
			const f32 y = sinTheta * (radius + arm);
			const f32 z = ringRadius * sinPhi;

			vertices[index].position = Math::Vector3(x, y, z);
			vertices[index].normal = Math::Vector3(cosTheta * arm, sinTheta * arm, z);
			vertices[index].tangent = Math::Vector3(-sinTheta, cosTheta, 0.0f);
			vertices[index].color = Color::White();
			vertices[index].texcoord = Math::Vector2(i * kUStep, j * kVStep);
			++index;
		}
	}
	
	// Fill indices
	index = 0;
	for (u32 i = 0; i < rings; ++i)
	{
		for (u32 j = 0; j < sides; ++j)
		{
			const u16 lb = (j)     + (i)     * (kNumVerticesPerRow);
			const u16 lt = (j)     + (i + 1) * (kNumVerticesPerRow);
			const u16 rb = (j + 1) + (i)     * (kNumVerticesPerRow);
			const u16 rt = (j + 1) + (i + 1) * (kNumVerticesPerRow);

			indices[index++] = lb;
			indices[index++] = lt;
			indices[index++] = rt;

			indices[index++] = lb;
			indices[index++] = rt;
			indices[index++] = rb;
		}
	}

	GenerateMesh(mesh, vertices, kNumVertices, indices, kNumIndices);
}

//----------------------------------------------------------------------------------------------------

void MeshBuilder::CreateTerrain(Mesh& mesh, const Heightmap& heightmap, f32 maxHeight)
{
	const u32 kColumns = heightmap.GetColumns();
	const u32 kRows = heightmap.GetRows();
	const u32 kNumVertices = kColumns * kRows;
	const u32 kNumIndices = (kColumns - 1) * (kRows - 1) * 6;
	
	// Allocate memory
	Mesh::Vertex* vertices = new Mesh::Vertex[kNumVertices];
	u16* indices = new u16[kNumIndices];

	// Fill vertices
	for (u32 z = 0; z < kRows; ++z)
	{
		for (u32 x = 0; x < kColumns; ++x)
		{
			const u32 vIndex = x + (z * kColumns);
			Mesh::Vertex& vertex = vertices[vIndex];
			
			const f32 height = heightmap.GetHeight(x, kRows - z - 1) * maxHeight;
			const f32 u = (f32)x / (kColumns - 1.0f);
			const f32 v = (f32)(kRows - z - 1) / (kRows - 1.0f);

			vertex.position = Math::Vector3((f32)x, height,(f32)z);
			vertex.normal =	Math::Vector3(0.0f, 1.0f, 0.0f);
			vertex.tangent = Math::Vector3(1.0f, 0.0f, 0.0f);
			vertex.color = Color::White();
			vertex.texcoord = Math::Vector2(u, v);
		}
	}

	// Fill indices
	u32 index = 0;
	for (u32 z = 0; z < kRows - 1; ++z)
	{
		for (u32 x = 0; x < kColumns - 1; ++x)
		{
			const u32 a = (x) +     ((z)     * kColumns);
			const u32 b = (x) +     ((z + 1) * kColumns);
			const u32 c = (x + 1) + ((z + 1) * kColumns);
			const u32 d = (x + 1) + ((z)     * kColumns);

			//
			//   b +-----+ c
			//     |   / |
			//     | /   |
			//   a +-----+ d
			//
			indices[index++] = a;
			indices[index++] = b;
			indices[index++] = c;

			indices[index++] = a;
			indices[index++] = c;
			indices[index++] = d;
		}
	}

	GenerateMesh(mesh, vertices, kNumVertices, indices, kNumIndices);
}