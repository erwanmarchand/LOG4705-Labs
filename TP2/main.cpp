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
static enum Algorithmes {
	algoVorace,
	algoDynamique,
	algoRetourArriere
};

class Node {
private:
	int m_id;
	bool m_visited;
	int m_indegree;
	int m_outdegree;
	
public:
	Node(int id){ m_id = id; m_indegree = 0; m_outdegree = 0; m_visited = false; };
	void incrementeIndegree(){ m_indegree++; };
	void incrementeOutdegree(){ m_outdegree++; };
	void decrementeIndegree(){ m_indegree--; };
	void decrementeOutdegree(){ m_outdegree--; };
	int indegree(){ return m_indegree; };
	int outdegree(){ return m_outdegree; };
	void setid(int id){ m_id = id; };
	int id() { return m_id; };
	void setvisited(bool visited){ m_visited = visited; };
	bool getVisited(){ return m_visited; };
};

class Arc {
private:
	Node* m_origin;
	Node* m_destination;
public:
	Arc(){};
	Arc(Node* origin, Node* destination){ m_origin = origin; m_destination = destination; origin->incrementeOutdegree(); destination->incrementeIndegree(); };
	void setorigin(Node* origin){ m_origin = origin; origin->incrementeOutdegree(); };
	Node* origin() { return m_origin; };
	void setdestination(Node* destination){ m_destination = destination;  destination->incrementeIndegree(); };
	Node* destination() { return m_destination; };
};

Node* returnNodeById(vector<Node*> nodes_vector, int id){
	for (std::vector<Node*>::const_iterator it = nodes_vector.begin(); it != nodes_vector.end(); ++it){
		if ((*it)->id() == id)
			return (*it);
	}
	return NULL;
}

void removeNodeAndIncidentArcs(vector<Node*>& nodes, vector<Arc*>& arcs, Node* nodeToRemove){

	//  remove all incident arcs from G;
	std::vector<Arc*>::const_iterator itt = arcs.begin();
	while (itt != arcs.end())
	{
		if ((*itt)->origin() == nodeToRemove || (*itt)->destination() == nodeToRemove)
		{
			itt = arcs.erase(itt);
		}
		else {
			++itt;
		}
	}
	// remove all vertices in c from G
	if (std::find(nodes.begin(), nodes.end(), nodeToRemove) != nodes.end())
	{
		nodes.erase(std::find(nodes.begin(), nodes.end(), nodeToRemove));
	}

}

bool nodeHasParent(vector<Arc*> arcs, Node* node){

	std::vector<Arc*>::const_iterator itt = arcs.begin();
	while (itt != arcs.end())
	{
		if ((*itt)->destination() == node)
		{
			return true;
		}
		++itt;
	}
	return false;

}

/* Algorithm 1: longestChain
*  input : directed acyclic graph G(V; A)
*  output : longest chain c in G*/
vector<Node*> longestChain(vector<Node*> nodes, vector<Arc*> arcs){
	map<Node*, Node*> predecessors;
	//forall the v in V do
	for (std::vector<Node*>::const_iterator it = nodes.begin(); it != nodes.end(); ++it){
		//  pred[v] <- -1;
		predecessors[(*it)] = NULL;
	}
	deque<Node*> Queue;
	//initialize queue Q with{ v in V : indegree(v) = 0 };
	for (std::vector<Node*>::const_iterator it = nodes.begin(); it != nodes.end(); ++it){
		if ((*it)->indegree() == 0)
			Queue.push_back((*it));
	}
	//last  <- -1;
	Node* last = NULL;
	//while Q is not empty do
	while (Queue.size() > 0){
		//  remove vertex u from the front of Q;
		//  last  <- u;
		last = Queue.front();
		Queue.pop_front();
		//  forall the arcs(u; v) in A do
		for (std::vector<Arc*>::const_iterator it = arcs.begin(); it != arcs.end(); ++it){
			if ((*it)->origin() == last){
				//    pred[v] <- u;
				predecessors[(*it)->destination()] = last;
				//    if Q contains v then
				if (std::find(Queue.begin(), Queue.end(), (*it)->destination()) != Queue.end())
				{
					//      move v to the end of Q;
					Queue.erase(std::find(Queue.begin(), Queue.end(), (*it)->destination()));
					Queue.push_back((*it)->destination());
				}
				//    else
				else {
					//      add v at the end of Q;
					Queue.push_back((*it)->destination());
				}
			}
		}
	}
	//c <- <>;
	vector<Node*> result;
	//while last different de -1 do
	while (last != NULL){
		//  push last on c;
		result.push_back(last);
		//  last <- pred[last];
		last = predecessors[last];
	}

	return result;
}

/*Algorithm 2: D�composition vorace en cha�nes
*input : Poset(P; <) represented as a reduced dag G
*	output : list L of chains*/
vector<vector<Node*>> voraceAlgorithm(vector<Node*> nodes, vector<Arc*> arcs){
	//L <- <>;
	vector<vector<Node*>> L;
	//c <- longestChain(G);
	vector<Node*> c = longestChain(nodes, arcs);
	//while c not empty do
	while (c.size() > 0){
		//  remove all vertices in c and incident arcs from G;
		for (std::vector<Node*>::const_iterator it = c.begin(); it != c.end(); ++it){
			removeNodeAndIncidentArcs(nodes, arcs, (*it));
		}
		//  push c on L;
		L.push_back(c);
		//  c <- longestChain(G);
		c = longestChain(nodes, arcs);
	}
	//forall the v in G do
	for (std::vector<Node*>::const_iterator it = nodes.begin(); it != nodes.end(); ++it){
		//  push <v> on L;
		vector<Node*> temp;
		temp.push_back(*it);
		L.push_back(temp);
	}
	return L;
}




/*Algorithm 3: Algorithme de retour arri�re
*  input : directed acyclic graph G(V; A)
*  output : number of permutation*/
void retourArriereReccu(vector<Node*> nodes, vector<Arc*> arcs, int& result){
	bool flag = false;

	for (std::vector<Node*>::const_iterator it = nodes.begin(); it != nodes.end(); ++it){

		if ((*it)->indegree() == 0 && !(*it)->getVisited())
		{

			for (std::vector<Arc*>::const_iterator itt = arcs.begin(); itt != arcs.end(); ++itt){
				if ((*itt)->origin() == (*it)){
					(*itt)->destination()->decrementeIndegree();
				}
			}


			(*it)->setvisited(true);
			retourArriereReccu(nodes, arcs, result);
			(*it)->setvisited(false);


			for (std::vector<Arc*>::const_iterator itt = arcs.begin(); itt != arcs.end(); ++itt){
				if ((*itt)->origin() == (*it)){
					(*itt)->destination()->incrementeIndegree();
				}
			}
			flag = true;
		}
	}

	if (!flag)
	{
		result++;
		cout << result << endl;
	}
}


int retourArriere(vector<Node*> nodes, vector<Arc*> arcs){

	for (std::vector<Node*>::const_iterator it = nodes.begin(); it != nodes.end(); ++it){
		(*it)->setvisited(false);
	}
	int result = 0;
	retourArriereReccu(nodes, arcs, result);
	return result;
}


/*Algorithm 4: Algorithme de programmation dynamique
*  input : directed acyclic graph G(V; A)
*  output : number of permutation*/
int dynamicAlgorithm(vector<Node*> nodes, vector<Arc*> arcs){
	if (nodes.size() == 0)
		return 1;
	int result = 0;
	vector<Node*> nodesTemp = nodes;
	vector<Arc*> arcsTemp = arcs;
	for (std::vector<Node*>::const_iterator it = nodes.begin(); it != nodes.end(); ++it){
		if (!nodeHasParent(arcs, (*it))){
			removeNodeAndIncidentArcs(nodesTemp, arcsTemp, (*it));
			result += dynamicAlgorithm(nodesTemp, arcsTemp);
			nodesTemp = nodes;
			arcsTemp = arcs;
		}
	}
	return result;
}

// Fonction pour lire un fichier
void readFile(string path, vector<Node*>& nodes_vector, vector<Arc*>& arcs_vector){

	int numberOfNodes = 0;
	string delimiter = " ";
	string token1;
	string token2;

	string line;
	ifstream myfile(path);
	if (myfile.is_open())
	{
		getline(myfile, line);
		token1 = line.substr(0, line.find(delimiter));
		line.erase(0, line.find(delimiter) + delimiter.length());
		token2 = line;
		//cout << "numberOfNodes:" << token1 << "-numberOfArcs:" << token2 << '\n';
		numberOfNodes = atoi(token1.c_str());

		/*nodes_vector.push_back(new Node(0));
		nodes_vector.push_back(new Node(1));
		nodes_vector.push_back(new Node(2));
		nodes_vector.push_back(new Node(3));
		arcs_vector.push_back(new Arc(returnNodeById(nodes_vector, 1), returnNodeById(nodes_vector, 3)));
		arcs_vector.push_back(new Arc(returnNodeById(nodes_vector,2), returnNodeById(nodes_vector, 3)));
		arcs_vector.push_back(new Arc(returnNodeById(nodes_vector, 2), returnNodeById(nodes_vector, 0)));*/

		for (int i = 0; i < numberOfNodes; i++){
			nodes_vector.push_back(new Node(i));
		}

		while (getline(myfile, line))
		{
			//cout << "line:" << line << endl;
			token1 = line.substr(0, line.find(delimiter));
			line.erase(0, line.find(delimiter) + delimiter.length());
			token2 = line;
			returnNodeById(nodes_vector, 1);
			//cout << "token1:"<<token1<<"-token2:"<<token2<< '\n';
			arcs_vector.push_back(new Arc(returnNodeById(nodes_vector, atoi(token1.c_str())), returnNodeById(nodes_vector, atoi(token2.c_str()))));
		}
		myfile.close();
	}

	else cout << "Unable to open file";
}


int main(int argc, const char * argv[]) {

	vector<Node*> nodes;
	vector<Arc*> arcs;

	std::chrono::time_point<std::chrono::system_clock> departChargement, departTri, finChargement, finTri;

	std::map<std::string, Algorithmes> mapAlgo;

	mapAlgo["vorace"] = algoVorace;
	mapAlgo["dynamique"] = algoDynamique;
	mapAlgo["retourArriere"] = algoRetourArriere;


	/*if (argc >= 3){


		string choixAlgorithme = argv[1];
		string chemin = argv[2];
		bool afficherNbExtensions = false;
		bool afficherTemps = false; */

			//DEBUG
			string choixAlgorithme = "retourArriere";
			string chemin = "C:\\Users\\erwan\\Desktop\\boulot\\session_8\\INF4705\\TPs\\TP2\\poset14\\poset14-6j";
			bool afficherNbExtensions = false;
			bool afficherTemps = false;
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

		unsigned long long dureeExecution = 0;

		readFile(chemin, nodes, arcs);
		
		vector<vector<Node*>> L;
		int nbrPermut = 0;

		finChargement = std::chrono::high_resolution_clock::now();

		switch (mapAlgo[choixAlgorithme]) {

		case algoVorace:
			departTri = std::chrono::high_resolution_clock::now();
			L = voraceAlgorithm(nodes, arcs);
			finTri = std::chrono::high_resolution_clock::now();
			dureeExecution += std::chrono::duration_cast<std::chrono::milliseconds>(finTri - departTri).count();
			break;

		case algoDynamique:
			departTri = std::chrono::high_resolution_clock::now();
			nbrPermut = dynamicAlgorithm(nodes, arcs);
			finTri = std::chrono::high_resolution_clock::now();
			dureeExecution += std::chrono::duration_cast<std::chrono::milliseconds>(finTri - departTri).count();
			break;

		case algoRetourArriere:
			departTri = std::chrono::high_resolution_clock::now();
			nbrPermut = retourArriere(nodes, arcs);
			finTri = std::chrono::high_resolution_clock::now();
			dureeExecution += std::chrono::duration_cast<std::chrono::milliseconds>(finTri - departTri).count();
			break;


		default:
			cout << "Algorithme incorrect" << endl;
			break;
		}

		long dureeChargement = std::chrono::duration_cast<std::chrono::milliseconds>(finChargement - departChargement).count();


		for (std::vector<Arc*>::const_iterator it = arcs.begin(); it != arcs.end(); ++it){
			delete(*it);
		}

		for (std::vector<Node*>::const_iterator it = nodes.begin(); it != nodes.end(); ++it){
			delete(*it);
		}

		// Afficher le temps d'execution
		if (afficherTemps){
			/*cout << "Temps pour chargement : " << dureeChargement <<"micros"<< endl;
			cout << "Temps pour tri : " << dureeExecution << "nanos" << endl<<endl;*/
			cout << dureeExecution<<endl;
		}

		// Afficher le resultat supposement trie
		if (afficherNbExtensions){
			cout << nbrPermut << endl;
		}


	//}
	
	return 0;
}