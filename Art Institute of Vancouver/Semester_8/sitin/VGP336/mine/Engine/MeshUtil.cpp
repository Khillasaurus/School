//====================================================================================================
// Filename:	MeshUtil.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "MeshUtil.h"

#include "GraphicsSystem.h"
#include "MeshBuffer.h"

//====================================================================================================
// Local Definitions
//====================================================================================================

namespace
{
	u32 CountChar(const char* str, char findMe)
	{
		u32 count = 0;
		while (str != nullptr && *str != 0)
		{
			if (*str == findMe)
			{
				++count;
			}
			++str;
		}
		return count;
	}
}

//====================================================================================================
// Function Definitions
//====================================================================================================

namespace MeshUtil
{

u32 ComputeVertexSize(u32 vertexFormat)
{
	u32 size = 0;
	if (vertexFormat & VF_Position)
	{
		size += 12;
	}
	if (vertexFormat & VF_Color)
	{
		size += 16;
	}
	if (vertexFormat & VF_Normal)
	{
		size += 12;
	}
	if (vertexFormat & VF_Tangent)
	{
		size += 12;
	}
	if (vertexFormat & VF_TexCoord)
	{
		size += 8;
	}
	if (vertexFormat & VF_Size)
	{
		size += 8;
	}
	if (vertexFormat & VF_Age)
	{
		size += 4;
	}
	if (vertexFormat & VF_Type)
	{
		size += 4;
	}
	return size;
}

//----------------------------------------------------------------------------------------------------

void CreateVertexLayout(u32 vertexFormat, std::vector<D3D11_INPUT_ELEMENT_DESC>& layout)
{
	layout.clear();
	u32 offset = 0;

	if (vertexFormat & VF_Position)
	{
		D3D11_INPUT_ELEMENT_DESC desc;
		desc.SemanticName = "POSITION";
		desc.SemanticIndex = 0;
		desc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
		desc.InputSlot = 0;
		desc.AlignedByteOffset = offset;
		desc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		desc.InstanceDataStepRate = 0;
		layout.push_back(desc);
		offset += 12;
	}
	if (vertexFormat & VF_Normal)
	{
		D3D11_INPUT_ELEMENT_DESC desc;
		desc.SemanticName = "NORMAL";
		desc.SemanticIndex = 0;
		desc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
		desc.InputSlot = 0;
		desc.AlignedByteOffset = offset;
		desc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		desc.InstanceDataStepRate = 0;
		layout.push_back(desc);
		offset += 12;
	}
	if (vertexFormat & VF_Tangent)
	{
		D3D11_INPUT_ELEMENT_DESC desc;
		desc.SemanticName = "TANGENT";
		desc.SemanticIndex = 0;
		desc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
		desc.InputSlot = 0;
		desc.AlignedByteOffset = offset;
		desc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		desc.InstanceDataStepRate = 0;
		layout.push_back(desc);
		offset += 12;
	}
	if (vertexFormat & VF_Color)
	{
		D3D11_INPUT_ELEMENT_DESC desc;
		desc.SemanticName = "COLOR";
		desc.SemanticIndex = 0;
		desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		desc.InputSlot = 0;
		desc.AlignedByteOffset = offset;
		desc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		desc.InstanceDataStepRate = 0;
		layout.push_back(desc);
		offset += 16;
	}
	if (vertexFormat & VF_TexCoord)
	{
		D3D11_INPUT_ELEMENT_DESC desc;
		desc.SemanticName = "TEXCOORD";
		desc.SemanticIndex = 0;
		desc.Format = DXGI_FORMAT_R32G32_FLOAT;
		desc.InputSlot = 0;
		desc.AlignedByteOffset = offset;
		desc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		desc.InstanceDataStepRate = 0;
		layout.push_back(desc);
		offset += 8;
	}
	if (vertexFormat & VF_Size)
	{
		D3D11_INPUT_ELEMENT_DESC desc;
		desc.SemanticName = "SIZE";
		desc.SemanticIndex = 0;
		desc.Format = DXGI_FORMAT_R32G32_FLOAT;
		desc.InputSlot = 0;
		desc.AlignedByteOffset = offset;
		desc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		desc.InstanceDataStepRate = 0;
		layout.push_back(desc);
		offset += 8;
	}
	if (vertexFormat & VF_Age)
	{
		D3D11_INPUT_ELEMENT_DESC desc;
		desc.SemanticName = "AGE";
		desc.SemanticIndex = 0;
		desc.Format = DXGI_FORMAT_R32_FLOAT;
		desc.InputSlot = 0;
		desc.AlignedByteOffset = offset;
		desc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		desc.InstanceDataStepRate = 0;
		layout.push_back(desc);
		offset += 4;
	}
	if (vertexFormat & VF_Type)
	{
		D3D11_INPUT_ELEMENT_DESC desc;
		desc.SemanticName = "TYPE";
		desc.SemanticIndex = 0;
		desc.Format = DXGI_FORMAT_R32_UINT;
		desc.InputSlot = 0;
		desc.AlignedByteOffset = offset;
		desc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		desc.InstanceDataStepRate = 0;
		layout.push_back(desc);
		offset += 4;
	}
}

} // namespace MeshUtil