#pragma once
#include <set>
#include <vector>
#include <utility>
#include <functional>
#include <unordered_map>
#include "EntityID.h"
#include "Behaviour.h"

namespace Sonic {

	class BaseBehaviourPool
	{
	protected:
		BaseBehaviourPool(Scene* scene)
			: m_Scene(scene) {}

		bool HasEntity(EntityID entity);

		void RemoveEntity(EntityID entity);

		int IndexOf(EntityID entity);

		void OnUpdate(float deltaTime);

		Scene* m_Scene;

		std::vector<EntityID> m_Entities;
		std::set<int, std::greater<int>> m_ToRemove;

		std::vector<Behaviour*> m_Behaviours;
		std::unordered_map<EntityID, Behaviour*> m_ToAdd;

		friend class Scene;
	};

	template<typename DerivedBehaviour> 
	class BehaviourPool : public BaseBehaviourPool
	{
	private:
		BehaviourPool(Scene* scene)
			: BaseBehaviourPool(scene) {}

		template<typename... Args>
		void AddBehaviour(EntityID entity, Args&&... args)
		{
			Behaviour* behaviour = static_cast<Behaviour*>(new DerivedBehaviour(std::forward<Args>(args)...));
			m_ToAdd.emplace(entity, behaviour);
		}

		friend class Scene;
	};
}
