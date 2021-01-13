#pragma once
#include "Scene.h"
#include "Entity.h"

namespace Sonic {

	Entity Scene::AddEntity()
	{
		return Entity(this);
	}

	void Scene::RemoveEntity(EntityID entity)
	{
		for (BaseBehaviourPool* pool : m_BehaviourPools)
			if (pool->HasEntity(entity))
				pool->RemoveEntity(entity);

		for (BaseComponentPool* pool : m_ComponentPools)
			if (pool->HasEntity(entity))
				pool->RemoveEntity(entity);
	}

	void Scene::Update(float deltaTime)
	{
		for (BaseComponentPool* pool : m_ComponentPools)
			pool->OnUpdate();

		for (BaseBehaviourPool* pool : m_BehaviourPools)
			pool->OnUpdate(deltaTime);
	}

}
