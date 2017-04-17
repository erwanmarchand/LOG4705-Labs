#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <random>
#include <cstdlib>
#include <ctime>
#include <map>
#include <deque>
#include <limits>

using namespace std;
using namespace std::chrono;

// Liste des differents algo
enum TypesDePointsDinterets {
	pointDeVue,
	entree,
	etape
};

class pointDInteret {
private:
	int m_id;
	TypesDePointsDinterets m_type;
	int m_nbrMaxSentier;
	int m_nbrSentier;
	map<pointDInteret*, double> m_couts;

public:
	pointDInteret(int id){ m_id = id; m_nbrSentier = 0; m_couts = map<pointDInteret*, double>(); };
	pointDInteret(int id, int type){
		m_id = id; m_nbrMaxSentier = 0; m_nbrSentier = 0; m_couts = map<pointDInteret*, double>();
		if (type == 1){
			m_type = pointDeVue;
		}
		else if (type == 2){
			m_type = entree;
		}
		else if (type == 3){
			m_type = etape;
		}
	};
	pointDInteret(int id, int type, int nbrMaxSentier){
		m_id = id; m_nbrMaxSentier = nbrMaxSentier; m_nbrSentier = 0; m_couts = map<pointDInteret*, double>();
		if (type == 1){
			m_type = pointDeVue;
		}
		else if (type == 2){
			m_type = entree;
		}
		else if (type == 3){
			m_type = etape;
		}
	};
	pointDInteret(int id, TypesDePointsDinterets type){ m_id = id; m_type = type; m_nbrMaxSentier = 0; m_nbrSentier = 0; m_couts = map<pointDInteret*, double>(); };
	void incrementeNbrSentier(){ m_nbrSentier++; };
	void decrementeNbrSentier(){ m_nbrSentier--; };
	int getId(){
		return m_id;
	};
	void setId(int id){
		m_id = id;
	};
	TypesDePointsDinterets getType(){
		return m_type;
	};
	void setType(TypesDePointsDinterets type){
		m_type = type;
	};
	int getnbrMaxSentier(){ return m_nbrMaxSentier; };
	void setnbrMaxSentier(int nbrMaxSentier){ m_nbrMaxSentier = nbrMaxSentier; };
	int getnbrSentier(){ return m_nbrSentier; };
	void setnbrSentier(int nbrSentier){ m_nbrSentier = nbrSentier; };

	map<pointDInteret*, double> getCouts(){
		return m_couts;
	};

	void addCout(pointDInteret* pi, double cout){
		m_couts[pi] = cout;
	};

};

class sentier{
private :
	pointDInteret* m_origin;
	pointDInteret* m_destination;
	double m_cout;

public :
	sentier(pointDInteret* origin, pointDInteret* destination){ m_origin = origin; m_destination = destination; m_cout = origin->getCouts()[destination]; };
	pointDInteret* origin() { return m_origin; };
	//void setorigin(pointDInteret* origin) { m_origin=origin; };
	pointDInteret* destination() { return m_destination; };
	//void setdestination(pointDInteret* destination) { m_destination = destination; };
};

class parc{
private:
	vector<pointDInteret*> m_listePI;
	vector<sentier*> m_listeSentiers;

public:
	parc(){ m_listePI = vector<pointDInteret*>(); };
	parc(vector<pointDInteret*> listPI){ m_listePI = listPI; };
	~parc(){ m_listeSentiers.clear(); };
	void addPointDinteret(pointDInteret* pi){ m_listePI.push_back(pi); };
	void addSentier(sentier* sentier){ m_listeSentiers.push_back(sentier); };
	void addSentier(pointDInteret* origin, pointDInteret* destination){ m_listeSentiers.push_back(new sentier(origin, destination)); };
};


// Fonction pour lire un fichier
void readFile(string path, vector<pointDInteret*>& listPI){

	int numberPointsDinteret = 0;
	string delimiter = " ";
	string token1;
	string token2;

	string line;
	string line2;
	ifstream myfile(path);
	if (myfile.is_open())
	{
		getline(myfile, line);

		numberPointsDinteret = atoi(line.c_str());

		getline(myfile, line);
		getline(myfile, line2);

		size_t pos = 0;
		size_t pos2 = 0;
		int id = 0;
		while ((pos = line.find(delimiter)) != std::string::npos && (pos2 = line2.find(delimiter)) != std::string::npos) {
			token1 = line.substr(0, pos);
			token2 = line2.substr(0, pos);
			pointDInteret* tempPI = new pointDInteret(id, atoi(token1.c_str()), atoi(token2.c_str()));
			line.erase(0, pos + delimiter.length());
			line2.erase(0, pos2 + delimiter.length());
			listPI.push_back(tempPI);
			id++;
		}
		pointDInteret* tempPI = new pointDInteret(id, atoi(line.c_str()), atoi(line2.c_str()));
		listPI.push_back(tempPI);
		
		for (auto &pi : listPI) // access by reference to avoid copying
		{
			getline(myfile, line);
			for (auto &pi2 : listPI) // access by reference to avoid copying
			{
				pos = line.find(delimiter);
				token1 = line.substr(0, pos);
				double cout = stod(token1.c_str());
				pi->addCout(pi2, cout);
				line.erase(0, pos + delimiter.length());
			}
		}

		myfile.close();
	}

	else cout << "Unable to open file";
}


int main(int argc, const char * argv[]) {

	vector<pointDInteret*> listPI;

	std::chrono::time_point<std::chrono::system_clock> departChargement, departTri, finChargement, finTri;


	/*if (argc >= 3){


	string choixAlgorithme = argv[1];
	string chemin = argv[2];
	bool afficherNbExtensions = false;
	bool afficherTemps = false; */

	//DEBUG
	string chemin = "C:\\Users\\erwan\\Desktop\\boulot\\session_8\\INF4705\\TPs\\TP3\\TP3Data\\Parc1-10Zones.txt";
	bool afficherNbExtensions = true;
	bool afficherTemps = true;
	//FIN DEBUG

	for (int i = 3; i < argc; i++){
		if (strncmp(argv[i], "-p", 2) == 0)
			afficherNbExtensions = true;
		else if (strncmp(argv[i], "-t", 2) == 0)
			afficherTemps = true;
	}


	/*cout << "Algorithme : " << choixAlgorithme << endl;
	cout << "Chemin vers serie : " << chemin << endl;
	cout << "Afficher Resultat trie : " << afficherArray << endl;
	cout << "Afficher temps : " << afficherTemps << endl;
	cout << "Le fichier possede : " << nombredElements << " nombres" << endl;*/

	//departChargement = std::chrono::high_resolution_clock::now();

	unsigned long dureeExecution = 0;

	readFile(chemin, listPI);

	parc* Parc = new parc(listPI);

	Parc->addSentier(listPI[0], listPI[1]);

	finChargement = std::chrono::high_resolution_clock::now();


	long dureeChargement = std::chrono::duration_cast<std::chrono::milliseconds>(finChargement - departChargement).count();




	//}
	//return 0;
	getchar();
}