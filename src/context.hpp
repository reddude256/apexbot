#pragma once

#include "sdk.hpp"

#include <cstdint>

class GameProcess;
class GameData;
class GameState;

// Controls the game's state of kbutton_t instance.
struct InState {
	// The raw button state.
	kbutton_t button;

	// True if the button is held down.
	bool state;
	// Set to true if the button should be overriden.
	bool force;
	// Force the button to be pressed.
	bool press;
	// Force the button to be released.
	bool release;

	void update(const GameProcess& process, uint32_t address);
	void post(const GameProcess& process, uint32_t address);
};

// The game context groups data together to make it convenient to pass around.
class GameContext {
public:
	GameContext(const GameProcess& process, const GameData& data, const GameState& state);
	void pre();
	void post();

	// Checks if the given entity handle still points to the specified entity address.
	// Use this to reduce the chance of losing the race condition when writing to entity memory.
	bool entity_check(EHandle handle, uint64_t address) const;

public:
	const GameProcess& process;
	const GameData& data;
	const GameState& state;
	double time;

	InState attack;
	InState jump;
};
