#ifndef INCLUDED_ENGINE_MESHBUILDER_H
#define INCLUDED_ENGINE_MESHBUILDER_H

//====================================================================================================
// Filename:	MeshBuilder.h
// Created by:	Peter Chan
// Description:	Helper class for generating meshes.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Mesh.h"

//====================================================================================================
// Forward Declarations
//====================================================================================================

class Heightmap;

//====================================================================================================
// Class Declarations
//====================================================================================================

class MeshBuilder
{
public:
	// Functions for building a custom mesh
	static void StartMesh();
	static u32 AddVertexToMesh(const Mesh::Vertex& vertex);
	static void AddFaceToMesh(u32 a, u32 b, u32 c);
	static void FinalizeMesh(Mesh& mesh);

	// Function to generating a mesh
	static void GenerateMesh(Mesh& mesh, const Mesh::Vertex* vertexData, u32 numVertices, const u16* indexData, u32 numIndices);

	// Functions for building generic primitives
	static void CreateQuad(Mesh& mesh);
	static void CreateCube(Mesh& mesh);
	static void CreateSkybox(Mesh& mesh);
	static void CreateSphere(Mesh& mesh, u32 slices, u32 rings);
	static void CreateCylinder(Mesh& mesh, f32 radius, u32 slices, u32 rings);
	static void CreateTorus(Mesh& mesh, f32 radius, f32 ringRadius, u32 sides, u32 rings);

	// Function to create a terrain based on a heightmap
	static void CreateTerrain(Mesh& mesh, const Heightmap& heightmap, f32 maxHeight);
};

#endif // #ifndef INCLUDED_ENGINE_MESHBUILDER_H
