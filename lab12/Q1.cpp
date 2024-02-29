#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Pokemon
{
private:
    string name;
    string sound;
    string type;
    int power;
    int speed;

public:
    Pokemon(string name, string sound, string type, int power, int speed) : name(name), sound(sound), type(type), power(power), speed(speed) {}

    string getName()
    {
        return name;
    }

    string getSound()
    {
        return sound;
    }

    string getType()
    {
        return type;
    }

    int getPower()
    {
        return power;
    }

    int getSpeed()
    {
        return speed;
    }
};

class WildPokemon : public Pokemon
{
private:
    int catchRate;

public:
    WildPokemon(string name, string sound, string type, int power, int speed, int catchRate) : Pokemon(name, sound, type, power, speed), catchRate(catchRate) {}

    int getCatchRate()
    {
        return catchRate;
    }

    void AttemptEsacpe()
    {
        if (rand() % 100 < getSpeed())
        {
            cout << Pokemon::getName() << " escaped!" << endl;
        }
        else
        {
            cout << Pokemon::getName() << " couldn't escape!" << endl;
        }
    }
};

class Palpokemon : public Pokemon
{
private:
    string caught;
    int level;

public:
    Palpokemon(string name, string sound, string type, int power, int speed, int level) : Pokemon(name, sound, type, power, speed), level(level) {}

    string getCaught()
    {
        return caught;
    }

    int getLevel()
    {
        return level;
    }
};

class Pokeball
{
private:
    string name;
    int efficiency;

public:
    Pokeball(string name, int efficiency) : name(name), efficiency(efficiency) {}

    string getName()
    {
        return name;
    }

    int getEfficiency()
    {
        return efficiency;
    }

    void catchPokemon(WildPokemon &pokemon)
    {
        if (rand() % 100 > (pokemon.getCatchRate() * efficiency) / 100)
        {
            cout << "You caught " << pokemon.getName() << "!" << endl;
        }
        else
        {
            cout << "You couldn't catch " << pokemon.getName() << "!" << endl;
        }
    }

    void IncreaseEfficientcy(int effectiveness)
    {
        efficiency += effectiveness;
    }
};

class Berry
{
private:
    string name;
    int effectiveness;

public:
    Berry(string name, int effectiveness) : name(name), effectiveness(effectiveness) {}

    void IncreaseEfficientcy(Pokeball &pokeball)
    {
        pokeball.IncreaseEfficientcy(effectiveness);
    }

    string getName()
    {
        return name;
    }
};

class Player
{
private:
    vector<Pokeball> pokeballs;
    vector<Berry> berries;

public:
    void addPokeball(Pokeball pokeball)
    {
        pokeballs.push_back(pokeball);
        cout << "You added " << pokeball.getName() << " to your bag!" << endl;
    }

    void addBerry(Berry berry)
    {
        berries.push_back(berry);
        cout << "You added " << berry.getName() << " to your bag!" << endl;
    }

    void catchPokemon(WildPokemon &pokemon)
    {
        if (!pokeballs.empty())
        {
            Pokeball &pokeball = pokeballs.front(); // Get the first Pokeball in the collection
            pokeball.catchPokemon(pokemon);         // Use the Pokeball to catch the Pokémon
        }
        else
        {
            std::cout << "You don't have any Pokeballs to catch the Pokémon!" << std::endl;
        }
    }
};

class World
{
private:
    WildPokemon wildPokemon;

public:
    World(WildPokemon wildPokemon) : wildPokemon(wildPokemon) {}

    void encounter()
    {
        cout << "You encountered " << wildPokemon.getName() << "!" << endl;
    }
};

class GameTester
{
public:
    static void test()
    {
        WildPokemon Pikachu("Pikachu", "Pika Pika", "Electric", 100, 35, 40);
        WildPokemon Charlizard("Charlizard", "Char Char", "Fire", 100, 100, 20);
        WildPokemon Blastoise("Blastoise", "Bla Bla", "Water", 100, 100, 30);
        Palpokemon palPokemon("Pikachu", "Pika Pika", "Electric", 100, 100, 50);
        Pokeball pokeball("Pokeball", 50);
        Pokeball greatball("Greatball", 75);
        Pokeball masterball("Masterball", 100);
        Berry berry("Cheri berry", 50);
        Player player;
        player.addPokeball(pokeball);
        player.addBerry(berry);
        World Pika(Pikachu);
        Pika.encounter();
        player.catchPokemon(Pikachu);
        World charliz(Charlizard);
        charliz.encounter();
        player.catchPokemon(Charlizard);
        World balst(Blastoise);
        balst.encounter();
        player.catchPokemon(Blastoise);
        cout << "--------------------------------" << endl;
        cout << "Test escape" << endl;
        Pikachu.AttemptEsacpe();
    }
};

int main()
{
    srand(time(0));
    GameTester gameTester;
    gameTester.test();
    return 0;
}