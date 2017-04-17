#include "pointDInteret.h"

pointDInteret::pointDInteret(int id){ 
	m_id = id; 
	m_nbrSentier = 0; 
	m_couts = map<pointDInteret*, double>(); 
	m_connectedToEnter = false;
}

pointDInteret::pointDInteret(int id, int type){
	m_id = id; m_nbrMaxSentier = 0; m_nbrSentier = 0; m_couts = map<pointDInteret*, double>();
	if (type == 1){
		m_type = pointDeVue;
		m_connectedToEnter = false;
	}
	else if (type == 2){
		m_type = entree;
		m_connectedToEnter = true;
	}
	else if (type == 3){
		m_type = etape;
		m_connectedToEnter = false;
	}
};

pointDInteret::pointDInteret(int id, int type, int nbrMaxSentier){
	m_id = id; m_nbrMaxSentier = nbrMaxSentier; m_nbrSentier = 0; m_couts = map<pointDInteret*, double>();
	if (type == 1){
		m_type = pointDeVue;
		m_connectedToEnter = false;
	}
	else if (type == 2){
		m_type = entree;
		m_connectedToEnter = true;
	}
	else if (type == 3){
		m_type = etape;
		m_connectedToEnter = false;
	}
};

pointDInteret::pointDInteret(int id, TypesDePointsDinterets type){ 
	m_id = id; 
	m_type = type; 
	m_nbrMaxSentier = 0; 
	m_nbrSentier = 0; 
	m_couts = map<pointDInteret*, double>(); 
	if (type == pointDeVue){
		m_connectedToEnter = false;
	}
	else if (type == entree){
		m_connectedToEnter = true;
	}
	else if (type == etape){
		m_connectedToEnter = false;
	}
};

void pointDInteret::incrementeNbrSentier(){ m_nbrSentier++; };
void pointDInteret::decrementeNbrSentier(){ m_nbrSentier--; };

int pointDInteret::getId(){
	return m_id;
};

void pointDInteret::setId(int id){
	m_id = id;
};

TypesDePointsDinterets pointDInteret::getType(){
	return m_type;
};

void pointDInteret::setType(TypesDePointsDinterets type){
	m_type = type;
};

int pointDInteret::getnbrMaxSentier(){ return m_nbrMaxSentier; };

void pointDInteret::setnbrMaxSentier(int nbrMaxSentier){ m_nbrMaxSentier = nbrMaxSentier; };

int pointDInteret::getnbrSentier(){ return m_nbrSentier; };

void pointDInteret::setnbrSentier(int nbrSentier){ m_nbrSentier = nbrSentier; };

map<pointDInteret*, double> pointDInteret::getCouts(){
	return m_couts;
};

void pointDInteret::addCout(pointDInteret* pi, double cout){
	m_couts[pi] = cout;
};

bool pointDInteret::connectedToEnter(){
	return m_connectedToEnter;
}

void pointDInteret::setConnectedToEnter(bool connectedToEnter){ m_connectedToEnter = connectedToEnter; }