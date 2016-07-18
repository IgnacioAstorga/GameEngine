#include "GameLoopModule.h"

#include "RuntimeStatus.h"

GameLoopModule::GameLoopModule() {
	// Do nothing
}

GameLoopModule::~GameLoopModule() {
	// Do nothing
}

RuntimeStatus GameLoopModule::Run() {
	// Sets the halt flag to false
	haltFlag = false;

	// Starts the game loop
	RuntimeStatus status;
	do {
		status = GameLoop();
	} while (status == CONTINUE);

	return status;
}

void GameLoopModule::Halt() {
	// Sets the halt flag so the loop will stop when the current iteration ends
	haltFlag = true;
}

RuntimeStatus GameLoopModule::GameLoop() {
	// Performs the game update
	try {
		GameUpdate();
	}
	catch (...) {
		return ERROR;
	}

	// Checks the halt flag
	if (haltFlag)
		return FINISH;

	// Waits until the next update should be performed
	while (!CheckNextUpdate());

	// Keeps looping
	return CONTINUE;
}

void GameLoopModule::Init() {
	// Do nothing
}

void GameLoopModule::Clean() {
	// Do nothing
}

void GameLoopModule::OnCreate() {
	// Do nothing
}

void GameLoopModule::OnDestroy() {
	// Do nothing
}
