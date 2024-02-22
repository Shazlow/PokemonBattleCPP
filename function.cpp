#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <thread>
#include <chrono>
#include <fstream>
#include <cstdlib>

using namespace std;

void renderArt(string filename,double render_delay);
void print_delay(string line, double second);

void renderArt(string filename,double render_delay){

  ifstream file(filename);

  if (!file) {
        cerr << "Failed to open file: " << filename << endl;
        return;
    }
    
  string line;

  while (getline(file,line)){
    print_delay(line,render_delay);
  }

  file.close();
}

//delays message to cout
void print_delay(string line, double second) {
  this_thread::sleep_for(chrono::duration<double>(second));
  cout << line << endl;
  
}

bool inputYN(){
      string input;
      cin >> input;
      if(input == "y"){
         return true;
      } else if(input == "n"){
        return false;
      } else {
        cout << "Error, invalid input. Please enter a valid input(y/n):" << endl;
        return inputYN();
      }
}

bool percent_chance(int percentChance) {
    int i = rand()%100;
    return i < percentChance;
    
}


void clear_console() {
  system("cls");
}



///////////////////////
///not used anymore////
///////////////////////
void random_generator(vector<string> vec) {
  /*
   case 0:
      Charmander obj("Chamander");
      Pokemonptr Chamanderptr = make_unique<Charmander>(obj);
      return Chamanderptr;
      {"Rattata", "Pidgey", "Spearow", "Weedle", "Caterpie", "Growlithe", "Bellsprout", "Abra", "Pidgeotto", "Mankey", "Ekans", "Sandshrew", "Machop", "Weepinbell", "Venonat", "Onix", "Slowpoke", "Gyarados"}
  */
  int i = 0;
  for (auto pk: vec) {
    cout << "case " << i << ":\n";
    cout << "\t"<< pk << " obj(\"" << pk << "\");\n";
    cout << "\t"<<"Pokemonptr " << pk << "ptr = make_unique<" << pk << ">(obj);\n";
    cout << "\t"<<"return " << pk << "ptr;\n";
    i++;
  }

}