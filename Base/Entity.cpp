#include "Entity.h"

#include "Globals.h"
#include "Application.h"
#include "SceneModule.h"
#include "Scene.h"

Entity::Entity(Scene* scene) {
	// If no scene is specified, the current one is used
	if (scene == nullptr)
		this->scene = &Application::GetSceneModule().GetCurrentScene();
	else
		this->scene = scene;
	parent = nullptr;

	// Adds itself to the scene
	scene->AddEntity(*this);
}

Entity::Entity(Entity& parent) {
	this->parent = &parent;
	scene = parent.scene;
	scene->AddEntity(*this);
}

Entity::~Entity() {
	// Destroys this object's children
	for each (Entity* child in children)
		RELEASE(child);
	children.clear();

	// Unparents itself from it's parent
	if (parent != nullptr)
		parent->RemoveChild(*this);

	// Removes itself from the scene
	scene->RemoveEntity(*this);
	scene = nullptr;
}

void Entity::Destroy() {
	// Flags this entity to be destroyed at the end of the frame
	Application::GetSceneModule().Destroy(*this);
}

void Entity::Start() {
	if (started || !IsEnabled())
		return;

	// Starts the entity
	started = true;
	// TODO
}

void Entity::SetParent(Entity* newParent) {
	// Removes the child from the parent's list
	if (parent != nullptr)
		parent->children.remove(this);

	// Sets the entity's new parent and scene (to the parent's one)
	parent = newParent;

	// Adds the child to the new parent's list
	if (newParent != nullptr)
		newParent->children.push_back(this);
}

void Entity::AddChild(Entity& child) {
	// Sets the child's parent to this object
	child.SetParent(this);
}

void Entity::RemoveChild(Entity& child) {
	// Removes the child's parent
	child.SetParent(nullptr);
}

Entity* Entity::GetParent() const {
	return parent;
}

std::list<Entity*> Entity::GetChildren() const {
	return children;
}

Scene* Entity::GetScene() const {
	return scene;
}

void Entity::Update() {
	// TODO
}

void Entity::FixedUpdate() {
	// TODO
}

void Entity::LateUpdate() {
	// TODO
}

void Entity::Render() const {
	// TODO
}

void Entity::PostRender() {
	// TODO
}

void Entity::OnEnable() {
	// Do nothing
}

void Entity::OnDisable() {
	// Do nothing
}
