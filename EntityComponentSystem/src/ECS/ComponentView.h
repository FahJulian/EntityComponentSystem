#pragma once
#include "ComponentPool.h"
#include "EntityID.h"

namespace Sonic {

	template<typename Component>
	class ComponentView
	{
	private:
		ComponentView(ComponentPool<Component>* pool)
			: pool(pool) {}
	public:
		std::vector<EntityID>::const_iterator begin() { return pool->m_Entities.cbegin(); }
		std::vector<EntityID>::const_iterator end() { return pool->m_Entities.cend(); }

		Component* GetComponent(EntityID entity) { return pool->GetComponent(entity); }
	private:
		ComponentPool<Component>* pool;

		friend class Scene;
	};

}
