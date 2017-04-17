#include "parc.h"


parc::parc(){ m_listePI = vector<pointDInteret*>(); m_coutTotal = 0; };
parc::parc(vector<pointDInteret*> listPI){ m_listePI = listPI;  m_coutTotal = 0; };
parc::~parc(){ m_listeSentiers.clear(); };
void parc::addPointDinteret(pointDInteret* pi){ m_listePI.push_back(pi); };
void parc::addSentier(sentier* sentier){ m_listeSentiers.push_back(sentier); m_coutTotal += sentier->cout(); };
void parc::addSentier(pointDInteret* origin, pointDInteret* destination){ addSentier(new sentier(origin, destination)); };

//1. Pour chaque point d’intérêt, il doit exister un chemin qui le relie à une entrée du parc.
bool parc::verifContrainte1(){ return true; };
//2. Chaque entrée de parc doit être le départ d’au moins un sentier.
bool parc::verifContrainte2(){ return true; };
//3. Les points étape doivent avoir au moins 2 sentiers incidents.
bool parc::verifContrainte3(){ return true; };
//4. Les points de vue ne sont accessibles que par un seul sentier.
bool parc::verifContrainte4(){ return true; };
//5. Chaque point d’intérêt possède un nombre limité de sentiers incidents.
bool parc::verifContrainte5(){ return true; };