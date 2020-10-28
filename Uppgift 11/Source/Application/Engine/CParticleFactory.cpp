#include "CParticleFactory.h"
#include "CDirectX11Framework.h"
#include <fstream>
#include <rapidjson\document.h>
#include "CParticle.h"
#include <d3d11.h>

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
    return false;
}

CParticle* CParticleFactory::GetPartticle(std::string aFilePath)
{
    rapidjson::Document particleDocument;
    particleDocument.Parse(aFilePath.c_str());
    CParticle particle;
    
    CParticle::SParticleData ParticleData;
    assert(particleDocument["NumberOfParticles"].IsInt());
    ParticleData.myNumberOfParticles = particleDocument["NumberOfParticles"].GetInt();
    assert(particleDocument["NumberOfParticles"].IsInt());
    ParticleData.myStride = particleDocument["Stride"].GetInt();
    assert(particleDocument["Offset"].IsInt());
    ParticleData.myOffset = particleDocument["Offset"].GetInt();
    assert(particleDocument["SpawnRate"].IsDouble());
    ParticleData.mySpawnRate = particleDocument["NumberOfParticles"].GetDouble();
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

    const rapidjson::Value& StartColor = particleDocument["StartColor"];
    assert(StartColor.IsArray());
    ParticleData.myParticleStartColor = { StartColor[0].GetDouble(),StartColor[1].GetDouble() ,StartColor[2].GetDouble() ,StartColor[3].GetDouble() };
    const rapidjson::Value& EndColor = particleDocument["EndColor"];
    assert(EndColor.IsArray());
    ParticleData.myParticleStartColor = { EndColor[0].GetDouble(),EndColor[1].GetDouble() ,EndColor[2].GetDouble() ,EndColor[3].GetDouble() };
    
    //assert(particleDocument["SpritePath"].IsString());
    //ParticleData.myTexture = particleDocument["SpritePath"].GetString();
    HRESULT result;
    assert(particleDocument["GeometryShader"].IsString());
    ParticleData.myGeometryShader = particleDocument["GeometryShader"].GetString();
    
    
    assert(particleDocument["PixelShader"].IsString());
    std::ifstream psFile;
    psFile.open(particleDocument["PixelShader"].GetString(), std::ios::binary);
    std::string psData = { std::istreambuf_iterator<char>(psFile),std::istreambuf_iterator<char>() };
    ID3D11PixelShader* pixelShader;
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
    ID3D11VertexShader* vertexShader;
    result = myDevice->CreateVertexShader(vsData.data(), vsData.size(), nullptr, &ParticleData.myVertexShader);
    if (FAILED(result))
    {
        vsFile.close();

        return nullptr;
    }
    vsFile.close();
    
    //assert(particleDocument["StartGcolor"].IsDouble());
    //ParticleData.myParticleSpeed = particleDocument["StartGcolor"].GetDouble();
    //assert(particleDocument["StartBcolor"].IsDouble());
    //ParticleData.myParticleSpeed = particleDocument["StartBcolor"].GetDouble();
    //assert(particleDocument["StartAcolor"].IsDouble());
    //ParticleData.myParticleSpeed = particleDocument["StartAcolor"].GetDouble();
    //assert(particleDocument["EndRcolor"].IsDouble());
    //ParticleData.myParticleSpeed = particleDocument["EndRcolor"].GetDouble();
    //assert(particleDocument["EndGcolor"].IsDouble());
    //ParticleData.myParticleSpeed = particleDocument["EndGcolor"].GetDouble();
    //assert(particleDocument["EndBcolor"].IsDouble());
    //ParticleData.myParticleSpeed = particleDocument["EndBcolor"].GetDouble();
    //assert(particleDocument["EndAcolor"].IsDouble());
    //ParticleData.myParticleSpeed = particleDocument["EndAcolor"].GetDouble();

    particle.Init()
    
        
   

    return nullptr;
}

CParticle* CParticleFactory::LoadParticle(std::string aFilePath)
{
    return nullptr;
}

CParticleFactory& CParticleFactory::GetInstance()
{
    return ourInstance;
}
