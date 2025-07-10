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

class PersonFactory {
    public:
        virtual ~PersonFactory() {}
        virtual Person* createPerson(map<string, string>& details) const = 0;
    };

class PlayerFactory : public PersonFactory {
    public:
        Person* createPerson(map<string, string>& details) const override {
            int jerseyNumber = stoi(details["jerseyNumber"]);
            return new Player(details["id"], details["firstName"], details["lastName"], details["dob"], details["nation"], jerseyNumber, details["position"]);
        }
    };

class CoachFactory : public PersonFactory {
    public:
        Person* createPerson(map<string, string>& details) const override {
            return new Coach(details["id"], details["firstName"], details["lastName"], details["dob"], details["nation"], details["license"], details["role"]);
        }
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

class Sponsor { string sponsorId, name; public: Sponsor(string id, string n):sponsorId(id), name(n){} };
class Contract { string contractId; public: Contract(string id):contractId(id){} };
class TrainingSession { string sessionId; public: TrainingSession(string id):sessionId(id){} };
class Match { string matchId; public: Match(string id):matchId(id){} };
class Season { string seasonId; public: Season(string id):seasonId(id){} };

int main() {
    Stadium stadion("STAD01", "Stadion Cakrawala", 5000, "Jl. Kemang Timur No.1, RT.14/RW.8, Pejaten Bar., Ps. Minggu, Kota Jakarta Selatan, DKI Jakarta 12510");
    Club fcCakrawala("CLUB01", "FC Cakrawala", "2025-07-10", stadion);
    Team timMuda("TEAM-U23", "FC Cakrawala Muda", "CLUB01");

    Coach* headCoach = new Coach("C001", "Fikri", "Guardiola", "2005-09-19", "Indonesia", "UEFA Pro", "Head Coach");
    Coach* asstCoach = new Coach("C002", "Andra", "Kidd", "1999-09-09", "Indonesia", "AFC A", "Assistant Coach");

    timMuda.setCoach(headCoach);

    vector<Player*> daftarPemain;
    for (int i = 1; i <= 15; ++i) {
        string namaPemain = (i == 1) ? "Irham" : "Pemain";
        string margaPemain = (i == 1) ? "Lionel" : to_string(i);
        Player* p = new Player("P" + to_string(i), namaPemain, margaPemain, "2001-01-01", "Indonesia", i, "All-rounder");
        daftarPemain.push_back(p);
        timMuda.addPlayer(p);
    }

    fcCakrawala.addTeam(timMuda);

    fcCakrawala.printClubInfo();
    fcCakrawala.getTeam(0).printTeamInfo();

    cout<<"\n--- Simulasi Aktivitas ---"<<endl;
    headCoach->conductTraining();
    daftarPemain[0]->playMatch();

    delete headCoach;
    delete asstCoach;
    for (Player* p : daftarPemain) {
        delete p;
    }

    return 0;
}