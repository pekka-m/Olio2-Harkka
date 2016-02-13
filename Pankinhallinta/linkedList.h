#ifndef LL
#define LL
#include <iostream>
#include "database.h"
#include "tableEdit.h"
using namespace std;

class linkedList : public database {

public:
	/*linkedList();
	~linkedList();*/

	/* parametrit:
	firstNode
	monennenko listan noden jälkeen uusi node sijoitetaan
	uuden noden id
	etunimi
	sukunimi
	hetu
	osoite
	postinumero
	kaupunki
	puhelin
	*/
	Node* addNode(Node *, int, string, string, string, string, string, string, string);
	void listanLinkitys();
	void initializeLL();
	void editNode(Node*, int, string, string);
	void dumpList(sqlite3*, Node*);
	/*
	firstNode
	int id
	*/
	Node* deleteNode(Node*, int);
	Node* getFirstNode();
	int biggestId(Node*);

private:
	unsigned int maxIdCnt;
	char *zErrMsg = 0;
	Node *firstNode;
	Node *currentNode;
	Node *newNode;
};
#endif // !LL