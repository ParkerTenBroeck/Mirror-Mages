#include "NativeScriptingSystem.h"

#include "ECS/components/components.h"

namespace NativeScriptingSystem
{
	void OnUpdate(IScene* scene, float fElapsedTime) {

		scene->m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
			{
				// TODO: Move to Scene::OnScenePlay
				if (!nsc.Instance)
				{
					nsc.Instance = nsc.InstantiateScript(Entity{ entity, scene });
					//nsc.Instance->m_Entity = Entity{ entity, scene };
					nsc.Instance->OnCreate();
				}

				nsc.Instance->OnUpdate(fElapsedTime);
			});
	}
}