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

class Stadium {
    private:
        string stadiumId;
        string name;
        int capacity;
        string address;

    public:
        Stadium(string id = "", string name = "", int cap = 0, string addr = "")
            : stadiumId(id), name(name), capacity(cap), address(addr) {}
        void hostMatch(Match& match) { cout<<"Stadion "<<name<<" menjadi tuan rumah pertandingan."<<endl; }
        string getName() const { return name; }
    };

class Team {
    private:
        string name;
        string teamId;
        string league;
        string division;
        string clubId;

        vector<Player*> players;
        Coach* ledByCoach;
        vector<TrainingSession*> trainingSessions;
        vector<Match*> matches;

    public:
        Team(string id = "", string name = "", string clubId = "")
            : teamId(id), name(name), clubId(clubId), ledByCoach(nullptr) {}

        void addPlayer(Player* player) { players.push_back(player); }
        void removePlayer(Player* player);
        void scheduleTraining(TrainingSession* session) { trainingSessions.push_back(session); }
        void setCoach(Coach* coach) { this->ledByCoach = coach; }

        void printTeamInfo() {
            cout<<"\nInfo Tim: "<<this->name<<" (Klub: "<<this->clubId<<")"<<endl;
            if (ledByCoach) {
                cout<<"  Dipimpin oleh: "<<ledByCoach->getFullName()<<" ("<<ledByCoach->getRole()<<")"<<endl;
            }
            cout<<"  Jumlah Pemain: "<<players.size()<<endl;
        }
        string getName() const { return name; }
    };

class Club {
    private:
        string clubId;
        string name;
        string foundingDate;
        double budget;
        string league;
        string stadiumId;

        Stadium ownedStadium;
        vector<Team> teams;
        vector<Sponsor*> sponsors;
        vector<Staff*> staffMembers;
        list<Contract*> issuedContracts;

    public:
        Club(string id, string name, string date, const Stadium& stadium)
            : clubId(id), name(name), foundingDate(date), ownedStadium(stadium) {}

        void manageBudget() { cout<<"Mengelola budget untuk "<<name<<"."<<endl; }
        void signSponsor(Sponsor* sponsor) { sponsors.push_back(sponsor); }
        list<Team> getTeams() { return list<Team>(); }
        void addTeam(const Team& team) { teams.push_back(team); }
        Team& getTeam(int index) { return teams.at(index); }

        void printClubInfo() {
            cout<<"\n------- Info Klub -------"<<endl; 
            cout<<"Nama: "<<this->name<<" (ID: "<<this->clubId<<")"<<endl;
            cout<<"Berdiri: "<<this->foundingDate<<endl;
            cout<<"Stadion: "<<this->ownedStadium.getName()<<endl;
            if (!teams.empty()) { cout<<"Mengelola Tim: "<<teams.front().getName()<<endl; }
            cout<<"--------------------------"<<endl;
        }
    };
class Sponsor {};
class Contract {};
class TrainingSession {};
class Match {};
class Season {};

int main() {
    return 0;
}