#ifndef ITEM_H
#define ITEM_H

#include "Obj.h"

enum ItemState {
    unPicked, Picked
};

class Player;

class Item: public Obj {
    protected:
        ItemType _type;
        ItemState _state; // unPicked and Picked
        double _itemX, _itemY; // center of the item
        double _deg;
    public:
        Item();
        Item(ItemType, double, double); // type x, y
        ~Item();
        void SetPosition(double, double);
        void SetAngle(double);
        void isPicked(Player*);
        double getItemX() { return _itemX; }
        double getItemY() { return _itemY; }
        void free();
        void update();
        void renderL(SDL_Rect&);
        void renderR(SDL_Rect&);
};

extern std::vector<Item*> items;

#endif