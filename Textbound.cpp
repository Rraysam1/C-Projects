#include <functional>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string currentLocation = "villageSquare";
vector<string> inventory;
vector<string> shop = {"sword", "chestplate", "helmet", "bow_and_arrows", "magic ring"};
vector<string> forestItems = {"potion", "berries"};
string homeItem = "bed";     

bool hasSword = false;    // Tracks if player is carrying a sword                                                                                                                                      
bool hasPotion = false;   // Tracks if player is carrying potions   

//actions                                                                                                                                                                                              
void get(string noun);                                                                                                                                                                                
void drop(string noun);                                                                                                                                                                               
void handleDropPotion();                                                                                                                                                                               
void location(string& currentLocation, vector<string>& shopItems, vector<string>& forestItem, string homeItem);

//direction handling
void move_N(string& currentLocation);                                                                                                                                                     
void move_S(string& currentLocation);                                                                                                                                                     
void move_E(string& currentLocation);                                                                                                                                                     
void move_W(string& currentLocation);

template<typename T>
vector<T> filter(vector<T> v, function<bool(T)> p) {
    for (size_t i = 0; i < v.size(); ) {
        if (!p(v[i])) {
            v.erase(v.begin() + i);  
        } else {
            ++i;  // increment only if we do not erase
        }
    }
    return v;
}


int main(){
  string playerName;

  cout << "\t*****WELCOME TO TEXTBOUND*****\n\n";                                                                                                                                                    
  cout << "You have spawned in the village square.\nWhat is your name adventurer? ";                                                                                                                                  
  getline(cin, playerName);                                                                                                                                  

  cout << "\nWelcome, " << playerName << "!\n\n";                                                                   
  location(currentLocation, shop, forestItems, homeItem);

  cout << "A shopkeeper stands nearby, and the area is bustling with people.\n";                             
  cout << "Let's get some gear and go on an adventure!\n";

  while(true){
    string line;
    getline(cin, line);

    size_t spacePos = line.find(' ');
    string verb;
    string noun;

    if (spacePos != string::npos) {
      verb = line.substr(0, spacePos);
      noun = line.substr(spacePos + 1);
    } 
    else {
    verb = line;    // The whole input is verb if no space found
    noun = "";
    }

     if (verb == "look") {
       cout << "Which direction would you like to look? ";       
     }     
      else if(verb == "get"){
        get(noun);
     } 
      else if(verb == "drop"){
        drop(noun);
     }           
      else if (verb == "move") {
            if (noun == "north") move_N(currentLocation);
            else if (noun == "south") move_S(currentLocation);
            else if (noun == "east") move_E(currentLocation);
            else if (noun == "west") move_W(currentLocation);
            else cout << "Unknown direction.\n";
      }
      else if(verb == "drop" && noun == "potion"){
        handleDropPotion();
     }  
  }
}
void get(string noun){
  inventory.push_back(noun);
  cout << noun << " has been added to inventory.";
    
    if(noun == "sword"){
      cout << "The sword is a bit rusty but useable.";
      hasSword = true;
    }

    if(noun == "potion"){
      cout << "A glowing red health potion. It has healing abilities"; 
      hasPotion = true;
    }
}

void removeItemFromInventory(const string& item) {
    vector<string> newInventory;
    for (const string& i : inventory) {
        if (i != item) {
            newInventory.push_back(i);
        }
    }
    inventory = newInventory;
}

void drop(string noun){
    if (noun == "sword"){
        if (hasSword){
            removeItemFromInventory(noun);
            hasSword = false;
            cout << "You drop the sword. \n";
        }
        else{
            cout << "You're not carrying a sword.\n";
        }    
    } else if (noun == "potion"){
        if (hasPotion){
            removeItemFromInventory(noun);
            hasPotion = false;
            cout << "You dropped the potion.\n";
        } else {
            cout << "You don't have a potion to drop.\n";
        }
    }
}

void handleDropPotion(){
  if(hasPotion){
    hasPotion = false;
      cout << "You dropped the potion.\n";
  }
}


//Directions to move between locations
void move_N(string& currentLocation){
  if(currentLocation == "villageSquare"){
    currentLocation = "forest";
    cout << "You enter the forest.\n";
    location(currentLocation, shop, forestItems, homeItem);
  } else {
    cout << "You can't move north from here.\n";
  }
}

void move_S(string& currentLocation){
  if(currentLocation == "villageSquare"){
    currentLocation = "home";
    cout << "You head south to your home.\n";
    location(currentLocation, shop, forestItems, homeItem);
  } else {
    cout << "You can't move south from here.\n";
  }
}

void move_E(string& currentLocation){
  if(currentLocation == "villageSquare"){
    currentLocation = "shop";
    cout << "You enter the weapons shop.\n";
    location(currentLocation, shop, forestItems, homeItem);
  } else {
    cout << "You can't move east from here.\n";
  }
}

void move_W(string& currentLocation){
  if(currentLocation == "villageSquare"){
    currentLocation = "tavern";
    cout << "You enter the tavern.\n";
    location(currentLocation, shop, forestItems, homeItem);
  } else {
    cout << "You can't move west from here.\n";
  }
}



void location(string& currentLocation, vector<string>& shopItems, vector<string>& forestItem, string homeItem){
  if(currentLocation == "villageSquare"){
    cout << "You're in the village square. There's a weapon shop to your east.\n";
    cout << "The fountain in the center bubbles gently.\n";
  }
  else if(currentLocation == "shop"){
    cout << "You are at the shop. To buy an item type:  (get item_name)\n";
    if (!shopItems.empty()){
      cout << "Available items:\n";
      for (string item : shopItems) {
        cout << "- " << item << endl;
      }
    }
  }
  else if(currentLocation == "forest"){
    cout << "You're in the forest. Trees surround you.\n";
    if (!forestItems.empty()){
      cout << "You notice: \n";
      for (string item : forestItems) {
        cout << "- " << item << endl;
      }
    }
  } 
  else if(currentLocation == "home"){
    cout << "You're in your house.\n";
    if (!homeItem.empty()){
      cout << "You go to your room and lay on your " << homeItem << ".\n";
    }
  }
  else if(currentLocation == "tavern"){
    cout << "You're in the tavern. The air is filled with laughter and the smell of ale.\n";  
  }
  else{
    cout << "There is nothing special here.\n";
  }
}
