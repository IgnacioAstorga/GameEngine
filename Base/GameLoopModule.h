#ifndef __GameLoopModule_H__
#define __GameLoopModule_H__

/// Includes
#include "IModule.h"

/// Depenencies
enum RuntimeStatus;

/*
* Class which provides an entry point to the engine.
* Define all the abstract methods and run the application.
*/
class GameLoopModule : public IModule {

/// Constructors
public:
	GameLoopModule();
	virtual ~GameLoopModule();

/// Public methods
public:
	// Starts the game loop.
	RuntimeStatus Run();

	// Halts the loop, stoping the game
	void Halt();

	// Loops, performing game updates.
	RuntimeStatus GameLoop();

/// Delegated methods
protected:
	// Performs a game update.
	virtual RuntimeStatus GameUpdate() = 0;

	// Checks if the next update should be performed.
	virtual bool CheckNextUpdate() = 0;

/// Attributes
private:
	bool haltFlag = false;

/// --- IModule methods ---
public: 
	void Init() override;
	void Clean() override;

private:
	virtual void OnCreate() override;
	virtual void OnDestroy() override;
};

#endif