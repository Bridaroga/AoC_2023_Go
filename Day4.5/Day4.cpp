// Day4.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

int main() {
    std::ifstream cardsDocument("Cards.txt");

    std::map<int, int> duplicadosCartas{}; //<# de carta, cantidad>
    
    int numeroCarta{ 0 };
    int numero{ 0 };
    int numerosIguales{ 0 };
    int puntos{ 0 };
    int sumaPuntos{ 0 };
    int totalCartas{ 0 };

    std::vector<int> numerosGanadores{};
    std::vector<int> numerosConseguidos{};

    std::string lineaCartas{ "" };

    std::size_t posicionDosPuntos{ 0 };
    std::size_t posicionLinea{ 0 };
    std::size_t posicionNumero{ 0 };

    while (!cardsDocument.eof()) {
        std::getline(cardsDocument, lineaCartas);

        posicionDosPuntos = lineaCartas.find(":");
        posicionLinea = lineaCartas.find("|");
        posicionNumero = lineaCartas.find_first_of("0123456789");

        numeroCarta = std::stoi(lineaCartas.substr(posicionNumero, posicionDosPuntos - posicionNumero));
        duplicadosCartas[numeroCarta] += 1;

        //std::cout << duplicadosCartas[numeroCarta] << "    ";

        // Mete los números en el primer vector.
        for (std::size_t i = posicionDosPuntos; i < posicionLinea; i++) {
            posicionNumero = lineaCartas.find_first_of("0123456789", i);
            i = lineaCartas.find_first_not_of("0123456789", posicionNumero);
            numero = std::stoi(lineaCartas.substr(posicionNumero, i - posicionNumero));
            numerosGanadores.push_back(numero);

            //std::cout << numero << " ";
        }

        //std::cout << " | ";

        // Introduce (Mete, >:C) los números en el segundo vector.
        for (std::size_t i = posicionLinea; i < lineaCartas.length(); i++) {
            posicionNumero = lineaCartas.find_first_of("0123456789", i);
            if (lineaCartas.find_first_not_of("0123456789", posicionNumero) != std::string::npos) {
                i = lineaCartas.find_first_not_of("0123456789", posicionNumero);
                numero = std::stoi(lineaCartas.substr(posicionNumero, i - posicionNumero));
            }
            else {
                numero = std::stoi(lineaCartas.substr(posicionNumero));
                i = lineaCartas.length();
            }
            numerosConseguidos.push_back(numero);

            //std::cout << numero << " ";
        }

        // Busca los números ganadores en los conseguidos.
        for (std::size_t i = 0; i < numerosGanadores.size(); i++) {
            for (std::size_t j = 0; j < numerosConseguidos.size(); j++) {
                if (numerosGanadores[i] == numerosConseguidos[j]) {
                    numerosIguales++;
                    //std::cout << numerosGanadores[i] << " ";
                }
            }
        }

        // Ver las cartas duplicadas por línea.
        for (int i = 0; i < duplicadosCartas[numeroCarta]; i++) {
            for (int j = 1; j <= numerosIguales; j++) {
                duplicadosCartas[numeroCarta + j] += 1;
                //std::cout << duplicadosCartas[numeroCarta + j] << " ";
                /*if (puntos == 0) {
                    puntos++;
                }
                else {
                    puntos *= 2;
                }*/
            }
        }
        


        std::cout << numeroCarta << '\n';

        //sumaPuntos += puntos;
        //std::cout << sumaPuntos << '\n';

        //std::cout << numeroCarta << "    " << posicionDosPuntos << "    " << posicionLinea << '\n';

        //puntos = 0;
        numerosIguales = 0;
        numerosGanadores.clear();
        numerosConseguidos.clear();
    }

    // Ver total de cartas.
    for (int i = 1; i <= numeroCarta; i++) {
        totalCartas += duplicadosCartas[i];
    }

    std::cout << totalCartas << '\n';
}
