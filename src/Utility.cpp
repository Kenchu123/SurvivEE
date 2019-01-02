#include "Utility.h"

std::string typeToString(PlayerType& type) {
    switch (type) {
        case DefaultPlayer: return "DefaultPlayer";
        case GunPlayer: return "GunPlayer";
        case MachineGunPlayer: return "MachineGunPlayer";
        case ShotGunPlayer: return "ShotGunPlayer";
        default: return "";
    }
}

std::string typeToString(GunType& type) {
    switch (type) {
        case Gun: return "Gun";
        case MachineGun: return "MachineGun";
        case AK47: return "AK47";
        case SubMachineGun: return "SubMachineGun";
        case ShotGun: return "ShotGun";
        default: return "";
    }
}

std::string typeToString(ButtonType& type) {
    switch (type) {
        case Start: return "start";
        case Tutorial: return "tutorial";
        case Option: return "option";
        default: return "";
    }
}