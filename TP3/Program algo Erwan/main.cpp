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
			pi->generateCoutsOrdered();
		}

		myfile.close();
	}

	else cout << "Unable to open file";
}


double generateParcAlgorithm(vector<pointDInteret*> listPI, double& bestCout){

	double result = 0;

	parc* Parc = new parc(listPI);

	/*Parc->addSentier(listPI[0], listPI[1]);
	Parc->addSentier(listPI[1], listPI[2]);
	Parc->addSentier(listPI[2], listPI[3]);
	Parc->addSentier(listPI[3], listPI[9]);
	Parc->addSentier(listPI[0], listPI[4]);
	Parc->addSentier(listPI[4], listPI[5]);
	Parc->addSentier(listPI[5], listPI[6]);
	Parc->addSentier(listPI[6], listPI[7]);
	Parc->addSentier(listPI[6], listPI[8]);*/

	//On place toutes les etapes
	while (Parc->m_listeEtapeNonPlacee.size() > 0){
		//selection du point etape a place aleatoirement
		int randValue = rand() % Parc->m_listeEtapeNonPlacee.size();
		pointDInteret* piToPlace = Parc->m_listeEtapeNonPlacee[randValue];
		// pour chaque element de la liste de cout ordonné par cout, on cherche le PI deja placé ayant le cout minimum 
		//si on arrive a la fin sans avoir trouvé, on recommence tout a 0 pour eviter trop de traitement
		bool findPath = false;
		for (auto &pi : piToPlace->coutsOrdered()){
			if (!pi.first->getType()==pointDeVue && pi.first->piPlacee() && pi.first->canAcceptMoreSentier())
			{
				Parc->addSentier(piToPlace, pi.first);
				piToPlace->setPIPlacee(true);
				Parc->m_listeEtapePlacee.push_back(piToPlace);
				Parc->m_listeEtapeNonPlacee.erase(Parc->m_listeEtapeNonPlacee.begin() + randValue);
				findPath = true;
				break;
			}

		}
		if (!findPath){
			delete(Parc);
			return 0;
		}
	}

	//On place tous les PDV
	while (Parc->m_listePDVNonPlacee.size() > 0){
		//selection du point etape a place aleatoirement
		int randValue = rand() % Parc->m_listePDVNonPlacee.size();
		pointDInteret* piToPlace = Parc->m_listePDVNonPlacee[randValue];
		// pour chaque element de la liste de cout ordonné par cout, on cherche le PI deja placé ayant le cout minimum 
		//si on arrive a la fin sans avoir trouvé, on recommence tout a 0 pour eviter trop de traitement
		bool findPath = false;
		for (auto &pi : piToPlace->coutsOrdered()){
			if (!pi.first->getType() == pointDeVue && pi.first->piPlacee() && pi.first->canAcceptMoreSentier())
			{
				Parc->addSentier(piToPlace, pi.first);
				piToPlace->setPIPlacee(true);
				Parc->m_listePDVPlacee.push_back(piToPlace);
				Parc->m_listePDVNonPlacee.erase(Parc->m_listePDVNonPlacee.begin() + randValue);
				findPath = true;
				break;
			}

		}
		if (!findPath){
			delete(Parc);
			return 0;
		}
	}

	//pour chaque etape n'ayant qu'un arc incident, on trouve une etape ou entree au cout minimum et pouvant accepter encore un sentier pour la relier
	for (auto &pi : Parc->m_listeEtapePlacee){
		if (pi->getnbrSentier()<2)
		{
			bool findPath = false;
			for (auto &pi2 : pi->coutsOrdered()){
				if (!pi2.first->getType() == pointDeVue && pi2.first->canAcceptMoreSentier() && !pi->piAlreadyLinked(pi2.first))
				{
					Parc->addSentier(pi, pi2.first);
					findPath = true;
					break;
				}
			}
			if (!findPath){
				delete(Parc);
				return 0;
			}
		}

	}

	//Parc->print();

	//Parc->executeAllVerifications();

	if (Parc->verifAllContraintes())
		result = Parc->coutTotal();

	if (result > 0)
		if (result < bestCout || bestCout == 0){
			bestCout = result;
			Parc->print();
		}

	delete(Parc);

	return result;
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
	string chemin = "C:\\Users\\erwan\\Desktop\\boulot\\session_8\\INF4705\\TPs\\TP3\\TP3Data\\Parc4-40Zones.txt";
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

	departChargement = std::chrono::high_resolution_clock::now();

	unsigned long dureeExecution = 0;

	readFile(chemin, listPI);

	double saveBestCout = 0;

	while (true){
		double coutParc = generateParcAlgorithm(listPI, saveBestCout);

		/*if (coutParc > 0)
			if (coutParc < saveBestCout || saveBestCout == 0)
				saveBestCout = coutParc;*/

	}

	/*parc* Parc = new parc(listPI);

	Parc->addSentier(listPI[0], listPI[1]);
	Parc->addSentier(listPI[1], listPI[2]);
	Parc->addSentier(listPI[2], listPI[3]);
	Parc->addSentier(listPI[3], listPI[9]);
	Parc->addSentier(listPI[0], listPI[4]);
	Parc->addSentier(listPI[4], listPI[5]);
	Parc->addSentier(listPI[5], listPI[6]);
	Parc->addSentier(listPI[6], listPI[7]);
	Parc->addSentier(listPI[6], listPI[8]);

	Parc->executeAllVerifications();

	Parc->print();

	delete(Parc);*/

	finChargement = std::chrono::high_resolution_clock::now();


	long dureeChargement = std::chrono::duration_cast<std::chrono::milliseconds>(finChargement - departChargement).count();




	//}
	//return 0;
	getchar();
}