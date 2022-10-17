// esercizio sulla programmazione a oggetti in c++
#include <iostream>
using namespace std;
#include <string>
#include <fstream>

const int NUM_CANOTTIERI = 8;

class Imbarcazione;
class Atleta {
	friend Imbarcazione;
	private:
		string cognome;
		string nome;
		string uni;
		char ruolo;

	public:
		// costruttori
		Atleta();
		Atleta(string nuovoCognome, string nuovoNome, string nuovoUni, char nuovoRuolo);

		// metodi
		void stampa();
		void cambiaUni(string nuovaUni);
};

class Imbarcazione {
	private:
		string uni;
		Atleta atleti[NUM_CANOTTIERI];
		Atleta timoniere;

	public:
		// costruttori
		Imbarcazione();
		Imbarcazione(string nuovaUni);

		// metodi
		void stampa();
		void aggiungiCanottiere(Atleta atl1);
		void eliminaCanottiere(Atleta atl1);
		void aggiungiTimoniere(Atleta atl1);
		void cambiaTimoniere(Atleta atl1);
		void eliminaTimoniere();
		void salva(string nomefile);
};

// il costruttore per l'atleta "vuoto"
Atleta :: Atleta() {
	cognome = "";
	nome = "";
	uni = "";
	ruolo = ' ';
}

// il costruttore per l'atleta di cui sono noti i dati
Atleta :: Atleta(string nuovoCognome, string nuovoNome, string nuovoUni, char nuovoRuolo) {
	cognome = nuovoCognome;
	nome = nuovoNome;
	uni = nuovoUni;
	ruolo = nuovoRuolo;
}

void Atleta :: stampa() {
	cout << "Cognome: " << cognome
		 << "\nNome: " << nome
		 << "\nUniversita`: " << uni
		 << "\nRuolo: " << ruolo << endl << endl;
}

// cambia l'universita` di un atleta dato
void Atleta :: cambiaUni(string nuovaUni) {
	uni = nuovaUni;
}

// costruttore per l'imbarcazione vuota e senza universita` assegnata
Imbarcazione :: Imbarcazione() {
	uni = "";
	timoniere = Atleta();
	for (int i = 0; i < NUM_CANOTTIERI; i++)
		atleti[i] = Atleta();
}

// costruttore per l'imbarcazione vuota con universita` assegnata
Imbarcazione :: Imbarcazione(string nuovaUni) {
	uni = nuovaUni;
	timoniere = Atleta();
	for (int i = 0; i < NUM_CANOTTIERI; i++)
		atleti[i] = Atleta();
}

// stampa dell'imbarcazione
void Imbarcazione :: stampa() {
	// nome universita`
	cout << "Universita`: " << uni << endl << endl
		 << "Timoniere: " << timoniere.cognome << " " << timoniere.nome << endl;

	for (int i = 0; i < NUM_CANOTTIERI; i++)
		if (atleti[i].ruolo == 'C') 
			cout << "Canottiere: " << atleti[i].cognome << " " << atleti[i].nome << endl;
}

// salvataggio su file dell'imbarcazione
void Imbarcazione :: salva(string nomefile) {
	// crea il file su cui salvare la stampa dell'imbarcazione
	ofstream out(nomefile);
	out << "Universita`: " << uni << endl << endl
		<< "Timoniere: " << timoniere.cognome << " " << timoniere.nome << endl;

	for (int i = 0; i < NUM_CANOTTIERI; i++)
		if (atleti[i].ruolo == 'C') 
			out << "Canottiere: " << atleti[i].cognome << " " << atleti[i].nome << endl;
	
	out.close();
}

// aggiunge un canottiere, se sono soddisfatte alcune condizioni (univ., ruolo, posti liberi)
void Imbarcazione :: aggiungiCanottiere(Atleta atl1) {
	int primoLibero = NUM_CANOTTIERI + 1; // la posizione del primo posto libero
	int giaPresente = 0;

	// verifico che si stia effettivamente cercando di inserire un canottiere e che faccia parte dell'universita`
	if (atl1.ruolo != 'C')
		cout << "Attenzione, l'atleta inserito non e` un canottiere\n";
	else if (atl1.uni != uni)
		cout << "Attenzione, l'atleta inserito non fa parte dell'universita` dell'imbarcazione\n";
	else {
		for (int i = 0; i < NUM_CANOTTIERI; i++) {
			// faccio scorrere la lista degli atleti nell'imbarcazione, controllando che non sia gia` presente l'atleta da
			// inserire. Se l'i-esimo non ha ruolo 'C' metto la posizione i-esima come prima libera
			if ((atleti[i].cognome == atl1.cognome) && (atleti[i].nome == atl1.nome)) {
				cout << "Attenzione, l'atleta inserito e` gia` presente sull'imbarcazione\n";
				giaPresente = 1;
				break;
			}
			else if (atleti[i].ruolo != 'C') {
				primoLibero = i;
				break;
			}	
		}

		// se primoLibero non e` uguale a NUM_CANOTTIERI+1 vuol dire che c'e` un posto libero nell'imbarcazione
		if (primoLibero != NUM_CANOTTIERI + 1)
			atleti[primoLibero] = atl1;

		// controllo se sono uscito dal ciclo perche` l'atleta era gia` presente
		else if (giaPresente != 1)
			cout << "Non ci sono posti di canottiere liberi su questa imbarcazione\n";
	}
}

// elimina un canottiere "spostando indietro" gli elementi dell'array
void Imbarcazione :: eliminaCanottiere(Atleta atl1) {
	int posElimina = NUM_CANOTTIERI + 1; // la posizione in cui si trova l'elemento da eliminare

	if ((atl1.ruolo != 'C') || (atl1.uni != uni))
		cout << "Attenzione, l'atleta inserito non e` corretto\n";
	else {
		for (int i = 0; i < NUM_CANOTTIERI; i++) {
			if ((atl1.cognome == atleti[i].cognome) && (atl1.nome == atleti[i].nome)) {
				posElimina = i;
				break;
			}
		}
	
		// se posElimina non e` stato modificato, l'atleta non era presente sull'imbarcazione
		if (posElimina == NUM_CANOTTIERI + 1)
			cout << "Attenzione, l'atleta non era presente sull'imbarcazione\n";

		// altrimenti "sposto indietro" gli elementi dell'array e libero l'ultimo posto
		else {
			for (int i = posElimina; i < NUM_CANOTTIERI - 1; i++) {
				atleti[i] = atleti[i + 1];
			}
			atleti[NUM_CANOTTIERI - 1] = Atleta();
		}	
	}
}

// aggiunge il timoniere all'imbarcazione, controllando delle condizioni (uni, ruolo, posto libero)
void Imbarcazione :: aggiungiTimoniere(Atleta atl1) {
	// controllo che l'atleta scelto faccia parte dell'universita` e sia un timoniere
	if (atl1.ruolo != 'T')
		cout << "Attenzione, l'atleta inserito non e` un timoniere\n";
	else if (atl1.uni != uni)
		cout << "Attenzione, l'atleta inserito non fa parte dell'universita` dell'imbarcazione\n";
	else if (timoniere.ruolo == 'T')
		cout << "Attenzione, l'imbarcazione ha gia` un timoniere\n";
	else
		timoniere = atl1;
}

// elimina il timoniere dell'imbarcazione, non sono necessari controlli
void Imbarcazione :: eliminaTimoniere() {
	timoniere = Atleta();
}

// cambia il timoniere: controlla che quello nuovo sia ammissibile (uni e ruolo), elimina il vecchio e aggiunge il nuovo
void Imbarcazione :: cambiaTimoniere(Atleta atl1) {
	if ((atl1.ruolo == 'T') && (atl1.uni == uni)) {
		eliminaTimoniere();
		aggiungiTimoniere(atl1);
	}
	else
		cout << "Attenzione, l'atleta inserito non e` corretto";
}

int main () {
	// crea degli atleti
	Atleta atl0;
	Atleta atl1("Rossi", "Mario", "polimi", 'T'),
		   atl2("Rossi", "Antonio", "polimi", 'C'),
		   atl3("Fasoli", "Simone", "polimi", 'C'),
		   atl4("Baglio", "Aldo", "unibo", 'C'),		// canottiere, universita` diversa
		   atl5("Storti", "Giovanni", "unibo", 'T'),	// timoniere, universita` diversa
		   atl6("Poretti", "Giacomo", "polimi", 'T'),	// secondo timoniere, stessa universita`
		   atl7("Moioli", "Giuseppe", "polimi", 'C'),
		   atl8("Keaton", "Buster", "polimi", 'C'),
		   atl9("Chaplin", "Charlie", "polimi", 'C'),
		   atl10("Wayne", "John", "polimi", 'C'),
		   atl11("Lorre", "Peter", "polimi", 'C'),
		   atl12("Welles", "Orson", "polimi", 'C');

	// crea delle imbarcazioni
	Imbarcazione canoa0;
	Imbarcazione canoa1("polimi");
	Imbarcazione canoa2("unibo");
/*
	cout << "\n** Stampa una canoa vuota\n";
	canoa1.stampa();

	cout << "\n** Stampa un atleta, gli cambia universita` e ristampa\n\n";
	atl2.stampa();
	atl2.cambiaUni("unibo");
	atl2.stampa();
	atl2.cambiaUni("polimi");
*/
	
	cout << "\n** Aggiunge un atleta corretto\n";
	canoa1.aggiungiTimoniere(atl1);

	cout << "\n** Aggiunge un atleta di un'altra univ.\n";
	canoa1.aggiungiCanottiere(atl4);
	cout << "\n** Aggiunge un timoniere anche se c'e` gia`\n";
	canoa1.aggiungiTimoniere(atl6);
	// riempie l'imbarcazione
	canoa1.aggiungiCanottiere(atl2);

	cout << "\n** Aggiunge due volte lo stesso canottiere\n";
	canoa1.aggiungiCanottiere(atl2);
	canoa1.aggiungiCanottiere(atl3);
	canoa1.aggiungiCanottiere(atl7);
	canoa1.aggiungiCanottiere(atl8);
	canoa1.aggiungiCanottiere(atl9);
	canoa1.aggiungiCanottiere(atl10);
	canoa1.aggiungiCanottiere(atl11);
	canoa1.aggiungiCanottiere(atl12);

	cout << "\n** Aggiunge un canottiere ma l'imbarcazione e` piena\n";
	atl4.cambiaUni("polimi");
	canoa1.aggiungiCanottiere(atl4);

	cout << "\n** Stampa l'imbarcazione, cambia il timoniere e ristampa l'imbarcazione\n";
	canoa1.stampa();
	canoa1.cambiaTimoniere(atl6);
	cout << endl;
	canoa1.stampa();
/*
	cout << "\n** Elimina un canottiere e ristampa\n";
	canoa1.eliminaCanottiere(atl7);
	canoa1.stampa();

	cout << "\n** Elimina il timoniere e ristampa\n";
	canoa1.eliminaTimoniere();
	canoa1.stampa();
*/
	cout << "\n** Elimina due volte lo stesso canottiere, ne elimina un altro e ristampa\n";
	canoa1.eliminaCanottiere(atl7);
	canoa1.eliminaCanottiere(atl7);
	canoa1.eliminaCanottiere(atl3);
	cout << endl;
	canoa1.stampa();

	// salva sul file "imbarcazione.txt" l'imbarcazione "canoa1"
	canoa1.salva("imbarcazione.txt");
}
