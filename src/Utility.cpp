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
        default: return "";
    }
}

std::string typeToString(rObstacleType& type) {
    switch (type) {
        case Tree: return "Tree";
        case Rock1: return "Rock1";
        case Rock2: return "Rock2";
        case Rock3: return "Rock3";
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

ItemType StringTotype(std::string s) {
    if(s == "Gun") return Gun;
    else if(s == "MachineGun") return MachineGun;
    else if(s == "ShotGun") return ShotGun;
    else if(s == "FireGun") return FireGun;
    else if(s == "AK47") return AK47;
    else if(s == "Bomb") return Bomb;
    else if(s == "BodyArmor1") return BodyArmor1;
    else if(s == "BodyArmor2") return BodyArmor2;
    else if(s == "Helmet1") return Helmet1;
    else if(s == "Helmet2") return Helmet2;
    else if(s == "Bandage") return Bandage;
    else if(s == "LifeBox") return LifeBox;
    else return Default;
}
