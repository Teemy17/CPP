#include <iostream>
#include <vector>
using namespace std;

// Base class
class SpaceObject
{
public:
    virtual void draw() const
    {
        std::cout << "Drawing a generic space object.\n";
    }
    virtual ~SpaceObject() {}
};
// Derived classes
class Martian : public SpaceObject
{
public:
    void draw() const override
    {
        std::cout << "Drawing a Martian object.\n";
    }
};
class Venutian : public SpaceObject
{
    void draw() const override
    {
        std::cout << "Drawing a Venutian object.\n";
    }
};
class Plutonian : public SpaceObject
{
    void draw() const override
    {
        std::cout << "Drawing a Plutonian object.\n";
    }
};
class Spaceship : public SpaceObject
{
    void draw() const override
    {
        std::cout << "Drawing a Spaceship object.\n";
    }
};
class LaserBeam : public SpaceObject
{
    void draw() const override
    {
        std::cout << "Drawing a LaserBeam object.\n";
    }
};
class Mercurian : public SpaceObject
{
    void draw() const override
    {
        std::cout << "Drawing a Mercurian object.\n";
    }
};

// ScreenManager class
class ScreenManager
{

    std::vector <SpaceObject*> objects;

public:
    void addObject(SpaceObject* obj)
    {
        objects.push_back(std::move(obj));
    }
    void refreshScreen()
    {
        for (const auto &obj : objects)
        {
            obj->draw();
        }
    }
};
// Main function to demonstrate functionality
int main()
{
    ScreenManager manager;
    manager.addObject(new Martian());
    manager.addObject(new Venutian());
    manager.addObject(new Plutonian());
    manager.addObject(new Spaceship());
    manager.addObject(new LaserBeam());
    manager.addObject(new Mercurian());   
    manager.refreshScreen();
    return 0;
}
