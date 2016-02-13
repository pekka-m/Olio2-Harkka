#include "pankki.h"

void pankki::run(){
	consoleGUI *cg = new consoleGUI();
	initializeDatabaseTables *idt = new initializeDatabaseTables();
	linkedList *linkedL = new linkedList();
	string toBeEdited;
	string editable;
	int id;
	int loop = 1;
	firstNode = new Node;
	Node *currentNode = new Node;
	Node *newNode = new Node;

	idt->initialize();
	delete idt;
	linkedL->initializeLL();
	this->firstNode = linkedL->getFirstNode();
	delete linkedL;

	while (loop ==  1){
		cg->otsikko();
		menu = cg->valikko();

		switch (this->menu)
		{
			//lisää uuden tilin
		case 1:{
			accountCreator *ac = new accountCreator(this->firstNode); 
			this->firstNode = ac->addAccount();
			delete ac;
			break;
		}
		//muokkaa tiliä
		case 2:{
			linkedList *ll = new linkedList();
			this->currentNode = this->firstNode;
			cout << "Muokattavat tilit: \n";
			while (this->currentNode) {
				cout << "id: " << this->currentNode->id
					<< " etunimi: " << this->currentNode->fn
					<< " sukunmi: " << this->currentNode->ln
					<< " hetu: " << this->currentNode->hetu
					<< " osoite: " << this->currentNode->address
					<< " kaupunki: " << this->currentNode->city
					<< " postinumero: " << this->currentNode->postalCode
					<< " puhelin: " << this->currentNode->phone << endl;
			this->currentNode = this->currentNode->next;
			}
			cout << "Muokkaa tilia (id, mihin, mita): ";
			cin >> id >> toBeEdited >> editable;
			ll->editNode(this->firstNode, id, toBeEdited, editable);
			delete ll;
				break;
		}
			// poista tili
		case 3:{
			linkedList *ll = new linkedList();
			this->currentNode = this->firstNode;
			cout << "Tilit: \n";
			while (this->currentNode) {
				cout << this->currentNode->id << " ";
				cout << this->currentNode->fn << endl;
				this->currentNode = this->currentNode->next;
			}
			
			this->firstNode = ll->deleteNode(this->firstNode, cg->deleteAccountMenu());
			delete ll;
			cout << "first node delete: " << this->firstNode << endl;
			
			break;
		}
			// lopettaa ohjelman
		case 0:{
			linkedL->dumpList(db, this->firstNode);
			loop = 0;
			break;
		}
		default:
			cout << "väärä syöte!!!\n";
			break;
		}
	}
	delete cg;
}
