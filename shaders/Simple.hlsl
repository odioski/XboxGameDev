//--------------------------------------------------------------------------------------
// Simple.hlsl
//
// Simple shader example for Xbox One
// Demonstrates basic vertex and pixel shader setup
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer ConstantBuffer : register(b0)
{
    matrix World;
    matrix View;
    matrix Projection;
    float4 Color;
}

//--------------------------------------------------------------------------------------
// Vertex Shader Input
//--------------------------------------------------------------------------------------
struct VS_INPUT
{
    float4 Pos : POSITION;
    float4 Color : COLOR;
};

//--------------------------------------------------------------------------------------
// Vertex Shader Output / Pixel Shader Input
//--------------------------------------------------------------------------------------
struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS(VS_INPUT input)
{
    PS_INPUT output = (PS_INPUT)0;
    
    // Transform the vertex position to world space
    output.Pos = mul(input.Pos, World);
    
    // Then to view space
    output.Pos = mul(output.Pos, View);
    
    // Finally to clip space
    output.Pos = mul(output.Pos, Projection);
    
    // Pass the color through
    output.Color = input.Color;
    
    return output;
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(PS_INPUT input) : SV_Target
{
    // Return the interpolated color
    return input.Color;
}
