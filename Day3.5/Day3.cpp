// Day3.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
// 
// 
// Importar 3 líneas, primero una, si la segunda o tercera andan libres, continue; para importar la siguiente, hasta tener 3 líneas.
// Trabajar la primera, luego la segunda, luego la tercera.
// Cuando se encuentre un símbolo, buscar en las 8 direcciones aledañas.
// cuando se termine de trabajar las 3 líneas, la primera copia la segunda, la segunda copia la tercera, la tercera importa otra línea.
// FIM, @_@
//

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <tuple>

int main() {
    std::ifstream engineDocument("Engine Schematic.txt");

    std::string primerLinea{ "" };
    std::string segundaLinea{ "" };
    std::string tercerLinea{ "" };
    std::string subSegundaLinea{ "" };
    std::string subBuscarCaracter{ "" };

    int contadorLineas{ 1 };
    int sumaNumeros{ 0 };
    int numeroUno{ 1 };
    int productoNumeros{ 0 };

    std::size_t posSimbolo{ 0 };
    std::size_t posNumero{ 0 };
    std::size_t inicioNumero{ 0 };
    std::size_t finNumero{ 0 };
    std::size_t anchoNumero{ 0 };
    std::size_t buscarNumeroIzq{ 0 };
    std::size_t buscarNumeroDer{ 0 };

    std::map<std::tuple<int, std::size_t>, std::string> simbolos{}; // <# de línea, posición del símbolo>, símbolo
    std::map<std::tuple<int, std::size_t>, std::tuple<int, std::size_t>> numeros{}; // <# de línea, posición del símbolo>, <número, 'dígitos del número>
    std::map<int, int> numerosEngine{}; // <Posición alrededor del *, valor>

    while (tercerLinea != "FIM") {
        primerLinea = segundaLinea;
        segundaLinea = tercerLinea;
        if (!engineDocument.eof()) {
            std::getline(engineDocument, tercerLinea);
        }
        else {
            tercerLinea = "FIM";
        }

        if (segundaLinea == "") { continue; }

        // Busca símbolos en la línea y guarda solamente los *.
        while (posSimbolo != std::string::npos) {
            posSimbolo = segundaLinea.find_first_of("*", posSimbolo);
            if (posSimbolo != std::string::npos) {
                simbolos[{contadorLineas, posSimbolo}] = segundaLinea[posSimbolo];

                // Busca números en la primer línea.
                if (primerLinea != "") {
                    if (posSimbolo > 0 && posSimbolo < segundaLinea.length()) {
                        if (primerLinea.find_last_of("1234567890", posSimbolo - 1) == posSimbolo - 1 && 
                            primerLinea.find_first_not_of("1234567890", posSimbolo) == posSimbolo) {
                            inicioNumero = primerLinea.find_last_not_of("1234567890", posSimbolo - 1) + 1;
                            finNumero = primerLinea.find_first_not_of("1234567890", inicioNumero);
                            numerosEngine[1] = std::stoi(primerLinea.substr(inicioNumero, finNumero - inicioNumero));
                            if (primerLinea.find_first_of("1234567890", posSimbolo + 1) == posSimbolo + 1) {
                                finNumero = primerLinea.find_first_not_of("1234567890", posSimbolo + 1);
                                inicioNumero = primerLinea.find_last_not_of("1234567890", finNumero - 1) + 1;
                                numerosEngine[2] = std::stoi(primerLinea.substr(inicioNumero, finNumero - inicioNumero));
                            }
                        }
                        else if (primerLinea.find_last_of("1234567890", posSimbolo - 1) == posSimbolo - 1) {
                            inicioNumero = primerLinea.find_last_not_of("1234567890", posSimbolo - 1) + 1;
                            finNumero = primerLinea.find_first_not_of("1234567890", inicioNumero);
                            numerosEngine[1] = std::stoi(primerLinea.substr(inicioNumero, finNumero - inicioNumero));
                        }
                        else {
                            if (primerLinea.find_first_of("1234567890", posSimbolo) <= posSimbolo + 1) {
                                inicioNumero = primerLinea.find_first_of("1234567890", posSimbolo);
                                finNumero = primerLinea.find_first_not_of("1234567890", inicioNumero);
                                numerosEngine[1] = std::stoi(primerLinea.substr(inicioNumero, finNumero - inicioNumero));
                            }
                        }
                        inicioNumero = 0;
                        finNumero = 0;
                    }
                    else if (posSimbolo == 0) {
                        if (primerLinea.find_first_of("1234567890") <= posSimbolo + 1) {
                            inicioNumero = primerLinea.find_first_of("1234567890");
                            finNumero = primerLinea.find_first_not_of("1234567890", inicioNumero);
                            numerosEngine[1] = std::stoi(primerLinea.substr(inicioNumero, finNumero - inicioNumero));
                        }
                        inicioNumero = 0;
                        finNumero = 0;
                    }
                    else {
                        if (primerLinea.find_last_of("1234567890") >= posSimbolo - 1) {
                            finNumero = primerLinea.find_last_of("1234567890");
                            inicioNumero = primerLinea.find_last_not_of("1234567890", finNumero) + 1;
                            numerosEngine[1] = std::stoi(primerLinea.substr(inicioNumero, finNumero - inicioNumero));
                        }
                        inicioNumero = 0;
                        finNumero = 0;
                    }
                }

                // Busca números en la segunda línea.
                if (posSimbolo > 0 && posSimbolo < segundaLinea.length()) {
                    if (segundaLinea.find_last_of("1234567890", posSimbolo - 1) == posSimbolo - 1) {
                        finNumero = posSimbolo;
                        inicioNumero = segundaLinea.find_last_not_of("1234567890", finNumero - 1) + 1;
                        numerosEngine[3] = std::stoi(segundaLinea.substr(inicioNumero, finNumero - inicioNumero));
                    }
                    if (segundaLinea.find_first_of("1234567890", posSimbolo + 1) == posSimbolo + 1) {
                        inicioNumero = posSimbolo + 1;
                        finNumero = segundaLinea.find_first_not_of("1234567890", inicioNumero);
                        numerosEngine[4] = std::stoi(segundaLinea.substr(inicioNumero, finNumero - inicioNumero));
                    }
                    inicioNumero = 0;
                    finNumero = 0;
                }
                else if (posSimbolo == 0) {
                    if (segundaLinea.find_first_of("1234567890", posSimbolo + 1) == posSimbolo + 1) {
                        inicioNumero = posSimbolo + 1;
                        finNumero = segundaLinea.find_first_not_of("1234567890", inicioNumero);
                        numerosEngine[3] = std::stoi(segundaLinea.substr(inicioNumero, finNumero - inicioNumero));
                    }
                    inicioNumero = 0;
                    finNumero = 0;
                }
                else {
                    if (segundaLinea.find_last_of("1234567890", posSimbolo - 1) == posSimbolo - 1) {
                        finNumero = posSimbolo;
                        inicioNumero = segundaLinea.find_last_not_of("1234567890", finNumero - 1) + 1;
                        numerosEngine[3] = std::stoi(segundaLinea.substr(inicioNumero, finNumero - inicioNumero));
                    }
                    inicioNumero = 0;
                    finNumero = 0;
                }

                // Busca números en la tercer línea.
                if (posSimbolo > 0 && posSimbolo < segundaLinea.length()) {
                    if (tercerLinea.find_last_of("1234567890", posSimbolo - 1) == posSimbolo - 1 &&
                        tercerLinea.find_first_not_of("1234567890", posSimbolo) == posSimbolo) {
                        inicioNumero = tercerLinea.find_last_not_of("1234567890", posSimbolo - 1) + 1;
                        finNumero = tercerLinea.find_first_not_of("1234567890", inicioNumero);
                        numerosEngine[5] = std::stoi(tercerLinea.substr(inicioNumero, finNumero - inicioNumero));
                        if (tercerLinea.find_first_of("1234567890", posSimbolo + 1) == posSimbolo + 1) {
                            finNumero = tercerLinea.find_first_not_of("1234567890", posSimbolo + 1);
                            inicioNumero = tercerLinea.find_last_not_of("1234567890", finNumero - 1) + 1;
                            numerosEngine[6] = std::stoi(tercerLinea.substr(inicioNumero, finNumero - inicioNumero));
                        }
                    }
                    else if (tercerLinea.find_last_of("1234567890", posSimbolo - 1) == posSimbolo - 1) {
                        inicioNumero = tercerLinea.find_last_not_of("1234567890", posSimbolo - 1) + 1;
                        finNumero = tercerLinea.find_first_not_of("1234567890", inicioNumero);
                        numerosEngine[5] = std::stoi(tercerLinea.substr(inicioNumero, finNumero - inicioNumero));
                    }
                    else {
                        if (tercerLinea.find_first_of("1234567890", posSimbolo) <= posSimbolo + 1) {
                            inicioNumero = tercerLinea.find_first_of("1234567890", posSimbolo);
                            finNumero = tercerLinea.find_first_not_of("1234567890", inicioNumero);
                            numerosEngine[5] = std::stoi(tercerLinea.substr(inicioNumero, finNumero - inicioNumero));
                        }
                    }
                    inicioNumero = 0;
                    finNumero = 0;
                }
                else if (posSimbolo == 0) {
                    if (tercerLinea.find_first_of("1234567890") <= posSimbolo + 1) {
                        inicioNumero = tercerLinea.find_first_of("1234567890");
                        finNumero = tercerLinea.find_first_not_of("1234567890", inicioNumero);
                        numerosEngine[5] = std::stoi(tercerLinea.substr(inicioNumero, finNumero - inicioNumero));
                    }
                    inicioNumero = 0;
                    finNumero = 0;
                }
                else {
                    if (tercerLinea.find_last_of("1234567890") >= posSimbolo - 1) {
                        finNumero = tercerLinea.find_last_of("1234567890");
                        inicioNumero = tercerLinea.find_last_not_of("1234567890", finNumero) + 1;
                        numerosEngine[5] = std::stoi(tercerLinea.substr(inicioNumero, finNumero - inicioNumero));
                    }
                    inicioNumero = 0;
                    finNumero = 0;
                }

                // Comprobar que solamente hayan 2 numerosEngine y multiplicarlos.
                if (numerosEngine.size() == 2) {
                    for (auto& it : numerosEngine) {
                        numeroUno *= it.second;
                    }
                    productoNumeros += numeroUno;
                    numeroUno = 1;
                }

                numerosEngine.clear();
                posSimbolo++;
            }
            std::cout << contadorLineas << "    " << productoNumeros << '\n';
        }

        // Busca números y sus dígitos.
        while (posNumero != std::string::npos) {
            posNumero = segundaLinea.find_first_of("1234567890", posNumero);
            if (posNumero != std::string::npos) {
                finNumero = segundaLinea.find_first_not_of("1234567890", posNumero);
                anchoNumero = finNumero - posNumero;
                if (finNumero != std::string::npos) {
                    subSegundaLinea = segundaLinea.substr(posNumero, anchoNumero);
                }
                else {
                    subSegundaLinea = segundaLinea.substr(posNumero);
                }

                numeros[{contadorLineas, posNumero}] = { std::stoi(subSegundaLinea), anchoNumero };
                
                // Buscar símbolos alrededor de los números
                // Buscar arriba del número
                if (primerLinea != "") {
                    if (posNumero != 0) {
                        if (finNumero == std::string::npos) {
                            subBuscarCaracter = primerLinea.substr(posNumero - 1);
                        }
                        else {
                            subBuscarCaracter = primerLinea.substr(posNumero - 1, anchoNumero + 2);
                        }
                        if (subBuscarCaracter.find_first_not_of(".1234567890") != std::string::npos) {
                            sumaNumeros += std::stoi(subSegundaLinea);
                            subSegundaLinea = "";
                        }
                    }
                    else {
                        if (finNumero == std::string::npos) {
                            subBuscarCaracter = primerLinea.substr(posNumero);
                        }
                        else {
                            subBuscarCaracter = primerLinea.substr(posNumero, anchoNumero + 2);
                        }
                        if (subBuscarCaracter.find_first_not_of(".1234567890") != std::string::npos) {
                            sumaNumeros += std::stoi(subSegundaLinea);
                            subSegundaLinea = "";
                        }
                    }
                }
                if (subSegundaLinea == "") {
                    posNumero += anchoNumero;
                    continue;
                }
                // Busca a los lados del número
                if (posNumero != 0) {
                    if (finNumero == std::string::npos) {
                        subBuscarCaracter = segundaLinea.substr(posNumero - 1);
                    }
                    else {
                        subBuscarCaracter = segundaLinea.substr(posNumero - 1, anchoNumero + 2);
                    }
                    if (subBuscarCaracter.find_first_not_of(".1234567890") != std::string::npos) {
                        sumaNumeros += std::stoi(subSegundaLinea);
                        subSegundaLinea = "";
                    }
                }
                else {
                    if (finNumero == std::string::npos) {
                        subBuscarCaracter = segundaLinea.substr(posNumero);
                    }
                    else {
                        subBuscarCaracter = segundaLinea.substr(posNumero, anchoNumero + 2);
                    }
                    if (subBuscarCaracter.find_first_not_of(".1234567890") != std::string::npos) {
                        sumaNumeros += std::stoi(subSegundaLinea);
                        subSegundaLinea = "";
                    }
                }
                if (subSegundaLinea == "") {
                    posNumero += anchoNumero;
                    continue;
                }
                // Busca abajo del número
                if (tercerLinea != "FIM") {
                    if (posNumero != 0) {
                        if (finNumero == std::string::npos) {
                            subBuscarCaracter = tercerLinea.substr(posNumero - 1);
                        }
                        else {
                            subBuscarCaracter = tercerLinea.substr(posNumero - 1, anchoNumero + 2);
                        }
                        if (subBuscarCaracter.find_first_not_of(".1234567890") != std::string::npos) {
                            sumaNumeros += std::stoi(subSegundaLinea);
                        }
                    }
                    else {
                        if (finNumero == std::string::npos) {
                            subBuscarCaracter = tercerLinea.substr(posNumero);
                        }
                        else {
                            subBuscarCaracter = tercerLinea.substr(posNumero, anchoNumero + 2);
                        }
                        if (subBuscarCaracter.find_first_not_of(".1234567890") != std::string::npos) {
                            sumaNumeros += std::stoi(subSegundaLinea);
                        }
                    }
                }

                posNumero += anchoNumero;
            }
        }

        std::cout << sumaNumeros << '\n';
        //std::cout << "1) " << primerLinea << '\n' << "2) " << segundaLinea << '\n' << "3) " << tercerLinea << "\n\n";
        contadorLineas++;
        posSimbolo = 0;
        posNumero = 0;
    }



    //for (auto& it : simbolos) {

    //}

    //for (auto& it : numeros) {
    //    std::cout << std::get<0>(it.first) << " " << std::get<1>(it.first) << " = " << std::get<0>(it.second) << " " << std::get<1>(it.second) << " -> " << sumaNumeros << '\n';
    //}
}
