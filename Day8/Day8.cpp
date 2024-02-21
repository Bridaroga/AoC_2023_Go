// Day8.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <tuple>
#include <vector>

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

    std::map<std::string, std::tuple<std::string, std::string>> nodos{};
    std::map<std::string, std::tuple<std::string, std::string>>::iterator itNodos;

    std::getline(networkDocument, instrucciones);
    // Guarda cada nodo en el map.
    while (!networkDocument.eof()) {
        std::getline(networkDocument, lineaNetwork);
        if (lineaNetwork == "") {
            continue;
        }

        primerParentesis =  lineaNetwork.find_first_of("(");
        coma =              lineaNetwork.find_first_of(",");
        espacioFinal =      lineaNetwork.find_last_of(" ");
        segundoParentesis = lineaNetwork.find_last_of(")");

        nodo = lineaNetwork.substr(0, lineaNetwork.find_first_of(" "));
        izquierda = lineaNetwork.substr(primerParentesis + 1, coma - primerParentesis - 1);
        derecha = lineaNetwork.substr(espacioFinal + 1, segundoParentesis - espacioFinal - 1);

        nodos.insert({ nodo, { izquierda, derecha } });
        //std::cout << nodo << "   " << izquierda << "   " << derecha << '\n';
    }

    itNodos = nodos.find("AAA");

    itInstrucciones = instrucciones.begin();

    while (itNodos->first != "ZZZ") {
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

    std::cout << contador << '\n';
}
