#ifndef TI
#define TI
#include <iostream>
#include "database.h"
using namespace std;

class tableEdit : public database{

public:
	//tableEdit();
	//~tableEdit();
	/* 
	tietokanta
	ID
	etunimi
	sukunimi
	hetu
	osoite
	postinumero
	kaupunki
	puhelin
	*/
	void RunInsertParamSQL(sqlite3* , int, string, string, string, string, string, string, string);
	void dorpTable(sqlite3*);
private:
	char *zErrMsg = 0;
	char *sql2;
};
#endif