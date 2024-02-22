#include <iostream>
#include <string>
#include <memory>
#include "pokemon_class.cpp"
#include <vector>
#include <cstdlib>
#include <fstream>

using namespace std;
using Pokemon = unique_ptr<PokemonBase>;
using Pokedex = vector<unique_ptr<PokemonBase>>;


class Battle {
  public:
    Battle(){cout << "Battle default constructor" << endl;};
    Battle(Pokemon& playerPK, Pokemon& enemyPK, string t){
      if (t == "t") {  
        //tutorial battle (1 time use only)
        
        cout << "Battle Initiated!\n" << endl;
        playerPK->draw();
        cout << "Versus\n" << endl;
        enemyPK->draw();
        cout << "The top Pokemon is your pokemon and the bottom is the enemy's Pokemon" << endl;
        print_delay("Your goal is to defeat the enemy's Pokemon by attacking until their HP is 0", 3);
        print_delay("Be careful, if your HP become 0 you will lose instead", 3);
        print_delay("You can choose a skill from your Pokemon to attack the enemy's Pokemon, try choosing one", 3);
        display_move(playerPK);
        attack_enemy(playerPK, enemyPK, "no random");
        cout << "Good job! the enemy took some good damage" << endl;
        print_delay("The amount of damage you can deal depends on the element of your attack and the enemy's element",3);
        print_delay("Some element can deal more damage to some other elment, or less damage",3);
        attack_enemy(enemyPK, playerPK, "random");
        print_delay("You just got attacked!", 2);
        print_delay("Remember, your HP can not drop below 0, now let's keep attacking until the enemy is defeated", 3);
        while (enemyPK->getHP() > 0) {
            display_move(playerPK);
            attack_enemy(playerPK, enemyPK, "no random");
        } 
        print_delay("The enemy is defeated! You will gain a certain amount of exp everytime you defeat an enemy", 2);
        print_delay("When you gain exp, your Pokemon can level up, and it will has a chance to evolve into a stronger Pokemon!",3);
        print_delay("Now go out there, and defeat the Pokemons!",3);
        print_delay("",3);
      } 

    };
  Battle(Pokemon& playerPK, Pokemon& enemyPK, int multiplier, int difficulty, Pokedex& pokedex){
      battle_stage(playerPK, enemyPK, multiplier, difficulty, pokedex);
    }

    void battle_stage(Pokemon& playerPK, Pokemon& enemyPK, int multiplier, int difficulty, Pokedex& pokedex) {
        cout << "Battle Initiated!\n" << endl;
        playerPK->draw();
        cout << "\tVersus\n" << endl;
        enemyPK->draw();
        while (playerPK->getHP() > 0 && enemyPK->getHP() > 0) {
          display_move(playerPK);
          attack_enemy(playerPK, enemyPK, "no random");
          if (enemyPK->getHP() <= 0) {  //ends battle if the enemy dies
            playerPK->draw();
            enemyPK->draw();
            break;
          }
          attack_enemy(enemyPK, playerPK, "random");
          if (enemyPK->getHP() <= 0) {  //ends battle if the player dies
            playerPK->draw();
            enemyPK->draw();
            break;
          }
          playerPK->draw();
          enemyPK->draw();
        }
        // when the player wins
        if (enemyPK->getHP() <= 0) {
          cout << enemyPK->getName() << " is defeated!" << endl;
          print_delay("",2);
          playerPK->setHP_full();
          playerPK->gainEXP(enemyPK, multiplier, lutLVL, difficulty);
          cout << "Do you want to catch " << enemyPK->getName() << "?(y/n)" << endl;
          
          if (inputYN()) {
            cout << endl;
            catch_to_pokedex(enemyPK, pokedex);    
          }
           
        }
        //when the player lose
        else if (playerPK->getHP() <= 0) {
          cout << "You have been defeated! Try again next battle" << endl;
          print_delay("",2);
          playerPK->setHP_full();
        }
      }
      
    
    void display_move(Pokemon& playerPK) {
        cout << "-----------------------------------------------------" << endl;
        auto vec = playerPK->getMoveset();
        int i = 1;
        int m = 1;
        for(auto move_: vec) {
            cout << i << ". " << move_.name << ": " << playerPK->element_to_string(move_.element) << ": " << move_.damage << " dmg  |  ";
            if (m%2 == 0) {
                cout << endl;
             }
        i++;
        m++;
      }
      cout << "\n-----------------------------------------------------" << endl;
    }

    //used to make attack damage vary a little bit
    int randomize_move(Pokemon& playerPK) {  
        int size = playerPK->getMoveset().size();
        int i = rand()%size + 1;
        return i;
    }

    double offset_attack() {
      double offset = -2;
      int i = rand()%4;
      offset = offset + i;
      return offset;
    }

    void attack_enemy(Pokemon& playerPK, Pokemon& enemyPK, string random) {
        if (random == "no random") { //used when the player attacks the enemy
            int move_number;
            cin >> move_number;
            
            if (move_number >= 1 && move_number <= playerPK->getMoveset().size()) {  //check if it's a valid move number
                auto move = playerPK->attack(move_number);
                auto multiplier = element_multiplier(move.element, enemyPK->get_element());
                double attack_damage = move.damage*multiplier;
                attack_damage += offset_attack();
                enemyPK->reduceHP(attack_damage);
                cout << playerPK->getName() << " used " << move.name << "." << endl;
                cout << playerPK->getName() <<" dealt " << attack_damage << " damage to " << enemyPK->getName() << "!" << endl;
                if (multiplier == 2.0) {
                  cout << "It's very effective!" << endl;
                }
                else if (multiplier < 1.0) {
                  cout << "It's not very effective!" << endl;
                }
                cout << "";
                print_delay("", 2);
            }
            else {
            cout << "Please enter valid move!" << endl;
            attack_enemy(playerPK, enemyPK, "no random");
            }
        }
        else if (random == "random") { //used when enemy attacks the player
            int move_number = randomize_move(playerPK);
            auto move = playerPK->attack(move_number);
            auto multiplier = element_multiplier(move.element, enemyPK->get_element());
            double attack_damage = move.damage*multiplier;
            attack_damage += offset_attack();
            enemyPK->reduceHP(attack_damage);
            cout << playerPK->getName() << " used " << move.name << "." << endl;
            cout << playerPK->getName() << " dealt " << attack_damage << " damage to " << enemyPK->getName() << "!" << endl;
            if (multiplier == 2.0) {
                  cout << "It's very effective!" << endl;
                }
                else if (multiplier < 1.0) {
                  cout << "It's not very effective!" << endl;
                }
                cout << "";
                print_delay("", 2);
            }
        }
    
    
    //random chance of catching the Pokemon by their catchDifficulty, the higher the harder it is to catch
    //if successfully catched, add the Pokemon to pokedex
    void catch_to_pokedex(Pokemon& pokemon, Pokedex& pokedex){
      //chance of catching the pokemon is 1/catchDifficulty
      cout << "Catching " << pokemon->getName() << "..." << endl;
      renderArt("ascii_art/pokeball.asciiart", 0.03);
      print_delay("",4);
      bool can_catch = percent_chance(pokemon->get_catchDifficulty());
      if (can_catch) {
        cout << "Catched " << pokemon->getName() << " successfully!" << endl;
        print_delay("",1.5);
        cout << "You can access it in the Pokedex in the main menu" << endl;
        print_delay("",1.5);
        pokemon->setHP_full();
        pokemon->setEXP(0);
        pokedex.push_back(move(pokemon));
      }
      else {
        cout << "Catch failed!" << endl;
        print_delay("The Pokemon Ran away, you wish someday you will meet it again",2);
        print_delay("",2);
      }
    }
    
    
    
    double element_multiplier(Element attackerEM, Element defenderEM) {
      if (attackerEM == Element::Normal) {
        if (defenderEM == Element::Rock || defenderEM == Element::Steel) {
          return 0.5;
        }
        else if (defenderEM == Element::Ghost) {
          return 0.0;
        }
        else {
          return 1.0;
        }
      }
      else if (attackerEM == Element::Fight) {
        if (defenderEM == Element::Normal || defenderEM == Element::Rock || defenderEM ==   Element::Steel || defenderEM == Element::Ice || defenderEM == Element::Dark) {
          return 2.0;
        }
        else if (defenderEM == Element::Flying || defenderEM == Element::Poison || defenderEM == Element::Bug || defenderEM == Element::Psychic || defenderEM == Element::Fairy) {
          return 0.5;
        } 
        else if (defenderEM == Element::Ghost) {
          return 0.0;
        }
        else {
          return 1.0;
        }
      }
      else if (attackerEM == Element::Flying) {
        if (defenderEM == Element::Fight || defenderEM == Element::Bug || defenderEM == Element::Grass) {
          return 2.0;
        }
        else if (defenderEM == Element::Rock || defenderEM == Element::Steel || defenderEM == Element::Electric) {
          return 0.5;
        }
        else {
          return 1.0;
        }
      }
      else if (attackerEM == Element::Poison) {
        if (defenderEM == Element::Grass || defenderEM == Element::Fairy) {
          return 2.0;
        }
        else if (defenderEM == Element::Poison || defenderEM == Element::Ground || defenderEM == Element::Rock || defenderEM == Element::Ghost) {
          return 0.5;
        }
        else if (defenderEM == Element::Steel) {
          return 0.0;
        }
        else {
          return 1.0;
        }
      }
      else if (attackerEM == Element::Ground) {
        if (defenderEM == Element::Poison || defenderEM == Element::Rock || defenderEM == Element::Steel || defenderEM == Element::Fire || defenderEM == Element::Electric) {
          return 2.0;
        } 
        else if (defenderEM == Element::Bug || defenderEM == Element::Grass) {
          return 0.5;
        }
        else if (defenderEM == Element::Flying) {
          return 0.0;
        }
        else {
          return 1.0;
        }
      }
      else if (attackerEM == Element::Rock) {
        if (defenderEM == Element::Flying || defenderEM == Element::Bug || defenderEM == Element::Fire || defenderEM == Element::Ice) {
          return 2.0;
        }
        else if (defenderEM == Element::Fight || defenderEM == Element::Ground || defenderEM == Element::Steel) {
          return 0.5;
        }
        else {
          return 1.0;
        }
      }
      else if (attackerEM == Element::Bug) {
        if (defenderEM == Element::Grass || defenderEM == Element::Psychic) {
          return 2.0;
        }
        else if (defenderEM == Element::Fight || defenderEM == Element::Flying || defenderEM == Element::Poison || defenderEM == Element::Ghost || defenderEM == Element::Steel || defenderEM == Element::Fire || defenderEM == Element::Dark) {
          return 0.5;
        }
        else {
          return 1.0;
        }
      }
      else if (attackerEM == Element::Ghost) {
        if (defenderEM == Element::Ghost || defenderEM == Element::Psychic) {
          return 2.0;
        } 
        else if (defenderEM == Element::Dark) {
          return 0.5;
        }
        else if (defenderEM == Element::Ghost) {
          return 0.0;
        }
        else {
          return 1.0;
        }
      }
      else if (attackerEM == Element::Steel) {
        if (defenderEM == Element::Rock || defenderEM == Element::Ice || defenderEM == Element::Fairy) {
          return 2.0;
        }
        else if (defenderEM == Element::Steel || defenderEM == Element::Fire || defenderEM == Element::Water || defenderEM == Element::Electric) {
          return 0.5;
        }
        else {
          return 1.0;
        }
      }
      else if (attackerEM == Element::Fire) {
        if (defenderEM == Element::Bug || defenderEM == Element::Steel || defenderEM == Element::Grass || defenderEM == Element::Ice) {
          return 2.0;
        }
        else if (defenderEM == Element::Rock || defenderEM == Element::Fire || defenderEM == Element::Water || defenderEM == Element::Dragon) {
          return 0.5;
        }
        else {
          return 1.0;
        }
      }
      else if (attackerEM == Element::Water) {
        if (defenderEM == Element::Ground || defenderEM == Element::Rock || defenderEM == Element::Fire) {
          return 2.0;
        }
        else if (defenderEM == Element::Water || defenderEM == Element::Grass || defenderEM == Element::Dragon) {
          return 0.5;
        }
        else {
          return 1.0;
        }
      }
      else if (attackerEM == Element::Grass) {
        if (defenderEM == Element::Ground || defenderEM == Element::Rock || defenderEM == Element::Water) {
          return 2.0;
        }
        else if (defenderEM == Element::Flying || defenderEM == Element::Poison || defenderEM == Element::Bug || defenderEM == Element::Steel || defenderEM == Element::Fire || defenderEM == Element::Grass || defenderEM == Element::Dragon) {
          return 0.5;
        }
        else {
          return 1.0;
        }
      }
      else if (attackerEM == Element::Electric) {
        if (defenderEM == Element::Flying || defenderEM == Element::Water) {
          return 2.0;
        }
        else if (defenderEM == Element::Grass || defenderEM == Element::Electric || defenderEM == Element::Dragon) {
          return 0.5;
        }
        else if (defenderEM == Element::Ground) {
          return 0.0;
        }
        else {
          return 1.0;
        }
      }
      else if (attackerEM == Element::Psychic) {
        if (defenderEM == Element::Fight || defenderEM == Element::Poison) {
          return 2.0;
        }
        else if (defenderEM == Element::Steel || defenderEM == Element::Psychic) {
          return 0.5;
        }
        else if (defenderEM == Element::Dark) {
          return 0.0;
        }
        else {
          return 1.0;
        }
      }
      else if (attackerEM == Element::Ice) {
        if (defenderEM == Element::Flying || defenderEM == Element::Ground || defenderEM == Element::Grass || defenderEM == Element::Dragon) {
          return 2.0;
        }
        else if (defenderEM == Element::Steel || defenderEM == Element::Fire || defenderEM == Element::Water || defenderEM == Element::Ice) {
          return 0.5;
        }
        else {
          return 1.0;
        }
      }
      else if (attackerEM == Element::Dragon) {
        if (defenderEM == Element::Dragon) {
          return 2.0;
        }
        else if (defenderEM == Element::Steel) {
          return 0.5;
        }
        else if (defenderEM == Element::Fairy) {
          return 0.0;
        }
        else {
          return 1.0;
        }
      }
      else if (attackerEM == Element::Dark) {
        if (defenderEM == Element::Ghost || defenderEM == Element::Psychic) {
          return 2.0;
        }
        else if (defenderEM == Element::Fight || defenderEM == Element::Dark || defenderEM == Element::Fairy) {
          return 0.5;
        }
        else {
          return 1.0;
        }
      }
      else if (attackerEM == Element::Fairy) {
        if (defenderEM == Element::Fight || defenderEM == Element::Dragon || defenderEM == Element::Dark ) {
          return 2.0;
        }
        else if (defenderEM == Element::Poison || defenderEM == Element::Steel || defenderEM == Element::Fire) {
          return 0.5;
        }
        else {
          return 1.0;
        }
      }
      else {
        return 1.0; 
      }
    }

    private:
      vector<int> lutLVL = {0, 0, 10, 30, 60, 100, 150, 210, 280, 360, 450, 550, 650, 750, 850, 1000, 1200, 1400, 1600, 1850, 2100, 2600, 3350, 
                          4350, 5600, 7100 , 9000, 11000, 13500, 16500, 20000, 25000, 30000, 37500, 47500, 60000, 75000, 95000, 120000, 150000, 200000};

};


//hi


class Game {
  public:
    Game():difficulty(100), expMultiplier(7){
      renderArt("ascii_art/pokemon.asciiart", 0.05);
    };
    ~Game(){};

    void start(){
      cout << "\t-press Enter to start-\t-press l to load save-" << endl;
      string enter;
      getline(cin,enter);
      if (enter == "") {
        cout << "Hi, what's your name?" << endl;
        getline(cin,playerName);
        nameSave();
        cout << "===========================" << endl << endl << endl;
        cout << "It's time to choose your starter pokemon." << endl;
        starterPokemonChoose();
        cout << "Now that you got a partner to go along on this journey" << endl;
        print_delay("===========================",1);
        cout << "How about a battle turtorial?(y/n)" << endl;
        if (inputYN()) {
          Charmander enemy("Tutorial Charmander");
          Pokemon enemyptr = make_unique<Charmander>(enemy);
          Battle fight(pkptr, enemyptr, "t");   
        } 
        cout << "At what difficulty would you want to set for this journey(it can be change later)" << endl;
        setGameDifficulty();

        //loops the main menu
        while(true){
          cout << "\n\n\n======================" << endl;
          menu();        
        }
      }
      else if (enter == "l") {
        cout << "\nWhich save file do you want to continue from?" << endl;
        cout << "1) save1  2) save2  3) save3" << endl;
        string n;
        while (true) {
          cin >> n;
          if (n == "1" || n == "2" || n == "3") {
            break;
          }
        }
        loadfile(n);
        while(true){
          cout << "\n\n\n======================" << endl;
          menu();        
        }
      }
    }


    void nameSave(){
      cout << "Is your name " << playerName << "?(y/n)" << endl;
      if(inputYN()){
        cout << "Great! Let's get started" << endl;
        print_delay("",1.5);
      } else {
        cout << "Oh, I'm sorry then. What's your name again?" << endl;
        cin >> playerName;
        nameSave();
        
      }
    }

    void starterPokemonChoose(){
      cout << "Please choose a starter pokemon" << endl;
      cout << "1) Charmander" << endl << "2) Squirtle" << endl << "3) Bulbasaur" << endl;
      int choice;
      cin >> choice;
      switch(choice){
        case 1:
          msgStarterPokemon("Charmander");
          break;
        case 2:
          msgStarterPokemon("Squirtle");
          break;
        case 3:
          msgStarterPokemon("Bulbasaur");
          break;
        default:
          cout << "Please choose a valid answer." << endl;
          starterPokemonChoose();
          
      }
    }


    void msgStarterPokemon(string pktype){
      cout << "Did you choose "<< pktype << "?(y/n)" << endl;
          if(inputYN()){
            cout << "Great! You have chosen " << pktype << " as your partner on this adventure" << endl;
            namePokemon(pktype);
          } else {
            cout << "Oh sorry." << endl;
            starterPokemonChoose();
          } 
    }

    void namePokemon(string pkt){
      cout << "Name your pokemon?(Enter \"d\" to leave your pokemon name as it's spicie)" << endl;
      cin >> pkname;
      if(pkname == "d"){
        pkname = pkt;
      }
      if(pkt == "Charmander"){
        Charmander pkobj(pkname);
        pkptr = make_unique<Charmander>(pkobj);
        pkptr->sound();

        Pokemon copy_pkptr = make_unique<Charmander>(pkobj);
        pokedex.push_back(move(copy_pkptr));
        
        
      } else if(pkt == "Squirtle"){
        Squirtle pkobj(pkname);
        pkptr = make_unique<Squirtle>(pkobj);
        pkptr->sound();

        Pokemon copy_pkptr = make_unique<Squirtle>(pkobj);
        pokedex.push_back(move(copy_pkptr));

      } else if(pkt == "Bulbasaur"){
        Bulbasaur pkobj(pkname);
        pkptr = make_unique<Bulbasaur>(pkobj);
        pkptr->sound();

        Pokemon copy_pkptr = make_unique<Bulbasaur>(pkobj);
        pokedex.push_back(move(copy_pkptr));
      }
      
    }
    
    void display_pokedex() {
      cout << "\n\t[ " << playerName <<"\'s Pokedex ]" << endl;
      cout <<   "====================================================" << endl;
      int i = 1;
      for (auto& pokemon : pokedex) {
        cout << i << ". ";
        pokemon->print_stats();
        cout << "\tEXP: "<< pokemon->getEXP();
        i++;
        cout << endl;
      }
      cout << "====================================================" << endl;
      cout << "Press c to continue   | Press the position of Pokemon to view their art" << endl;
      string enter;
      cin >> enter;
      if (enter == "c") {
        return;
      } 
      else if (stoi(enter) > 0 && stoi(enter) <= pokedex.size()) {
        pokedex[stoi(enter)-1]->draw();
        display_pokedex();
      }
      else {
        cout <<"\nEnter a valid input!";
        display_pokedex();
      }
    }
    void setDifficulty(int n){
      difficulty = n;
    }

    void setEXPMultiplier(int n){
      expMultiplier = n;
    }

    void setGameDifficulty(){
      cout << "0)Easiest 1)Easy 2)Medium 3)Hard 4)Extreme" << endl;
      string msg = "Difficulty set to ";
      int n;
      cin >> n; 
      switch(n){
        case 0: //Easiest
          setDifficulty(1);
          setEXPMultiplier(1000);
          cout << msg << "Easiest." << endl;
          break;
        case 1: //Easy
          setDifficulty(3);
          setEXPMultiplier(100);
          cout << msg << "Easy." << endl;
          break;
        case 2: //Medium
          setDifficulty(10);
          setEXPMultiplier(50);
          cout << msg << "Medium." << endl;
          break;
        case 3: //Hard
          setDifficulty(100);
          setEXPMultiplier(20);
          cout << msg << "Hard." << endl;
          break;
        case 4: //Normal
          setDifficulty(100);
          setEXPMultiplier(7);
          cout << msg << "Extreme." << endl;
          break;
        default:
          setDifficulty(100);
          setEXPMultiplier(7);
          cout << msg << "Normal." << endl;
      }
    }

    //random enemy for battle
    Pokemon randomize_enemy() {
      int random = rand()%21;      
        switch(random) {
        case 0:{
          Bulbasaur obj("Bulbasaur");
          Pokemon Bulbasaurptr = make_unique<Bulbasaur>(obj);  
          return Bulbasaurptr;
          }
        case 1: {
          Squirtle obj("Squirtle");
          Pokemon Squirtleptr = make_unique<Squirtle>(obj);    
          return Squirtleptr;
          }
        case 2: {
          Charmander obj("Charmander");
          Pokemon Charmanderptr = make_unique<Charmander>(obj);
          return Charmanderptr;
          }
        case 3:  {
          Rattata obj("Rattata");
          Pokemon Rattataptr = make_unique<Rattata>(obj);      
          return Rattataptr;
          }
        case 4: {
          Pidgey obj("Pidgey");
          Pokemon Pidgeyptr = make_unique<Pidgey>(obj);
          return Pidgeyptr;
          }
        case 5: {
          Spearow obj("Spearow");
          Pokemon Spearowptr = make_unique<Spearow>(obj);
          return Spearowptr;
          }
        case 6: {
          Weedle obj("Weedle");
          Pokemon Weedleptr = make_unique<Weedle>(obj);
          return Weedleptr;
          }
        case 7: {
          Caterpie obj("Caterpie");
          Pokemon Caterpieptr = make_unique<Caterpie>(obj);
          return Caterpieptr;
          }
        case 8: {
          Growlithe obj("Growlithe");
          Pokemon Growlitheptr = make_unique<Growlithe>(obj);
          return Growlitheptr;
          }
        case 9: {
          Bellsprout obj("Bellsprout");
          Pokemon Bellsproutptr = make_unique<Bellsprout>(obj);
          return Bellsproutptr;
          }
        case 10: {
          Abra obj("Abra");
          Pokemon Abraptr = make_unique<Abra>(obj);
          return Abraptr;
          }
        case 11: {
          Pidgeotto obj("Pidgeotto");
          Pokemon Pidgeottoptr = make_unique<Pidgeotto>(obj);
          return Pidgeottoptr;
          }
        case 12: {
          Mankey obj("Mankey");
          Pokemon Mankeyptr = make_unique<Mankey>(obj);
          return Mankeyptr;
          }
        case 13:{
          Ekans obj("Ekans");
          Pokemon Ekansptr = make_unique<Ekans>(obj);
          return Ekansptr;
          }
        case 14:{
          Sandshrew obj("Sandshrew");
          Pokemon Sandshrewptr = make_unique<Sandshrew>(obj);
          return Sandshrewptr;
         }
        case 15:{
          Machop obj("Machop");
          Pokemon Machopptr = make_unique<Machop>(obj);
          return Machopptr;
          }
        case 16:{
          Weepinbell obj("Weepinbell");
          Pokemon Weepinbellptr = make_unique<Weepinbell>(obj);
          return Weepinbellptr;
         }
        case 17:{
          Venonat obj("Venonat");
          Pokemon Venonatptr = make_unique<Venonat>(obj);
          return Venonatptr;
          }
        case 18:{
          Onix obj("Onix");
          Pokemon Onixptr = make_unique<Onix>(obj);
          return Onixptr;
          }
        case 19:{
          Slowbro obj("Slowbro");
          Pokemon Slowbroptr = make_unique<Slowbro>(obj);
          return Slowbroptr;
          }
        case 20:{
          Gyarados obj("Gyarados");
          Pokemon Gyaradosptr = make_unique<Gyarados>(obj);
          return Gyaradosptr;
          }
        default: {
          Charmander obj("Gyarados");
          Pokemon Charmanderptr = make_unique<Charmander>(obj);
          return Charmanderptr;
          }
      }
 
    }
    
    void savefile(){
      cout << "Which save would you like to save to?" << endl
      << "1)save1 2)save2 3)save3" << endl;
      string num;
      cin >> num;
      string filename = "save" + num + ".txt";
      ofstream MyFile(filename, ios::out | ios::trunc);
      if (MyFile.is_open()){
        MyFile << playerName << endl
              << pkname << endl
              << pkptr->getSpecie() << endl
              << pkptr->getLVL() << endl
              << pkptr->getEXP();
      } else {
        cout << "File is not open" << endl;
      }
      MyFile.close();
      
    }

    void loadfile(string num){  
      
      string filename = "save" + num + ".txt";
      ifstream MyFile(filename, ios::in);
      string line;
      vector<string> gameinfo = {"playerName_", "pkname_", "pkspecie_", "pklvl_", "pkexp_"};
      int i;
      i = 0;
      if (!MyFile) {
        cerr << "Failed to open file: " << filename << endl;
        return;
      }
      while(getline(MyFile, line)){
        gameinfo[i] = line;
        i++;
      }
      playerName = gameinfo[0];
      pkname = gameinfo[1];
      
      if (gameinfo[2] == "Bulbasaur"){                                                                        
        Pokemon Bulbasaurptr = make_unique<Bulbasaur>(gameinfo[1], stod(gameinfo[4]), stoi(gameinfo[3]));  
        pkptr = move(Bulbasaurptr);   

        Pokemon copy_pkptr = make_unique<Bulbasaur>(gameinfo[1], stod(gameinfo[4]), stoi(gameinfo[3]));
        pokedex.push_back(move(copy_pkptr));
        
      }
      else if (gameinfo[2] == "Charmander") {
        Pokemon Charmanderptr = make_unique<Charmander>(gameinfo[1], stod(gameinfo[4]), stoi(gameinfo[3]));  
        pkptr = move(Charmanderptr); 
        
        Pokemon copy_pkptr = make_unique<Charmander>(gameinfo[1], stod(gameinfo[4]), stoi(gameinfo[3]));
        pokedex.push_back(move(copy_pkptr));
      }
      else if (gameinfo[2] == "Squirtle"){
        Pokemon Squirtleptr = make_unique<Squirtle>(gameinfo[1], stod(gameinfo[4]), stoi(gameinfo[3]));  
        pkptr = move(Squirtleptr); 
        
        Pokemon copy_pkptr = make_unique<Squirtle>(gameinfo[1], stod(gameinfo[4]), stoi(gameinfo[3]));
        pokedex.push_back(move(copy_pkptr));
      }
      else if (gameinfo[2] == "Charmeleon") {
        Pokemon Charmeleonptr = make_unique<Charmeleon>(gameinfo[1], stod(gameinfo[4]), stoi(gameinfo[3]));  
        pkptr = move(Charmeleonptr); 
        
        Pokemon copy_pkptr = make_unique<Charmeleon>(gameinfo[1], stod(gameinfo[4]), stoi(gameinfo[3]));
        pokedex.push_back(move(copy_pkptr));
      }
      else if (gameinfo[2] == "Wartortle"){
        Pokemon Wartortleptr = make_unique<Wartortle>(gameinfo[1], stod(gameinfo[4]), stoi(gameinfo[3]));  
        pkptr = move(Wartortleptr); 
        
        Pokemon copy_pkptr = make_unique<Wartortle>(gameinfo[1], stod(gameinfo[4]), stoi(gameinfo[3]));
        pokedex.push_back(move(copy_pkptr));
      }
      else if (gameinfo[2] == "Ivysaur") {
        Pokemon Ivysaurptr = make_unique<Ivysaur>(gameinfo[1], stod(gameinfo[4]), stoi(gameinfo[3]));  
        pkptr = move(Ivysaurptr); 
        
        Pokemon copy_pkptr = make_unique<Ivysaur>(gameinfo[1], stod(gameinfo[4]), stoi(gameinfo[3]));
        pokedex.push_back(move(copy_pkptr));
      }
      else if (gameinfo[2] == "Venusaur"){
        Pokemon Venusaurptr = make_unique<Venusaur>(gameinfo[1], stod(gameinfo[4]), stoi(gameinfo[3]));  
        pkptr = move(Venusaurptr); 
        
        Pokemon copy_pkptr = make_unique<Venusaur>(gameinfo[1], stod(gameinfo[4]), stoi(gameinfo[3]));
        pokedex.push_back(move(copy_pkptr));
      }
      else if (gameinfo[2] == "Blastoise") {
        Pokemon Blastoiseptr = make_unique<Blastoise>(gameinfo[1], stod(gameinfo[4]), stoi(gameinfo[3]));  
        pkptr = move(Blastoiseptr); 
        
        Pokemon copy_pkptr = make_unique<Blastoise>(gameinfo[1], stod(gameinfo[4]), stoi(gameinfo[3]));
        pokedex.push_back(move(copy_pkptr));
      }
      else if (gameinfo[2] == "Charizard"){
        Pokemon Charizardptr = make_unique<Charizard>(gameinfo[1], stod(gameinfo[4]), stoi(gameinfo[3]));  
        pkptr = move(Charizardptr); 
       
        Pokemon copy_pkptr = make_unique<Charizard>(gameinfo[1], stod(gameinfo[4]), stoi(gameinfo[3]));
        pokedex.push_back(move(copy_pkptr));
      }
      MyFile.close();
    }  
      
       
      
    
    
    void menu(){
      cout << "What would you like to do next?" << endl;
      cout << "1) Challenge an encounter." << endl
          << "2) Open Pokedex." << endl
          << "3) Change difficulty." << endl
          << "4) Save your progress." << endl
          << "5) Exit game." << endl;
      int n;
      cin >> n;
      switch(n){
        case 1:{
          //random enouncter
          Pokemon enemy = randomize_enemy();
          Battle fight(pkptr, enemy, expMultiplier, difficulty, pokedex); 
          break;}
        case 2:
          //open pokedex
          display_pokedex();
          break;
        case 3:
          //set game difficulty
          setGameDifficulty();
          break;
        case 4:
          //open, write, close file
          savefile();
          break;
        case 5:
          //exit loop
          cout << "\n\nAre you sure you want to quit?(y/n)" << endl;
          if (inputYN()) {
            exit(0);
          }
          else {
            menu();
          }
          break;
        default:
          cout << "Please choose a valid response." << endl;
          menu();
      }
    }
  protected:
    string pkname;
    string playerName;
    Pokemon pkptr;
    Pokedex pokedex;
    vector<int> lutLVL = {0, 0, 10, 30, 60, 100, 150, 210, 280, 360, 450, 550, 650, 750, 850, 1000, 1200, 1400, 1600, 1850, 2100, 2600, 3350, 
                          4350, 5600, 7100 , 9000, 11000, 13500, 16500, 20000, 25000, 30000, 37500, 47500, 60000, 75000, 95000, 120000, 150000, 200000};
    int difficulty;
    int expMultiplier;
   
};
