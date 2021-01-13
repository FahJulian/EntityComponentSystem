#pragma once
#include <iostream>
#include "Scene.h"
#include "Entity.h"
#include "Behaviour.h"

struct TestComponent
{

};

class Behaviour1 : public Sonic::Behaviour
{
	void OnInit() override
	{
		std::cout << "Behaviour 1 Initialized" << std::endl;
		GetEntity()->AddComponent<TestComponent>();
	}

	void OnUpdate(float deltaTime) override
	{
		std::cout << "Behaviour 1 Updated" << std::endl;
	}

	void OnDestroy() override
	{
		std::cout << "Behaviour 1 Destroyed" << std::endl;
	}
};

struct Component1
{
	float f;

	Component1()
		: f(0.0f) {}

	Component1(float f)
		: f(f) {}
};

struct Component2
{

};

int main()
{
	Sonic::Scene scene;

	Sonic::Entity e1 = scene.AddEntity();
	Sonic::Entity e2 = scene.AddEntity();
	Sonic::Entity e3 = scene.AddEntity();

	e1.AddComponent<Component1>(-0.1f);
	e1.AddBehaviour<Behaviour1>();
	e2.AddComponent<Component1>(6.4f);
	e3.AddComponent<Component2>();

	scene.Update(0.016f);

	e2.AddBehaviour<Behaviour1>();
	e1.AddComponent<Component1>();

	scene.Update(0.018f);

	e1.RemoveBehaviour<Behaviour1>();
	e3.RemoveComponent<Component2>();

	scene.RemoveEntity(e2);

	scene.Update(0.05f);
}
