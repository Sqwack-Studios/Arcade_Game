//=================================================================================
// Namespace		: Arcade_Game
// Name				: FileCommandLoader.h
// Author			: Daniel Crespo Muñoz
// Version			:
// Copyright		:
// Description		:
// Creation time	: 22/09/2022 14:22:41
//=================================================================================

#ifndef _Arcade_Game_FileCommandLoader_H_
#define _Arcade_Game_FileCommandLoader_H_

#pragma once
#include <functional>
#include <vector>
#include <string>
#include <stdint.h>

class Color;
class Vec2D;

enum CommandType
{
	COMMAND_ONE_LINE = 0,
	COMMAND_MULTI_LINE
};

struct ParseFuncParams
{
	std::string line;
	size_t delimitPos;
	uint32_t LineNum;
};
using ParseFunc = std::function<void(const ParseFuncParams& params)>;

struct Command
{
	CommandType commandType {COMMAND_ONE_LINE};
	std::string command{ "" };
	ParseFunc parseFunc{ nullptr };
};

class FileCommandLoader
{
private:
	std::vector<Command> mCommands;
protected:

public:
	void AddCommand(const Command& command);
	void LoadFile(const std::string& filePath);

	static Color ReadColor(const ParseFuncParams& params);
	static Vec2D ReadSize(const ParseFuncParams& params);
	static int ReadInt(const ParseFuncParams& params);
	static std::string ReadString(const ParseFuncParams& params);
	static char ReadChar(const ParseFuncParams& params);


};
#endif // !_Arcade_Game_FileCommandLoader_H_

