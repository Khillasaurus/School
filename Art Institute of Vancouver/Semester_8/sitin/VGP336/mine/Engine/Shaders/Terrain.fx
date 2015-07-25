//====================================================================================================
// Filename:	Terrain.fx
// Created by:	Peter Chan
// Description:	Shader for multi-layer terrain.
//====================================================================================================

//====================================================================================================
// Constant Buffers
//====================================================================================================

cbuffer CBPerFrame : register(b0)
{
	matrix WVP;
	float4 layer[4];
}

//====================================================================================================
// Textures and Samplers
//====================================================================================================

Texture2D TextureLayer0 : register( t0 );
Texture2D TextureLayer1 : register( t1 );
Texture2D TextureLayer2 : register( t2 );
Texture2D TextureLayer3 : register( t3 );
SamplerState Sampler : register(s0);

//====================================================================================================
// Structs
//====================================================================================================

struct VS_INPUT
{
	float4 position : POSITION;
	float3 normal	: NORMAL;
	float3 tangent	: TANGENT;
	float4 color	: COLOR;
	float2 texcoord	: TEXCOORD;
};

//----------------------------------------------------------------------------------------------------

struct VS_OUTPUT
{
	float4 position	: SV_POSITION;
	float2 texcoord	: TEXCOORD0;
	float2 height	: TEXCOORD1;
};

//====================================================================================================
// Vertex Shader
//====================================================================================================

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	output.position = mul(input.position, WVP);
	output.texcoord = input.texcoord;
	output.height = input.position.y;

	return output;
}

//====================================================================================================
// Pixel Shader
//====================================================================================================

float4 PS(VS_OUTPUT input) : SV_Target
{
	float4 layer0 = TextureLayer0.Sample(Sampler, input.texcoord * layer[0].z);
	float4 layer1 = TextureLayer1.Sample(Sampler, input.texcoord * layer[1].z);
	float4 layer2 = TextureLayer2.Sample(Sampler, input.texcoord * layer[2].z);
	float4 layer3 = TextureLayer3.Sample(Sampler, input.texcoord * layer[3].z);

	float h = input.height.x;
	float4 color = layer0;
	if (h < layer[1].x)
	{
		color = layer0;
	}
	else if (h < layer[0].y)
	{
		float t = (h - layer[1].x) / (layer[0].y - layer[1].x);
		color = lerp(layer0, layer1, t);
	}
	else if (h < layer[2].x)
	{
		color = layer1;
	}
	else if (h < layer[1].y)
	{
		float t = (h - layer[2].x) / (layer[1].y - layer[2].x);
		color = lerp(layer1, layer2, t);
	}
	else if (h < layer[3].x)
	{
		color = layer2;
	}
	else if (h < layer[2].y)
	{
		float t = (h - layer[3].x) / (layer[2].y - layer[3].x);
		color = lerp(layer2, layer3, t);
	}
	else
	{
		color = layer3;
	}
	return color;
}
