#include <string.h>
#include "sqlite3.h"

// Insert record
void RunInsertParamSQL(sqlite3 *db, char *fn, char *ln, int age)
{
	if (!db)
		return;

	char *zErrMsg = 0;
	sqlite3_stmt *stmt;
	const char *pzTest;
	char *szSQL;

	// Insert data item into myTable
	szSQL = "insert into myTable (FirstName, LastName, Age) values(? , ? , ? )";

		int rc = sqlite3_prepare(db, szSQL, strlen(szSQL), &stmt, &pzTest);

	if (rc == SQLITE_OK) {
		// bind the value 
		sqlite3_bind_text(stmt, 1, fn, strlen(fn), 0);
		sqlite3_bind_text(stmt, 2, ln, strlen(ln), 0);
		sqlite3_bind_int(stmt, 3, age);

		// commit 
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
	}
} */