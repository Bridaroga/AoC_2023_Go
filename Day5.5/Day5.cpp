// Day5.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
// No calcular tooooooda la matriz, solo los puntos por donde van las semillas.
// map con tuple<size_t, size_t, size_t> y long: map<std::tuple<size_t, size_t, size_t>, long>
// map<<destino, origen, ancho>, diferencia>
// luego de cada mapa, hacer .clear() ya que no se usará más... espero.
// 
// Tomar la semilla y buscar el origen anterior a la semilla, map siempre organiza todo, pero hay que tener cuidado que esté en el ancho del map.
// Si no está en el ancho del map, es probable que esté fuera de todos los map, así que se toma el valor tal cual de la semilla.
// Luego de pasar todas las semillas, .clear() y calcular el siguiente mapa.
// Las semillas pueden guardar su valor, no creo que haga falta crear un array de semillas... espero.
// Al final, tomar la semilla que tenga el valor con la menor localización (o más cercano a 0).

// 5.5:
// Ver las semillas como intervalos.
// Tomar solo el inicio y final de cada intervalo.
// Cuando pasen por cada mapa, es probable que se corte el intervalo en 2,
//     así que sería mejor guardar las semillas en un (creo) std::map<size_t, std::tuple<size_t, size_t>>



#include <iostream>
#include <fstream>
#include <map>
#include <tuple>
#include <vector>
#include <string>

int main() {
    std::ifstream almanacDocument("Almanac.txt");

    std::map<std::tuple<size_t, size_t, size_t>, long long> mapa{}; // <<destino, origen, ancho>, diferencia>
    std::map<size_t, std::tuple<size_t, size_t>> semillas{}; // <Intervalo, <Menor, Mayor>>

    long long menorDiferencia{ 0 };
    
    size_t posicionDosPuntos{ 0 };
    size_t posicionNumero{ 0 };
    size_t numero{ 0 };
    size_t segundoNumero{ 0 };
    size_t numerosMapas[3]{};
    size_t menorOrigen{ 0 };
    size_t menorAncho{ 0 };
    size_t ancho{ 0 };
    size_t contador{ 0 };
    size_t location{ std::string::npos };

    //std::vector<size_t> semillas{};

    std::string lineaAlmanac{ "" };

    bool dentroDelMapa{ false };
    bool noFin{ true };
    bool primerNumero{ true };

    std::getline(almanacDocument, lineaAlmanac);
    posicionDosPuntos = lineaAlmanac.find(":");

    // Guardar semillas en el map.
    for (size_t i = posicionDosPuntos; i < lineaAlmanac.length(); i++) {
        posicionNumero = lineaAlmanac.find_first_of("0123456789", i);
        if (lineaAlmanac.find_first_not_of("0123456789", posicionNumero) != std::string::npos) {
            i = lineaAlmanac.find_first_not_of("0123456789", posicionNumero);
            if (primerNumero) {
                numero = std::stoull(lineaAlmanac.substr(posicionNumero, i - posicionNumero));
            }
            else {
                segundoNumero = numero + std::stoull(lineaAlmanac.substr(posicionNumero, i - posicionNumero));
            }
        }
        else {
            segundoNumero = numero + std::stoull(lineaAlmanac.substr(posicionNumero));
            i = lineaAlmanac.length();
        }
        if (primerNumero) {
            primerNumero = false;
        }
        else {
            semillas[contador++] = { numero, segundoNumero };
            primerNumero = true;
            std::cout << numero << '\n';
        }
    }

    while (noFin) {
        if (!almanacDocument.eof()) {
            std::getline(almanacDocument, lineaAlmanac);
        }
        else {
            noFin = false;
            lineaAlmanac = "";
        }
        numero = 0;

        if (lineaAlmanac == "") {
            for (size_t i = 0; i < semillas.size(); i++) {
                for (auto& it : mapa) {
                    // Omito mayores que la semilla, y "mido" la distancia entre la semilla y el origen más cercano, y el que tengo guardado como posible origen cercano.
                    if (std::get<1>(it.first) <= std::get<0>(semillas[i]) && 
                        std::get<0>(semillas[i]) - std::get<1>(it.first) <= std::get<0>(semillas[i]) - menorOrigen) {
                        dentroDelMapa = true;
                        menorOrigen  = std::get<1>(it.first);
                        menorAncho   = std::get<2>(it.first);
                        menorDiferencia = it.second;
                        ancho = menorOrigen + menorAncho;
                    }
                }

                // Si está dentro del mapa, calcula el inicio del intervalo y corta el intervalo si la semilla se sale del mapa.
                if (dentroDelMapa && std::get<0>(semillas[i]) < ancho) {
                    std::get<0>(semillas[i]) += menorDiferencia;
                    if (std::get<1>(semillas[i]) < ancho) {
                        std::get<1>(semillas[i]) += menorDiferencia;
                    }
                    else {
                        semillas[semillas.size()] = { ancho, std::get<1>(semillas[i]) };
                        std::get<1>(semillas[i]) = ancho - 1;
                        std::get<1>(semillas[i]) += menorDiferencia;
                    }
                    std::cout << menorDiferencia << "    " << menorOrigen << "    ";
                }
                std::cout << "Inicio semilla: " << std::get<0>(semillas[i]) << "    Fin semilla: " << std::get<1>(semillas[i]) << '\n';

                dentroDelMapa = false;
                menorOrigen = 0;
                menorAncho = 0;
                menorDiferencia = 0;
                ancho = 0;
            }

            std::cout << '\n';
            mapa.clear();
            continue;
        }
        if (lineaAlmanac.find_first_of("0123456789") == std::string::npos) {
            std::cout << lineaAlmanac.substr(0, lineaAlmanac.find(":")) << '\n';
            continue;
        }

        // Guardar el destino, origen y ancho en el map.
        for (size_t i = 0; i < lineaAlmanac.length(); i++) {
            posicionNumero = lineaAlmanac.find_first_of("0123456789", i);
            if (lineaAlmanac.find_first_not_of("0123456789", posicionNumero) != std::string::npos) {
                i = lineaAlmanac.find_first_not_of("0123456789", posicionNumero);
                numerosMapas[numero++] = std::stoull(lineaAlmanac.substr(posicionNumero, i - posicionNumero));
            }
            else {
                numerosMapas[numero++] = std::stoull(lineaAlmanac.substr(posicionNumero));
                i = lineaAlmanac.length();
            }

            //std::cout << numero << " ";
        }

        // Guarda la diferencia entre el destino y origen.
        mapa[{ numerosMapas[0], numerosMapas[1], numerosMapas[2] }] = numerosMapas[0] - numerosMapas[1];
        //std::cout << mapa[{ numerosMapas[0], numerosMapas[1], numerosMapas[2] }] << '\n';


    }

    for (size_t i = 0; i < semillas.size(); i++) {
        if (std::get<0>(semillas[i]) < location) {
            location = std::get<0>(semillas[i]);
        }
    }

    std::cout << '\n';
    std::cout << location << '\n';
    std::cout << '\n';
}
