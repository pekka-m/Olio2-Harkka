#ifndef DB
#define DB
#include <iostream>
#include <string>
#include "sqlite3.h"

using namespace std;

class database{

protected:
	struct			Node {
							unsigned int id;
							string fn;
							string ln;
							string hetu;
							string address;
							string city;
							string postalCode;
							string phone;
							Node* next = NULL;
						};
	sqlite3			*db;
	sqlite3_stmt	*stmt;
	const char		*pzTest;
	char			*sql;
	int				rc;
	Node			*firstNode;
	Node			*currentNode;
	Node			*newNode;
	Node			*tmp;

};
#endif