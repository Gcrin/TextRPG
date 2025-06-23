#ifdef _WIN32

#include <iostream>

#include "ui_utils.h"
#include <windows.h>

#endif

void setConsoleColor(int color) 
{
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
#endif
}

void clearConsole() 
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void drawMonsterArt(const std::string& name) 
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
    |    ∇     |
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