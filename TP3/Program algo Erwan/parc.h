#pragma once
#include "sentier.h"

class parc
{
private:
	vector<sentier*> m_listeSentiers;
	double m_coutTotal;

public:
	vector<pointDInteret*> m_listeEntree;
	vector<pointDInteret*> m_listeEtapeNonPlacee;
	vector<pointDInteret*> m_listeEtapePlacee;
	vector<pointDInteret*> m_listePDVNonPlacee;
	vector<pointDInteret*> m_listePDVPlacee;

	parc();
	parc(vector<pointDInteret*> listPI);
	~parc();
	//void addPointDinteret(pointDInteret* pi);
	void addSentier(sentier* sentier);
	void addSentier(pointDInteret* origin, pointDInteret* destination);

	//1. Pour chaque point d’intérêt, il doit exister un chemin qui le relie à une entrée du parc.
	bool verifContrainte1();
	//2. Chaque entrée de parc doit être le départ d’au moins un sentier.
	bool verifContrainte2();
	//3. Les points étape doivent avoir au moins 2 sentiers incidents.
	bool verifContrainte3();
	//4. Les points de vue ne sont accessibles que par un seul sentier.
	bool verifContrainte4();
	//5. Chaque point d’intérêt possède un nombre limité de sentiers incidents.
	bool verifContrainte5();

	bool verifAllContraintes();

	void executeAllVerifications();

	void print();

	double coutTotal(){ return m_coutTotal; }

};

