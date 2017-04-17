#include "parc.h"


parc::parc(){ m_listePI = vector<pointDInteret*>(); m_coutTotal = 0; };
parc::parc(vector<pointDInteret*> listPI){ m_listePI = listPI;  m_coutTotal = 0; };
parc::~parc(){ m_listeSentiers.clear(); };
void parc::addPointDinteret(pointDInteret* pi){ m_listePI.push_back(pi); };
void parc::addSentier(sentier* sentier){ m_listeSentiers.push_back(sentier); m_coutTotal += sentier->cout(); };
void parc::addSentier(pointDInteret* origin, pointDInteret* destination){ addSentier(new sentier(origin, destination)); };

//1. Pour chaque point d�int�r�t, il doit exister un chemin qui le relie � une entr�e du parc.
bool parc::verifContrainte1(){ return true; };
//2. Chaque entr�e de parc doit �tre le d�part d�au moins un sentier.
bool parc::verifContrainte2(){ return true; };
//3. Les points �tape doivent avoir au moins 2 sentiers incidents.
bool parc::verifContrainte3(){ return true; };
//4. Les points de vue ne sont accessibles que par un seul sentier.
bool parc::verifContrainte4(){ return true; };
//5. Chaque point d�int�r�t poss�de un nombre limit� de sentiers incidents.
bool parc::verifContrainte5(){ return true; };