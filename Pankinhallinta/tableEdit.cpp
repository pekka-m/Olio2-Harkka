#include "tableEdit.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
	int i;
	for (i = 0; i < argc; i++){
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

//työntää tietoa linkitetyltä listalta tietokantaan
void tableEdit::RunInsertParamSQL(sqlite3 *db, int id, string  en, string sn, string hetu, string osoite, string postinumero, string kaupunki, string puh){
	sqlite3_open("pankkidb", &db);

	sql = "insert into ASIAKASTIEDOT (ID, ETUNIMI  , SUKUNIMI , HETU , OSOITE , POSTINUMERO , KAUPUNKI , PUH ) values(? , ? , ? , ? , ? , ? , ? , ?)";
	sqlite3_prepare(db, sql, strlen(sql), &stmt, &pzTest);
	
	sqlite3_bind_int(stmt, 1, id);
	sqlite3_bind_text(stmt, 2, en.c_str(), strlen(en.c_str()), 0);
	sqlite3_bind_text(stmt, 3, sn.c_str(), strlen(sn.c_str()), 0);
	sqlite3_bind_text(stmt, 4, hetu.c_str(), strlen(hetu.c_str()), 0);
	sqlite3_bind_text(stmt, 5, osoite.c_str(), strlen(osoite.c_str()), 0);
	sqlite3_bind_text(stmt, 6, postinumero.c_str(), strlen(postinumero.c_str()), 0);
	sqlite3_bind_text(stmt, 7, kaupunki.c_str(), strlen(kaupunki.c_str()), 0);
	sqlite3_bind_text(stmt, 8, puh.c_str(), strlen(puh.c_str()), 0);

	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}

// tuhoaa taulukon
void tableEdit::dorpTable(sqlite3 *db){
	sqlite3_open("pankkidb", &db);
	sql = "drop table ASIAKASTIEDOT";
	sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	sqlite3_close(db);
}