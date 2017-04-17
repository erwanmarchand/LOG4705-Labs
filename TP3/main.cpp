#include "parc.h"

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
	Parc->addSentier(listPI[1], listPI[2]);
	Parc->addSentier(listPI[2], listPI[3]);
	Parc->addSentier(listPI[3], listPI[9]);
	Parc->addSentier(listPI[0], listPI[4]);
	Parc->addSentier(listPI[4], listPI[5]);
	Parc->addSentier(listPI[5], listPI[6]);
	Parc->addSentier(listPI[6], listPI[7]);
	Parc->addSentier(listPI[6], listPI[8]);

	finChargement = std::chrono::high_resolution_clock::now();


	long dureeChargement = std::chrono::duration_cast<std::chrono::milliseconds>(finChargement - departChargement).count();




	//}
	//return 0;
	getchar();
}