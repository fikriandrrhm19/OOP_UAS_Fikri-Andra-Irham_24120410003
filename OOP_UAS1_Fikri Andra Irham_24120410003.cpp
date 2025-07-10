#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>

using namespace std;

class Person; class Player; class Coach; class Staff;
class Team; class Club; class Stadium; class Sponsor;
class Contract; class TrainingSession; class Match; class Season;

class Person {
    protected:
        string personId;
        string firstName;
        string lastName;
        string dateOfBirth;
        string nationality;

    public:
        Person(string id, string fName, string lName, string dob, string nation)
            : personId(id), firstName(fName), lastName(lName), dateOfBirth(dob), nationality(nation) {}
        virtual ~Person() {}
        string getFullName() const { return firstName + " " + lastName; }
    };

class Player : public Person {
    private:
        int jerseyNumber;
        double marketValue;
        string playerId;
        string teamId;
        string position;
        string status;

    public:
        Player(string pId, string fName, string lName, string dob, string nation, int jNum, string pos)
            : Person(pId, fName, lName, dob, nation), jerseyNumber(jNum), marketValue(0), position(pos), status("Active") {}
        void train() { cout<<getFullName()<<" sedang berlatih."<<endl; }
        void playMatch() { cout<<getFullName()<<" (Jersey #"<<jerseyNumber<<") sedang bermain."<<endl; }
    };

class Coach : public Person {
    private:
        string licenseLevel;
        string coachId;
        string teamId;
        string role;

    public:
        Coach(string pId, string fName, string lName, string dob, string nation, string license, string role)
            : Person(pId, fName, lName, dob, nation), licenseLevel(license), role(role) {}
        void conductTraining() { cout<<role<<" "<<getFullName()<<" sedang memimpin latihan."<<endl; }
        void selectSquad() { cout<<getFullName()<<" sedang memilih skuad."<<endl; }
        string getRole() const { return role; }
    };

class Staff : public Person {
    private:
        string department;
        string staffId;
        string clubId;
        string role;

    public:
        Staff(string pId, string fName, string lName, string dob, string nation, string dept, string role)
            : Person(pId, fName, lName, dob, nation), department(dept), role(role) {}
        void performDuties() { cout<<getFullName()<<" sedang bekerja di "<<department<<"."<<endl; }
    };
class Stadium {};
class Team {};
class Club {};
class Sponsor {};
class Contract {};
class TrainingSession {};
class Match {};
class Season {};

int main() {
    return 0;
}