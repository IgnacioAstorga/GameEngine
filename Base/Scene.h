#ifndef __Scene_H__
#define __Scene_H__

/// Includes
#include <list>
#include "IUpdatable.h"

/// Dependencies
class Entity;

class Scene : public IUpdatable {

/// Constructors
public:
	Scene();
	virtual ~Scene();

/// Public methods
public:
	// Adds an entity to the scene
	void AddEntity(Entity& entity);

	// Removes an entity from the scene
	void RemoveEntity(Entity& entity);

/// Attributes
private:
	std::list<Entity*> entities;

/// --- IUpdatable methods ---
public:
	void Update() override;
	void FixedUpdate() override;
	void LateUpdate() override;
	void Render() const override;
	void PostRender() override;
};

#endif