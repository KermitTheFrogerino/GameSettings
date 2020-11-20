#include <gtkmm-3.0/gtkmm.h>
#include <iostream>
#include <map>
#include <memory>
#include <regex>
#include <string>
#include <vector>
#include "../gameItem/gameItem.hpp"
#include "../vdfParser/vdfParser.hpp"

using namespace std;

#ifndef SRC_FUNC_FUNC_HPP_
#define SRC_FUNC_FUNC_HPP_

class Func {
 public:
    static bool vectorMatch(vector<string> ref, vector<string> comp, bool matchSize = true);

    static vector<string> split(string str, string token);

    static vector<string> split(string split, char splitter);

    static bool stringInList(string ref, vector<string> li, bool lose = false);

    static string getSteamUserID();

    static vector<string> getDrives();

    static GameItem::Game getGame(string path);

    static string readGameOptions(string gameID, string userID);

    static string removeCharRFromString(const string &str, char ch);

    static string replaceCharInString(const string &str, char ch, char replace);

    static string removeCharRFromStart(string str, char ch);
};
#endif  // SRC_FUNC_FUNC_HPP_
