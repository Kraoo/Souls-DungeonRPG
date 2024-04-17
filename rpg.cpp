#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <vector>

using namespace std;

struct Weapon {
    string name;
    int baseDamage;
    int additionalDamage;
    string specialAttribute;
};

struct Armor {
    string name;
    int durability;
};

struct Item {
    string name;
    string description;
};

struct Enemy {
    string name;
    int health;
    int damage;

    Enemy(const string& n, int h, int d) : name(n), health(h), damage(d) {}
};

void delay(int seconds) {
    this_thread::sleep_for(chrono::seconds(seconds));
}

bool isCriticalHit() {
    return rand() % 100 < 30;
}

bool didDodge() {
    return rand() % 100 < 50;
}

void useWeapon(const Weapon& weapon, Enemy& enemy, int& health, Armor& armor) {
    cout << "You use the " << weapon.name << ".\n";
    cout << "Attacking...\n";
    delay(2);
    
    int totalDamage = weapon.baseDamage + weapon.additionalDamage;
    
    if (weapon.specialAttribute == "slash") {
        bool isSlashing = rand() % 100 < 15; // 15% chance for slash
        int slashHits = 2; // 2 hits for slash
        
        if (isSlashing) {
            cout << "You perform a slashing attack with the " << weapon.name << "!\n";
            cout << "The enemy takes " << totalDamage << " slash damage.\n";
            delay(2);
            cout << "The slashing damage continues...\n";
            while (slashHits > 1) {
                delay(2);
                cout << "The enemy takes " << totalDamage << " slash damage.\n";
                slashHits--;
            }
        } else {
            cout << "You strike normally with the " << weapon.name << ".\n";
            cout << "The enemy takes " << totalDamage << " damage.\n";
        }
    } else if (weapon.specialAttribute == "blunt") {
        cout << "You strike with the " << weapon.name << "!\n";
        if (isCriticalHit()) {
            totalDamage += (totalDamage * 0.1);
            cout << "Critical hit! Damage increased by 10%.\n";
        }
        cout << "The enemy takes " << totalDamage << " blunt damage.\n";
    } else if (weapon.specialAttribute == "dodge") {
        if (didDodge()) {
            cout << "You dodge the enemy's attack with your agility!\n";
        } else {
            cout << "You couldn't dodge the enemy's attack.\n";
        }
    }
    
    cout << "The enemy's health is now " << enemy.health << ".\n";

    if (enemy.health > 0) {
        cout << "The " << enemy.name << " attacks you!\n";
        delay(2);
        
        if (armor.durability > 0) {
            cout << "Your armor absorbs the damage.\n";
            if (armor.durability >= enemy.damage) {
                armor.durability -= enemy.damage;
                cout << "Armor durability remaining: " << armor.durability << endl;
            } else {
                cout << "Your " << armor.name << " breaks!\n";
                cout << "You will now take direct damage to your health.\n";
                health -= (enemy.damage - armor.durability);
                armor.durability = 0;
                armor.name = "";
            }
        } else {
            cout << "You take " << enemy.damage << " damage.\n";
            health -= enemy.damage;
        }
    }
}

void exploreDungeon(int& health, const Weapon& weapon, Armor& armor, vector<Item>& inventory) {
    string choice;
    bool exitRequested = false;
    Enemy goblin("Goblin", 30, 10);
    Enemy knight("Knight", 50, 15);
    Enemy giant("Giant", 100, 20);
    Enemy dragon("Dragon", 150, 25);
    Enemy skeleton("Skeleton", 25, 12);
    Enemy zombie("Zombie", 40, 8);
    Enemy orc("Orc", 60, 18);
    Enemy slime("Slime", 20, 5);
    Enemy werewolf("Werewolf", 70, 15);
    Enemy witch("Witch", 45, 10);
    
    while (!exitRequested) {
        cout << "You find yourself in a dark dungeon filled with danger.\n";
        cout << "You notice three doors ahead of you:\n";
        cout << "1. Door on the left\n";
        cout << "2. Door in the middle\n";
        cout << "3. Door on the right\n";
        cout << "Choose a door to proceed: ";
        cin >> choice;
        
        if (choice == "1") {
            cout << "You open the door on the left and prepare for what lies beyond.\n";
            cout << "You see a chest in the corner of the room and another door.\n";
            cout << "What would you like to do?\n";
            cout << "1. Check the chest\n";
            cout << "2. Continue to the next room\n";
            cout << "Choose an option: ";
            cin >> choice;
            
            if (choice == "1") {
                cout << "You open the chest and find chain mail armor inside.\n";
                cout << "Do you want to take the armor?\n";
                cout << "1. Yes\n";
                cout << "2. No\n";
                cout << "Choose an option: ";
                cin >> choice;
                
                if (choice == "1") {
                    cout << "You take the chain mail armor.\n";
                    armor.name = "Chain Mail";
                    armor.durability = 40;
                } else {
                    cout << "You decide not to take the armor.\n";
                }
            } else if (choice == "2") {
                cout << "You decide to continue to the next room.\n";
            } else {
                cout << "Invalid choice! Please choose either 1 or 2.\n";
            }
        } else if (choice == "2") {
            cout << "You proceed through the door and enter the room...\n";
            
            Enemy currentEnemy("", 0, 0);
            
            vector<Enemy> enemies;
            enemies.push_back(goblin);
            enemies.push_back(knight);
            enemies.push_back(giant);
            enemies.push_back(dragon);
            enemies.push_back(skeleton);
            enemies.push_back(zombie);
            enemies.push_back(orc);
            enemies.push_back(slime);
            enemies.push_back(werewolf);
            enemies.push_back(witch);
            
            int randomIndex = rand() % enemies.size();
            currentEnemy = enemies[randomIndex];
            
            cout << "You encounter a " << currentEnemy.name << "!\n";
            bool playerTurn = true;
            
            while (currentEnemy.health > 0) {
                if (playerTurn) {
                    cout << "What would you like to do?\n";
                    cout << "1. Fight\n";
                    cout << "2. Use a potion\n";
                    cout << "3. Run away\n";
                    cout << "4. Check stats\n";
                    cout << "5. Check inventory\n";
                    cout << "6. Exit\n";
                    cout << "Choose an option: ";
                    cin >> choice;
                    
                    if (choice == "1") {
                        useWeapon(weapon, currentEnemy, health, armor);
                        playerTurn = false;
                    } else if (choice == "2") {
                        cout << "You use a potion to heal yourself.\n";
                        health += 20;
                        playerTurn = false;
                    } else if (choice == "3") {
                        if (rand() % 100 < 10) {
                            cout << "You successfully flee to the previous room!\n";
                            break;
                        } else {
                            cout << "You couldn't escape!\n";
                            playerTurn = false;
                        }
                    } else if (choice == "4") {
                        cout << "Weapon: " << weapon.name << " (Damage: " << weapon.baseDamage + weapon.additionalDamage << ")\n";
                        if (armor.name != "") {
                            cout << "Armor: " << armor.name << " (Durability: " << armor.durability << ")\n";
                        } else {
                            cout << "No Armor Equipped\n";
                        }
                        cout << "Health: " << health << endl;
                    } else if (choice == "5") {
                        cout << "Inventory:\n";
                        for (const auto& item : inventory) {
                            cout << "- " << item.name << ": " << item.description << endl;
                        }
                    } else if (choice == "6") {
                        exitRequested = true;
                        break;
                    } else {
                        cout << "Invalid choice! Please choose a valid option.\n";
                    }
                } else {
                    cout << "The " << currentEnemy.name << " attacks you!\n";
                    health -= currentEnemy.damage;
                    cout << "Your health is now " << health << ".\n";
                    playerTurn = true;
                }
            }
        } else if (choice == "3") {
            cout << "You open the door on the right and find a room with various items scattered around.\n";
            cout << "You see a health potion, a chest, and another door.\n";
            cout << "What would you like to do?\n";
            cout << "1. Pick up the health potion\n";
            cout << "2. Check the chest\n";
            cout << "3. Enter the next room\n";
            cout << "4. Return to the previous room\n";
            cout << "Choose an option: ";
            cin >> choice;
            
            if (choice == "1") {
                cout << "You pick up the health potion.\n";
                Item potion;
                potion.name = "Health Potion";
                potion.description = "A magical potion that restores health.";
                inventory.push_back(potion);
            } else if (choice == "2") {
                cout << "You check the chest, but it's empty.\n";
            } else if (choice == "3") {
                cout << "You decide to enter the next room.\n";
            } else if (choice == "4") {
                cout << "You decide to return to the previous room.\n";
            } else {
                cout << "Invalid choice! Please choose a valid option.\n";
            }
        } else {
            cout << "Invalid choice! Please choose a number between 1 and 3.\n";
        }
    }
}

int main() {
    srand(time(nullptr));
    
    cout << "Welcome to the Dungeon Adventure RPG!\n";
    cout << "You wake up in a dark dungeon, unsure of how you got there.\n";
    cout << "You need to find a way out, but first, you need a weapon to defend yourself.\n";
    
    cout << "You notice three weapons lying on the ground:\n";
    cout << "1. Sword (Slash damage)\n";
    cout << "2. Hammer (Blunt damage with chance of critical hit)\n";
    cout << "3. Bow (Long-range weapon with dodge chance)\n";
    cout << "Choose your weapon wisely: ";
    
    string choice;
    cin >> choice;
    
    Weapon weapon;
    Armor armor;
    vector<Item> inventory;
    
    if (choice == "1") {
        weapon.name = "Sword";
        weapon.baseDamage = 20;
        weapon.additionalDamage = 0;
        weapon.specialAttribute = "slash";
    } else if (choice == "2") {
        weapon.name = "Hammer";
        weapon.baseDamage = 15;
        weapon.additionalDamage = 0;
        weapon.specialAttribute = "blunt";
    } else if (choice == "3") {
        weapon.name = "Bow";
        weapon.baseDamage = 10;
        weapon.additionalDamage = 0;
        weapon.specialAttribute = "dodge";
    } else {
        cout << "Invalid choice! Please choose a number between 1 and 3.\n";
        return 1;
    }
    
    cout << "You pick up the " << weapon.name << ".\n";
    
    cout << "Armed with your " << weapon.name << ", you venture deeper into the dungeon...\n";
    
    int playerHealth = 100;
    exploreDungeon(playerHealth, weapon, armor, inventory);
    
    return 0;
}
