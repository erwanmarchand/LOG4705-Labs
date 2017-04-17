#include "parc.h"


parc::parc(){ m_listePI = vector<pointDInteret*>(); m_coutTotal = 0; };

parc::parc(vector<pointDInteret*> listPI){ m_listePI = listPI;  m_coutTotal = 0; };

parc::~parc(){ 
	for (auto &sentier : m_listeSentiers) // access by reference to avoid copying
	{
		delete sentier;
	}
};

void parc::addPointDinteret(pointDInteret* pi){ m_listePI.push_back(pi); };
void parc::addSentier(sentier* sentier){ m_listeSentiers.push_back(sentier); m_coutTotal += sentier->cout(); };
void parc::addSentier(pointDInteret* origin, pointDInteret* destination){ addSentier(new sentier(origin, destination)); };

//1. Pour chaque point d’intérêt, il doit exister un chemin qui le relie à une entrée du parc.
bool parc::verifContrainte1(){ return true; }

//2. Chaque entrée de parc doit être le départ d’au moins un sentier.
bool parc::verifContrainte2(){ 
	for (auto &pi : m_listePI) // access by reference to avoid copying
	{
		if (pi->getType()==entree && pi->getnbrSentier() == 0)
			return false;
	}
	return true; 
}

//3. Les points étape doivent avoir au moins 2 sentiers incidents.
bool parc::verifContrainte3(){
	for (auto &pi : m_listePI) // access by reference to avoid copying
	{
		if (pi->getType() == etape && pi->getnbrSentier() < 2)
			return false;
	}
	return true;
}

//4. Les points de vue ne sont accessibles que par un seul sentier.
bool parc::verifContrainte4(){ 

	for (auto &pi : m_listePI) // access by reference to avoid copying
	{
		if (pi->getType() == pointDeVue && pi->getnbrSentier() != 1)
			return false;
	}
	return true;
}

//5. Chaque point d’intérêt possède un nombre limité de sentiers incidents.
bool parc::verifContrainte5(){ 
	for (auto &pi : m_listePI) // access by reference to avoid copying
	{
		if (pi->getnbrSentier() > pi->getnbrMaxSentier())
			return false;
	}
	return true; 
}


void parc::executeAllVerifications(){

	cout << "Contrainte 1 :" << endl;
	if (verifContrainte1())
		cout << "   Respectee" << endl;
	else
		cout << "   Non respectee" << endl;

	cout << "Contrainte 2 :" << endl;
	if (verifContrainte2())
		cout << "   Respectee" << endl;
	else
		cout << "   Non respectee" << endl;

	cout << "Contrainte 3 :" << endl;
	if (verifContrainte3())
		cout << "   Respectee" << endl;
	else
		cout << "   Non respectee" << endl;

	cout << "Contrainte 4 :" << endl;
	if (verifContrainte4())
		cout << "   Respectee" << endl;
	else
		cout << "   Non respectee" << endl;

	cout << "Contrainte 5 :" << endl;
	if (verifContrainte5())
		cout << "   Respectee" << endl;
	else
		cout << "   Non respectee" << endl;

	cout << endl;
}