// Day6.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
// 
// c = 0
// b = tiempo
// a = -1
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>
#include <math.h>

int main() {
    std::ifstream raceDocument("Race.txt");

    std::string lineaRace{ "" };
    std::string carreras{ "" };

    std::vector<long double> tiempo{};
    std::vector<long double> distancia{};
    std::vector<long double> x1{};
    std::vector<long double> x2{};

    long double discriminante{ 0 };
    long double numero{ 1 };

    size_t posicionDosPuntos{ 0 };
    size_t inicioNumero{ 0 };

    std::getline(raceDocument, lineaRace);
    posicionDosPuntos = lineaRace.find(":");

    // Guarda el tiempo.
    for (size_t i = posicionDosPuntos; i < lineaRace.length(); i++) {
        inicioNumero = lineaRace.find_first_of("0123456789", i);
        if (lineaRace.find_first_not_of("0123456789", inicioNumero) != std::string::npos) {
            i = lineaRace.find_first_not_of("0123456789", inicioNumero);
            carreras += lineaRace.substr(inicioNumero, i - inicioNumero);
        }
        else {
            carreras += lineaRace.substr(inicioNumero);
            i = lineaRace.length();
        }
    }
    tiempo.push_back(std::stod(carreras));
    carreras = "";

    std::getline(raceDocument, lineaRace);
    posicionDosPuntos = lineaRace.find(":");

    // Guarda la distancia.
    for (size_t i = posicionDosPuntos; i < lineaRace.length(); i++) {
        inicioNumero = lineaRace.find_first_of("0123456789", i);
        if (lineaRace.find_first_not_of("0123456789", inicioNumero) != std::string::npos) {
            i = lineaRace.find_first_not_of("0123456789", inicioNumero);
            carreras += lineaRace.substr(inicioNumero, i - inicioNumero);
        }
        else {
            carreras += lineaRace.substr(inicioNumero, i - inicioNumero);
            i = lineaRace.length();
        }
    }
    distancia.push_back(std::stod(carreras));

    // Halla los tiempos en los que se pasa la distancia récord.
    // c = -distancia
    for (size_t i = 0; i < tiempo.size(); i++) {
        discriminante = std::pow(tiempo[i], 2) - (4 * (-1) * (-1) * distancia[i]);
        x1.push_back(((-1) * tiempo[i] + std::sqrt(discriminante)) / (2 * (-1)));
        x2.push_back(((-1) * tiempo[i] - std::sqrt(discriminante)) / (2 * (-1)));

        numero *= std::ceil(x2[i]) - std::ceil(x1[i]);

        //std::cout << x1[i] << "    " << x2[i] << '\n';
    }

    std::cout << std::fixed << numero << '\n';

    /*for (size_t i = 0; i < tiempo.size(); i++) {
        std::cout << tiempo[i] << '\n';
        std::cout << distancia[i] << '\n';
    }*/
}
