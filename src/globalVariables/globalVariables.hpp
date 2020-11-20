#include <iostream>
#include <string>
#include <vector>
#include "../gameItem/gameItem.hpp"

using namespace std;

#ifndef SRC_GLOBALVARIABLES_GLOBALVARIABLES_HPP_
#define SRC_GLOBALVARIABLES_GLOBALVARIABLES_HPP_

class GlobalVariables {
 public:
    static string MESA_DRIVERPath();

    static string AMDVLK_DRIVERPath();

    static string commandEnd();

    static vector<GameItem::GameSetting> itemsList;

    static vector<string> gameBList;
};

#endif  // SRC_GLOBALVARIABLES_GLOBALVARIABLES_HPP_
