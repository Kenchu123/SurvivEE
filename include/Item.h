#ifndef ITEM_H
#define ITEM_H

#include "Obj.h"

enum ItemState {
    unPicked, Picked
};

class Item: public Obj {
    private:
        std::string _type;
        ItemState _state; // unPicked and Picked
        double _itemX, _itemY; // center of the item
    public:
        Item();
        Item(std::string, double&, double&); // type x, y
        void SetPosition(double&, double&);
        void update(SDL_Rect&);
        Item* isPicked();
        double getItemX() { return _itemX; }
        double getItemY() { return _itemY; }
};

extern std::vector<Item*> items;

#endif