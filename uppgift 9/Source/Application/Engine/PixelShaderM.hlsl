#pragma warning (disable : 3206)
#include "ShaderStructs.hlsli"

#define PI 3.1416
#define FLT_EPSILON 1.192092896e-07f
#define nMipOffset 3

float3 LinearToGamma(float3 aColor)
{
	return pow(abs(aColor), 1.0 / 2.2);
}

float3 GammaToLinear(float3 aColor)
{
	return pow(abs(aColor), 2.2);
}

int GetNumMips(TextureCube cubeTex)
{
	int iWidth = 0, iHeight = 0, numMips = 0;
	cubeTex.GetDimensions(0, iWidth, iHeight, numMips);
	return numMips;
}

float bias(float value, float b)
{
	return (b > 0.0) ? pow(abs(value), log(b) / log(0.5)) : 0.0f;
}

float gain(float value, float g)
{
	return 0.5 * ((value < 0.5) ? bias(2.0 * value, 1.0 - g) : (2.0 - bias(2.0 - 2.0 * value, 1.0 - g)));
}

float RoughnessFromPerceptualRoughness(float fPerceptualRoughness)
{
	return fPerceptualRoughness * fPerceptualRoughness;
}

float PerceptualRoughnessFromRoughness(float fRoughness)
{
	return sqrt(max(0.0, fRoughness));
}

float SpecularPowerFromPerceptualRoughness(float fPerceptualRoughness)
{
	float fRoughness = RoughnessFromPerceptualRoughness(fPerceptualRoughness);
	return (2.0 / max(FLT_EPSILON, fRoughness * fRoughness)) - 2.0;
}

float PerceptualRoughnessFromSpecularPower(float fSpecPower)
{
	float fRoughness = sqrt(2.0 / (fSpecPower + 2.0));
	return PerceptualRoughnessFromRoughness(fRoughness);
}

float BurleyToMip(float fPerceptualRoughness, int nMips, float NdotR)
{
	float fSpecPower = SpecularPowerFromPerceptualRoughness(fPerceptualRoughness);
	fSpecPower /= (4 * max(NdotR, FLT_EPSILON));
	float fScale = PerceptualRoughnessFromSpecularPower(fSpecPower);
	return fScale * (nMips - 1 - nMipOffset);
}

float3 GetSpecularDominantDir(float3 vN, float3 vR, float fRealRoughness)
{
	float fInvRealRough = saturate(1 - fRealRoughness);
	float lerpFactor = fInvRealRough * (sqrt(fInvRealRough) + fRealRoughness);
	return lerp(vN, vR, lerpFactor);
}

float GetReductionInMicrofacets(float perceptualRoughness)
{
	float roughness = RoughnessFromPerceptualRoughness(perceptualRoughness);
	return 1.0f / (roughness * roughness + 1.0);
}

float EmpiricalSpecularAO(float ao, float perceptualRoughness)
{
	float fSmooth = 1 - perceptualRoughness;
	float fSpecAo = gain(ao, 0.5 + max(0.0, fSmooth * 0.4));
	return min(1.0, fSpecAo + lerp(0.0, 0.5, fSmooth * fSmooth * fSmooth * fSmooth));
}

float ApproximateSpecularSelfOcclusion(float3 vR, float3 vertexNormalNormalized)
{
	const float fFadeParam = 1.3;
	float rimmask = clamp(1 + fFadeParam * dot(vR, vertexNormalNormalized), 0.0, 1.0);
	rimmask *= rimmask;
	return rimmask;
}

PixelOutput PixelShader_Albedo(VertexToPixel input)
{
	PixelOutput output;
	float3 albedo = albedoTexture.Sample(defaultSampler, input.myUV.xy).rgb;
	albedo = GammaToLinear(albedo);
	output.myColor.rgb = albedo;
	output.myColor.a = 1.0f;
	return output;
}

PixelOutput PixelShader_Normal(VertexToPixel input)
{
	float3 normal = normalTexture.Sample(defaultSampler, input.myUV.xy).rgb;
	normal = (normal * 2) - 1;
	normal = normalize(normal);

	float3x3 tangentspacematrix = float3x3(normalize(input.myTangent.xyz), normalize(input.myBinormal.xyz), normalize(input.myNormal.xyz));
	normal = mul(normal.xyz, tangentspacematrix);
	normal = normalize(normal);

	PixelOutput output;
	output.myColor.xyz = normal.xyz;
	output.myColor.a = 1.0f;
	return output;
}

PixelOutput PixelShader_AmbientOcclusion(VertexToPixel input)
{
	PixelOutput output;
	float ao = normalTexture.Sample(defaultSampler, input.myUV.xy).a;
	output.myColor.rgb = ao.xxx;
	output.myColor.a = 1.0f;
	return output;
}

PixelOutput PixelShader_Material(VertexToPixel input)
{
	PixelOutput output;
	float3 material = materialTexture.Sample(defaultSampler, input.myUV.xy).rgb;	
	output.myColor.rgb = material.rgb;
	output.myColor.a = 1.0f;
	return output;
}

PixelOutput PixelShader_Metalness(VertexToPixel input)
{
	PixelOutput output;
	PixelOutput material = PixelShader_Material(input);
	output.myColor.rgb = material.myColor.rrr;
	output.myColor.a = 1.0f;
	return output;
}

PixelOutput PixelShader_PerceptualRoughness(VertexToPixel input)
{
	PixelOutput output;
	PixelOutput material = PixelShader_Material(input);
	output.myColor.rgb = material.myColor.ggg;
	output.myColor.a = 1.0f;
	return output;
}

PixelOutput PixelShader_Emissive(VertexToPixel input)
{
	PixelOutput output;
	PixelOutput material = PixelShader_Material(input);
	output.myColor.rgb = material.myColor.bbb;
	output.myColor.a = 1.0f;
	return output;
}

float3 Diffuse(float3 pAlbedo)
{
	return pAlbedo / PI;
}

float NormalDistribution_GGX(float a, float NdH)
{
	float a2 = a * a;
	float NdH2 = NdH * NdH;
	
	float denominator = NdH2 * (a2 - 1.0f) + 1.0f;
	denominator *= denominator;
	denominator *= PI;
	
	return a2 / denominator;
}

float Specular_D(float a, float NdH)
{
	return NormalDistribution_GGX(a, NdH);
}

float Geometric_Smith_Schlick_GGX(float a, float NdV, float NdL)
{
	float k		= a * 0.5f;
	float GV	= NdV / (NdV * (1 - k) + k);
	float GL	= NdL / (NdL * (1 - k) + k);

	return GV * GL;
}

float Specular_G(float a, float NdV, float NdL, float NdH, float VdH, float LdV)
{
	return Geometric_Smith_Schlick_GGX(a, NdV, NdL);
}

float3 Fresnel_Schlick(float3 specularColor, float3 h, float3 v)
{
	return (specularColor + (1.0f - specularColor) * pow((1.0f - saturate(dot(v, h))), 5));
}

float3 Specular_F(float3 specularColor, float3 h, float3 v)
{
	return Fresnel_Schlick(specularColor, h, v);
}

float3 Specular(float3 specularColor, float3 h, float3 v, float3 l, float a, float NdL, float NdV, float NdH, float VdH, float LdV)
{
	return ((Specular_D(a, NdH) * Specular_G(a, NdV, NdL, NdH, VdH, LdV)) * Specular_F(specularColor, v, h)) / (4.0f * NdL * NdV + 0.0001f);
}

float3 EvaluateAmbience(TextureCube lysBurleyCube, float3 vN, float3 org_normal, float3 to_cam, float perceptualRoughness, float metalness, float3 albedo, float ao, float3 dfcol, float3 spccol)
{
	int numMips				= GetNumMips(lysBurleyCube);
	const int nrBrdfMips	= numMips - nMipOffset;
	float VdotN				= clamp(dot(to_cam, vN), 0.0, 1.0f);
	const float3 vRorg		= 2 * vN * VdotN - to_cam;

	float3 vR				= GetSpecularDominantDir(vN, vRorg, RoughnessFromPerceptualRoughness(perceptualRoughness));
	float RdotNsat			= saturate(dot(vN, vR));

	float l					= BurleyToMip(perceptualRoughness, numMips, RdotNsat);

	float3 specRad			= lysBurleyCube.SampleLevel(defaultSampler, vR, l).xyz;
	float3 diffRad			= lysBurleyCube.SampleLevel(defaultSampler, vN, (float)(nrBrdfMips - 1)).xyz;

	float fT				= 1.0 - RdotNsat;
	float fT5				= fT * fT; fT5 = fT5 * fT5 * fT;
	spccol					= lerp(spccol, (float3) 1.0, fT5);

	float fFade				= GetReductionInMicrofacets(perceptualRoughness);
	fFade					*= EmpiricalSpecularAO(ao, perceptualRoughness);
	fFade					*= ApproximateSpecularSelfOcclusion(vR, org_normal);

	float3 ambientDiffuse	= ao * dfcol * diffRad;
	float3 ambientSpecular	= fFade * spccol * specRad;
	
	return ambientDiffuse + ambientSpecular;
}

float3 EvaluateDirectionalLight(float3 albedoColor, float3 specularColor, float3 normal, float roughness, float3 lightColor, float3 lightDir, float3 viewDir)
{
	float NdL		= saturate(dot(normal, lightDir));
	float lambert	= NdL;
	float NdV		= saturate(dot(normal, viewDir));
	float3 h		= normalize(lightDir + viewDir);
	float NdH		= saturate(dot(normal, h));
	float VdH		= saturate(dot(viewDir, h));
	float LdV		= saturate(dot(lightDir, viewDir));
	float a			= max(0.001f, roughness * roughness);
	
	float3 cDiff	= Diffuse(albedoColor);
	float3 cSpec	= Specular(specularColor, h, viewDir, lightDir, a, NdL, NdV, NdH, VdH, LdV);
	
	return saturate(lightColor * lambert * (cDiff * (1.0f - cSpec) + cSpec) * PI);
}

PixelOutput main(VertexToPixel input)
{
	PixelOutput output;
	float3 toEye				= normalize(cameraPosition.xyz - input.myWorldPosition.xyz);
	float3 albedo				= PixelShader_Albedo(input).myColor.rgb;
	float3 normal				= PixelShader_Normal(input).myColor.xyz;
	float ambientOcclusion		= PixelShader_AmbientOcclusion(input).myColor.r;
	float metalness				= PixelShader_Metalness(input).myColor.r;
	float perceptualRoughness	= PixelShader_PerceptualRoughness(input).myColor.r;
	float emissiveData			= PixelShader_Emissive(input).myColor.r;

	float3 specularColor		= lerp((float3) 0.04, albedo, metalness);
	float3 diffuseColor			= lerp((float3) 0.00, albedo, 1 - metalness);

	float3 ambience				= EvaluateAmbience(EnvironmentCubemapTexture, normal, input.myNormal.xyz, toEye, perceptualRoughness, metalness, albedo, ambientOcclusion, diffuseColor, specularColor);
	float3 directionalLight		= EvaluateDirectionalLight(diffuseColor, specularColor, normal, perceptualRoughness, directionalLightColor.xyz, toDirectionalLight.xyz, toEye.xyz);
	float3 emissive				= albedo * emissiveData;
	float3 radiance				= ambience + directionalLight + emissive;

    output.myColor.rgb			= LinearToGamma(radiance); //directionalLight; // den kr�nglar
	output.myColor.a			= 1.0f;
	
	return output;
}