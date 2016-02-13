#ifndef AC
#define AC
#include <iostream>
#include "linkedList.h"
#include "database.h"
#include "tableEdit.h"

using namespace std;

class accountCreator : public database{
public:
	accountCreator(database::Node*);
	Node* addAccount();
private:
	Node *newAccount;
	int idNro;
	Node *firstNode;

};
#endif