#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class World;

class Pokemon
{
protected:
    string name;
    string sound;
    string type;
    int power;
    int speed;

public:
    Pokemon(string _name, string _sound, string _type, int _power, int _speed)
        : name(_name), sound(_sound), type(_type), power(_power), speed(_speed) {}

    string getName() const { return name; }
    string getSound() const { return sound; }
    string getType() const { return type; }
    int getPower() const { return power; }
    int getSpeed() const { return speed; }
};

class WildPokemon : public Pokemon
{
private:
    int catchRate;

public:
    WildPokemon(string _name, string _sound, string _type, int _power, int _speed, int _catchRate)
        : Pokemon(_name, _sound, _type, _power, _speed), catchRate(_catchRate) {}

    int getCatchRate() const { return catchRate; }

    bool attemptEscape() const
    {

        int escapeChance = rand() % 100 + 1;
        return (escapeChance <= speed);
    }
};

class PalPokemon : public Pokemon
{
public:
    PalPokemon(string _name, string _sound, string _type, int _power, int _speed)
        : Pokemon(_name, _sound, _type, _power, _speed) {}
};

class Pokeball
{
private:
    string name;
    int efficiency;

public:
    Pokeball(string _name, int _efficiency) : name(_name), efficiency(_efficiency) {}

    string getName() const { return name; }
    int getEfficiency() const { return efficiency; }

    bool catchPokemon(const WildPokemon &pokemon) const
    {
        int catchChance = rand() % 100 + 1;
        return (catchChance <= (efficiency * pokemon.getCatchRate()));
    }
};

class Berry
{
private:
    string name;
    int effectiveness;

public:
    Berry(string _name, int _effectiveness) : name(_name), effectiveness(_effectiveness) {}

    string getName() const { return name; }
    int getEffectiveness() const { return effectiveness; }

    void applyEffect(Pokeball &pokeball) const
    {
        pokeball = Pokeball(pokeball.getName(), pokeball.getEfficiency() + effectiveness);
    }
};

class Player
{
private:
    vector<Pokeball> pokeballs;
    vector<WildPokemon> capturedPokemons;
    Berry berry;

public:
    Player(const Berry &_berry = Berry("", 0)) : berry(_berry) {}

    void addPokeball(const Pokeball &pokeball)
    {
        pokeballs.push_back(pokeball);
    }

    void stockpilePokeballs()
    {

        for (int i = 0; i < 5; ++i)
        {
            int efficiency = rand() % 3 + 1;
            string pokeballType;
            switch (efficiency)
            {
            case 1:
                pokeballType = "Normal";
                break;
            case 2:
                pokeballType = "Strong";
                break;
            case 3:
                pokeballType = "Ultra";
                break;
            }
            pokeballs.push_back(Pokeball(pokeballType + " Pokeball", efficiency));
        }
    }

    void explore(World &world);

    bool catchPokemon(const WildPokemon &pokemon)
    {
        for (const auto &pokeball : pokeballs)
        {
            if (pokeball.catchPokemon(pokemon))
            {
                cout << "You caught " << pokemon.getName() << "!" << endl;
                capturedPokemons.push_back(pokemon);
                pokeballs.pop_back();
                return true;
            }
        }
        cout << "Oh no! " << pokemon.getName() << " escaped!" << endl;
        return false;
    }

    void displayPokeballs() const
    {
        cout << "Your Pokeball inventory:" << endl;
        for (const auto &pokeball : pokeballs)
        {
            cout << pokeball.getName() << " (Efficiency: " << pokeball.getEfficiency() << ")" << endl;
        }
    }

    bool checkPokeballs() const
    {
        if (pokeballs.size() == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool checkPokeballs2() const
    {
        if (pokeballs.size() > 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void displayCapturedPokemons() const
    {
        cout << "Your captured Pokemons:" << endl;
        for (const auto &pokemon : capturedPokemons)
        {
            cout << pokemon.getName() << endl;
        }
    }
};

class World
{
private:
    vector<WildPokemon> wildPokemons;

public:
    void addWildPokemon(const WildPokemon &pokemon)
    {
        wildPokemons.push_back(pokemon);
    }

    bool checkMon()
    {
        if (wildPokemons.size() > 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void explore(Player &player)
    {
        if (wildPokemons.empty())
        {
            cout << "No more wild Pokemons in this area." << endl;
            exit(0);
        }

        WildPokemon wildPokemon = wildPokemons.back();
        wildPokemons.pop_back();

        cout << "You encountered a wild " << wildPokemon.getName() << "!" << endl;

        if (player.catchPokemon(wildPokemon))
        {

            PalPokemon palPokemon(wildPokemon.getName(), wildPokemon.getSound(), wildPokemon.getType(),
                                  wildPokemon.getPower(), wildPokemon.getSpeed());
            cout << "You now have " << palPokemon.getName() << " in your collection!" << endl;
        }
    }
};

void Player::explore(World &world)
{

    if (rand() % 4 == 0)
    {
        world.explore(*this);
    }
    else
    {
        cout << "You didn't encounter any wild Pokemon during exploration." << endl;
    }
}

void playGame()
{

    srand(time(nullptr));

    Player player;
    World world;

    world.addWildPokemon(WildPokemon("Charizard", "Roar", "Fire", 100, 90, 10));
    world.addWildPokemon(WildPokemon("Blastoise", "Splash", "Water", 100, 90, 10));
    world.addWildPokemon(WildPokemon("Pikachu", "Pika Pika", "Electric", 100, 90, 10));
    world.addWildPokemon(WildPokemon("Jigglypuff", "Jiggly", "Fairy", 100, 90, 10));
    world.addWildPokemon(WildPokemon("Venusaur", "Venus", "Grass", 100, 90, 10));

    bool gameRunning = true;
    bool first_time = true;

    while ((world.checkMon() && player.checkPokeballs2()) || first_time)
    {
        cout << "\nActions:\n"
             << "1. Add pokeball to stock\n"
             << "2. Walk\n"
             << "3. List pokeball\n"
             << "4. List caught pokemon\n"
             << "5. Exit\n";
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            if (player.checkPokeballs())
            {
                player.stockpilePokeballs();
                cout << "Five Pokeballs added to your inventory." << endl;
                first_time = false;
                break;
            }
            else
            {
                cout << "Full pokeballs" << endl;
            }
        case 2:

            player.explore(world);
            break;
        case 3:

            player.displayPokeballs();
            break;
        case 4:

            player.displayCapturedPokemons();
            break;
        case 5:

            gameRunning = false;
            cout << "Exiting the game. Goodbye!" << endl;
            exit(0);
        default:
            cout << "Invalid choice. Please enter a number between 1 and 5." << endl;
            break;
        }
    }

    cout << "Game over" << endl;
    player.displayCapturedPokemons();
}

int main()
{
    playGame();
    return 0;
}
