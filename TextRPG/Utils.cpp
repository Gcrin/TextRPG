#include "Utils.h"
#include <random>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

int Utils::getRandomInt(int min, int max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

void Utils::setConsoleColor(EColor color)
{
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<std::uint8_t>(color));
#endif
}

void Utils::drawMonsterArt(const std::string& name)
{
    if (name == "Goblin")
    {
        std::cout << R"(
            /(.-""-.)\
        |\  \/      \/  /|
        | \ / =.  .= \ / |
        \( \   o\/o   / )/
         \_, '-/  \-' ,_/
           /   \__/   \
           \ \__/\__/ /
         ___\ \|--|/ /___
       /`    \      /    `\
      /       '----'       \
        Goblin
)";
    }
    else if (name == "Slime") {
        std::cout << R"(
       ______
     /        \
    |  o    o  |
    |    กิ     |
     \_________/
        Slime
)";
    }
    else if (name == "Orc") {
        std::cout << R"(
       /---.__   
     /       `\  
    | o     o  \ 
  ./| .vvvvv.  |\
 / /| |     |  | \
//' | `^vvvv'  |/\\
    \          |  \\
    |          |    
     7        /
    /    .    |
      Orc
)";
    }
    else if (name == "Skeleton") {
        std::cout << R"(
        .-.
       (o.o)
        |=|
       __|__
     //.=|=.\\
    // .=|=. \\
    \\ .=|=. //
     \\(_=_)//
      (:| |:)
       || ||
       () ()
       || ||
       || ||
      ==' '==
      Skeleton
)";
    }
    else if (name == "Dragon") {
        std::cout << R"(
                ^    ^
               / \  //\
 |\___/|      /   \//  .\
 /O  O  \__  /    //  | \ \
/     /  \/_/    //   |  \  \
@___@'    \/_   //    |   \   \
   |       \/_ //     |    \    \
   |        \///      |     \     \
  _|_ /   )  //       |      \     _\
 '/,_ _ _/  ( ; -.    |    _ _\.-~        .-~~~^-.
 ,-{        _      `-.|.-~-.           .~         `.
  '/\      /                 ~-. _ .-~      .-~^-.  \
     `.   {            }                   /      \  \
   .----~-.\        \-'                 .~         \  `. \^-.
  ///.----..&gt;    c   \             _ -~             `.  ^-`   ^-_
    ///-._ _ _ _ _ _ _}^ - - - - ~                     ~--,   .-~
     Dragon
)";

    }
}