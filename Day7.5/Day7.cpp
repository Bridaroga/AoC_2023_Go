// Day7.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <fstream>
#include <map>
#include <string>

std::string compararManos(std::string, std::string);

std::map<char, int> cartas = {
    {'J', 1},
    {'2', 2},
    {'3', 3},
    {'4', 4},
    {'5', 5},
    {'6', 6},
    {'7', 7},
    {'8', 8},
    {'9', 9},
    {'T', 10},
    {'Q', 11},
    {'K', 12},
    {'A', 13}
};

size_t winnings{ 0 };
size_t contador{ 1 };

// Nodo con solamente apuntadores a la izquierda y derecha.
struct nodo {
    int apuesta;
    int rank;
    std::string mano;
    struct nodo* izquierda;
    struct nodo* derecha;
};

// Crea un nuevo nodo.
nodo* nuevoNodo(int apuesta, int rank, std::string mano) {
    struct nodo* temporal = new struct nodo;
    temporal->apuesta = apuesta;
    temporal->rank = rank;
    temporal->mano = mano;
    temporal->izquierda = NULL;
    temporal->derecha = NULL;

    return temporal;
}

// Inserta un nuevo nodo con la apuesta, el rank y la mano en el BST.
nodo* insertar(struct nodo* nodo, int apuesta, int rank, std::string mano) {
    if (nodo == NULL) {
        return nuevoNodo(apuesta, rank, mano);
    }

    if (rank < nodo->rank) {
        nodo->izquierda = insertar(nodo->izquierda, apuesta, rank, mano);
    }
    else if (rank > nodo->rank) {
        nodo->derecha = insertar(nodo->derecha, apuesta, rank, mano);
    }
    else if (compararManos(mano, nodo->mano) == "izquierda") {  // Cuando rank == nodo->rank
        nodo->izquierda = insertar(nodo->izquierda, apuesta, rank, mano);
    }
    else {
        nodo->derecha = insertar(nodo->derecha, apuesta, rank, mano);
    }

    return nodo;
}

// Pues el rank de la mano.
int rankMano(std::string mano) {
    int rank{ 0 };

    std::map<char, int> contador{};

    std::map<char, int>::iterator itJ;

    for (size_t i = 0; i < mano.length(); i++) {
        contador[mano[i]] += 1;
        //std::cout << mano[i] << "=" << contador[mano[i]] << " ";
    }
    std::map<char, int>::iterator it = contador.begin();
    itJ = contador.find('J');

    if (contador.size() == 1) {
        return 7;   // Five of a kind
    }
    else if (contador.size() == 2) {
        if (itJ != contador.end()) {
            return 7;   // Pasa a Five of a kind con cualquier combinación de J
        }
        else if (it->second == 1 || it->second == 4) {
            return 6;   // Four of a kind
        }
        return 5;   // Full house
    }
    else if (contador.size() == 3) {
        if (itJ != contador.end() && itJ->second != 1) {
            return 6;   // Four of a kind con 2 o 3 J
        }
        while (it != contador.end()) {
            if (it->second == 1) {
                it++;
                continue;
            }
            break;
        }
        
        if (it->second == 3) {
            if (itJ != contador.end()) {
                return 6;   // Four of a kind con 1 J
            }
            return 4;   // Three of a kind
        }
        if (itJ != contador.end()) {
            return 5;   // Full house con 1 J
        }
        return 3;   // Two pair
    }
    else if (contador.size() == 4) {
        if (itJ != contador.end()) {
            return 4;   // Three of a kind con J
        }
        return 2;   // One pair
    }
    if (itJ != contador.end()) {
        return 2;   // One pair con J
    }
    return 1;   // High card
}

// Compara las manos del nodo y del nuevo nodo.
std::string compararManos(std::string nuevaMano, std::string manoNodo) {
    std::map<char, int>::iterator itNuevaMano;
    std::map<char, int>::iterator itManoNodo;
    for (size_t i = 0; i < nuevaMano.size(); i++) {
        if (nuevaMano[i] == manoNodo[i]) {
            continue;
        }

        itNuevaMano = cartas.find(nuevaMano[i]);
        itManoNodo = cartas.find(manoNodo[i]);
        if (itNuevaMano->second < itManoNodo->second) {
            return "izquierda";
        }
        break;
    }
    return "derecha";
}

void printEnOrden(struct nodo* nodo) {
    if (nodo == NULL) {
        return;
    }

    printEnOrden(nodo->izquierda);

    std::cout << "Rank: " << nodo->rank << "    Mano: " << nodo->mano << "    Apuesta: " << nodo->apuesta << '\n';
    winnings += nodo->apuesta * contador;
    contador++;

    printEnOrden(nodo->derecha);
}


int main() {
    std::ifstream pokerDocument("Poker.txt");

    struct nodo* raizArbol = NULL;

    std::string lineaPoker{ "" };
    std::string mano{ "" };

    int rank{ 0 };
    int apuesta{ 0 };

    while (!pokerDocument.eof()) {
        std::getline(pokerDocument, lineaPoker);
        mano = lineaPoker.substr(0, lineaPoker.find_first_of(" "));
        rank = rankMano(mano);
        apuesta = std::stoi(lineaPoker.substr(lineaPoker.find_first_of(" ") + 1));

        if (raizArbol == NULL) {
            raizArbol = insertar(raizArbol, apuesta, rank, mano);
        }
        else {
            insertar(raizArbol, apuesta, rank, mano);
        }

        //std::cout << rank << "  " << apuesta << '\n';
    }


    printEnOrden(raizArbol);

    std::cout << winnings << '\n';

    /*for (auto& it : cartas) {
        std::cout << it.first << "  " << it.second << '\n';
    }*/
}
