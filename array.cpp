// esercizio su array in c++
#include <iostream>
using namespace std;

const int R = 6, C = 8; // le dimensioni della matrice

int individuaTipoSottomatrici(int [R][C], int);	// la funzione che fa scorrere le celle della matrice
int individuaSottomatrice(int [R][C], int, int, int); // la funzione che verifica le sottomatrici

int main() {
	int matrice[R][C] = {{0,5,7,9,3,4,0,0},
						 {4,0,0,8,9,0,0,0},
						 {0,0,0,0,3,9,5,3},
						 {7,0,0,0,5,7,0,0},
						 {5,9,0,0,8,0,9,0},
						 {1,9,3,6,7,0,0,5}};
						 
	int matrice2[R][C] = {{0,5,7,9,3,4,0,0},
				 		  {4,0,3,8,9,0,0,0},
				 		  {0,0,8,4,3,9,5,3},
				 		  {7,3,0,6,5,7,0,0},
						  {5,9,0,0,8,0,9,0},
						  {1,9,3,6,7,0,0,5}};
	
	cout << "Valore restituito: " << individuaTipoSottomatrici(matrice, 4) << endl << endl;
	cout << "Valore restituito: " << individuaTipoSottomatrici(matrice2, 3) << endl << endl;
}

// la funzione scorre la matrice e chiama una seconda funzione che verifica la sottomatrice
int individuaTipoSottomatrici(int matrice[R][C], int dim) {
	
	int valoreRitorno = 0;
	// scorre la matrice fino a R - dim per evitare di uscire dai margini
	for (int y = 0; y <= (R - dim); y++) {
		for (int x = 0; x <= (C - dim); x++) {
			valoreRitorno += individuaSottomatrice(matrice, dim, y, x);
		}
	}

	return valoreRitorno;
}

// la funzione controlla la singola sottomatrice di dimensione data
int individuaSottomatrice(int matrice[R][C], int dim, int y, int x) {
	
	int triangolareSuperiore = 1, triangolareInferiore = 1; // inizializzate a 1, diventano 0 se la rispettiva condizione non e` verificata
	int i = 0, j = 0;
	
	// controlla se la sottomatrice e` triangolare inferiore
	// scorre tutte le celle della parte superiore della matrice e se ne trova una = 0 esce dal ciclo
	// per semplicita` le righe vengono contate partendo da 0 e passando alla matrice la coordinata
	// i + y, in questo modo le colonne possono essere fatte scorrere partendo dalla posizione x + i
	for (i = 0; i < (dim - 1); i++) {
		for (j = x + i + 1; j < (dim + x); j++) {
			if (matrice[i + y][j] != 0) {
				triangolareSuperiore = 0;
				break;
			}
		}
	}

	// controlla se la sottomatrice e` triangolare superiore (stesso principio della matrice inferiore)
	for (i = 1; i < dim; i++) {
		for (j = x; j < (x + i); j++) {
			if (matrice[i + y][j] != 0) {
				triangolareInferiore = 0;
				break;
			}
		}
	}

	// stampa il tipo di sottomatrice
	if ((triangolareInferiore == 1) && (triangolareSuperiore == 1)) {
		cout << "Sottomatrice diagonale a partire dalla cella di coordinate (" << y << ", " << x << ")\n";
		return 1;
	}
	else if (triangolareInferiore == 1) {
		cout << "Sottomatrice triangolare inferiore a partire dalla cella di coordinate (" << y << ", " << x << ")\n";
		return 1;
	}
	else if (triangolareSuperiore == 1) {
		cout << "Sottomatrice triangolare superiore a partire dalla cella di coordinate (" << y << ", " << x << ")\n";
		return 1;
	}
	else
		return 0;
}


