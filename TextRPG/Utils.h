#pragma once

#include <string>


enum class EColor : std::uint8_t
{
	Default = 7,
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Yellow = 6,
	White = 7,
	Gray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	LightYellow = 14
};

namespace Utils
{
    int getRandomInt(int min, int max);
	void setConsoleColor(EColor color);
	void drawMonsterArt(const std::string& name);
}
