#include "accountCreator.h"

accountCreator::accountCreator(database::Node* firstNode){
	this->firstNode = new Node;
	this->firstNode = firstNode;
}


database::Node* accountCreator::addAccount(){
	newAccount = new Node;

	cin.ignore();
	cout << "Uuden asiakkaan lisays\n\n";
	cout << "Syota etunimi: ";
	getline(cin, this->newAccount->fn);

	cout << "Syota sukunimi: ";
	getline(cin, this->newAccount->ln);

	cout << "Syota hetu: ";
	getline(cin, this->newAccount->hetu);

	cout << "Syota puhelinnumero: ";
	getline(cin, this->newAccount->phone);

	cout << "Syota osoite: ";
	getline(cin,this->newAccount->address);

	cout << "Syota kaupunki: ";
	getline(cin, this->newAccount->city);

	cout << "Syota postinumero: ";
	getline(cin, this->newAccount->postalCode);

	linkedList *ll = new linkedList();
	return ll->addNode(this->firstNode, ll->biggestId(this->firstNode)+1, this->newAccount->fn, this->newAccount->ln, this->newAccount->hetu, this->newAccount->address, this->newAccount->postalCode, this->newAccount->city, this->newAccount->phone);
}