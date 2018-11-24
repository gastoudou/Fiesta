/* GLM Studio @ copyright 2018 */

#pragma once

class StateMachine;
class Renderer;
class EventManager;
class Texture;

class GameStateManager
{
public:
	GameStateManager();
	~GameStateManager();

	void Update();
	bool Quit() const;

	bool IsPaused() const;

	StateMachine* stateMachine;
private:
	bool quit = false;
	bool pause = false;

	float deltaTime = EventManager::FIXED_TIME_STAMP;

	Renderer* renderer = nullptr;
	EventManager* eventer = nullptr;
};