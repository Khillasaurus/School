#ifndef INCLUDED_ENGINE_RESOURCEMANAGER_H
#define INCLUDED_ENGINE_RESOURCEMANAGER_H

//====================================================================================================
// Filename:	ResourceManager.h
// Created by:	Peter Chan
// Description:	Templatized class for a resource manager.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Hash.h"

//====================================================================================================
// Class Declarations
//====================================================================================================

template <typename T>
class ResourceManager
{
public:
	ResourceManager();
	virtual ~ResourceManager();

	void Terminate();

	T* GetResource(const wchar_t* pFilename);

private:
	NONCOPYABLE(ResourceManager);

	virtual void InitResource(T*, const wchar_t* pFilename) = 0;
	virtual void CleanupResource(T*) = 0;

	typedef std::map<u64, T*> Inventory;
	Inventory mInventory;
};

//====================================================================================================
// Inline Definitions
//====================================================================================================

#include "ResourceManager.inl"

#endif // #ifndef INCLUDED_ENGINE_RESOURCEMANAGER_H