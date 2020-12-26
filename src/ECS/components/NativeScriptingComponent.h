#include "core/game/scene/ScriptableEntity.h"


struct NativeScriptComponent
{
	ScriptableEntity* Instance = nullptr;

	//void (*InstantiateScript)(Entity);
	ScriptableEntity* (*InstantiateScript)(Entity);
	void (*DestroyScript)(NativeScriptComponent*);
	//void (*InstantiateScript)(void*);
	//std::function<void(Entity)> InstantiateScript;

	inline bool OnCreate() {
		return Instance->OnCreate();
	}
	inline bool OnUpdate(float fElapsedTime) {
		return Instance->OnUpdate(fElapsedTime);
	}
	inline bool OnDestroy() {
		return Instance->OnDestroy();
	}

	template<typename T>
	void Bind()
	{
		InstantiateScript = [](Entity entity) {
			auto* se = static_cast<ScriptableEntity*>(new T());
			se->m_Entity = entity;
			return se;
		};
		DestroyScript = [](NativeScriptComponent* nsc) {delete (T*)nsc->Instance; };
	}
};

/*
struct NativeScriptComponent
{ 

	ScriptableEntity* Instance = nullptr;

	ScriptableEntity(*InstantiateScript)();
	void (*DestroyScrpit)(NativeScriptComponent*);
	//std::function<void()> InstantiateFunction;
	//std::function<void()> DestroyInstanceFunction;

	virtual bool OnCreate() { return true; };
	virtual bool OnUpdate(float fElapsedTime) { return true; };
	virtual bool OnDestroy() { return true; };

	//std::function<void(ScriptableEntity*)> OnCreateFunction;
	//std::function<void(ScriptableEntity*)> OnDestroyFunction;
	//std::function<void(ScriptableEntity*, float)> OnUpdateFunction;

	template<typename T>
	void Bind()
	{
		InstantiateScript = []() {return new T(); };
		DestroyScript = [](NativeScriptComponent* nsc) {delete (T*)nsc->Instance;}
		//DestroyScript = []() {delete ((T*)Instance); };

		//OnCreateFunction = [](ScriptableEntity* instance) {((T*)instance)->OnCreate(); };
		//OnDestroyFunction = [](ScriptableEntity* instance) {((T*)instance)->OnDestroy(); };
		//OnUpdateFunction = [](ScriptableEntity* instance, float fElapsedTime) {((T*)instance)->OnUpdate(fElapsedTime); };
	}


};
*/