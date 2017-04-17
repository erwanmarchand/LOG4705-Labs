#pragma once
#include "sentier.h"

class parc
{
private:
	vector<pointDInteret*> m_listePI;
	vector<sentier*> m_listeSentiers;
	double m_coutTotal;

public:
	parc();
	parc(vector<pointDInteret*> listPI);
	~parc();
	void addPointDinteret(pointDInteret* pi);
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
};

