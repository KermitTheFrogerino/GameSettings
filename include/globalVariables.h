#include <iostream>
#include <string>
#include <vector>
#include "gameItem/gameItem.h"

using namespace std;

#ifndef INCLUDE_GLOBALVARIABLES_H_
#define INCLUDE_GLOBALVARIABLES_H_

struct {
    string MESA_DRIVERPath =
      "VK_ICD_FILENAMES=/usr/share/vulkan/icd.d/radeon_icd.i686.json:/usr/share/vulkan/icd.d/"
      "radeon_icd.x86_64.json";

    string AMDVLK_DRIVERPath =
      "VK_ICD_FILENAMES=/usr/share/vulkan/icd.d/amd_icd32.json:/usr/share/vulkan/"
      "icd.d/amd_icd64.json";

    string commandEnd = "%command%";
    vector<GameItem::GameSetting> itemsList = {
      {GameItem::GameSetting("Esync", {{"Esync", "PROTON_NO_ESYNC=1"}})},
      {GameItem::GameSetting("Fsync", {{"Fsync", "PROTON_NO_FSYNC=1"}})},
      {GameItem::GameSetting("MangoHud", {{"MangoHud", "mangohud"}})},
      {GameItem::GameSetting("Gamemode", {{"Gamemode", "gamemoderun"}})},
      {
        GameItem::GameSetting(
          "AMD Driver",
          {{"Mesa", "export " + MESA_DRIVERPath}, {"AMDVLK", "export " + AMDVLK_DRIVERPath}},
          ItemType::multiple),
      },
      {GameItem::GameSetting("Nvidia Prime", {{"Nvidia Prime", "prime-run"}})},
      {GameItem::GameSetting("WineDebug", {{"WineDebug", "winedebug=-all"}})},
      {GameItem::GameSetting("Log", {{"Log", "PROTON_LOG=1"}})},
    };

    vector<string> gameBList = {
      "Proton",
      "Steam",
    };
} GlobalVariables;

#endif  // INCLUDE_GLOBALVARIABLES_H_
