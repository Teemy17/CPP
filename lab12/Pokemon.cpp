#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

class Pokemon {
protected:
    std::string name, sound, type;
    int power, speed;

public:
    Pokemon(std::string name, std::string sound, std::string type, int power, int speed)
        : name(std::move(name)), sound(std::move(sound)), type(std::move(type)), power(power), speed(speed) {}

    virtual ~Pokemon() = default;

    std::string getName() const { return name; }
    std::string getSound() const { return sound; }
    std::string getType() const { return type; }
    int getPower() const { return power; }
    int getSpeed() const { return speed; }
};

class WildPokemon : public Pokemon {
    int catchRate;

public:
    WildPokemon(std::string name, std::string sound, std::string type, int power, int speed, int catchRate)
        : Pokemon(std::move(name), std::move(sound), std::move(type), power, speed), catchRate(catchRate) {}

    int getCatchRate() const { return catchRate; }
    bool attemptEscape() const { return (speed * catchRate) % 100 > 50; }
};

class PalPokemon : public Pokemon {
public:
    using Pokemon::Pokemon;
};

enum class PokeballType { Normal, Strong, Ultra };

class Pokeball {
    PokeballType type;
    std::string name;
    int efficiency;

public:
    Pokeball(PokeballType type, std::string name, int efficiency)
        : type(type), name(std::move(name)), efficiency(efficiency) {}


    std::string getName() const { return name; }
    int getEfficiency() const { return efficiency; }


    bool catchPokemon(const WildPokemon& wildPokemon) const {
        int successThreshold = 50;
        int catchChance = efficiency - wildPokemon.getCatchRate() + successThreshold;
        return (rand() % 100) < catchChance;
    }

    void increaseEfficiency(int increase) {
        efficiency += increase;
    }
};

class Berry {
    std::string name;
    int effectiveness;

public:
    Berry(std::string name, int effectiveness)
        : name(std::move(name)), effectiveness(effectiveness) {}

    std::string getName() const { return name; }
    int getEffectiveness() const { return effectiveness; }

    void applyEffect(Pokeball& pokeball) const {
        pokeball.increaseEfficiency(effectiveness);

    }
};

class Player {
    std::vector<Pokeball> pokeballs;
    std::vector<PalPokemon> caughtPokemons;
    bool pokeballsAdded = false; 

public:
    // Method to add a new Pokeball to the player's inventory
    void addPokeballs() {
        if (!pokeballsAdded) { // Check if Pokeballs have not been added before
            for (int i = 0; i < 5; ++i) {
                PokeballType randomType = static_cast<PokeballType>(rand() % 3); // Generate a random type (assuming 3 types)
                Pokeball newPokeball = createPokeballOfType(randomType);
                pokeballs.push_back(newPokeball);
            }
            pokeballsAdded = true; // Set the flag to true to prevent further additions
        }
    }


    bool hasPokeballs() const { return !pokeballs.empty(); }

    bool catchPokemon(WildPokemon& wildPokemon) {
        for (auto& pokeball : pokeballs) {
            if (pokeball.catchPokemon(wildPokemon)) {
                caughtPokemons.emplace_back(wildPokemon.getName(), wildPokemon.getSound(), wildPokemon.getType(), wildPokemon.getPower(), wildPokemon.getSpeed());
                pokeballs.erase(pokeballs.begin());  // Use one Pokeball
                return true;
            }
        }
        return false;
    }

    // Method to list all Pokeballs in the player's inventory
    void listPokeballs() const {
        std::cout << "Player's Pokeballs:\n";
        for (const auto& pokeball : pokeballs) {
            std::cout << pokeball.getName() << " (Efficiency: " << pokeball.getEfficiency() << ")\n";
        }
    }

    void listCaughtPokemons() const {
        std::cout << "Caught Pokemons:\n";
        for (const auto& pokemon : caughtPokemons) {
            std::cout << pokemon.getName() << std::endl;
        }
    }
private:
    // Helper method to create a Pokeball based on its type
    Pokeball createPokeballOfType(PokeballType type) {
        switch (type) {
            case PokeballType::Normal:
                return Pokeball(type, "Normal Pokeball", 30);
            case PokeballType::Strong:
                return Pokeball(type, "Strong Pokeball", 50);
            case PokeballType::Ultra:
                return Pokeball(type, "Ultra Pokeball", 70);
            default:
                // Default to Normal Pokeball if type is unknown
                return Pokeball(PokeballType::Normal, "Normal Pokeball", 30);
        }
    }
};

class World {
    std::vector<WildPokemon> wildPokemons;

public:
    World() {
        wildPokemons.emplace_back("Pidgey", "Chirp", "Flying", 10, 60, 30);
        wildPokemons.emplace_back("Rattata", "Squeak", "Normal", 15, 72, 25);
        wildPokemons.emplace_back("Zubat", "Screech", "Poison", 18, 75, 35);
        wildPokemons.emplace_back("Geodude", "Rumble", "Rock", 25, 40, 40);
        wildPokemons.emplace_back("Magikarp", "Splash", "Water", 5, 80, 10);
    }

    bool explore(Player& player) {
        if (wildPokemons.empty()) return false;  // No more wild PokÃ©mon in the world

        int encounterChance = rand() % 100;
        if (encounterChance < 25) {  // 25% chance to encounter a PokÃ©mon
            int pokemonIndex = rand() % wildPokemons.size();
            WildPokemon& wildPokemon = wildPokemons[pokemonIndex];
            std::cout << "Encountered a wild " << wildPokemon.getName() << "!\n";

            if (!player.hasPokeballs()) {
                std::cout << "You have no Pokeballs to catch " << wildPokemon.getName() << ". It escaped!\n";
                wildPokemons.erase(wildPokemons.begin() + pokemonIndex);  // Remove the PokÃ©mon as it escapes
                return false;  // Indicate that no PokÃ©mon was caught
            }

            if (player.catchPokemon(wildPokemon)) {
                std::cout << "Caught " << wildPokemon.getName() << "!\n";
                wildPokemons.erase(wildPokemons.begin() + pokemonIndex);  // Remove the caught PokÃ©mon from the world
                return true;  // Indicate that a PokÃ©mon was caught
            } else {
                std::cout << wildPokemon.getName() << " escaped!\n";
            }
        } else {
            std::cout << "No PokÃ©mon encountered on this walk.\n";
        }
        return false;  // Indicate that no PokÃ©mon was caught or encountered
    }
    
    bool isExhausted() const {
        return wildPokemons.empty();
    }
};


int main() {
    bool firstTime = true;
    srand(static_cast<unsigned>(time(nullptr)));

    Player player;
    World world;
    std::cout << "PokegonGame! ";

    while ((player.hasPokeballs() && !world.isExhausted()) || firstTime) {
        std::cout << "\nChoose an action:\n"
                  << "1. Add Pokeballs to stock\n"
                  << "2. Walk\n"
                  << "3. List Pokeballs\n"
                  << "4. List caught Pokemon\n"
                  << "5. Exit\n";
        int choice;
        std::cin >> choice;
        switch (choice) {
            case 1:
                player.addPokeballs();
                firstTime = false;
                break;
            case 2:
                world.explore(player);
                break;
            case 3:
                player.listPokeballs();
                break;
            case 4:
                player.listCaughtPokemons();
                break;
            case 5:
                return 0;
            default:
                std::cout << "Invalid choice. Please select again.\n";
        }
        if (!player.hasPokeballs() && !firstTime) {
            std::cout << "Game over: You've run out of Pokeballs." << std::endl;
            break;
        }
        if (world.isExhausted()) {
            std::cout << "Game over: All wild Pokemon have been caught." << std::endl;
            break;
        }
    }

    return 0;
}
