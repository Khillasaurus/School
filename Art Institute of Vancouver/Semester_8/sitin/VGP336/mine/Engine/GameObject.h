#ifndef INCLUDED_ENGINE_GAMEOBJECT_H
#define INCLUDED_ENGINE_GAMEOBJECT_H

//====================================================================================================
// Filename:	GameObject.h
// Created by:	Peter Chan
// Description:	Class for a game object.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

//====================================================================================================
// Forward Declarations
//====================================================================================================

class Component;

//====================================================================================================
// Class Declarations
//====================================================================================================

class GameObject
{
public:
	GameObject();
	~GameObject();

	const char* GetName() const				{ return mName.c_str(); }
	
	template <typename T>
	bool GetComponent(T*& component);
	template <typename T>
	bool GetComponent(const T*& component) const;
	
	template <typename T>
	bool FindComponent(T*& component);
	template <typename T>
	bool FindComponent(const T*& component) const;

private:
	std::string mName;

	typedef std::vector<Component*> Components;
	Components mComponents;
};

#endif // #ifndef INCLUDED_ENGINE_GAMEOBJECT_H