#ifndef __IModule_H__
#define __IModule_H__

/// Includes
#include "IEnableable.h"

/*
 * Interface for the application modules. Provides
 * some standard methods that all modules share.
 */
class IModule {

/// Constructors
public:
	IModule() { OnCreate(); };
	virtual ~IModule() { OnDestroy(); };

/// Public methods
public:
	// Called after all modules are created.
	virtual void Init() = 0;

	// Called after all modules are initialized.
	virtual void Start() = 0;

	// Called right before any module is destroyed.
	virtual void Clean() = 0;

/// Private methods
private:
	// Called after being created. Other modules may not have been created yet.
	virtual void OnCreate() = 0;

	// Called when the module is destroyed. Other modules may have been already destroyed.
	virtual void OnDestroy() = 0;
};

#endif