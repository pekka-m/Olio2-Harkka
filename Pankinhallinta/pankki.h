#ifndef BANK
#define BANK
#include <iostream>
#include "database.h"
#include "initializeDatabaseTables.h"
#include "accountCreator.h"
#include "consoleGUI.h"
#include "tableEdit.h"

using namespace std;

class pankki : public database{
public:
	//pankki();
	//~pankki();
	void run();
private:
	Node *firstNode;
	int menu;
};
#endif