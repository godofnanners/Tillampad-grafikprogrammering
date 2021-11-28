#include "CParticleFactory.h"
#include "CDirectX11Framework.h"
#include <fstream>
#include <rapidjson\document.h>
#include "CParticle.h"
#include <d3d11.h>
#include "Macro.h"
#include <sstream>
#include <DDSTextureLoader.h>
#include <locale>
#include <codecvt>
#include "CParticle.h"

CParticleFactory CParticleFactory::ourInstance;

CParticleFactory::CParticleFactory()
{
	myDevice = nullptr;
}

CParticleFactory::~CParticleFactory()
{
}

bool CParticleFactory::Init(CDirectX11Framework* aFramework)
{
	myDevice = aFramework->GetDevice();
	return true;
}

CParticle* CParticleFactory::GetPartticle(std::string aFilePath)
{
	return nullptr;
}

CParticle* CParticleFactory::LoadParticle(std::string aFilePath)
{
	const std::ifstream input_stream(aFilePath, std::ios_base::binary);

	if (input_stream.fail()) {
		throw std::runtime_error("Failed to open file");
	}
	std::stringstream buffer;
	buffer << input_stream.rdbuf();

	rapidjson::Document particleDocument;
	particleDocument.Parse(buffer.str().c_str());
	CParticle* particle = new CParticle();

	CParticle::SParticleData ParticleData;
	ParticleData.myStride = sizeof(CParticle::SParticleVertex);
	assert(particleDocument["Offset"].IsInt());
	ParticleData.myOffset = particleDocument["Offset"].GetInt();
	assert(particleDocument["SpawnRate"].IsDouble());
	ParticleData.mySpawnRate = particleDocument["SpawnRate"].GetDouble();
	assert(particleDocument["Angle"].IsDouble());
	ParticleData.mySpawnAngle = particleDocument["Angle"].GetDouble();
	assert(particleDocument["Lifetime"].IsDouble());
	ParticleData.myParticleLifetime = particleDocument["Lifetime"].GetDouble();
	assert(particleDocument["Speed"].IsDouble());
	ParticleData.myParticleSpeed = particleDocument["Speed"].GetDouble();
	assert(particleDocument["StartSize"].IsDouble());
	ParticleData.myParticleStartSize = particleDocument["StartSize"].GetDouble();
	assert(particleDocument["EndSize"].IsDouble());
	ParticleData.myParticleEndSize = particleDocument["EndSize"].GetDouble();
	ParticleData.myNumberOfParticles = ceilf(ParticleData.myParticleLifetime * ParticleData.mySpawnRate);

	const rapidjson::Value& StartColor = particleDocument["StartColor"];
	assert(StartColor.IsArray());
	ParticleData.myParticleStartColor = { (float)StartColor[0].GetDouble(),(float)StartColor[1].GetDouble() ,(float)StartColor[2].GetDouble() ,(float)StartColor[3].GetDouble() };
	
	const rapidjson::Value& EndColor = particleDocument["EndColor"];
	assert(EndColor.IsArray());
	ParticleData.myParticleEndColor = { (float)EndColor[0].GetDouble(),(float)EndColor[1].GetDouble() ,(float)EndColor[2].GetDouble() ,(float)EndColor[3].GetDouble() };

	HRESULT result;
	assert(particleDocument["GeometryShader"].IsString());
	std::ifstream gsFile;
	gsFile.open(particleDocument["GeometryShader"].GetString(), std::ios::binary);
	std::string gsData = { std::istreambuf_iterator<char>(gsFile),std::istreambuf_iterator<char>() };
	result = myDevice->CreateGeometryShader(gsData.data(), gsData.size(), nullptr, &ParticleData.myGeometryShader);
	if (FAILED(result))
	{
		gsFile.close();
		return nullptr;
	}
	gsFile.close();

	assert(particleDocument["PixelShader"].IsString());
	std::ifstream psFile;
	psFile.open(particleDocument["PixelShader"].GetString(), std::ios::binary);
	std::string psData = { std::istreambuf_iterator<char>(psFile),std::istreambuf_iterator<char>() };
	result = myDevice->CreatePixelShader(psData.data(), psData.size(), nullptr, &ParticleData.myPixelShader);
	if (FAILED(result))
	{
		psFile.close();
		return nullptr;
	}
	psFile.close();

	assert(particleDocument["VertexShader"].IsString());
	std::ifstream vsFile;
	vsFile.open(particleDocument["VertexShader"].GetString(), std::ios::binary);
	std::string vsData = { std::istreambuf_iterator<char>(vsFile),std::istreambuf_iterator<char>() };
	result = myDevice->CreateVertexShader(vsData.data(), vsData.size(), nullptr, &ParticleData.myVertexShader);
	if (FAILED(result))
	{
		vsFile.close();
		assert(!"wasnt able to create a shaderresource for particles");
		return nullptr;
	}
	vsFile.close();


	//Start Layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"LIFETIME",0,DXGI_FORMAT_R32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"POSITION",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"MOVEMENT",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"SIZE",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{"DISTANCE",0,DXGI_FORMAT_R32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0 },
	};

	ID3D11InputLayout* inputLayout;
	result = myDevice->CreateInputLayout(layout, sizeof(layout) / sizeof(D3D11_INPUT_ELEMENT_DESC), vsData.data(), vsData.size(), &ParticleData.myInputLayout);
	if (FAILED(result))
	{
		return nullptr;
	}
	//End Layout


	assert(particleDocument["SpritePath"].IsString());
	std::ifstream textureFile;
	textureFile.open(particleDocument["SpritePath"].GetString(), std::ios::binary);
	std::string textureData = particleDocument["SpritePath"].GetString();
	std::wstring wTextureData(textureData.begin(), textureData.end());
	result = DirectX::CreateDDSTextureFromFile(myDevice, wTextureData.c_str(), nullptr, &ParticleData.myTexture);
	if (FAILED(result))
	{
		textureFile.close();
		assert(!"wasnt able to create a shader resource for particles");
	}
	textureFile.close();

	//Start Vertex
	D3D11_BUFFER_DESC vertexBufferDescription = { 0 };
	vertexBufferDescription.ByteWidth = ceilf(ParticleData.myParticleLifetime*ParticleData.mySpawnRate)*sizeof(CParticle::SParticleVertex);
	vertexBufferDescription.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	result = myDevice->CreateBuffer(&vertexBufferDescription, nullptr, &ParticleData.myPartcleVertexBuffer);
	if (FAILED(result))
	{
		return nullptr;
	}
	//End Vertex

	particle->Init(ParticleData);
	
	return particle;
}

CParticleFactory& CParticleFactory::GetInstance()
{
	return ourInstance;
}
