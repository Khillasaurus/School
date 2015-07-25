#ifndef INCLUDED_ENGINE_MODELMANAGER_H
#define INCLUDED_ENGINE_MODELMANAGER_H

//====================================================================================================
// Filename:	ModelManager.h
// Created by:	Peter Chan
// Description:	Class for managing model resources.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "ResourceManager.h"
#include "Model.h"

//====================================================================================================
// Class Declarations
//====================================================================================================

class ModelManager : public ResourceManager<Model>
{
public:
	ModelManager();

	void Initialize(GraphicsSystem& gs);

private:
	virtual void InitResource(Model* model, const wchar_t* pFilename);
	virtual void CleanupResource(Model* model);

	GraphicsSystem* mpGraphicsSystem;
};

#endif // #ifndef INCLUDED_ENGINE_MODELMANAGER_H