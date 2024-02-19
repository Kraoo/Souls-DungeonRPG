# Dungeon Adventure RPG

This is a simple text-based RPG (Role-Playing Game) implemented in C++, where the player navigates through a dungeon, encounters enemies, collects items, and engages in combat.

## Gameplay Mechanics

- **Combat**: Combat involves attacking enemies using the chosen weapon. Each weapon has different attributes and may trigger special effects, such as critical hits or dodges.
- **Health and Armor**: The player has a health bar representing their remaining health. Additionally, the player can equip armor to mitigate incoming damage.
- **Items**: Items found in the dungeon, such as health potions and armor, can be collected and utilized during the game to enhance the player's capabilities.
- **Random Events**: Certain actions, such as attacking or attempting to flee, have random outcomes based on probabilities.

## Code Structure

- The code is structured into several structs representing game entities such as weapons, armor, enemies, and items.
- Functions are defined for various game actions, such as attacking with a weapon, exploring the dungeon, and handling combat scenarios.
- Random number generation is utilized for implementing chance-based mechanics, such as critical hits and dodges.

## Dependencies

- The code utilizes standard C++ libraries such as `<iostream>`, `<string>`, `<ctime>`, and `<cstdlib>`.
- Additionally, it includes `<chrono>` and `<thread>` for implementing delays in the game.

## Contributing

Contributions to this project are welcome. Feel free to fork the repository, make improvements, and submit pull requests.

## License

This project is licensed under the [MIT License](LICENSE). Feel free to use and modify the code for your own purposes.
