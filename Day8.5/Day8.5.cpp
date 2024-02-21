// Day8.5.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <tuple>
#include <vector>

typedef std::map<std::string, std::tuple<std::string, std::string>> mapa;

int main() {
    std::ifstream networkDocument("Network.txt");

    std::string lineaNetwork{ "" };
    std::string instrucciones{ "" };
    std::string::iterator itInstrucciones;
    std::string nodo{ "" };
    std::string izquierda{ "" };
    std::string derecha{ "" };
    std::string posicionNodo{ "" };

    size_t primerParentesis{ 0 };
    size_t segundoParentesis{ 0 };
    size_t coma{ 0 };
    size_t espacioFinal{ 0 };
    size_t contador{ 0 };
    size_t contadorNodos{ 0 };

    // Valores para hallar el mcm
    size_t residuo{ 0 };
    size_t mcm{ 0 };
    size_t producto{ 0 };

    mapa nodos{};
    mapa::iterator itNodos;

    std::vector<std::string> nodosFinalA{};

    std::getline(networkDocument, instrucciones);
    // Guarda cada nodo en el map.
    while (!networkDocument.eof()) {
        std::getline(networkDocument, lineaNetwork);
        if (lineaNetwork == "") {
            continue;
        }

        primerParentesis = lineaNetwork.find_first_of("(");
        coma = lineaNetwork.find_first_of(",");
        espacioFinal = lineaNetwork.find_last_of(" ");
        segundoParentesis = lineaNetwork.find_last_of(")");

        nodo = lineaNetwork.substr(0, lineaNetwork.find_first_of(" "));
        izquierda = lineaNetwork.substr(primerParentesis + 1, coma - primerParentesis - 1);
        derecha = lineaNetwork.substr(espacioFinal + 1, segundoParentesis - espacioFinal - 1);

        nodos.insert({ nodo, { izquierda, derecha } });
        if (nodo[2] == 'A') {
            nodosFinalA.push_back(nodo);
        }
    }

    for (size_t i = 0; i < nodosFinalA.size(); i++) {
        itInstrucciones = instrucciones.begin();
        itNodos = nodos.find(nodosFinalA[i]);

        // Cuenta los pasos desde cada nodo inicial hasta el final.
        while (itNodos->first[2] != 'Z') {
            if (*itInstrucciones == 'L') {
                itNodos = nodos.find(std::get<0>(itNodos->second));
            }
            else {
                itNodos = nodos.find(std::get<1>(itNodos->second));
            }

            contador++;
            itInstrucciones++;
            if (itInstrucciones == instrucciones.end()) {
                itInstrucciones = instrucciones.begin();
            }
        }

        // Calcula el mcm de los pasos ya calculados por cada nodo.
        // No sé como funciona, ¬_¬
        // Bueno, sí sé como funciona, pero no entiendo de dónde salió el algoritmo.
        if (i == 0) {
            mcm = contador;
        } else {
            producto = mcm * contador;

            do {
                residuo = mcm % contador;
                mcm = contador;
                contador = residuo;
            } while (residuo != 0);

            mcm = producto / mcm;
        }

        contador = 0;
    }

    std::cout << mcm << '\n';
}
