#include "parc.h"


parc::parc(){
	m_listeEntree = vector<pointDInteret*>();
	m_listeEtapeNonPlacee = vector<pointDInteret*>();
	m_listeEtapePlacee = vector<pointDInteret*>();
	m_listePDVNonPlacee = vector<pointDInteret*>();
	m_listePDVPlacee = vector<pointDInteret*>();
	m_coutTotal = 0;
};

parc::parc(vector<pointDInteret*> listPI){
	m_listeEntree = vector<pointDInteret*>();
	m_listeEtapeNonPlacee = vector<pointDInteret*>();
	m_listeEtapePlacee = vector<pointDInteret*>();
	m_listePDVNonPlacee = vector<pointDInteret*>();
	m_listePDVPlacee = vector<pointDInteret*>();

	for (auto &pi : listPI) // access by reference to avoid copying
	{
		if (pi->getType() == entree)
			m_listeEntree.push_back(pi);
		else if (pi->getType() == pointDeVue)
			m_listePDVNonPlacee.push_back(pi);
		else if (pi->getType() == etape)
			m_listeEtapeNonPlacee.push_back(pi);
	}

	m_coutTotal = 0;
};

parc::~parc(){

	for (auto &sentier : m_listeSentiers) // access by reference to avoid copying
	{
		delete sentier;
	}

	for (auto &pi : m_listeEntree) // access by reference to avoid copying
	{
		pi->resetLinks();
	}

	for (auto &pi : m_listeEtapeNonPlacee) // access by reference to avoid copying
	{
		pi->setConnectedToEnter(false);
		pi->resetLinks();
	}

	for (auto &pi : m_listeEtapePlacee) // access by reference to avoid copying
	{
		pi->setConnectedToEnter(false);
		pi->resetLinks();
	}

	for (auto &pi : m_listePDVNonPlacee) // access by reference to avoid copying
	{
		pi->setConnectedToEnter(false);
		pi->resetLinks();
	}

	for (auto &pi : m_listePDVPlacee) // access by reference to avoid copying
	{
		pi->setConnectedToEnter(false);
		pi->resetLinks();
	}

};

//void parc::addPointDinteret(pointDInteret* pi){ m_listePI.push_back(pi); };
void parc::addSentier(sentier* sentier){ m_listeSentiers.push_back(sentier); m_coutTotal += sentier->cout(); };
void parc::addSentier(pointDInteret* origin, pointDInteret* destination){ addSentier(new sentier(origin, destination)); };

//1. Pour chaque point d’intérêt, il doit exister un chemin qui le relie à une entrée du parc.
bool parc::verifContrainte1(){
	bool change = true;
	while (change){
		change = false;
		for (auto &pi : m_listeSentiers) // access by reference to avoid copying
		{
			if (pi->origin()->connectedToEnter() && !pi->destination()->connectedToEnter()){
				change = true;
				pi->destination()->setConnectedToEnter(true);
			}
			else if (!pi->origin()->connectedToEnter() && pi->destination()->connectedToEnter()){
				change = true;
				pi->origin()->setConnectedToEnter(true);
			}
		}
	}
	for (auto &pi : m_listeEtapeNonPlacee) // access by reference to avoid copying
	{
		if (!pi->connectedToEnter()){
			return false;
		}
	}
	for (auto &pi : m_listeEtapePlacee) // access by reference to avoid copying
	{
		if (!pi->connectedToEnter()){
			return false;
		}
	}
	for (auto &pi : m_listePDVNonPlacee) // access by reference to avoid copying
	{
		if (!pi->connectedToEnter()){
			return false;
		}
	}
	for (auto &pi : m_listePDVPlacee) // access by reference to avoid copying
	{
		if (!pi->connectedToEnter()){
			return false;
		}
	}
	return true;
}

//2. Chaque entrée de parc doit être le départ d’au moins un sentier.
bool parc::verifContrainte2(){
	for (auto &pi : m_listeEntree) // access by reference to avoid copying
	{
		if (pi->getnbrSentier() == 0)
			return false;
	}
	return true;
}

//3. Les points étape doivent avoir au moins 2 sentiers incidents.
bool parc::verifContrainte3(){
	for (auto &pi : m_listeEtapeNonPlacee) // access by reference to avoid copying
	{
		if (pi->getnbrSentier() < 2)
			return false;
	}
	for (auto &pi : m_listeEtapePlacee) // access by reference to avoid copying
	{
		if (pi->getnbrSentier() < 2)
			return false;
	}
	return true;
}

//4. Les points de vue ne sont accessibles que par un seul sentier.
bool parc::verifContrainte4(){

	for (auto &pi : m_listePDVNonPlacee) // access by reference to avoid copying
	{
		if (pi->getnbrSentier() != 1)
			return false;
	}
	for (auto &pi : m_listePDVPlacee) // access by reference to avoid copying
	{
		if (pi->getnbrSentier() != 1)
			return false;
	}
	return true;
}

//5. Chaque point d’intérêt possède un nombre limité de sentiers incidents.
bool parc::verifContrainte5(){

	for (auto &pi : m_listeEntree) // access by reference to avoid copying
	{
		if (pi->getnbrSentier() > pi->getnbrMaxSentier())
			return false;
	}
	for (auto &pi : m_listeEtapeNonPlacee) // access by reference to avoid copying
	{
		if (pi->getnbrSentier() > pi->getnbrMaxSentier())
			return false;
	}
	for (auto &pi : m_listeEtapePlacee) // access by reference to avoid copying
	{
		if (pi->getnbrSentier() > pi->getnbrMaxSentier())
			return false;
	}
	for (auto &pi : m_listePDVNonPlacee) // access by reference to avoid copying
	{
		if (pi->getnbrSentier() > pi->getnbrMaxSentier())
			return false;
	}
	for (auto &pi : m_listePDVPlacee) // access by reference to avoid copying
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

bool parc::verifAllContraintes(){
	return (verifContrainte1() && verifContrainte2() && verifContrainte3() && verifContrainte4() && verifContrainte5());
}

void parc::print(){
	for (auto &se : m_listeSentiers){
		cout << se->origin()->getId() << " " << se->destination()->getId()<< endl;
	}
	cout << "cout : " << m_coutTotal<<endl;
	cout << "fin" << endl;
}
