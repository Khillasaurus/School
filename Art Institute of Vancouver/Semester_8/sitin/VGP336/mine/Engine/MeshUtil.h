#ifndef INCLUDED_ENGINE_MESHUTIL_H
#define INCLUDED_ENGINE_MESHUTIL_H

//====================================================================================================
// Filename:	MeshUtil.h
// Created by:	Peter Chan
// Description:	Mesh related helper functions.
//====================================================================================================

//====================================================================================================
// Forward Declarations
//====================================================================================================

class GraphicsSystem;
class MeshBuffer;

//====================================================================================================
// Constants
//====================================================================================================

enum VertexFormat
{
	VF_Position	= 1 << 0,
	VF_Color	= 1 << 1,
	VF_Normal	= 1 << 2,
	VF_Tangent	= 1 << 3,
	VF_TexCoord	= 1 << 4,
	VF_Size		= 1 << 5,
	VF_Age		= 1 << 6,
	VF_Type		= 1 << 7
};

//====================================================================================================
// Function Declarations
//====================================================================================================

namespace MeshUtil
{
	u32 ComputeVertexSize(u32 vertexFormat);

	void CreateVertexLayout(u32 vertexFormat, std::vector<D3D11_INPUT_ELEMENT_DESC>& layout);
} // namespace MeshUtil

#endif // #ifndef INCLUDED_ENGINE_MESHUTIL_H
