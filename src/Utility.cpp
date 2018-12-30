#include "Utility.h"

std::string typeToString(PlayerType& type) {
    switch (type) {
        case DefaultPlayer: return "DefaultPlayer";
        case GunPlayer: return "GunPlayer";
        case MachineGunPlayer: return "MachineGunPlayer";
        default: return "";
    }
}

std::string typeToString(GunType& type) {
    switch (type) {
        case Gun: return "Gun";
        case MachineGun: return "MachineGun";
        default: return "";
    }
}