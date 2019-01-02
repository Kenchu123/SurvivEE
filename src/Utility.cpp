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

// std::string typeToString(ItemType& type) {
//     switch (type) {
//         case BodyArmor1: return "BodyArmor1";
//         case BodyArmor2: return "BodyArmor2";
//         case Helmet1: return "Helmet1";
//         case Helmet2: return "Helmet2";
//         case Bandage: return "Bandage";
//         case LifeBox: return "LifeBox";
//         case Gun: return "Gun";
//         case ShotGun: return "ShotGun";
//         case MachineGun: return "MachineGun";
//         case SubMachineGun: return "SubMachineGun";
//         case AK47: return "AK47";
//         case Default: return "";
//         default: return "";
//     }
// }