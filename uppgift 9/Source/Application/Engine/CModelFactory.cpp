#include "CModelFactory.h"
#include "CModel.h"
#include <Windows.h>
#include <d3d11.h>
#include <fstream>
#include "DDSTextureLoader.h"
#include "FBXLoader.h"
CModelFactory CModelFactory::myInstance;

CModelFactory& CModelFactory::GetInstance()
{
	return myInstance;
}

CModel* CModelFactory::GetCube()
{
	HRESULT result;

	//Start Vertex
	struct Vertex
	{
		float x, y, z, w;
		float r, g, b, a;
		float u, v;
	}vertices[8] =
	{
		{1,1,1,1,1,1,1,1,1,0},
		{1,1,-1,1,1,1,0,1,1,0},
		{1,-1,1,1,1,0,1,1,1,1},
		{-1,1,1,1,0,1,1,1,0,0},
		{1,-1,-1,1,1,0,0,1,1,1},
		{-1,1,-1,1,0,1,0,1,0,0},
		{-1,-1,1,1,0,0,1,1,0,1},
		{-1,-1,-1,1,0,0,0,1,0,1},
	};
	unsigned int indices[36] =
	{
		0,2,1,
		0,1,3,
		0,3,2,
		1,2,4,
		2,3,6,
		3,1,5,
		4,5,1,
		5,6,3,
		6,4,2,
		7,6,5,
		7,5,4,
		7,4,6
	};

	D3D11_BUFFER_DESC vertexBufferDescription = { 0 };
	vertexBufferDescription.ByteWidth = sizeof(vertices);
	vertexBufferDescription.Usage = D3D11_USAGE_IMMUTABLE;
	vertexBufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA vertexSubresourceData = { 0 };
	vertexSubresourceData.pSysMem = vertices;

	ID3D11Buffer* vertexBuffer;
	result = myDevice->CreateBuffer(&vertexBufferDescription, &vertexSubresourceData, &vertexBuffer);

	if (FAILED(result))
	{
		return nullptr;
	}

	D3D11_BUFFER_DESC indexbufferDescription = { 0 };
	indexbufferDescription.ByteWidth = sizeof(indices);
	indexbufferDescription.Usage = D3D11_USAGE_IMMUTABLE;
	indexbufferDescription.BindFlags = D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA indexSubresourceData = { 0 };
	indexSubresourceData.pSysMem = indices;

	ID3D11Buffer* indexBuffer;
	result = myDevice->CreateBuffer(&indexbufferDescription, &indexSubresourceData, &indexBuffer);

	if (FAILED(result))
	{
		return nullptr;
	}
	//End Vertex

	//Start Shader
	std::ifstream vsFile;
	vsFile.open("CubeVertexShader.cso", std::ios::binary);
	std::string vsData = { std::istreambuf_iterator<char>(vsFile),std::istreambuf_iterator<char>() };
	ID3D11VertexShader* vertexShader;
	result = myDevice->CreateVertexShader(vsData.data(), vsData.size(), nullptr, &vertexShader);
	if (FAILED(result))
	{
		vsFile.close();

		return nullptr;
	}
	vsFile.close();

	std::ifstream psFile;
	psFile.open("CubePixelShader.cso", std::ios::binary);
	std::string psData = { std::istreambuf_iterator<char>(psFile),std::istreambuf_iterator<char>() };
	ID3D11PixelShader* pixelShader;
	result = myDevice->CreatePixelShader(psData.data(), psData.size(), nullptr, &pixelShader);
	if (FAILED(result))
	{
		psFile.close();
		return nullptr;
	}
	psFile.close();
	//End Shader

	//Start Layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"UV",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
	};

	ID3D11InputLayout* inputLayout;
	result = myDevice->CreateInputLayout(layout, sizeof(layout)/sizeof(D3D11_INPUT_ELEMENT_DESC), vsData.data(), vsData.size(), &inputLayout);
	if (FAILED(result))
	{
		return nullptr;
	}
	//End Layout

	//Start Textures
	std::wstring filename = L"Textures/Texture.dds";
	ID3D11ShaderResourceView* shaderResourceView;
	result = DirectX::CreateDDSTextureFromFile(myDevice, filename.c_str(), nullptr, &shaderResourceView);
	if (FAILED(result))
	{
		return nullptr;
	}
	//End Textures

	CModel* model = new CModel();
	if (!model)
	{
		return nullptr;
	}
	CModel::SModelData modelData;
	modelData.myNumberOfVerticies = sizeof(vertices) / sizeof(Vertex);
	modelData.myNumberOfIndices = sizeof(indices) / sizeof(unsigned int);
	modelData.myStride = sizeof(Vertex);
	modelData.myOffset = 0;
	modelData.myVertexBuffer = vertexBuffer;
	modelData.myIndexBuffer = indexBuffer;
	modelData.myVertexShader = vertexShader;
	modelData.myPixelShader = pixelShader;
	modelData.myPrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	modelData.myInputLayout = inputLayout;
	modelData.myTexture[0] = shaderResourceView;
	model->Init(modelData);

	return model;
}

CModel* CModelFactory::GetModel(std::string aFilePath)
{
	HRESULT result;

	//Start Vertex
	struct Vertex
	{
		float x, y, z, w;
		float r, g, b, a;
	} vertices[3] =
	{
		{-0.8f,-0.8f,0,1,1,0,0,1},
		{0.0f,0.8f,0,1,0,1,0,1},
		{0.8f,-0.8f,0,1,0,0,1,1}
	};

	D3D11_BUFFER_DESC bufferDescription = { 0 };
	bufferDescription.ByteWidth = sizeof(vertices);
	bufferDescription.Usage = D3D11_USAGE_IMMUTABLE;
	bufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA subresourceData = { 0 };
	subresourceData.pSysMem = vertices;

	ID3D11Buffer* vertexBuffer;
	result = myDevice->CreateBuffer(&bufferDescription, &subresourceData, &vertexBuffer);

	if (FAILED(result))
	{
		return nullptr;
	}
	//End Vertex

	//Start Shader
	std::ifstream vsFile;
	vsFile.open("VertexShader.cso", std::ios::binary);
	std::string vsData = { std::istreambuf_iterator<char>(vsFile),std::istreambuf_iterator<char>() };
	ID3D11VertexShader* vertexShader;
	result = myDevice->CreateVertexShader(vsData.data(), vsData.size(), nullptr, &vertexShader);
	if (FAILED(result))
	{
		vsFile.close();

		return nullptr;
	}
	vsFile.close();

	std::ifstream psFile;
	psFile.open("PixelShader.cso", std::ios::binary);
	std::string psData = { std::istreambuf_iterator<char>(psFile),std::istreambuf_iterator<char>() };
	ID3D11PixelShader* pixelShader;
	result = myDevice->CreatePixelShader(psData.data(), psData.size(), nullptr, &pixelShader);
	if (FAILED(result))
	{
		psFile.close();
		return nullptr;
	}
	psFile.close();
	//End Shader

	//Start Layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
	};

	ID3D11InputLayout* inputLayout;
	result = myDevice->CreateInputLayout(layout, 2, vsData.data(), vsData.size(), &inputLayout);
	if (FAILED(result))
	{
		return nullptr;
	}
	//End Layout

	CModel* model = new CModel();
	if (!model)
	{
		return nullptr;
	}

	CModel::SModelData modelData;
	modelData.myNumberOfVerticies = sizeof(vertices) / sizeof(Vertex);
	modelData.myStride = sizeof(Vertex);
	modelData.myOffset = 0;
	modelData.myVertexBuffer = vertexBuffer;
	modelData.myVertexShader = vertexShader;
	modelData.myPixelShader = pixelShader;
	modelData.myPrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	modelData.myInputLayout = inputLayout;
	model->Init(modelData);

	return model;
}

CModel* CModelFactory::LoadModel(std::string aFilePath)
{
	HRESULT result;


	CLoaderModel* loadmodel = myModelLoader->LoadModel(aFilePath.c_str());
	CLoaderMesh* loadmesh = loadmodel->myMeshes[0];
	//Start Vertex

	D3D11_BUFFER_DESC vertexBufferDescription = { 0 };
	vertexBufferDescription.ByteWidth = loadmesh->myVertexSize*loadmesh->myVertexCount;
	vertexBufferDescription.Usage = D3D11_USAGE_IMMUTABLE;
	vertexBufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA subresourceData = { 0 };
	subresourceData.pSysMem = loadmesh->myVertices;

	ID3D11Buffer* vertexBuffer;
	result = myDevice->CreateBuffer(&vertexBufferDescription, &subresourceData, &vertexBuffer);
	if (FAILED(result))
	{
		return nullptr;
	}
	
	D3D11_BUFFER_DESC indexbufferDescription = { 0 };
	indexbufferDescription.ByteWidth = sizeof(unsigned int)* static_cast<unsigned int>(loadmesh->myIndices.size());
	indexbufferDescription.Usage = D3D11_USAGE_IMMUTABLE;
	indexbufferDescription.BindFlags = D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA indexSubresourceData = { 0 };
	indexSubresourceData.pSysMem = &loadmesh->myIndices[0];

	ID3D11Buffer* indexBuffer;
	result = myDevice->CreateBuffer(&indexbufferDescription, &indexSubresourceData, &indexBuffer);

	if (FAILED(result))
	{
		return nullptr;
	}
	//End Vertex

	//Start Shader
	std::ifstream vsFile;
	vsFile.open("VertexShader.cso", std::ios::binary);
	std::string vsData = { std::istreambuf_iterator<char>(vsFile),std::istreambuf_iterator<char>() };
	ID3D11VertexShader* vertexShader;
	result = myDevice->CreateVertexShader(vsData.data(), vsData.size(), nullptr, &vertexShader);
	if (FAILED(result))
	{
		vsFile.close();

		return nullptr;
	}
	vsFile.close();

	std::ifstream psFile;
	psFile.open("PixelShader.cso", std::ios::binary);
	std::string psData = { std::istreambuf_iterator<char>(psFile),std::istreambuf_iterator<char>() };
	ID3D11PixelShader* pixelShader;
	result = myDevice->CreatePixelShader(psData.data(), psData.size(), nullptr, &pixelShader);
	if (FAILED(result))
	{
		psFile.close();
		return nullptr;
	}
	psFile.close();
	//End Shader

	//Start Layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"NORMAL",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"TANGENT",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"BINORMAL",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"UV",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0 },
	};

	ID3D11InputLayout* inputLayout;
	result = myDevice->CreateInputLayout(layout, sizeof(layout)/sizeof(D3D11_INPUT_ELEMENT_DESC), vsData.data(), vsData.size(), &inputLayout);
	if (FAILED(result))
	{
		return nullptr;
	}
	//End Layout

	//Start Textures
	std::wstring modelpath = std::wstring(loadmodel->myModelPath.begin(),loadmodel->myModelPath.end());
	size_t lastdotpos = modelpath.find_last_of('.');
	modelpath.erase(modelpath.begin() + lastdotpos, modelpath.end());
	std::wstring filename = modelpath;
	filename.append(L"_D.dds");
	//this should be linked in the fbx file wich will allow you to write
	//filename.append(std::wstring(loadmodel->myTextures[0].begin(),loadmodel->myTextures[0].end()));
	//filename.append(std::wstring(L"Particle_Chest_D.dds"));
	ID3D11ShaderResourceView* albedoShaderResourceView;
	result = DirectX::CreateDDSTextureFromFile(myDevice, filename.c_str(), nullptr, &albedoShaderResourceView);
	if (FAILED(result))
	{
		return nullptr;
	}

	std::wstring normalpath = modelpath;
	//normalpath.append(std::wstring(loadmodel->myTextures[5].begin(), loadmodel->myTextures[5].end()));
	normalpath.append(L"_N.dds");
	ID3D11ShaderResourceView* normalShaderResourceView;
	result = DirectX::CreateDDSTextureFromFile(myDevice, normalpath.c_str(), nullptr, &normalShaderResourceView);
	if (FAILED(result))
	{
		return nullptr;
	}

	std::wstring materialpath = modelpath;
	//normalpath.append(std::wstring(loadmodel->myTextures[5].begin(), loadmodel->myTextures[5].end()));
	materialpath.append(L"_M.dds");
	ID3D11ShaderResourceView* MaterialShaderResourceView;
	result = DirectX::CreateDDSTextureFromFile(myDevice, materialpath.c_str(), nullptr, &MaterialShaderResourceView);
	if (FAILED(result))
	{
		return nullptr;
	}

	
	//End Textures

	CModel* model = new CModel();
	if (!model)
	{
		return nullptr;
	}

	CModel::SModelData modelData;
	modelData.myNumberOfVerticies = loadmesh->myVertexCount;
	modelData.myNumberOfIndices = static_cast<unsigned int>(loadmesh->myIndices.size());
	modelData.myStride = loadmesh->myVertexSize;
	modelData.myOffset = 0;
	modelData.myVertexBuffer = vertexBuffer;
	modelData.myIndexBuffer = indexBuffer;
	modelData.myVertexShader = vertexShader;
	modelData.myPixelShader = pixelShader;
	modelData.myPrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	modelData.myInputLayout = inputLayout;
	modelData.myTexture[0] = albedoShaderResourceView;
	modelData.myTexture[1] = normalShaderResourceView;
	modelData.myTexture[2] = MaterialShaderResourceView;
	
	model->Init(modelData);

	return model;
}

void CModelFactory::Init(ID3D11Device* aDevice)
{
	myDevice = aDevice;
	myModelLoader = new CFBXLoader();
}

CModelFactory::CModelFactory()
{
	myDevice = nullptr;
	myModelLoader = nullptr;
}
