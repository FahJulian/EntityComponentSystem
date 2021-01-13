#include "BehaviourPool.h"

namespace Sonic {

	bool BaseBehaviourPool::HasEntity(EntityID entity)
	{
		return IndexOf(entity) != -1;
	}

	void BaseBehaviourPool::RemoveEntity(EntityID entity)
	{
		m_ToRemove.insert(IndexOf(entity));
	}

	int BaseBehaviourPool::IndexOf(EntityID entity)
	{
		static unsigned int index = 0;

		unsigned int iteration = 0;
		while (iteration < m_Entities.size())
		{
			if (index >= m_Entities.size())
				index = 0;

			if (m_Entities.at(index) == entity)
				return index;

			index++;
			iteration++;
		}

		return -1;
	}

	void BaseBehaviourPool::OnUpdate(float deltaTime)
	{
		for (Behaviour* behaviour : m_Behaviours)
			behaviour->OnUpdate(deltaTime);

		for (int index : m_ToRemove)
		{
			m_Entities.erase(m_Entities.begin() + index);
			m_Behaviours.at(index)->OnDestroy();
			m_Behaviours.erase(m_Behaviours.begin() + index);
		}

		for (auto& [entity, behaviour] : m_ToAdd)
		{
			m_Entities.push_back(entity);
			behaviour->m_Scene = m_Scene;
			behaviour->m_Entity = entity;
			behaviour->OnInit();
			m_Behaviours.push_back(behaviour);
		}

		m_ToRemove.clear();
		m_ToAdd.clear();
	}
}
