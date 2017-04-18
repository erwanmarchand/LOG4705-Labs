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
#include <algorithm>

using namespace std;
using namespace std::chrono;

// Liste des differents algo
enum TypesDePointsDinterets {
	pointDeVue,
	entree,
	etape
};

template <typename T1, typename T2>
struct less_second {
	typedef pair<T1, T2> type;
	bool operator ()(type const& a, type const& b) const {
		return a.second < b.second;
	}
};


class pointDInteret {
private:

	struct compareId
	{
		bool operator()(pointDInteret *a, pointDInteret *b) const
		{
			// implement your comparison logic here
			return (a->getId()<b->getId());
		}
	};

	int m_id;
	TypesDePointsDinterets m_type;
	int m_nbrMaxSentier;
	int m_nbrSentier;
	map<pointDInteret*, double, compareId> m_couts;
	vector<pair<pointDInteret*, double> > m_coutsOrdered;
	bool m_connectedToEnter;
	vector<pointDInteret*> m_linkedPI;

	bool m_piPlacee;



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

	map<pointDInteret*, double, compareId> getCouts();

	void addCout(pointDInteret* pi, double cout);

	bool connectedToEnter();

	void setConnectedToEnter(bool connectedToEnter);

	bool canAcceptMoreSentier();

	void generateCoutsOrdered();

	void addLink(pointDInteret* a);

	void resetLinks();

	bool piAlreadyLinked(pointDInteret* a);

	vector<pair<pointDInteret*, double> > coutsOrdered(){ return m_coutsOrdered; };

	void setPIPlacee(bool value){ m_piPlacee = value; }

	bool piPlacee(){ return m_piPlacee; }
};