#include "FG_Input.h"

void FG_Inputs::DefaultInit()
{
	actions.push_back(FG_Action("5L", STATE_STAND, std::vector<FG_Command>({ CMD_LIGHT })));
	actions.push_back(FG_Action("6L", STATE_STAND, std::vector<FG_Command>({ CMD_FORWARD, CMD_LIGHT })));
	actions.push_back(FG_Action("2A", STATE_CROUCH, std::vector<FG_Command>({ CMD_LIGHT })));
	actions.push_back(FG_Action("jA", STATE_JUMP, std::vector<FG_Command>({ CMD_LIGHT })));
	actions.push_back(FG_Action("5M", STATE_STAND, std::vector<FG_Command>({ CMD_MEDIUM })));
	actions.push_back(FG_Action("6M", STATE_STAND, std::vector<FG_Command>({ CMD_FORWARD, CMD_MEDIUM })));
	actions.push_back(FG_Action("2M", STATE_CROUCH, std::vector<FG_Command>({ CMD_MEDIUM })));
	actions.push_back(FG_Action("jM", STATE_JUMP, std::vector<FG_Command>({ CMD_MEDIUM })));
	actions.push_back(FG_Action("5H", STATE_STAND, std::vector<FG_Command>({ CMD_HEAVY })));
	actions.push_back(FG_Action("6H", STATE_STAND, std::vector<FG_Command>({ CMD_FORWARD, CMD_HEAVY })));
	actions.push_back(FG_Action("2H", STATE_CROUCH, std::vector<FG_Command>({ CMD_HEAVY })));
	actions.push_back(FG_Action("jH", STATE_JUMP, std::vector<FG_Command>({ CMD_HEAVY })));
	actions.push_back(FG_Action("5A", STATE_STAND, std::vector<FG_Command>({ CMD_ABILITY })));
	actions.push_back(FG_Action("jA", STATE_JUMP, std::vector<FG_Command>({ CMD_ABILITY })));
	index = -1;
	grounded = true;
}

void FG_Inputs::AddAction(FG_Action _action)
{
	actions.push_back(_action);
}

void FG_Inputs::AddActions(std::vector<FG_Action> _actions)
{
	for (size_t i = 0; i < _actions.size(); i++)
	{
		AddAction(_actions.at(i));
	}
}

void FG_Inputs::AddAction(std::string _name, FG_State _state, std::vector<FG_Command> _command)
{
	AddAction(FG_Action(_name, _state, _command));
}

void FG_Inputs::BestActionMatch()
{
	for (int ai = 0; ai < actions.size(); ai++)//ai = action index
	{
		int ci = commands.size() - 1; //ci = command index
		int matchCount = 0;
		for (int ii = actions.at(ai).command.size() - 1; ii >= 0; ii--) //ii = input index
		{
			while (ci >= 0)
			{
				if (actions.at(ai).command.at(ii) == commands.at(ci).input)
				{
					matchCount++;
					break;
				}
				ci--;
			}
		}

		if (matchCount == actions.at(ai).command.size())
		{
			matchCount = ai;
			actions.at(ai).execute();
			commands.clear();
			break;
		}
	}
}

void FG_Inputs::ProcessInput(float _dt)
{
	for (int i = 0; i < commands.size(); i++)
	{
		commands.at(i).time += _dt;
		if (commands.at(i).time >= CMD_MAX_AGE)
		{
			commands.erase(commands.begin() + i);
			i--;
		}
	}

	if (SDLInput::GetKey(UP))
		AddCommand(CMD_UP);
	else if (SDLInput::GetKey(DOWN))
		AddCommand(CMD_DOWN);
	if (SDLInput::GetKey(LEFT))
		AddCommand(CMD_BACK);
	else if (SDLInput::GetKey(RIGHT))
		AddCommand(CMD_FORWARD);

	if (SDLInput::GetKey(LIGHT))
	{
		if (SDLInput::GetKey(MEDIUM) || SDLInput::GetKey(HEAVY))
		{
			if (SDLInput::GetKey(MEDIUM))
			{
				if (SDLInput::GetKey(HEAVY))
				{
					if (SDLInput::GetKey(ABILITY))
						AddCommand(CMD_LMHA);
					else
						AddCommand(CMD_LMH);
				}
				else
					AddCommand(CMD_LM);
			}
			else
				AddCommand(CMD_LH);
		}
		else
			AddCommand(CMD_LIGHT);
	}
	else if (SDLInput::GetKey(MEDIUM))
	{
		if (SDLInput::GetKey(HEAVY))
			AddCommand(CMD_MH);
		else
			AddCommand(CMD_MEDIUM);
	}
	else if (SDLInput::GetKey(HEAVY))
		AddCommand(CMD_HEAVY);
	else if (SDLInput::GetKey(ABILITY))
		AddCommand(CMD_ABILITY);

	BestActionMatch();
}

std::string FG_Inputs::BestMatchAsString()
{
	return (index == -1 ? "NO MATCH" : actions.at(index).name);
}

std::string FG_Inputs::GetCommandString()
{
	std::string commandString;
	for (int i = 0; i < commands.size(); i++)
	{
		if (i > 0) commandString += " ";
		commandString += CommandToString(commands.at(i).input);
	}
	return commandString;
}

std::string FG_Inputs::GetActionString()
{
	std::string actionString;
	for (FG_Action action : actions)
	{
		actionString += action.name + " <" + std::to_string(action.state) + ">(";
		for (int i = 0; i < action.command.size(); i++)
		{
			if (i > 0) actionString += ",";
			actionString += CommandToString(action.command.at(i));
		}
		actionString += ")\n";
	}
	return actionString;
}

std::string FG_Inputs::CommandToString(FG_Command _input)
{
	switch (_input)
	{
	case CMD_UP:		return "8";
	case CMD_DOWN:		return "2";
	case CMD_BACK:		return "4";
	case CMD_FORWARD:		return "6";
	case CMD_LIGHT:		return "L";
	case CMD_MEDIUM:	return "M";
	case CMD_HEAVY:		return "H";
	case CMD_ABILITY:	return "A";
	case CMD_LM:		return "L+M";
	case CMD_MH:		return "M+H";
	case CMD_LH:		return "L+H";
	case CMD_LMH:		return "L+M+H";
	case CMD_LMHA:		return "L+M+H+A";
	}
	return "";
}

void FG_Inputs::AddCommand(FG_Command _command)
{
	commands.push_back(FG_InputCommand(_command, 0.1f));
}

void FG_Inputs::AddCommand(FG_Command _command, float _time)
{
	commands.push_back(FG_InputCommand(_command, _time));
}