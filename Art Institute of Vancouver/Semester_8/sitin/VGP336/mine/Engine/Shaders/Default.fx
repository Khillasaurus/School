//====================================================================================================
// Filename:	Default.fx
// Created by:	Peter Chan
// Description:	Basic shader for applying transform and lighting.
//====================================================================================================

//====================================================================================================
// Constant Buffers
//====================================================================================================

cbuffer CBPerFrame : register(b0)
{
	matrix World;
	matrix WVP;
	float4 ViewPosition;
	float4 LightDirection;
	float4 AmbientLight;
	float4 DiffuseLight;
	float4 SpecularLight;
	float4 AmbientMaterial;
	float4 DiffuseMaterial;
	float4 SpecularMaterial;
	float SpecularPower;
}

//====================================================================================================
// Textures and Samplers
//====================================================================================================

Texture2D DiffuseMap : register(t0);
SamplerState Sampler : register(s0);

//====================================================================================================
// Structs
//====================================================================================================

struct A2V
{
	float4 position : POSITION;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float4 color : COLOR;
	float2 texcoord : TEXCOORD;
};

//----------------------------------------------------------------------------------------------------

struct V2P
{
	float4 position : SV_POSITION;
	float3 normal : NORMAL;
	float3 dirToView : TEXCOORD0;
	float2 texcoord : TEXCOORD1;
};

//====================================================================================================
// Vertex Shader
//====================================================================================================

V2P VS(A2V input)
{
	V2P output = (V2P)0;

	output.position = mul(input.position, WVP);
	output.normal = mul(float4(input.normal, 0.0f), World).xyz;
	output.dirToView = normalize(ViewPosition.xyz - mul(input.position, World).xyz);
	output.texcoord = input.texcoord;

	return output;
}

//====================================================================================================
// Pixel Shader
//====================================================================================================

float4 PS(V2P input) : SV_Target
{
	// Ambient
	float4 ambient = AmbientMaterial * AmbientLight;

	// Diffuse
	float3 n = normalize(input.normal);
	float d = saturate(dot(n, -LightDirection.xyz));
	float4 diffuse = d * DiffuseMaterial * DiffuseLight;

	// Specular
	float3 v = normalize(input.dirToView);
	float3 r = normalize(reflect(LightDirection.xyz, n));
	float s = saturate(dot(v, r));
	float4 specular = pow(s, SpecularPower) * SpecularMaterial * SpecularLight;

	float4 texColor = DiffuseMap.Sample(Sampler, input.texcoord);
	return ((ambient + diffuse) * texColor) + specular;
}