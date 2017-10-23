FLAGS = -g -Wall -std=c++11
CFLAGS = -c $(FLAGS)
INC_DIR = Headers

# Create character files
beast.o: Characters/Beast.cpp Headers/Beast.h 
	g++ $(CFLAGS) -o beast.o Characters/Beast.cpp -I$(INC_DIR)

deathknight.o: Characters/DeathKnight.cpp Headers/DeathKnight.h 
	g++ $(CFLAGS) -o deathknight.o Characters/DeathKnight.cpp -I$(INC_DIR)

mage.o: Characters/Mage.cpp Headers/Mage.h 
	g++ $(CFLAGS) -o mage.o Characters/Mage.cpp -I$(INC_DIR)

paladin.o: Characters/Paladin.cpp Headers/Paladin.h 
	g++ $(CFLAGS) -o paladin.o Characters/Paladin.cpp -I$(INC_DIR)

priest.o: Characters/Priest.cpp Headers/Priest.h 
	g++ $(CFLAGS) -o priest.o Characters/Priest.cpp -I$(INC_DIR)

boss.o: Characters/Boss.cpp Headers/Boss.h
	g++ $(CFLAGS) -o boss.o Characters/Boss.cpp -I$(INC_DIR)

# Create setting files
gurubashi.o: Settings/Gurubashi.cpp Headers/Gurubashi.h 
	g++ $(CFLAGS) -o gurubashi.o Settings/Gurubashi.cpp -I$(INC_DIR)

icecrown.o: Settings/Icecrown.cpp Headers/Icecrown.h 
	g++ $(CFLAGS) -o icecrown.o Settings/Icecrown.cpp -I$(INC_DIR)

orgrimmar.o: Settings/Orgrimmar.cpp Headers/Orgrimmar.h 
	g++ $(CFLAGS) -o orgrimmar.o Settings/Orgrimmar.cpp -I$(INC_DIR)

ruins.o: Settings/Ruins.cpp Headers/Ruins.h 
	g++ $(CFLAGS) -o ruins.o Settings/Ruins.cpp -I$(INC_DIR)

woods.o: Settings/Woods.cpp Headers/Woods.h 
	g++ $(CFLAGS) -o woods.o Settings/Woods.cpp -I$(INC_DIR)

onyxia.o: Settings/Onyxia.cpp Headers/Onyxia.h
	g++ $(CFLAGS) -o onyxia.o Settings/Onyxia.cpp -I$(INC_DIR)

# Create item files
chest.o: Items/Chest.cpp Headers/Chest.h 
	g++ $(CFLAGS) -o chest.o Items/Chest.cpp -I$(INC_DIR)

key.o: Items/Key.cpp Headers/Key.h 
	g++ $(CFLAGS) -o key.o Items/Key.cpp -I$(INC_DIR)

map.o: Items/Map.cpp Headers/Map.h 
	g++ $(CFLAGS) -o map.o Items/Map.cpp -I$(INC_DIR)

scroll.o: Items/Scroll.cpp Headers/Scroll.h 
	g++ $(CFLAGS) -o scroll.o Items/Scroll.cpp -I$(INC_DIR)

potion.o: Items/Potion.cpp Headers/Potion.h
	g++ $(CFLAGS) -o potion.o Items/Potion.cpp -I$(INC_DIR)

equipment.o: Items/Equipment.cpp Headers/Equipment.h
	g++ $(CFLAGS) -o equipment.o Items/Equipment.cpp -I$(INC_DIR)

C = beast.o deathknight.o mage.o paladin.o priest.o boss.o
S = gurubashi.o orgrimmar.o icecrown.o ruins.o woods.o onyxia.o
I = chest.o key.o map.o scroll.o potion.o equipment.o
General = GameEngine.cpp Setting.cpp Character.cpp

game.out: Main.cpp $(General) $(C) $(S) $(I)
	g++ $(FLAGS) Main.cpp $(General) $(C) $(S) $(I) -I$(INC_DIR)

memory.out: game.out
	valgrind --leak-check=full -v ./a.out
