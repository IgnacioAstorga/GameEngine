#ifndef __SceneModule_H__
#define __SceneModule_H__

/// Includes
#include <list>
#include "IUpdatable.h"
#include "IModule.h"

/// Dependencies
class Scene;
class Entity;

/*
 * Module which manages the current scene of the game
 * and the transition between scenes.
 */
class SceneModule : public IModule, public IUpdatable {

	/// Friends
	friend class Application;

/// Constructors
public:
	SceneModule();
	virtual ~SceneModule();

/// Public methods
public:
	// Changes the current scene to a new one. The change will be done at the end of the frame.
	void ChangeScene(Scene& newScene);

	// Returns the current scene of the game.
	Scene& GetCurrentScene() const;

	// Destroys an entity at the end of the frame.
	void Destroy(Entity& entity);

/// Private methods
private:
	// Performs the actual change of scene.
	void DoChangeScene();

	// Destroys the entities marked for it.
	void DoDestroy();

/// Delegated methods
protected:
	/// --- Entry points ---
	// Entry point for user code right before a scene change.
	virtual void OnChangeScene(Scene& previousScene, Scene& nextScene) = 0;

/// Attributes
private:
	// The current scene of the game.
	Scene* currentScene;

	// The scene which will be set at the end of the frame.
	Scene* nextScene;

	// The entities that should be destroyed at the end of the current frame.
	std::list<Entity*> toDestroy;

/// --- IModule methods ---
public:
	void Init() override;
	void Start() override;
	void Clean() override;

private:
	virtual void OnCreate() override;
	virtual void OnDestroy() override;

/// --- IUpdatable methods ---
public:
	void Update() override;
	void FixedUpdate() override;
	void LateUpdate() override;
	void Render() const override;
	void PostRender() override;
};

#endif