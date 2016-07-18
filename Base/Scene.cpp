#include "Scene.h"

#include "Globals.h"
#include "Entity.h"

Scene::Scene() {
	// Do nothing
}

Scene::~Scene() {
	// Destroys the entities placed on the scene
	for each (Entity* entity in entities)
		RELEASE(entity);
	entities.clear();
}

void Scene::AddEntity(Entity& entity) {
	if (!CONTAINS(entities, &entity))
		entities.push_back(&entity);
}

void Scene::RemoveEntity(Entity & entity) {
	entities.remove(&entity);
}

void Scene::Update() {
	// Trys to start each entity
	for each (Entity* entity in entities)
		entity->Start();

	// Updates the entities, if enabled
	for each (Entity* entity in entities)
		if (entity->IsEnabled())
			entity->Update();
}

void Scene::FixedUpdate() {
	// Updates the entities, even if disabled
	for each (Entity* entity in entities)
		entity->Update();
}

void Scene::LateUpdate() {
	// Performs a last update before rendering
	for each (Entity* entity in entities)
		if (entity->IsEnabled())
			entity->LateUpdate();
}

void Scene::Render() const {
	// Renders the entities
	for each (Entity* entity in entities)
		if (entity->IsEnabled())
			entity->Render();
}

void Scene::PostRender() {
	// Performs the remaining operations after rendering
	for each (Entity* entity in entities)
		if (entity->IsEnabled())
			entity->PostRender();
}
