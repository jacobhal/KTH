//in main.cpp
#include "Headers/Character.h"
#include "Setting.h"
#include "Headers/Item.h"
#include "Headers/GameEngine.h"
#include "Equipment.h"


// Make header files later

// Items
#include "Scroll.h"
#include "Chest.h"
#include "Key.h"
#include "Map.h"
#include "Potion.h"

// Settings
#include "Ruins.h"
#include "Woods.h"
#include "Gurubashi.h"
#include "Orgrimmar.h"
#include "Icecrown.h"
#include "Onyxia.h"

// Characters
#include "Paladin.h"
#include "Priest.h"
#include "DeathKnight.h"
#include "Mage.h"
#include "Beast.h"
#include "Boss.h"


// Non-program includes
#include <time.h>
#include <limits>

using std::cout;
using std::cin;
using std::vector;
using std::string;

// Ubuntu/Linux/Mac color codes to spice things up
#define RESET   ""
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA ""      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     ""      /* Bold Red */
#define BOLDGREEN   ""      /* Bold Green */
#define BOLDYELLOW  ""      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */



int main()
{
cout << "Welcome to World of Adrian, a boring MMO game, please choose what class you would like to play: \n";
cout << "(1) Priest" << "\n";
cout << "(2) Paladin" << "\n"; 
cout << "(3) DeathKnight" << "\n"; 

// Create new player

Character *player;

// Let player choose class
int c;
bool b = 0;
while (!b) {
    cin >> c;
    switch (c)
    {
        case 1:
        {
            cout << "You chose Priest! \n";
            player = new Priest("I'm a healer!", "Lars");
            b = 1;
            break;
        }
        case 2:
        {
            cout << "You chose Paladin! \n";
            player = new Paladin("I'm a tank!", "Olle");
            b = 1;
            break;
        }
        case 3:
        {
            cout << "You chose Death Knight! \n";
            player = new DeathKnight("I'm DPS", "Rutger");
            b = 1;
            break;
        }
        default:
        {
            cout << "That is not a valid choice. Try again." << "\n";
            cin.clear();
            // Ignore the rest of the line since it is wrong input
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            b = 0;
            break;
        }
    }
}

// Let player choose weapon
cout << "Before your journey begins you must choose your weapon of choice: \n";
vector<Equipment> weps = player->weapons();
for(int i = 0; i < weps.size(); ++i) {
    cout << "(" << i + 1 << ") " <<  weps[i] << "\n";
}

cin >> c;
while (c > weps.size() || !cin) {
    cout << "That is not a valid choice. Try again." << "\n";
    cin.clear();
    // Ignore the rest of the line since it is wrong input
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin >> c;
}
    // Choice of weapon is always wise...
player->equipItem(&weps[c-1]);
cout << "You chose " << weps[c-1] << ", a wise choice!\n";
cout << "Let the journey begin! Type help to see all available commands and call a specific command with " <<
        "the -h option to see a more detailed description of what it does.\n";

// Create characters & environment & items and start the game engine

// Create characters
Character *tyrael = new Paladin("Hey duuudeee, I got something for you, but you need to figure out how to get it. XDDDDD", "Tyrael");
Character *jaina = new Mage("Champion! I need your help! Defeat the ugly ogre to the south and I will reward you greatly.", "Jaina");
Character *benedictus = new Priest("Greetings traveler, I hear that if you're looking to increase your power you should travel to Gurubashi. Lots of good drugs there.", "Benedictus");

// Bosses
Character *basilisk = new Boss("Basilisk", "HISSSSSS (A basilisk stands in your way. Defend yourself!)", "*SQUEAL*");
Character *lichKing = new Boss("LichKing", "I'll rek ya m8", "Ice... Cold...");
Character *onyxia = new Boss("Onyxia", "Foolish mortals! Perish in fire!", "Bwleeuuughhh!");
Character *shrek = new Boss("Shrek", "GET OUT OF MY SWAMMPPPP!", "It's all ogre now...");


// Create items
Item *key = new Key("key", "a key to unlock secret doors with");
Item *scroll = new Scroll("scroll", "A scroll which when used permanently increases your stats.");
Item *map = new Map("map", "a map to guide you through this adventure");
Item *potion = new Potion("potion", "a healing potion");
Item *sword = new Equipment("Frostmourne", "A sword containing the souls of thousands of the Lich Kings foes.", 30, 50, 50);
Item *chest = new Chest("chest", "a chest with unknown content", potion);


std::vector<Item*> items;
items.push_back(key);
items.push_back(chest);
items.push_back(scroll);
items.push_back(map);
items.push_back(potion);
items.push_back(sword);
for(int i = 0; i < player->weapons().size(); ++i) {
    items.push_back(&player->weapons()[i]);
}

// Add items to characters
basilisk->addItem(potion);
tyrael->addItem(key);
jaina->addItem(scroll);
lichKing->addItem(sword);
lichKing->addItem(key);


// Add settings with optional characters items
Setting *ruins = new Ruins("Ruins", "The fearsome ruins where giants fought over 1000 years ago. Some say such creatures still exist.");
Setting *gurubashi = new Gurubashi("Gurubashi", "Gurubashi, the arena where champions have arised and fallen for many decades.");
Setting *icecrown = new Icecrown("Icecrown", "Icecrown, the chilling castle where Lich King rules.");
Setting *orgrimmar = new Orgrimmar("Orgrimmar", "Orgrimmar, the famous capital city of the Hordes. The leader Thrall might be found somewhere around.");
Setting *woods = new Woods("Woods", "The dark woods, infamous for its dark creatures lurking around.");
Setting *onyxiaslair = new Onyxia("Onyxia's lair", "Onyxia's lair, the lair of the mighty dragon Onyxia");

// Setup routes (inverses too)
ruins->addRoute(icecrown, "north");
icecrown->addRoute(ruins, "south");

ruins->addRoute(woods, "east");
woods->addRoute(ruins, "west");

ruins->addRoute(orgrimmar, "south");
orgrimmar->addRoute(ruins, "north");

woods->addRoute(gurubashi, "east");
gurubashi->addRoute(woods, "west");

icecrown->addRoute(onyxiaslair, "west");
onyxiaslair->addRoute(icecrown, "east");

ruins->lockRoute(1); // Lock north route
icecrown->lockRoute(2); // Lock west route

// Maybe add subsettings too?
int c1 = rand() % 4 + 1;
int c2 = rand() % 4 + 1;
int c3 = rand() % 4 + 1;
int c4 = rand() % 4 + 1;
int c5 = rand() % 4 + 1;

// Add characters to zones (1: North, 2: West, 3: South, 4: East)
ruins->addCharacter(tyrael, 2);
gurubashi->addCharacter(jaina, 1);
icecrown->addCharacter(lichKing, 1);
orgrimmar->addCharacter(benedictus, 3);
woods->addCharacter(basilisk, 2);
onyxiaslair->addCharacter(onyxia, 2);
gurubashi->addCharacter(shrek, 3);


// Player starting items


// Setting items
int l1 = rand() % 4 + 1;
int l2 = rand() % 4 + 1;
int l3 = rand() % 4 + 1;
// 1: north 2: west 3: south 4: east
woods->addItem(chest, 1);
orgrimmar->addItem(map, 4);
// Idea is to use look to try and find specific items but using look also means risk to face hostile NPCs


// Start the game for player at specified area with these items
GameEngine *game = new GameEngine(orgrimmar, player, items);


// Prevent memory loss
delete game;
delete player;
delete tyrael;
delete jaina;
delete lichKing;
delete basilisk;
delete shrek;
delete onyxia;
delete benedictus;
delete key;
delete map;
delete potion;
delete sword;
delete chest;
delete scroll;
delete ruins;
delete gurubashi;
delete icecrown;
delete orgrimmar;
delete woods;
delete onyxiaslair;


return 0;
}