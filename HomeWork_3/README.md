# **Library_dungeon_escape**

![screenshot of start screen](images/start.png)

## Chosen theme and a short description: 

The theme of library taken in a gaming direction. A short game about trying to escape a library by gettin new spellbooks and fighting enemies.

*scope*: terminal based (text) C++ game for school project.

*goal*: manage mana, grow your spellbook inventory and escape a library full of enemies.

## A list of the features your app currently has: 

### The app is a playable game containing:

- implementation of basic stats such as: hit points, mana, damage.
- implementation of level (and experience points) that scales those stats and changes environment.
- options to choose 3 actions: mana recovery, physical damage or cast a spellbook.
- options to choose available spellbooks based on player level (up to 7 spellbooks).
- 9 enemies with different stats and behaiviour for attacking (e.g., physical attack, mana draining, using spellbooks and combinations).
- enemies are chosen at random (including level) and attacks have a miss chance of 20%.
- a win condition: beating the actual librarian (lorewise stealing their access card and escaping) appearing after level 7.

### requirements fullfilment:

 - 3 design patterns: Singleton(Game class),
 - 1 template class: in Utility, the class LimitedStat.
 - 1 template function: 
 - 2 STL containers: std::vector (Game has a vector of Enemy),
 - 2 STL algorithmic methods: sort (in Game, Enemies are sorted on their minimum player level),
 - 2 smart pointers: unique_ptr (in Game to remember the enemies for upcasting),
 - Default 1 point.

 Bonus:
- not implemented.
