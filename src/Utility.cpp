#include "Utility.h"

std::string typeToString(PlayerType& type) {
    switch (type) {
        case DefaultPlayer: return "DefaultPlayer";
        case GunPlayer: return "GunPlayer";
        case MachineGunPlayer: return "MachineGunPlayer";
        case ShotGunPlayer: return "ShotGunPlayer";
        case FireGunPlayer: return "FireGunPlayer";
        case AK47Player: return "AK47Player";
        default: return "";
    }
}

// std::string typeToString(GunType& type) {
//     switch (type) {
//         case Gun: return "Gun";
//         case MachineGun: return "MachineGun";
//         case AK47: return "AK47";
//         case FireGun: return "FireGun";
//         case ShotGun: return "ShotGun";
//         default: return "";
//     }
// }

std::string typeToString(ButtonType& type) {
    switch (type) {
        case Start: return "start";
        case Tutorial: return "tutorial";
        case Option: return "option";
        case Continue: return "continue";
        case Restart: return "restart";
        default: return "";
    }
}

std::string typeToString(ObstacleType& type) {
    switch (type) {
        case Tree: return "Tree";
        case Rock1: return "Rock1";
        case Rock2: return "Rock2";
        case Rock3: return "Rock3";
        case Box: return "Box";
        case BrickWall: return "BrickWall";
        default: return "";
    } 
}

std::string typeToString(ItemType type) {
    switch (type) {
        case Gun: return "Gun";
        case MachineGun: return "MachineGun";
        case AK47: return "AK47";
        case FireGun: return "FireGun";
        case ShotGun: return "ShotGun";
        case Bomb: return "Bomb";
        case BodyArmor1: return "BodyArmor1";
        case BodyArmor2: return "BodyArmor2";
        case Helmet1: return "Helmet1";
        case Helmet2: return "Helmet2";
        case Bandage: return "Bandage";
        case LifeBox: return "LifeBox";
        case Default: return "";
        default: return "";
    }
}

double getDis(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1- y2, 2));
}