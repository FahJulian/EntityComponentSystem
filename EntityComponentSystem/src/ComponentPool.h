#pragma once
#include <set>
#include <unordered_map>
#include <vector>
#include <functional>
#include "EntityID.h"

namespace Sonic {

	class BaseComponentPool
	{
	protected:
		virtual void OnUpdate() = 0;

		bool HasEntity(EntityID entity);

		void RemoveEntity(EntityID entity);

		int IndexOf(EntityID entity);

		std::vector<EntityID> m_Entities;
		std::set<int, std::greater<int>> m_ToRemove;

		friend class Scene;
	};

	template<typename Component>
	class ComponentPool : public BaseComponentPool
	{
		template<typename... Args>
		void AddComponent(EntityID entity, Args&&... args)
		{
			m_ToAdd.emplace(entity, Component(std::forward<Args>(args)...));
		}

		Component* GetComponent(EntityID entity)
		{
			return &m_Components.at(IndexOf(entity));
		}

		void OnUpdate() override
		{
			for (int index : m_ToRemove)
			{
				m_Entities.erase(m_Entities.begin() + index);
				m_Components.erase(m_Components.begin() + index);
			}

			for (auto& [entity, component] : m_ToAdd)
			{
				m_Entities.push_back(entity);
				m_Components.push_back(component);
			}

			m_ToRemove.clear();
			m_ToAdd.clear();
		}

		std::vector<Component> m_Components;
		std::unordered_map<EntityID, Component> m_ToAdd;

		friend class Scene;
		template<typename> friend class ComponentView;
	};

}
