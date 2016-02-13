#include "linkedList.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
	int i;
	for (i = 0; i < argc; i++){
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

// lisää uuden Noden parametrina annetun id:n jälkeen
database::Node* linkedList::addNode(Node* firstNode, int id, string fn, string ln, string hetu, string address, string postalCode, string city, string phone) {
	// lisätään parametreissa annetut arvot uuteen nodeen
	newNode = new Node;
	newNode->id = id;
	newNode->fn = fn;
	newNode->ln = ln;
	newNode->hetu = hetu;
	newNode->address = address;
	newNode->postalCode = postalCode;
	newNode->city = city;
	newNode->phone = phone;

	//jos lista on tyhjä, tehdään uusi eka node
	if (!firstNode) {
		firstNode = new Node;
		firstNode = newNode;
	}
	//lisätään uusinode listan loppuun
	else {
		//siirrytään ensimmäiseen nodeen
		this->currentNode = firstNode;
		//edetään listalla loppuun asti
		while (this->currentNode->next) this->currentNode = this->currentNode->next;
		//lisätään newNode node
		this->currentNode->next = newNode;
	}
	 return firstNode;
}

void linkedList::editNode(Node *firstNode, int id, string toBeEdited, string editable){
	this->currentNode = new Node;
	this->currentNode = firstNode;
	while (1){
		if (id == this->currentNode->id){
			if (toBeEdited == "etunimi") currentNode->fn = editable;
			if (toBeEdited == "sukunimi") currentNode->ln = editable;
			if (toBeEdited == "hetu") currentNode->hetu = editable;
			if (toBeEdited == "osoite") currentNode->address = editable;
			if (toBeEdited == "postinumero") currentNode->postalCode = editable;
			if (toBeEdited == "kaupunki") currentNode->city = editable;
			if (toBeEdited == "puhelin") currentNode->phone = editable;
			break;
		}
		this->currentNode = this->currentNode->next;
	}
}

//poistaa annetun id:n omaavan noden
database::Node* linkedList::deleteNode(Node* firstNode, int id) {
	//mennään listan alkuun
	this->currentNode = firstNode;

		while (1){
			//jos tulaan listan lopuun, niin lopetetaan loop
			if (this->currentNode->next == NULL) break;
			//jos on vain yksi node tai ensimmäinen on poistettava node
			if (firstNode->next == NULL || this->currentNode->id == id ){
				this->firstNode = new Node;
				this->firstNode = firstNode->next;
				return this->firstNode;
				break;
			}
			// muiden nodejen poisto
			else if (id == this->currentNode->next->id){
				this->currentNode->next = this->currentNode->next->next;
				break;
			}
			//liikutaan eteenpäin
			this->currentNode = this->currentNode->next;
		}
		return firstNode;
	}
	
void linkedList::initializeLL() {
	currentNode = new Node;
	sqlite3_open("pankkidb", &db);
	sql = "select * from ASIAKASTIEDOT";
	rc = sqlite3_prepare(db, sql, strlen(sql), &stmt, &pzTest);

	while (1){
		//sqlite3_stepin palauttama arvo (onko vielä rivejä vai ollaanko lopussa)
		int s;
		//tehdään newNode node, joka lisätään linkitettyyn listaan
		newNode = new Node;
		s = sqlite3_step(stmt);
		//haetaan tietokannasta tiedot uuteen nodeen
		if (s == SQLITE_ROW){
			newNode->id = sqlite3_column_int(stmt, 0);
			newNode->fn = string(reinterpret_cast <const char*> (sqlite3_column_text(stmt, 1)));
			newNode->ln = string(reinterpret_cast <const char*> (sqlite3_column_text(stmt, 2)));
			newNode->hetu = string(reinterpret_cast <const char*> (sqlite3_column_text(stmt, 3)));
			newNode->address = string(reinterpret_cast <const char*> (sqlite3_column_text(stmt, 4)));
			newNode->city = string(reinterpret_cast <const char*> (sqlite3_column_text(stmt, 5)));
			newNode->postalCode = string(reinterpret_cast <const char*> (sqlite3_column_text(stmt, 6)));
			newNode->phone = string(reinterpret_cast <const char*> (sqlite3_column_text(stmt, 7)));
			newNode->next = NULL;
			//jos listaa ei ole, newNode node on ensimmäinen
			if (!this->firstNode) {
				firstNode = new Node;
				this->firstNode = newNode;				
			}
			else {
				//siirrytään ensimmäiseen nodeen
				this->currentNode = this->firstNode;
				//edetään listalla loppuun asti
				while (this->currentNode->next) this->currentNode = this->currentNode->next;
				//lisätään newNode node
				this->currentNode->next = newNode;
			}
		}
		//ollaan tietokannan lopussa
		else if (s == SQLITE_DONE) break;
	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}

//hakee suurimman id numeron linkitetystä listasta
int linkedList::biggestId(Node *firstNode){
	//Biggest ID
	int BID = NULL;
	this->currentNode = new Node;
	//jos on linkitettyä listaa
	if (firstNode != NULL){
		this->currentNode = firstNode;
		//jos ensimmäinen alkio on ainoa
		if (firstNode->next == NULL) BID = 1;
		//muuten kaikki muut
		else{
			//valitsee suurimman bidin
			while (this->currentNode->next) {
				if (!BID) BID = this->currentNode->id;
				if (this->currentNode->next->id > BID) BID = this->currentNode->next->id;
				this->currentNode = this->currentNode->next;
			}
		}
	}
	// jos ei ole listaa
	else BID = 0;
	return BID;
}


//dumppaa linkitetyn listan tiedot tietokantaan
void linkedList::dumpList(sqlite3 *db, Node* firstNode){
	int idCntTmp = 0;
	//tuhoaa taulukon
	tableEdit *te = new tableEdit();
	te->dorpTable(db);
	delete te;

	sqlite3_open("pankkidb", &db);
	sql = "create table ASIAKASTIEDOT( ID smallint not null, ETUNIMI TEXT , SUKUNIMI TEXT, HETU TEXT, OSOITE TEXT,		POSTINUMERO TEXT, KAUPUNKI TEXT, PUH TEXT)";
	sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	
	//siirrytään ensimmäiseen nodeen
	this->currentNode = firstNode;
	//edetään listalla loppuun asti
	while (this->currentNode->next) {
		this->currentNode = this->currentNode->next;
		idCntTmp++;
	}
	//lisää tietokantaan alkioiden tiedot
	this->currentNode = firstNode;
	for (int i = 0; i <= idCntTmp; i++)
	{
		te->RunInsertParamSQL(db, this->currentNode->id, this->currentNode->fn, this->currentNode->ln, this->currentNode->hetu, this->currentNode->address, this->currentNode->postalCode, this->currentNode->city, this->currentNode->phone);
		this->currentNode = this->currentNode->next;
	}
	sqlite3_close(db);
}

database::Node* linkedList::getFirstNode(){
	return this->firstNode;
}