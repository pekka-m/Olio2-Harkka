#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include <iostream>
#include "insertParamSQL.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
	int i;
	for (i = 0; i<argc; i++){
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}


int main(int argc, char* argv[])
{
	
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	char *sql;
	char *jokumuuttuja ;
	jokumuuttuja = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)";
	rc = sqlite3_open("asgsgjhgsdashdjg.apina", &db);

	if (rc){
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		exit(0);
	}
	else{
		fprintf(stderr, "Opened database successfully\n");
	}

	/* Create SQL statement */
	sql = 
		 " INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
		"VALUES (5, 'Mark', 25, 'Rich-Mond ', 65000.00 );";

/* Execute SQL statement */
rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
if (rc != SQLITE_OK){
	fprintf(stderr, "SQL error: %s\n", zErrMsg);
	sqlite3_free(zErrMsg);
}
else{
	fprintf(stdout, "Table created successfully\n");
}
sqlite3_close(db);


return 0;
}