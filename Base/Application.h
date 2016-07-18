#ifndef __Application_H__
#define __Application_H__

/// Dependencies
class GameLoopModule;
class SceneModule;
class Scene;

/*
 * Class which provides an entry point to the engine.
 * Define all the abstract methods and run the application.
 */
class Application {

/// Constructors
public:
	Application();
	virtual ~Application();

/// Public methods
public:
	// Runs the application, starting the engine and, therefore, the game.
	void Run();

/// Private methods
private:
	// Creates all the game modules
	void CreateModules();

	// Runs the initialization routines, starting the engine.
	void Init();

	// Further module starting routines, performed once all modules have been initialized.
	void Start();

	// Selects the starting scene
	void SelectScene();

	// Starts the game.
	void Play();

	// Stops the game.
	void Finish();

	// Runs the cleanance routines, stoping the engine.
	void Clean();

/// Delegated methods
protected:
	/// --- Entry points ---
	// Entry point for user code before the application is initialized.
	virtual void OnInit() = 0;

	// Entry point for user code before the application starts playing.
	virtual void OnPlay() = 0;

	/// --- Module initialization ---
	// Selects the game loop module used on the engine.
	virtual GameLoopModule* OnSelectGameLoopModule() = 0;

	// Selects the scene module used on the engine.
	virtual SceneModule* OnSelectGameSceneModule() = 0;

	/// --- Game initialization ---
	// Selects the scene the application will start with.
	virtual Scene* OnSelectScene() const = 0;

	/// Static methods
public:
	// Returns the game loop module.
	static GameLoopModule& GetGameLoopModule();

	// Returns the scene module.
	static SceneModule& GetSceneModule();

/// Attributes
private:
	/// --- Modules ---
	// The game loop module.
	static GameLoopModule* gameLoop;

	// The scene module.
	static SceneModule* scene;
};

#endif