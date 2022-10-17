// esercizio su liste e puntatori in c++
#include <iostream>
#include <string>
using namespace std;

struct Prodotto {
	int codice;
	int collocazione;
	Prodotto *nextProdotto;
};

struct Spesa {
	Prodotto *prodotto;
	int codice;
	int quantita;
	Spesa *nextSpesa;
};

struct ListaOperatore {
	Spesa *spesa;
	ListaOperatore *nextlistaOperatore;
};

ListaOperatore * generaListaOperatore(Prodotto *, Spesa *);
void aggiungiProdotto(Prodotto *&, int, int);
void aggiungiArticoliSpesa(Prodotto *, Spesa *&, int, int);
void stampaListaProdotti(Prodotto *);
void stampaListaSpesa(Spesa *);
void stampaListaOperatore(ListaOperatore *);

int main() {
	Prodotto *listaProdotti = nullptr;
	Spesa *listaSpesa1 = nullptr;
	ListaOperatore *listaOperatore1 = nullptr;
	
	aggiungiProdotto(listaProdotti, 1005, 8);
	aggiungiProdotto(listaProdotti, 1009, 14);
	aggiungiProdotto(listaProdotti, 1006, 1);
	aggiungiProdotto(listaProdotti, 1000, 15);
	aggiungiProdotto(listaProdotti, 1004, 9);
	aggiungiProdotto(listaProdotti, 1003, 10);
	aggiungiProdotto(listaProdotti, 1002, 12);
	aggiungiProdotto(listaProdotti, 1010, 18);
	aggiungiProdotto(listaProdotti, 1001, 13);
	aggiungiProdotto(listaProdotti, 1008, 3);
	aggiungiProdotto(listaProdotti, 1007, 20);
	stampaListaProdotti(listaProdotti);
	
	aggiungiArticoliSpesa(listaProdotti, listaSpesa1, 1010, 1);
	aggiungiArticoliSpesa(listaProdotti, listaSpesa1, 1005, 5);
	aggiungiArticoliSpesa(listaProdotti, listaSpesa1, 1001, 1);
	aggiungiArticoliSpesa(listaProdotti, listaSpesa1, 1000, 2);
	aggiungiArticoliSpesa(listaProdotti, listaSpesa1, 1106, 3);
	aggiungiArticoliSpesa(listaProdotti, listaSpesa1, 1006, 3);
	aggiungiArticoliSpesa(listaProdotti, listaSpesa1, 1004, 1);
	stampaListaSpesa(listaSpesa1);

	listaOperatore1 = generaListaOperatore(listaProdotti, listaSpesa1);
	stampaListaOperatore(listaOperatore1);
}


// aggiunge un nuovo prodotto alla lista
void aggiungiProdotto(Prodotto *&listaProdotti, int codice, int collocazione) {
	Prodotto *nuovoProdotto = new Prodotto;
	
	nuovoProdotto->codice = codice;
	nuovoProdotto->collocazione = collocazione;
	nuovoProdotto->nextProdotto = nullptr;
	
	// se la lista e` vuota
	if (listaProdotti == nullptr) {
		listaProdotti = nuovoProdotto;
	}
	// aggiunge in cima, dato che non e` richiesto un ordine particolare
	else {
		nuovoProdotto->nextProdotto = listaProdotti;
		listaProdotti = nuovoProdotto;
	}
}

// aggiunge un articolo alla lista della spesa indicata (e ne verifica la disponibilita`)
void aggiungiArticoliSpesa(Prodotto *listaProdotti, Spesa *&listaSpesa, int codice, int quantita) {
	
	Prodotto *tempProdotto = listaProdotti; // per maggiore chiarezza crea una nuova variabile puntatore
	Spesa *nuovaSpesa = new Spesa;
	nuovaSpesa->codice = codice;
	nuovaSpesa->quantita = quantita;
	nuovaSpesa->prodotto = nullptr;
	nuovaSpesa->nextSpesa = nullptr;
	
	// cerca l'articolo nel catalogo
	for (tempProdotto; tempProdotto != nullptr; tempProdotto = tempProdotto->nextProdotto) {
		if (tempProdotto->codice == codice)
			break;
	}
	
	// ora tempProdotto punta all'elemento nel catalogo che va aggiungo alla spesa (o a nullptr se non c'e`)
	nuovaSpesa->prodotto = tempProdotto;
	
	// se listaSpesa e` vuoto, aggiunge nuovaSpesa
	if (listaSpesa == nullptr) {
		listaSpesa = nuovaSpesa;
	}
	else {
		nuovaSpesa->nextSpesa = listaSpesa;
		listaSpesa = nuovaSpesa;
	}
}

// genera la lista per l'operatore, ordinata in funzione della collocazione
ListaOperatore * generaListaOperatore(Prodotto *listaProdotti, Spesa *listaSpesa) {
	Prodotto *tempProdotto = listaProdotti;
	Spesa *tempSpesa = listaSpesa;
	ListaOperatore *tempListaOperatore = nullptr;
	ListaOperatore *prevListaOperatore = nullptr;
	ListaOperatore *nuovaListaOperatore = nullptr;
	ListaOperatore *nuovoElementoLista = nullptr;
		
	// scorre la lista della spesa
	for (tempSpesa; tempSpesa != nullptr; tempSpesa = tempSpesa->nextSpesa) {
		if (tempSpesa->prodotto != nullptr) {
			
			nuovoElementoLista = new ListaOperatore;
			nuovoElementoLista->spesa = tempSpesa;
			nuovoElementoLista->nextlistaOperatore = nullptr;
			
			// controlla se la lista per l'operatore e` vuota
			if (nuovaListaOperatore == nullptr) {				
				nuovaListaOperatore = nuovoElementoLista;
			}
			else {
			//prevListaOperatore = nuovaListaOperatore;
				for (tempListaOperatore = nuovaListaOperatore; tempListaOperatore != nullptr; tempListaOperatore = tempListaOperatore->nextlistaOperatore) {

					if (nuovoElementoLista->spesa->prodotto->collocazione < tempListaOperatore->spesa->prodotto->collocazione) {
						break; 
			// a questo punto tempListaOperatore punta all'elemento che andra` dopo tempSpesa 
					}
					prevListaOperatore = tempListaOperatore;
				}
				
				// se va all'inizio della lista
				if (tempListaOperatore == nuovaListaOperatore) {
					nuovoElementoLista->nextlistaOperatore = tempListaOperatore;
					nuovaListaOperatore = nuovoElementoLista;
				}
				// se tempListaOperatore e` nullptr vuol dire che il nuovo articolo va in fondo alla lista
				else if (tempListaOperatore == nullptr) {
					prevListaOperatore->nextlistaOperatore = nuovoElementoLista;
				}

				else {
					nuovoElementoLista->nextlistaOperatore = tempListaOperatore;
					prevListaOperatore->nextlistaOperatore = nuovoElementoLista;
				}
			}
		}
	}
	return nuovaListaOperatore;
}

void stampaListaProdotti(Prodotto *listaProdotti) {
	for (listaProdotti; listaProdotti != nullptr; listaProdotti = listaProdotti->nextProdotto)
		cout << "Codice: " << listaProdotti->codice << " Collocazione: " << listaProdotti->collocazione << endl;
}

void stampaListaSpesa(Spesa *listaSpesa) {
	for (listaSpesa; listaSpesa != nullptr; listaSpesa = listaSpesa->nextSpesa) {
		cout << "Codice: " << listaSpesa->codice << " Quantita`: " << listaSpesa->quantita;
		if (listaSpesa->prodotto == nullptr) {
			cout << " Attenzione, articolo non presente" << endl;
		}
		else {
			cout << " Collocazione: " << listaSpesa->prodotto->collocazione << endl;
		}
	}
}

void stampaListaOperatore(ListaOperatore *listaOperatore) {
	for (listaOperatore; listaOperatore != nullptr; listaOperatore = listaOperatore->nextlistaOperatore)
		cout << "Codice: " << listaOperatore->spesa->codice << " Quantita: " << listaOperatore->spesa->quantita << " Collocazione: " << listaOperatore->spesa->prodotto->collocazione << endl;
}
