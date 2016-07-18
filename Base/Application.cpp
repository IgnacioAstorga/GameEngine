#include "Application.h"

#include "Globals.h"
#include "GameLoopModule.h"
#include "SceneModule.h"

Application::Application() {
	// Do nothing
}

Application::~Application() {
	// Destroys the modules
	RELEASE(gameLoop);
	RELEASE(scene);
}

void Application::Run() {
	// Creates the game modules
	CreateModules();

	// Initializes the modules
	Init();

	// Selectes the starting scene
	SelectScene();

	// Starts the modules once they are all initialized
	Start();

	// Begins to play
	Play();
}

void Application::CreateModules() {
	// Creates each module
	gameLoop = OnSelectGameLoopModule();
	scene = OnSelectGameSceneModule();
}

void Application::Init() {
	// Initializes the modules
	gameLoop->Init();
	scene->Init();
}

void Application::Start() {
	// Starts the modules
	gameLoop->Start();
	scene->Start();
}

void Application::SelectScene() {
	// Sets the starting scene on the module
	scene->currentScene = OnSelectScene();
}

void Application::Play() {
	// Starts the game loop. The function will not continue as long as the game is running
	RuntimeStatus endStatus = gameLoop->Run();

	// Finishes the application
	Finish();
}

void Application::Finish() {
	// Cleans the modules, exiting the application
	Clean();
}

void Application::Clean() {
	// Cleans the modules
	gameLoop->Clean();
	scene->Clean();
}

GameLoopModule& Application::GetGameLoopModule() {
	return *gameLoop;
}

SceneModule& Application::GetSceneModule() {
	return *scene;
}
