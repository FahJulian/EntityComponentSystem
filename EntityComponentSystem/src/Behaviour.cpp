#include "Behaviour.h"
#include "Entity.h"

namespace Sonic{
	
	Entity* Behaviour::GetEntity()
	{
		static Entity entity = { m_Scene, m_Entity };
		return &entity;
	}

}
