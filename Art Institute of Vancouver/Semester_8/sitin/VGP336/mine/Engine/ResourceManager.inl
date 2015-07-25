//====================================================================================================
// Filename:	ResourceManager.inl
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Class Definitions
//====================================================================================================

template <typename T>
ResourceManager<T>::ResourceManager()
{}

//----------------------------------------------------------------------------------------------------

template <typename T>
ResourceManager<T>::~ResourceManager()
{
	ASSERT(mInventory.empty(), "[ResourceManager] Inventory not empty!");
}

//----------------------------------------------------------------------------------------------------

template <typename T>
void ResourceManager<T>::Terminate()
{
	// Make sure we are holding the last reference of each resource
	for (Inventory::iterator iter = mInventory.begin();
		 iter != mInventory.end();
		 ++iter)
	{
		T* resource = iter->second;
		ASSERT(resource->GetRefCount() == 1, "[ResourceManager] Resource count must be 1 on terminate. Potential memory leak!");
		CleanupResource(resource);
		SafeRelease(resource);
	}
	mInventory.clear();
}

//----------------------------------------------------------------------------------------------------

template <typename T>
T* ResourceManager<T>::GetResource(const wchar_t* pFilename)
{
	// Check if resource already exist in our inventory
	const u64 hash = GetHash(pFilename);
	Inventory::iterator iter = mInventory.find(hash);
	if (iter != mInventory.end())
	{
		iter->second->AddRef();
		return iter->second;
	}

	// Create a new entry in our inventory
	T* newResource = new T();
	newResource->AddRef();
	InitResource(newResource, pFilename);
	mInventory.insert(std::make_pair(hash, newResource));

	newResource->AddRef();
	return newResource;
}