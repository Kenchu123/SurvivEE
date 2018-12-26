#include <iostream>
#include <string>

class Obj {
    protected:
        std::string _id;
    public:
        Obj() {
            _id = "Obj_ID";
            std::cout << "Obj constructor\n";
        }
        Obj(std::string id) {
            _id = id;
            std::cout << "Obj constructor with id\n";
        }
        std::string get_Id() { return _id; }
};

class Player : public Obj {
    protected:
        int pos_x, pos_y;
    public:
        Player(int x, int y, std::string id): Obj(id) {
            pos_x = x, pos_y = y;
            std::cout << "Player constructor\n";
        }
        int getx () { return pos_x; }
        int gety () { return pos_y; }
};

int main() {
    Player player(10, 5, "hello");
    std::cout << player.get_Id();
}