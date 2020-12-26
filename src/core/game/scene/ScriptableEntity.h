#pragma once
#include "Entity.h"

struct NativeScriptComponent;

class ScriptableEntity
{
public:
	virtual ~ScriptableEntity() {};

	template<typename T> T& GetComponent()
	{
		return m_Entity.GetComponent<T>();
	}
//protected:
	virtual bool OnCreate() { return true; };
	virtual bool OnDestroy() { return true; };
	virtual bool OnUpdate(float fElapstedTime) { return true; };

private:
	Entity m_Entity;
	friend class Scene;
	friend class NativeScriptComponent;
};
