#ifndef IDT
#define IDT
#include <iostream>
#include "database.h"


using namespace std;

class initializeDatabaseTables : public database{
public:
	void initialize();

private:
	char *zErrMsg = 0;
};
#endif