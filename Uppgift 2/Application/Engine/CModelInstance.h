#pragma once
class CModel;
class CModelInstance
{
public:
	void Init(CModel * aModel);
	CModel* GetModel();
private:
	CModel* myModel;
};

