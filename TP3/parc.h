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

	//1. Pour chaque point d�int�r�t, il doit exister un chemin qui le relie � une entr�e du parc.
	bool verifContrainte1();
	//2. Chaque entr�e de parc doit �tre le d�part d�au moins un sentier.
	bool verifContrainte2();
	//3. Les points �tape doivent avoir au moins 2 sentiers incidents.
	bool verifContrainte3();
	//4. Les points de vue ne sont accessibles que par un seul sentier.
	bool verifContrainte4();
	//5. Chaque point d�int�r�t poss�de un nombre limit� de sentiers incidents.
	bool verifContrainte5();
};

