
// Author: Salma Awan, sma9000
// hw02.cpp
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;


// class Warrior with nested class Weapon which contains weapon name and weapon strength
// contains attributes (data: warrior name, strength, weapon strength)
// contains methods (functions: "behaviors" which are the battles between warriors)
class Warrior{

    friend ostream& operator<<(ostream& os, const Warrior& aWarrior){
        os << "Warrior: " << aWarrior.warName << ", " << aWarrior.warWeapon << endl;
        return os;
    }

public:
    // constructors(initalizes the qualities of a warrior which are the warrior's name and weapon. The weapon contains the weapon name and the weaon strength)
    Warrior(const string& aName, const string& wpName, int wpStrength) : warName(aName), warWeapon( wpName,wpStrength){}
    // getter methods
    string getName() const {
        return warName; // coming from Warrior class
    }
    int getWeaponstrength(){
        return warWeapon.getWeaponstrength(); // coming from Weapon class
    }
    void changeStrength(int newStrength){
        return warWeapon.changeStrength(newStrength); // coming from Weapon class
    }
    // method called battle which puts two warriors into battle
    // depending on necessary conditions, two warriors may either both die, or one may die.
    void battle(Warrior& warrior2){

        int warStrength = getWeaponstrength();
        cout << warName << " battles " << warrior2.getName() << endl;
        if ( warStrength == 0 && warrior2.getWeaponstrength() == 0){
            cout << "Oh, NO! They're both dead! Yuck! ";
        }else if (warStrength == 0){
            cout << "He's dead, " << warrior2.getName() << endl;
        }else if (warrior2.getWeaponstrength() == 0){
            cout << "He's dead, " << warName << endl;
        }else if (warStrength == warrior2.getWeaponstrength()) {
            changeStrength(0);
            warrior2.changeStrength(0);
            cout << "Mutual Annihilation: " << warName << " and " << warrior2.getName() << " die at each other's hands" << endl;
        }else if (warStrength>warrior2.getWeaponstrength()) {
            changeStrength(warStrength-warrior2.getWeaponstrength());
            warrior2.changeStrength(0);
            cout << warName << " defeats " << warrior2.getName() << endl;
        }else if (warrior2.getWeaponstrength()> warStrength) {
            changeStrength(warrior2.getWeaponstrength()-warStrength);
            changeStrength(0);
            cout << warrior2.getName() << " defeats " << warName << endl;
        }

    }
private:
    // In Warrior class, the weapon class is created in privated since it must not be accessed by any other part of the code that is not the class
    class Weapon {
        friend ostream& operator<<(ostream& os, const Warrior::Weapon& aWeapon){
            os << "weapon: " << aWeapon.weaponName << ", " << aWeapon.weaponStrength;
            return os;
        }
    public:
        //constructor
        Weapon(const string &aName, int strength) : weaponName(aName), weaponStrength(strength) {}

        int getWeaponstrength() const{
            return weaponStrength;
        }
        void changeStrength(int strength){
            strength = weaponStrength;
        }

    private:
        string weaponName;
        int weaponStrength;

    };
    string warName;
    Weapon warWeapon;

};



//prototypes
void showStatus(vector<Warrior>& warriorInfo);
size_t findWarrior(const string& name, const vector<Warrior>& warriorInfo);


int main(){
    // attempt to open the file warriors.txt
    ifstream warriorFile("warriors.txt");
    if (!warriorFile){
        cerr << "Could not open the file.\n";
        exit(1);
    }

    // vector of warrior structs
    vector<Warrior> warriorInfo;
    string command;
    // checking for the word "warrior", "status", and "battle"
    while (warriorFile>>command){
        // if command is "warrior", create a new warrior with specified name and strength
        if (command == "Warrior"){
            string newName;
            string newWeapon;
            int weaponStrength;
            warriorFile >> newName >> newWeapon>>weaponStrength;
            warriorInfo.emplace_back(newName,newWeapon,weaponStrength);
        // if command is "status", then display all warriors, either dead or alive
        }else if (command== "Status"){
            showStatus(warriorInfo);
        // if command is "battle", cause a battle between the two warriors
        }else if (command == "Battle"){
            string warriorA;
            string warriorB;
            int locA = findWarrior(warriorA,warriorInfo);
            int locB = findWarrior(warriorB,warriorInfo);
            warriorInfo[locA].battle(warriorInfo[locB]);

        }
    }

}

// show warrior status by displaying all info (name and strength)
void showStatus(vector<Warrior>& warriorInfo) {
    cout << "There are: " << warriorInfo.size() << " warriors" << endl;
    for (const Warrior &curr_warrior: warriorInfo) {
        cout << curr_warrior;
    }
}

// findWarrior function locates warriors preparing for battle by looping through vector of warriors and returning the index of location
size_t findWarrior(const string& name, const vector<Warrior>& warriorInfo){
    for (size_t idx = 0; warriorInfo.size(); ++idx){
        if (warriorInfo[idx].getName() == name){
                    return idx;
            }
    }
    return warriorInfo.size();
}
