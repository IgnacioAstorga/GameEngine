#ifndef __Entity_H__
#define __Entity_H__

/// Includes
#include <list>
#include "IUpdatable.h"

/// Dpendencies
class Scene;

/*
 * Interface for parentable objects. An object may have
 * many children, but only one parent.
 */
class Entity : public IUpdatable, public IEnableable {

/// Constructors
public:
	Entity(Scene* scene = nullptr);
	Entity(Entity& parent);
	virtual ~Entity();

/// Public methods
public:
	// Destroys the entity
	void Destroy();

	// Called only once at the begninng of the first frame this entity is enabled
	void Start();

	/// --- Setters ---
	// Sets this object's parent
	void SetParent(Entity* newParent);

	// Adds an object to this object's children
	void AddChild(Entity& child);

	// Removes an object from this object's children
	void RemoveChild(Entity& child);

	/// --- Getters ---
	// Returns the parent of this object
	Entity* GetParent() const;

	// Returns the list of children of this object
	std::list<Entity*> GetChildren() const;

	// Returns the scene associated with this entity
	Scene* GetScene() const;

/// Attributes
private:
	// The parent of this object
	Entity* parent;

	// The scene this entity belongs to
	Scene* scene;

	// The list of children of this object
	std::list<Entity*> children;

	// If the entity has already been started
	bool started = false;

/// --- IUpdatable methods ---
public:
	void Update() override;
	void FixedUpdate() override;
	void LateUpdate() override;
	void Render() const override;
	void PostRender() override;

/// --- IEnableable methods ---
public:
	virtual void OnEnable() override;
	virtual void OnDisable() override;
};

#endif