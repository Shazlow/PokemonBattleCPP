#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "function.cpp"

using namespace std;

double const RENDER_DELAY = 0.03;

enum Element {
    Normal,
    Fire, 
    Water,
    Grass,
    Electric, 
    Ice,
    Fight,
    Poison,
    Ground,
    Flying,
    Psychic,
    Bug,
    Rock,
    Ghost,
    Dark,
    Dragon,
    Steel,
    Fairy
};

struct Move {
    string name;
    double damage;
    Element element;
};



class PokemonBase {
  
  public:
    PokemonBase():name("Pokemon"){};
    PokemonBase(string n):name(n){};
    ~PokemonBase(){};
    
    //copy assignment
    PokemonBase& operator=(const PokemonBase& other) {
      if (this == &other) {
        return *this;
      }
      
      // Copy member variables from 'other' to 'this'
      name = other.name;
      hp = other.hp;
      maxHP = other.maxHP;
      exp = other.exp;
      catchDifficulty = other.catchDifficulty;
      moveset = other.moveset;
      vecele = other.vecele;
      lvl = other.lvl;
      
      return *this;
    }
    
    
    virtual void sound(){
      cout << name << ": Pokemon!" << endl;
    }

    string element_to_string() {
      string res;
      
      for(Element e:vecele){
        switch(e){
          case Normal:
            res = res + "Normal ";
            break;
          case Fire:
            res = res + "Fire ";
            break;
          case Water:
            res = res + "Water ";
            break;
          case Grass:
            res = res + "Grass ";
            break;
          case Electric:
            res = res + "Electric ";
            break;
          case Ice:
            res = res + "Ice ";
            break;
          case Fight:
            res = res + "Fight ";
            break;
          case Poison:
            res = res + "Poison ";
            break;
          case Ground:
            res = res + "Ground ";
            break;
          case Flying:
            res = res + "Flying ";
            break;
          case Psychic:
            res = res + "Psychic ";
            break;
          case Bug:
            res = res + "Bug ";
            break;
          case Rock:
            res = res + "Rock ";
            break;
          case Ghost:
            res = res + "Ghost  ";
            break;
          case Dark:
            res = res + "Dark  ";
            break;
          case Dragon:
            res = res + "Dragon  ";
            break;
          case Steel:
            res = res + "Steel  ";
            break;
          case Fairy:
            res = res + "Fairy  ";
            break;
        }  
      }
      return res;
    }

    string element_to_string(Element e) { 
      switch(e){
        case Normal:
          return"Normal";
          break;
        case Fire:
          return "Fire";
          break;
        case Water:
          return "Water";
          break;
        case Grass:
          return "Grass";
          break;
        case Electric:
          return "Electric";
          break;
        case Ice:
          return "Ice";
          break;
        case Fight:
          return "Fight";
          break;
        case Poison:
          return "Poison";
          break;
        case Ground:
          return "Ground";
          break;
        case Flying:
          return "Flying";
          break;
        case Psychic:
          return "Psychic";
          break;
        case Bug:
          return "Bug";
          break;
        case Rock:
          return "Rock";
          break;
        case Ghost:
          return "Ghost";
          break;
        case Dark:
          return "Dark";
          break;
        case Dragon:
          return "Dragon";
          break;
        case Steel:
          return "Steel";
          break;
        case Fairy:
          return "Fairy";
          break;
        default:
          return "";
          break;
        }  
    }

    Element get_element() {
        return vecele[0];
    }

    virtual void draw() {
      cout << "" << endl;
      print_stats();
    }

    //used in draw() function
    void print_stats() {
      cout << "\n\t" << name << "\t HP:[ " << hp << " / " << maxHP << " ]" << "\t Element: " << element_to_string() <<  endl; 
    }

    Move attack(int n){
        return moveset[n-1];
    }

    string getName(){
      return name;
    }

    double getHP(){
      return hp;
    }

    void setHP_full(){
      hp = maxHP;
    }

    double getMaxHP() {
      return maxHP;
    }
        
    double getEXP(){
      return exp;
    }

    void setEXP(double exp_){
      exp = exp_;
    }

    void setLVL(int lv){
      lvl = lv;
    }

    int getLVL(){
      return lvl;
    }

    string getSpecie(){
      return specieName;
    }

    vector<Move> getMoveset() {
        return moveset;
    }

    void reduceHP(double n) {
        hp = hp - n;
    }

    int get_catchDifficulty() {
      return catchDifficulty;
    }

      
        //function to update the experience of pokemon, taking in enemy unique_ptr to calculate the experience given to player's pokemon
    void gainEXP(unique_ptr<PokemonBase>& enemypk, int expMultiplier, vector<int>& lut, int difficulty){
      double tempexp = (enemypk->getLVL()*expMultiplier);
      exp = exp + tempexp;
      cout << name << " gained " << tempexp << " EXP." << endl;
      print_delay("",1);
      upLVL(lut, difficulty);
    }

    
    //once an amount of experience a pokemon reached, their level increased
    //take a reference of a lookup talbe from game class to see if the limit of experience reached for the level to change or not
    //take in difficulty as multiplier to the lookup table
    void upLVL(vector<int>& lut, int difficulty){
      bool temp;
      for(int i = lvl; exp >= lut[lvl]*difficulty; i++){
          lvl++;
          //because everytime the level is update, there is a chance for pokemon to evolve
          detectEvolution();
          
      }
          cout << name << "\'s level is now " << lvl << endl;         
          
          
    }

  
    //once pokemon reached level 25 and 40, they evolve   
    void detectEvolution(){
      if(lvl == 25){
        cout << endl;
        unique_ptr<PokemonBase> evolvedPK = this->evolve();
        *this = move(*evolvedPK);
      } else if(lvl == 40) {
        cout << endl;
        unique_ptr<PokemonBase> evolvedPK = this->evolve();
        *this = move(*evolvedPK);
      } else {
        //
      }
    }
    //return unique_ptr of pokemonBase because this pokemon cannot evolve
    virtual unique_ptr<PokemonBase> evolve(){
      cout << "Base pokemon has no evolution, only the starters have the ability to evolve, Pokemon!" << endl;
      PokemonBase base(name);
      unique_ptr<PokemonBase> respk = make_unique<PokemonBase>(base);
      return respk;
    }

  

  protected:
    string specieName;
    string name;
    double hp;
    double maxHP;
    double exp;
    int catchDifficulty;    //chance of catching the pokemon is 1/catchDifficulty
    vector<Move> moveset;
    vector<Element> vecele;
    int lvl;
    
   
};

class Charizard : public PokemonBase {
  public:
    const string sName = "Charizard";
    Charizard(){cout << "Charizard created" << endl; name = "Charizard"; specieName = sName; catchDifficulty = 10;};     //default constructor
    Charizard(string n){name = n; hp = 85; maxHP = 85; vecele = {Fire, Flying}; exp = 0.0; specieName = sName;    //constructor assigning components of pokemon
                      moveset = {{"Fire Spin", 14.0, Fire}, {"Dragon Claw", 25.0, Dragon}, {"Flamethrower", 35.0, Fire}, {"Air Slash", 21.0, Flying}}; lvl = 40;  catchDifficulty = 10;};
    Charizard(string n, double e, int lv){name = n; hp = 85; vecele = {Fire, Flying}; exp = e; specieName = sName;; 
                      moveset = {{"Fire Spin", 14.0, Fire}, {"Dragon Claw", 25.0, Dragon}, {"Flamethrower", 35.0, Fire}, {"Air Slash", 21.0, Flying}}; lvl = lv;  catchDifficulty = 10;}
    Charizard(unique_ptr<PokemonBase>& pkcharmeleon){name = pkcharmeleon->getName(); hp = 85; vecele = {Fire, Flying}; exp = pkcharmeleon->getEXP();  specieName = sName;
                      moveset = {{"Fire Spin", 14.0, Fire}, {"Dragon Claw", 25.0, Dragon}, {"Flamethrower", 35.0, Fire}, {"Air Slash", 21.0, Flying}}; lvl = pkcharmeleon->getLVL(); catchDifficulty = 10;};
    ~Charizard() = default;

  void sound(){
    cout << name << ": Charizard!" << endl;
  }

  void draw(){
    renderArt("ascii_art/charizard.asciiart", RENDER_DELAY);
    print_stats();
  }
};

class Charmeleon : public PokemonBase {
  public:
    const string sName = "Charmeleon";
    Charmeleon(){cout << "Charmeleon created" << endl; name = "Charmeleon"; specieName = sName; catchDifficulty = 25;};
    Charmeleon(string n){name = n; hp = 45.0; maxHP = 45.0; vecele = {Fire}; exp = 0.0; specieName = sName;
                        moveset = {{"Ember", 12.0, Fire}, {"Flamethrower", 23.0, Fire}, {"Scratch", 6.0, Normal}};
                        lvl = 25; catchDifficulty = 25;};
    Charmeleon(string n, double e, int lv){name = n; hp = 45.0; maxHP = 45.0; vecele = {Fire}; exp = e; specieName = sName;
                        moveset = {{"Ember", 12.0, Fire}, {"Flamethrower", 23.0, Fire}, {"Scratch", 6.0, Normal}};
                        lvl = lv; catchDifficulty = 25;};
    Charmeleon(unique_ptr<PokemonBase>& pkcharmander){name = pkcharmander->getName(); hp = 45.0; vecele = {Fire}; exp = pkcharmander->getEXP(); specieName = sName;
                        moveset = {{"Ember", 12.0}, {"Flamethrower", 23.0}, {"Scratch", 6.0}}; lvl = pkcharmander->getLVL(); catchDifficulty = 25;};
    ~Charmeleon() = default;

    void sound(){
      cout << name << ": Charmeleon!" << endl;
    }

    unique_ptr<PokemonBase> evolve() override {
      cout << name << " is evolving!" << endl;
      return make_unique<Charizard>(name, exp, lvl);
    }

    void draw(){
      renderArt("ascii_art/charmeleon.asciiart", RENDER_DELAY);
      print_stats();
    }

};

class Charmander : public PokemonBase {
  public:
    const string sName = "Charmander";
    Charmander(){cout << "Charmander created"<< endl; name = "Charmander"; specieName = sName; catchDifficulty = 80;};
    Charmander(string n){name = n; hp = 23.0; maxHP = 23.0; vecele = {Fire}; exp = 0.0; specieName = sName;
                        moveset = {{"Scratch", 4.0, Normal}, 
                                  {"Ember", 8.0, Fire}}; lvl = 1; catchDifficulty = 80;};
    Charmander(string n, double e , int lv){name = n; hp = 23.0; maxHP = 23.0; vecele = {Fire}; exp = e; specieName = sName;
                        moveset = {{"Scratch", 4.0, Normal}, 
                                  {"Ember", 8.0, Fire}}; lvl = lv; catchDifficulty = 80;};
    ~Charmander() = default;

    void sound(){
      cout << name << ": Charmander!" << endl;
    }


    unique_ptr<PokemonBase> evolve() override {
      cout << name << " is evolving!" << endl;
      return make_unique<Charmeleon>(name, exp, lvl);
    }

    

    void draw() {
      renderArt("ascii_art/charmander.asciiart", RENDER_DELAY);
      print_stats();
    }
    
};

class Blastoise : public PokemonBase {
  public:
    const string sName = "Blastoise";
    Blastoise(){cout << "Blastoise created" << endl; name = "Blastoise"; specieName = sName; catchDifficulty = 15;};
    Blastoise(string n){name = n; hp = 102; maxHP = 102; vecele = {Water}; exp = 0.0; specieName = sName;
                        moveset = {{"Tackle", 9.0, Normal}, {"Water Gun", 20.0, Water}, {"Ice Beam", 30.0, Ice}, 
                        {"Hydro Pump", 23.0, Water}}; lvl = 0.0; catchDifficulty = 15;};
    Blastoise(string n, double e, int lv){name = n; hp = 102; maxHP = 102; vecele = {Water}; exp = e; specieName = sName;
                        moveset = {{"Tackle", 9.0, Normal}, {"Water Gun", 20.0, Water}, {"Ice Beam", 30.0, Ice}, 
                        {"Hydro Pump", 23.0, Water}}; lvl = lv; catchDifficulty = 15;};
    Blastoise(unique_ptr<PokemonBase>& pkwartortle){name = pkwartortle->getName(); hp = 102; maxHP = 50.0; specieName = sName;
                        vecele = {Water}; exp = pkwartortle->getEXP();
                        moveset = {{"Tackle", 9.0, Normal}, {"Water Gun", 20.0, Water}, {"Ice Beam", 30.0, Ice}, 
                        {"Hydro Pump", 23.0, Water}}; lvl = pkwartortle->getLVL(); catchDifficulty = 15;};
    ~Blastoise() = default;
  
    void sound(){
      cout << name << ": Blastoise!" << endl;
    }
  
    void draw(){
      renderArt("ascii_art/blastoise.asciiart", RENDER_DELAY);
      print_stats();
    }
};

class Wartortle : public PokemonBase {
  public:
    const string sName = "Wartortle";
    Wartortle(){cout << "Wartortle created" << endl; name = "Wartortle"; specieName = sName; catchDifficulty = 30;};
    Wartortle(string n){name = n; hp = 60.0; maxHP = 60.0; vecele = {Water}; exp = 0.0; specieName = sName;
                      moveset = {{"Tackle", 7.0, Normal}, {"Water Gun", 12.0, Water}, {"Aqua Jet", 21.0, Water}};
                      lvl = 25; catchDifficulty = 30;};
    Wartortle(string n, double e, int lv){name = n; hp = 60.0; maxHP = 60.0; vecele = {Water}; exp = e; specieName = sName;
                      moveset = {{"Tackle", 7.0, Normal}, {"Water Gun", 12.0, Water}, {"Aqua Jet", 21.0, Water}};
                      lvl = lv; catchDifficulty = 30;};
    Wartortle(unique_ptr<PokemonBase>& pksquirtle){name = pksquirtle->getName(); hp = 60.0; maxHP = 50.0; specieName = sName;
                      vecele = {Water}; exp = pksquirtle->getEXP();
                      moveset = {{"Tackle", 7.0, Normal}, {"Water Gun", 12.0, Water}, {"Aqua Jet", 21.0, Water}};
                      lvl = pksquirtle->getLVL(); catchDifficulty = 30;};
    ~Wartortle() = default;

    void sound(){
      cout << name << ": Wartortle!" << endl;
    }

    unique_ptr<PokemonBase> evolve() override {
      cout << name << " is evolving!" << endl;
      return make_unique<Blastoise>(name, exp, lvl);
    }

    void draw(){
      renderArt("ascii_art/wartortle.asciiart", RENDER_DELAY);
      print_stats();
    }

};

class Squirtle : public PokemonBase {
  public:
    const string sName = "Squirtle";
    Squirtle(){cout << "Squirtle created" << endl; name = "Squirtle"; specieName = sName; catchDifficulty = 75;};
    Squirtle(string n){name = n; hp = 26.0; maxHP = 26.0; vecele = {Water}; exp = 0.0; specieName = sName;
                      moveset = {{"Tackle", 3.0, Normal}, {"Bubble", 7.0, Water}}; lvl = 1; catchDifficulty = 75;};
    Squirtle(string n, double e, int lv){name = n; hp = 26.0; maxHP = 26.0; vecele = {Water}; exp = e; specieName = sName;
                      moveset = {{"Tackle", 3.0, Normal}, {"Bubble", 7.0, Water}}; lvl = lv; catchDifficulty = 75;};                  
    ~Squirtle() = default;

    void sound(){
      cout << name << ": Squirtle!" << endl;
    }

    unique_ptr<PokemonBase> evolve() override {
      cout << name << " is evolving!" << endl;
      return make_unique<Wartortle>(name, exp, lvl);
    }

    void draw() {
      renderArt("ascii_art/squirtle.asciiart", RENDER_DELAY);
      print_stats();
    }
};

class Venusaur : public PokemonBase {
  public:
    const string sName = "Venusaur";
    Venusaur(){cout << "Venusaur created" << endl; name = "Venusaur"; specieName = sName; catchDifficulty = 15;};
    Venusaur(string n){name = n; hp = 90; maxHP = 90; vecele = {Grass, Poison};
                    moveset = {{"Vine Whip", 11.0, Grass}, {"Razor Leaf", 22.0, Grass}, {"Solar Beam", 33.0, Grass}, {"Petal Blizzard", 11.0, Grass}}; lvl = 40; specieName = sName; catchDifficulty = 15;};
    Venusaur(string n, double e, int lv){name = n; hp = 50.0; maxHP = 50.0; specieName = sName;
                    vecele = {Grass, Poison}; exp = e;
                    moveset = {{"Vine Whip", 11.0, Grass}, {"Razor Leaf", 22.0, Grass}, {"Solar Beam", 33.0, Grass}, {"Petal Blizzard", 11.0, Grass}}; lvl = lv;catchDifficulty = 15;};
    Venusaur(unique_ptr<PokemonBase>& pkivysaur){name = pkivysaur->getName(); hp = 50.0; maxHP = 50.0; specieName = sName;
                    vecele = {Grass, Poison};
                    moveset = {{"Vine Whip", 11.0, Grass}, {"Razor Leaf", 22.0, Grass}, {"Solar Beam", 33.0, Grass}, {"Petal Blizzard", 11.0, Grass}}; lvl = pkivysaur->getLVL();  catchDifficulty = 25;};
    ~Venusaur() = default;

    void sound() {
      cout << name << ": Venusaur!" << endl;
    }

    void draw(){
      renderArt("ascii_art/venusaur.asciiart", RENDER_DELAY);
      print_stats();
    }

};

class Ivysaur : public PokemonBase {
  public:
    const string sName = "Ivysaur";
    Ivysaur(){cout << "Ivysaur created" << endl; name = "Ivysaur"; specieName = sName;  catchDifficulty = 25;};
    Ivysaur(string n){name = n; hp = 50.0; maxHP = 50.0; vecele = {Grass, Poison}; specieName = sName;
                     moveset = {{"Vine Whip", 7.0, Grass}, {"Razor Leaf", 13.0, Grass}, {"Solar Beam", 20.0, Grass}};
                      lvl =25; catchDifficulty = 25;};
    Ivysaur(string n, double e, int lv){name = n; hp = 50.0; maxHP = 50.0; specieName = sName;
                    vecele = {Grass, Poison}; exp = e;
                    moveset = {{"Vine Whip", 7.0, Grass}, {"Razor Leaf", 13.0, Grass}, {"Solar Beam", 20.0, Grass}};
                    lvl = lv; catchDifficulty = 25;};
    Ivysaur(unique_ptr<PokemonBase>& pkbulbasaur){name = pkbulbasaur->getName(); hp = 50.0; maxHP = 50.0; specieName = sName;
                    vecele = {Grass, Poison}; 
                    moveset = {{"Vine Whip", 7.0, Grass}, {"Razor Leaf", 13.0, Grass}, {"Solar Beam", 20.0, Grass}};
                    lvl = pkbulbasaur->getLVL(); catchDifficulty = 25;};
    ~Ivysaur() = default;

    void sound(){
      cout << name << ": Ivysaur!" << endl;
    }

    
    unique_ptr<PokemonBase> evolve() override {
      cout << name << " is evolving!" << endl;
      return make_unique<Venusaur>(name, exp, lvl);
    }

    void draw(){
      renderArt("ascii_art/ivysaur.asciiart", RENDER_DELAY);
      print_stats();
    }
};

class Bulbasaur : public PokemonBase {
  public:
    const string sName = "Bulbasaur";
    Bulbasaur(){cout << "Bulbasaur created" << endl; name = "Bulbasaur"; specieName = sName; catchDifficulty = 80;};
    Bulbasaur(string n){name = n; hp = 25.0; maxHP = 25.0; vecele = {Grass, Poison}; exp = 0.0;
                       moveset = {{"Vine Whip", 2.0, Grass}, {"Power Whip", 7.0, Grass}}; lvl = 1; catchDifficulty = 80;};
    Bulbasaur(string n, double e, int lv){name = n; hp = 25.0; maxHP = 25.0; vecele = {Grass, Poison}; exp = e;
                       moveset = {{"Vine Whip", 2.0, Grass}, {"Power Whip", 7.0, Grass}}; lvl = lv; catchDifficulty = 80;};
      
      
    ~Bulbasaur() = default;

    void sound(){
      cout << name << ": Bulbasaur!" << endl;
    }

    unique_ptr<PokemonBase> evolve() override {
      cout << name << " is evolving!" << endl;
      return make_unique<Ivysaur>(name, exp, lvl);
    }

    void draw() {
      renderArt("ascii_art/bulbasaur.asciiart", RENDER_DELAY);
      print_stats();
    }
    
};




class Rattata : public PokemonBase {
	public:
		Rattata(){cout << "Rattata created" << name << endl; name = "Rattata"; catchDifficulty = 70;};
		Rattata(string n){name = n; hp = 19.0; maxHP = 19.0; vecele = {Normal};
                     moveset = {{"Quick Attack", 3.0, Normal}, {"Hyper Fang", 7.0, Normal}, {"Body Slam", 10.0, Normal}};
                     lvl = 3; catchDifficulty = 70;};
		~Rattata() = default;

		void sound(){
			cout << name << ": Rattata!" << endl;
		}
    void draw() {
      renderArt("ascii_art/rattata.asciiart", RENDER_DELAY);
      print_stats();
    }
};

class Pidgey : public PokemonBase {
public:
		Pidgey(){cout << "Pidgey created" << name << endl; name = "Pidgey"; catchDifficulty = 75;};
		Pidgey(string n){name = n; hp = 17.0; maxHP = 17.0; vecele = {Normal, Flying}; 
                    moveset = {{"Quick Attack", 3.0, Normal}, {"Aerial Ace", 10.0, Flying}};
                    lvl = 3; catchDifficulty = 75;};
		~Pidgey() = default;

		void sound(){
			cout << name << ": Pidgey!" << endl;
		}

    void draw() {
      renderArt("ascii_art/pidgey.asciiart", RENDER_DELAY);
      print_stats();
    }
};

class Spearow : public PokemonBase {
	public:
		Spearow(){cout << "Spearow created" << name << endl; name = "Spearow"; catchDifficulty = 60;};
		Spearow(string n){name = n; hp = 15.0; maxHP = 15.0; vecele = {Normal, Flying};
                     moveset = {{"Quick Attack", 3.0, Normal}, {"Sky Attack", 12.0, Flying}, {"Peck", 7.0, Flying}};
                     lvl = 4; catchDifficulty = 60;};
		~Spearow() = default;

		void sound(){
			cout << name << ": Spearow!" << endl;
		}

    void draw() {
      renderArt("ascii_art/spearow.asciiart", RENDER_DELAY);
      print_stats();
    }
};

class Weedle : public PokemonBase {
	public:
		Weedle(){cout << "Weedle created" << name << endl; name = "Weedle"; catchDifficulty = 90;};
		Weedle(string n){name = n; hp = 11.0; maxHP = 11.0; vecele = {Bug, Poison};
                    moveset = {{"Bug Bite", 6.0, Bug}, {"Poison Sting", 5.0, Poison}};
                    lvl = 2; catchDifficulty = 90;};
		~Weedle() = default;

		void sound(){
			cout << name << ": Weedle!" << endl;
		}

    void draw() {
      renderArt("ascii_art/weedle.asciiart", RENDER_DELAY);
      print_stats();
    }
};

class Caterpie : public PokemonBase {
	public:
		Caterpie(){cout << "Caterpie created" << name << endl; name = "Caterpie"; catchDifficulty = 90;};
		Caterpie(string n){name = n; hp = 13.0; maxHP = 13.0; vecele = {Bug};
                      moveset = {{"Bug Bite", 6.0, Bug}, {"Tackle", 3.0, Normal}};
                      lvl = 3; catchDifficulty = 90;};
		~Caterpie() = default;

		void sound(){
			cout << name << ": Caterpie!" << endl;
		}

    void draw() {
      renderArt("ascii_art/caterpie.asciiart", RENDER_DELAY);
      print_stats();
    }
};

class Growlithe : public PokemonBase {
	public:
		Growlithe(){cout << "Growlithe created" << name << endl; name = "Growlithe"; catchDifficulty = 50;};
		Growlithe(string n){name = n; hp = 21.0; maxHP = 21.0; vecele = {Fire};
                       moveset = {{"Bite", 6.0, Dark}, {"Ember", 12.0, Fire}};
                       lvl = 7; catchDifficulty = 50;};
		~Growlithe() = default;

		void sound(){
			cout << name << ": Growlithe!" << endl;
		}

    void draw() {
      renderArt("ascii_art/growlithe.asciiart", RENDER_DELAY);
      print_stats();
    }
};

class Bellsprout : public PokemonBase {
	public:
		Bellsprout(){cout << "Bellsprout created" << name << endl; name = "Bellsprout"; catchDifficulty = 65;};
		Bellsprout(string n){name = n; hp = 12.0; maxHP = 12.0; vecele = {Grass, Poison};
                        moveset = {{"Vine Whip", 7.0, Grass}, {"Power Whip", 13.0, Grass}, {"Acid", 3.0, Poison}};
                        lvl = 5; catchDifficulty = 65;};
		~Bellsprout() = default;

		void sound(){
			cout << name << ": Bellsprout!" << endl;
		}

    void draw() {
      renderArt("ascii_art/bellsprout.asciiart", RENDER_DELAY);
      print_stats();
    }
};

class Abra : public PokemonBase {
	public:
		Abra(){cout << "Abra created" << name << endl; name = "Abra"; catchDifficulty = 60;};
		Abra(string n){name = n; hp = 19.0; maxHP = 19.0; vecele = {Psychic};
                  moveset = {{"Zen Headbutt", 12.0, Psychic}, {"Psyshock", 7.0, Psychic}, {"Shadow Ball", 10.0, Ghost}};
                  lvl = 10; catchDifficulty = 60;};
		~Abra() = default;

		void sound(){
			cout << name << ": Abra!" << endl;
		}

    void draw() {
      renderArt("ascii_art/abra.asciiart", RENDER_DELAY);
      print_stats();
    }
};

class Pidgeotto : public PokemonBase {
	public:
		Pidgeotto(){cout << "Pidgeotto created" << name << endl; name = "Pidgeotto"; catchDifficulty = 30;};
		Pidgeotto(string n){name = n; hp = 31.0; maxHP = 31.0; vecele = {Normal, Flying};
                       moveset = {{"Wing Attack", 11.0, Flying}, {"Aerial Ace", 17.0, Flying}, {"Air Cutter", 10.0, Flying}}; lvl = 21; catchDifficulty = 30;};
		~Pidgeotto() = default;

		void sound(){
			cout << name << ": Pidgeotto!" << endl;
		}

    void draw() {
      renderArt("ascii_art/pidgeotto.asciiart", RENDER_DELAY);
      print_stats();
    }
};

class Mankey : public PokemonBase {
	public:
		Mankey(){cout << "Mankey created" << name << endl; name = "Mankey"; catchDifficulty = 35;};
		Mankey(string n){name = n; hp = 23.0; maxHP = 23.0; vecele = {Fight};
                    moveset = {{"Karate Chop", 17.0, Fight}, {"Scratch", 7.0, Normal},};
                    lvl = 15; catchDifficulty = 35;};
		~Mankey() = default;

		void sound(){
			cout << name << ": Mankey!" << endl;
		}

    void draw() {
      renderArt("ascii_art/mankey.asciiart", RENDER_DELAY);
      print_stats();
    }
};

class Ekans : public PokemonBase {
	public:
		Ekans(){cout << "Ekans created" << name << endl; name = "Ekans"; catchDifficulty = 40;};
		Ekans(string n){name = n; hp = 28.0; maxHP = 28.0; vecele = {Poison};
                   moveset = {{"Acid", 8.0, Poison}, {"Poison Sting", 9.0, Poison}, {"Poison Fang", 7.0, Poison}};
                   lvl = 22; catchDifficulty = 40;};
		~Ekans() = default;

		void sound(){
			cout << name << ": Ekans!" << endl;
		}

    void draw() {
      renderArt("ascii_art/ekans.asciiart", RENDER_DELAY);
      print_stats();
    }
};

class Sandshrew : public PokemonBase {
	public:
		Sandshrew(){cout << "Sandshrew created" << name << endl; name = "Sandshrew"; catchDifficulty = 30;};
		Sandshrew(string n){name = n; hp = 33.0; maxHP = 33.0; vecele = {Ground};                        
                       moveset = {{"Mud Shot", 11.0, Ground}, {"Scratch", 4.0, Normal}, {"Dig", 7.0, Ground}};
                       lvl = 23; catchDifficulty = 30;};
		~Sandshrew() = default;

		void sound(){
			cout << name << ": Sandshrew!" << endl;
		}
    
    void draw() {
      renderArt("ascii_art/sandshrew.asciiart", RENDER_DELAY);
      print_stats();
    }
};

class Machop : public PokemonBase {
	public:
		Machop(){cout << "Machop created" << name << endl; name = "Machop"; catchDifficulty = 20;};
		Machop(string n){name = n; hp = 41.0; maxHP = 41.0; vecele = {Fight};
                    moveset = {{"Karate Chop", 20.0, Fight}, {"Brick Break", 17.0, Fight}, {"Rock Smash", 15.0, Fight}};
                    lvl = 24; catchDifficulty = 20;};
		~Machop() = default;

		void sound(){
			cout << name << ": Machop!" << endl;
		}

    void draw() {
      renderArt("ascii_art/machop.asciiart", RENDER_DELAY);
      print_stats();
    }
};

class Weepinbell : public PokemonBase {
	public:
		Weepinbell(){cout << "Weepinbell created" << name << endl; name = "Weepinbell"; catchDifficulty = 20;};
		Weepinbell(string n){name = n; hp = 47.0; maxHP = 47.0; vecele = {Grass, Poison}; 
                        moveset = {{"Acid", 4.0, Poison}, {"Power Whip", 17.0, Grass}, {"Bullet Seed", 14.0, Grass}, {"Seed Bomb" ,20.0, Grass}}; lvl = 47; catchDifficulty = 20;};
		~Weepinbell() = default;

		void sound(){
			cout << name << ": Weepinbell!" << endl;
		}

    void draw() {
      renderArt("ascii_art/weepinbell.asciiart", RENDER_DELAY);
      print_stats();
    }
};

class Venonat : public PokemonBase {
	public:
		Venonat(){cout << "Venonat created" << name << endl; name = "Venonat"; catchDifficulty = 35;};
		Venonat(string n){name = n; hp = 21.0; maxHP = 21.0; vecele = {Bug, Poison};
                     moveset = {{"Bug Bite", 7.0, Bug}, {"Signal Beam", 17.0, Bug}, {"Poison Fang", 22.0, Poison}};
                     lvl = 35; catchDifficulty = 35;};
		~Venonat() = default;

		void sound(){
			cout << name << ": Venonat!" << endl;
		}

    void draw() {
      renderArt("ascii_art/venonat.asciiart", RENDER_DELAY);
      print_stats();
    }
};

class Onix : public PokemonBase {
	public:
		Onix(){cout << "Onix created" << name << endl; name = "Onix"; catchDifficulty = 5;};
		Onix(string n){name = n; hp = 110.0; maxHP = 110.0; vecele = {Rock, Ground};
                  moveset = {{"Tackle", 12.0, Normal}, {"Rock Throw", 30.0, Rock}, {"Rock Slide", 35.0, Rock}};
                  lvl = 47; catchDifficulty = 5;};
		~Onix() = default;

		void sound(){
			cout << name << ": Onix!" << endl;
		}

    void draw() {
      renderArt("ascii_art/onix.asciiart", RENDER_DELAY);
      print_stats();
    }
};

class Slowbro : public PokemonBase {
	public:
		Slowbro(){cout << "Slowbro created" << name << endl; name = "Slowbro"; catchDifficulty = 15;};
		Slowbro(string n){name = n; hp = 50.0; maxHP = 50.0; vecele = {Water, Psychic};
                     moveset = {{"Water Gun", 7.0, Water}, {"Confusion", 20.0, Psychic}, {"Surf", 40.0, Water}, {"Ice Beam", 22.0, Ice}}; lvl = 65; catchDifficulty = 15;};
		~Slowbro() = default;

		void sound(){
			cout << name << ": Slowbro!" << endl;
		}

    void draw() {
      renderArt("ascii_art/slowbro.asciiart", RENDER_DELAY);
      print_stats();
    }
};

class Gyarados : public PokemonBase {
	public:
		Gyarados(){cout << "Gyarados created" << name << endl; name = "Gyarados"; catchDifficulty = 5;};
		Gyarados(string n){name = n; hp = 130.0; maxHP = 130.0; vecele = {Water, Flying};
                      moveset = {{"Waterfall", 16.0, Water}, {"Hydro Pump", 47.0, Water}, {"Bite", 6.0, Dark}, {"Twister", 70.0, Dragon}};
                      lvl = 412; catchDifficulty = 5;};
		~Gyarados() = default;

		void sound(){
			cout << name << ": Gyarados!" << endl;
		}

    void draw() {
      renderArt("ascii_art/gyarados.asciiart", RENDER_DELAY);
      print_stats();
    }
};