#include "initializeDatabaseTables.h"

using namespace std;

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
	int i;
	for (i = 0; i < argc; i++){
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

void initializeDatabaseTables::initialize(){
	//avataan tietokanta, jos ei ole olemassa, luodaan uusi tietokanta tiedosto
	rc = sqlite3_open("pankkidb", &db);

	//testataan onko ASIAKASTIEDOT niminen taulu olemassa
	sql = "SELECT * FROM ASIAKASTIEDOT";
	rc = sqlite3_prepare(db, sql, strlen(sql), &stmt, &pzTest);
	int s = sqlite3_step(stmt);
	// jos ei ole olemassa kyseistä taulua, niin luodaan sekä alustetaan taulut
	if (s == SQLITE_MISUSE){
		sql = "create table ASIAKASTIEDOT( ID smallint not null, ETUNIMI TEXT , SUKUNIMI TEXT, HETU TEXT, OSOITE TEXT, POSTINUMERO TEXT, KAUPUNKI TEXT, PUH TEXT, SALDO REAL)";
		rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}