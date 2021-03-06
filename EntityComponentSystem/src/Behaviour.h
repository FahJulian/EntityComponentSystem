#pragma once
#include "EntityID.h"

namespace Sonic {

	class Scene;
	class Entity;

	class Behaviour
	{
	protected:
		virtual void OnInit() {}

		virtual void OnUpdate(float deltaTime) {}

		virtual void OnDestroy() {}

		Scene* GetScene() { return m_Scene; }

		Entity* GetEntity();

		EntityID m_Entity;
		Scene* m_Scene;

		friend class Scene;
		friend class BaseBehaviourPool;
	};

}
