#include "globalVariables.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "../gameItem/gameItem.hpp"

using namespace std;

string GlobalVariables::MESA_DRIVERPath() {
    return "VK_ICD_FILENAMES=/usr/share/vulkan/icd.d/radeon_icd.i686.json:/usr/share/vulkan/icd.d/"
           "radeon_icd.x86_64.json";
}

string GlobalVariables::AMDVLK_DRIVERPath() {
    return "VK_ICD_FILENAMES=/usr/share/vulkan/icd.d/amd_icd32.json:/usr/share/vulkan/icd.d/"
           "amd_icd64.json";
}

string GlobalVariables::commandEnd() { return "%command%"; }

vector<GameItem::GameSetting> GlobalVariables::itemsList = {
  {GameItem::GameSetting("Esync", {{"Esync", "PROTON_NO_ESYNC=1"}})},
  {GameItem::GameSetting("Fsync", {{"Fsync", "PROTON_NO_FSYNC=1"}})},
  {GameItem::GameSetting("MangoHud", {{"MangoHud", "mangohud"}})},
  {GameItem::GameSetting("Gamemode", {{"Gamemode", "gamemoderun"}})},
  {
    GameItem::GameSetting(
      "AMD Driver",
      {{"Mesa", "export " + MESA_DRIVERPath()}, {"AMDVLK", "export " + AMDVLK_DRIVERPath()}},
      ItemType::multiple),
  },
  {GameItem::GameSetting("Nvidia Prime", {{"Nvidia Prime", "prime-run"}})},
  {GameItem::GameSetting("WineDebug", {{"WineDebug", "winedebug=-all"}})},
  {GameItem::GameSetting("Proton Log", {{"Log", "PROTON_LOG=1"}})},
};

vector<string> GlobalVariables::gameBList = {
  "Proton",
  "Steam",
};
