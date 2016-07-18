#include "SceneModule.h"

#include "Globals.h"
#include "Scene.h"

SceneModule::SceneModule() {
	// Do nothing
}

SceneModule::~SceneModule() {
	// Destroys the current scene and the next one (if setted)
	if (nextScene != nullptr && nextScene != currentScene)
		RELEASE(nextScene);
	RELEASE(currentScene);
}

void SceneModule::ChangeScene(Scene& newScene) {
	// Destroys the previous next scene (if setted)
	if (nextScene != nullptr && nextScene != currentScene)
		RELEASE(nextScene);

	// Sets the next scene
	nextScene = &newScene;
}

Scene& SceneModule::GetCurrentScene() const {
	return *currentScene;
}

void SceneModule::Destroy(Entity& entity) {
	// Marks the entity to be destroyed
	toDestroy.push_back(&entity);
}

void SceneModule::DoChangeScene() {
	// Performes the actual change of scene (if setted)
	if (nextScene != nullptr && nextScene != currentScene) {
		RELEASE(currentScene);
		currentScene = nextScene;
		nextScene = nullptr;
	}
}

void SceneModule::DoDestroy() {
	// Destroys all the entities marked for it
	for each (Entity* entity in toDestroy) {
		RELEASE(entity);
	}
	toDestroy.clear();
}

void SceneModule::Init() {
	// Do nothing
}

void SceneModule::Start() {
	// Do nothing
}

void SceneModule::Clean() {
	// Do nothing
}

void SceneModule::OnCreate() {
	// Do nothing
}

void SceneModule::OnDestroy() {
	// Do nothing
}

void SceneModule::Update() {
	// Updates the scene
	currentScene->Update();
}

void SceneModule::FixedUpdate() {
	// Updates the scene, even if disabled
	currentScene->FixedUpdate();
}

void SceneModule::LateUpdate() {
	// Updates the scene before rendering
	currentScene->LateUpdate();
}

void SceneModule::Render() const {
	// Renders the scene
	currentScene->Render();
}

void SceneModule::PostRender() {
	// Updates the scene before the frame's end
	currentScene->PostRender();

	// Destroys the marked entities
	DoDestroy();

	// Performs the scene change
	DoChangeScene();
}
