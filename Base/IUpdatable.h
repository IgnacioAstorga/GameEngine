#ifndef __IUpdatable_H__
#define __IUpdatable_H__

/// Includes
#include "IEnableable.h"

/*
 * Interface for objects which will be updated with the
 * game loop ticks.
 */
class IUpdatable {

/// Default constructors
public:
	IUpdatable() {};
	virtual ~IUpdatable() {};

/// Update methods
public:
	/// -------> Start
	virtual void Update() = 0;
	virtual void FixedUpdate() = 0;	// Performed even if the object is disabled
	/// -------> Animation
	/// -------> Physics
	virtual void LateUpdate() = 0;
	/// -------> State lock
	virtual void Render() const = 0;
	/// -------> Actual render
	virtual void PostRender() = 0;
	/// -------> Entity destruction
	/// -------> Scene transition

/// Attributes
private:
	bool started = false;
};

#endif