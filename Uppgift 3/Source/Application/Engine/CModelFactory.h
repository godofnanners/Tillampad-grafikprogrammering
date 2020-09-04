#pragma once
#include <string>
struct ID3D11Device;
class CModel;


class CModelFactory
{
public:
	CModelFactory(const CModelFactory&) = delete;
	static CModelFactory& GetInstance();
	CModel* GetModel(std::string aFilePath);
	CModel* LoadModel(std::string aFilePath);
	void Init(ID3D11Device* aDevice);
private:
	ID3D11Device* myDevice;
	CModelFactory();
	static CModelFactory myInstance;
};

