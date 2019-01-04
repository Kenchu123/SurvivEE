#ifndef ITEM_H
#define ITEM_H

#include "Obj.h"
#include "Player.h"

enum ItemState {
    unPicked, Picked
};

class Item: public Obj {
    protected:
        // std::string _type;
        ItemType _type;
        ItemState _state; // unPicked and Picked
        double _itemX, _itemY; // center of the item
        double _deg;
    public:
        Item();
        Item(ItemType, double, double); // type x, y
        ~Item();
        void SetPosition(double, double);
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