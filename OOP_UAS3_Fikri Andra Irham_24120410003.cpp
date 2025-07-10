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
        string playerId;
        string teamId;
        string position;
        int jerseyNumber;
        double marketValue;
        string status;
    public:
        Player(string pId, string fName, string lName, string dob, string nation, int jNum, string pos)
            : Person(pId, fName, lName, dob, nation), playerId(pId), jerseyNumber(jNum), position(pos), marketValue(0), status("Active") {}
        void train() { cout<<getFullName()<<" sedang berlatih."<<endl; }
        void playMatch() { cout<<getFullName()<<" (Jersey #"<<jerseyNumber<<") sedang bermain."<<endl; }
    };

class Coach : public Person {
    private:
        string coachId;
        string teamId;
        string role;
        string licenseLevel;
    public:
        Coach(string pId, string fName, string lName, string dob, string nation, string license, string role)
            : Person(pId, fName, lName, dob, nation), coachId(pId), role(role), licenseLevel(license) {}
        void conductTraining() { cout<<role<<" "<<getFullName()<<" sedang memimpin latihan."<<endl; }
        void selectSquad() { cout<<getFullName()<<" sedang memilih skuad."<<endl; }
        string getRole() const { return role; }
    };

class Staff : public Person {
    private:
        string staffId;
        string clubId;
        string role;
        string department;
    public:
        Staff(string pId, string fName, string lName, string dob, string nation, string dept, string role)
            : Person(pId, fName, lName, dob, nation), staffId(pId), department(dept), role(role) {}
        void performDuties() { cout<<getFullName()<<" sedang bekerja di "<<department<<"."<<endl; }
    };

class Stadium {
    private:
        string stadiumId;
        string name;
        int capacity;
        string address;
    public:
        Stadium(string id, string name, int cap, string addr) : stadiumId(id), name(name), capacity(cap), address(addr) {}
        void hostMatch(Match& match) {}
        string getName() const { return name; }
    };

class Team {
    private:
        string teamId;
        string clubId;
        string name;
        string league;
        string division;
        vector<Player*> players;
        Coach* ledByCoach;
        vector<TrainingSession*> trainingSessions;
        vector<Match*> matches;
    public:
        Team(string id, string name, string clubId) : teamId(id), name(name), clubId(clubId), ledByCoach(nullptr) {}
        void addPlayer(Player* player) { players.push_back(player); }
        void removePlayer(Player* player) {}
        void scheduleTraining(TrainingSession* session) {}
        void setCoach(Coach* coach) { this->ledByCoach = coach; }
        void printTeamInfo() {
            cout<<"\nInfo Tim: "<<this->name<<" (Klub: "<<this->clubId<<")"<<endl;
            if (ledByCoach) { cout<<"  Dipimpin oleh: "<<ledByCoach->getFullName()<<" ("<<ledByCoach->getRole()<<")"<<endl; }
            cout<<"  Jumlah Pemain: "<<players.size()<<endl;
        }
        string getName() const { return name; }
    };

class Sponsor {
    private:
        string sponsorId;
        string name;
        string contactPerson;
        string phone;
        string email;
        double contractValue;
        string contractStartDate;
        string contractEndDate;
    public:
        Sponsor(string id, string n) : sponsorId(id), name(n) {}
        void renewContract(string newEndDate, double newValue) {}
    };

class Contract {
    private:
        string contractId;
        string clubId;
        string personId;
        string startDate;
        string endDate;
        double salary;
        string clauses;
    public:
        Contract(string id) : contractId(id) {}
        void renew() {}
        void terminate() {}
    };

class TrainingSession {
    private:
        string sessionId;
        string teamId;
        string sessionDate;
        string sessionTime;
        string location;
        string focusArea;
    public:
        TrainingSession(string id) : sessionId(id) {}
        void recordAttendance(Player& player, bool present) {}
    };

class Match {
    private:
        string matchId;
        string homeTeamId;
        string awayTeamId;
        string matchDate;
        string matchTime;
        string stadiumId;
        int homeScore;
        int awayScore;
        string competition;
        string seasonId;
    public:
        Match(string id) : matchId(id), homeScore(0), awayScore(0) {}
        void recordScore(int home, int away) { this->homeScore = home; this->awayScore = away; }
        map<string, string> generateReport() { return map<string, string>(); }
    };

class Season {
    private:
        string seasonId;
        int year;
        string league;
        string startDate;
        string endDate;
    public:
        Season(string id) : seasonId(id), year(0) {}
        list<Match*> getMatches() { return list<Match*>(); }
        map<string, int> getStandings() { return map<string, int>(); }
    };

class Club {
    private:
        string clubId;
        string name;
        string stadiumId;
        string foundingDate;
        double budget;
        string league;
        Stadium ownedStadium;
        vector<Team> teams;
        vector<Sponsor*> sponsors;
        vector<Staff*> staffMembers;
        list<Contract*> issuedContracts;
    public:
        Club(string id, string name, string date, const Stadium& stadium) : clubId(id), name(name), foundingDate(date), ownedStadium(stadium), budget(0) {}
        void manageBudget() {}
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