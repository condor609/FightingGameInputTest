#ifndef FG_INPUT_H
#define FG_INPUT_H
#include <string>
#include <vector>
#include <iostream>
#include "SDLInput.h"

#define CMD_MAX_AGE 0.5f
#define MEMORY_TIME 1.0f
#define UP SDLK_w
#define LEFT SDLK_a
#define RIGHT SDLK_d
#define DOWN SDLK_s
#define LIGHT SDLK_LEFT
#define MEDIUM SDLK_UP
#define HEAVY SDLK_RIGHT
#define ABILITY SDLK_DOWN

enum FG_State
{
	STATE_STAND, STATE_JUMP, STATE_CROUCH, 
	STATE_BLOCK, STATE_STUN, STATE_DOWN
};

enum FG_Command
{
	CMD_UP, CMD_DOWN, CMD_BACK, CMD_FORWARD,
	CMD_LIGHT, CMD_MEDIUM, CMD_HEAVY, CMD_ABILITY,
	CMD_LM, CMD_MH, CMD_LH, CMD_LMH, CMD_LMHA, CMD_JUMP
};

enum ActionFlag_Type
{
	AF_TYPE_NORMAL, AF_TYPE_SPECIAL, AF_TYPE_SUPER, AF_TYPE_IK
};

enum ActionFlag_Cancel
{
	AF_CANCEL_DASH, AF_CANCEL_JUMP, AF_CANCEL_SPECIAL, AF_CANCEL_SUPER, AF_CANCEL_IK
};

enum ActionFlag_Properties
{
	AF_PROP_LOW, AF_PROP_HIGH, AF_PROPERTY_UNBLOCKABLE, 
	AF_PROPERTY_THROW, AF_PROPERTY_AIRTHROW, AF_PROPERTY_OTG
};

enum ActionFlag_OnHit
{
	AF_ONHIT_WALLBOUNE, AF_ONHIT_WALLSTICK, AF_ONHIT_GROUNDBOUNCE
};

struct FG_InputCommand
{
	FG_InputCommand(FG_Command _input, float _time) : input(_input), time(_time) {}
	FG_Command input;
	float time;
};

struct FG_Action
{
	FG_Action(std::string _name, FG_State _state, std::vector<FG_Command> _command) : name(_name), state(_state), command(_command) {}
	std::string name;
	
	FG_State state;
	void execute() {}//fuction that is called when the action is to be executed
	std::vector<FG_Command> command;
};

class FG_Inputs
{
private:
	std::vector<FG_InputCommand> commands;
	std::vector<FG_Action> actions;
	int index;
	bool grounded;

public:
	void DefaultInit();
	void BestActionMatch();
	void ProcessInput(float _dt);
	std::string BestMatchAsString();
	std::string GetCommandString();
	bool IsGrounded() { return grounded; }
	void SetGrounded(bool _state) { grounded = _state; }
	std::string GetActionString();

	std::string CommandToString(FG_Command _input);
	void AddCommand(FG_Command _command);
	void AddCommand(FG_Command _command, float _time);
	void AddAction(FG_Action _action);
	void AddAction(std::string _name, FG_State _state, std::vector<FG_Command> _command);
	void AddActions(std::vector<FG_Action> _actions);
};
#endif