#pragma once
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
enum TypesDePointsDinterets {
	pointDeVue,
	entree,
	etape
};

class pointDInteret {
private:
	int m_id;
	TypesDePointsDinterets m_type;
	int m_nbrMaxSentier;
	int m_nbrSentier;
	map<pointDInteret*, double> m_couts;
	bool m_connectedToEnter;

public:
	pointDInteret(int id);
	pointDInteret(int id, int type);
	pointDInteret(int id, int type, int nbrMaxSentier);
	pointDInteret(int id, TypesDePointsDinterets type);
	void incrementeNbrSentier();
	void decrementeNbrSentier();
	int getId();
	void setId(int id);
	TypesDePointsDinterets getType();
	void setType(TypesDePointsDinterets type);
	int getnbrMaxSentier();
	void setnbrMaxSentier(int nbrMaxSentier);
	int getnbrSentier();
	void setnbrSentier(int nbrSentier);

	map<pointDInteret*, double> getCouts();

	void addCout(pointDInteret* pi, double cout);

	bool connectedToEnter();

	void setConnectedToEnter(bool connectedToEnter);
};