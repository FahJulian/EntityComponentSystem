#pragma once
#include "EntityID.h"
#include "ComponentPool.h"
#include "ComponentView.h"
#include "BehaviourPool.h"

namespace Sonic {

	class Entity;

	class Scene
	{
	public:
		Entity AddEntity();

		void RemoveEntity(EntityID entity);

		void Update(float deltaTime);

		template<typename Component, typename... Args>
		void AddComponent(EntityID entity, Args&&... args)
		{
			GetComponentPool<Component>()->AddComponent(entity, std::forward<Args>(args)...);
		}

		template<typename DerivedBehaviour, typename... Args>
		void AddBehaviour(EntityID entity, Args&&... args)
		{
			GetBehaviourPool<DerivedBehaviour>()->AddBehaviour(entity, std::forward<Args>(args)...);
		}

		template<typename Component>
		bool HasComponent(EntityID entity)
		{
			return GetComponentPool<Component>()->HasComponent(entity);
		}

		template<typename Component>
		Component* GetComponent(EntityID entity)
		{
			return GetComponentPool<Component>()->GetComponent(entity);
		}

		template<typename Component>
		void RemoveComponent(EntityID entity)
		{
			GetComponentPool<Component>()->RemoveEntity(entity);
		}

		template<typename DerivedBehaviour>
		void RemoveBehaviour(EntityID entity)
		{
			GetBehaviourPool<DerivedBehaviour>()->RemoveEntity(entity);
		}

		template<typename Component>
		ComponentView<Component> View()
		{
			return ComponentView<Component>(GetComponentPool<Component>());
		}

	private:
		template<typename Component>
		ComponentPool<Component>* GetComponentPool()
		{
			static ComponentPool<Component>* pool = CreateComponentPool<Component>();
			return pool;
		}

		template<typename DerivedBehaviour>
		BehaviourPool<DerivedBehaviour>* GetBehaviourPool()
		{
			static BehaviourPool<DerivedBehaviour>* pool = CreateBehaviourPool<DerivedBehaviour>();
			return pool;
		}

		template<typename Component>
		ComponentPool<Component>* CreateComponentPool()
		{
			static ComponentPool<Component> pool;
			m_ComponentPools.push_back(static_cast<BaseComponentPool*>(&pool));
			return &pool;
		}

		template<typename DerivedBehaviour>
		BehaviourPool<DerivedBehaviour>* CreateBehaviourPool()
		{
			static BehaviourPool<DerivedBehaviour> pool(this);
			m_BehaviourPools.push_back(static_cast<BaseBehaviourPool*>(&pool));
			return &pool;
		}

		std::vector<BaseComponentPool*> m_ComponentPools;
		std::vector<BaseBehaviourPool*> m_BehaviourPools;

		friend class Entity;
	};
	
}
