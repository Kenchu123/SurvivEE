#ifndef ITEM_H
#define ITEM_H

#include "Obj.h"
#include "Player.h"

enum ItemState {
    unPicked, Picked
};

class Item: public Obj {
    protected:
        std::string _type;
        ItemState _state; // unPicked and Picked
        double _itemX, _itemY; // center of the item
    public:
        Item();
        Item(std::string, double, double); // type x, y
        ~Item();
        void SetPosition(double&, double&);
        void update(SDL_Rect&);
        virtual void isPicked(Player*);
        double getItemX() { return _itemX; }
        double getItemY() { return _itemY; }
        void free();
};

class Helmet1: public Item {
    public:
        Helmet1() {};
        Helmet1(std::string, double, double) {};
        void isPicked(Player* player);
};

class Helmet2: public Item {
    public:
        Helmet2() {};
        Helmet2(std::string, double, double) {};
        void isPicked(Player* player);
};

class BodyArmor1: public Item {
    public:
        BodyArmor1() {};
        BodyArmor1(std::string, double, double) {};
        void isPicked(Player* player);
};

class BodyArmor2: public Item {
    public:
        BodyArmor2() {};
        BodyArmor2(std::string, double, double) {};
        void isPicked(Player* player);
};

class Bomb: public Item {
    public:
        Bomb() {};
        Bomb(std::string, double, double) {};
        void isPicked(Player* player);
};

class Bandage: public Item {
    public:
        Bandage() {};
        Bandage(std::string, double, double) {};
        void isPicked(Player* player);
};

class Gun: public Item {
    public:
        Gun() {};
        Gun(std::string, double, double) {};
        void isPicked(Player* player);
};

class ShotGun: public Item {
    public:
        ShotGun() {};
        ShotGun(std::string, double, double) {};
        void isPicked(Player* player);
};

class MachineGun: public Item {
    public:
        MachineGun() {};
        MachineGun(std::string, double, double) {};
        void isPicked(Player* player);
};

class SubMachineGun: public Item {
    public:
        SubMachineGun() {};
        SubMachineGun(std::string, double, double) {};
        void isPicked(Player* player);
};

class AK47: public Item {
    public:
        AK47() {};
        AK47(std::string, double, double) {};
        void isPicked(Player* player);
};

class LifeBox: public Item {
    public:
        LifeBox() {};
        LifeBox(std::string, double, double) {};
        void isPicked(Player* player);
};

extern std::vector<Item*> items;

#endif