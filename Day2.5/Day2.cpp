// Day2.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <fstream>
#include <map>
#include <tuple>
#include <string>

int main()
{
    std::ifstream gameDocument("games.txt");

    const int redMax = 99;
    const int greenMax = 99;
    const int blueMax = 99;
    std::string lineaArchivo{ "" };
    const std::string game{ "Game " };
    std::string subLineaArchivo{ "" };
    const std::string palabraRed{ "red" };
    const std::string palabraGreen{ "green" };
    const std::string palabraBlue{ "blue" };

    int numGame{ 0 };
    int red{ 0 };
    int green{ 0 };
    int blue{ 0 };
    int gameValido{ 0 };
    int minRed{ 0 };
    int minGreen{ 0 };
    int minBlue{ 0 };
    int powerMin{ 0 };

    std::size_t posRed{};
    std::size_t posGreen{};
    std::size_t posBlue{};

    bool max{ false };

    //std::map<int, std::tuple<int, int, int>> cubes{};   //  tuple <red, green, blue>
    std::map<std::size_t, char> separadores{};

    while (!gameDocument.eof()) {
        std::getline(gameDocument, lineaArchivo);
        numGame = std::stoi(lineaArchivo.substr(game.length(), lineaArchivo.find(':') - game.length()));
        
        for (std::size_t i = 0; i < lineaArchivo.length(); i++) {
            if (lineaArchivo[i] == ';' || lineaArchivo[i] == ':') {
                separadores[i] = lineaArchivo[i];
            }
        }

        for (auto& it : separadores) {
            subLineaArchivo = lineaArchivo.substr(it.first + 1, lineaArchivo.find(';', it.first + 1) - it.first);

            posRed = subLineaArchivo.find(palabraRed);
            posGreen = subLineaArchivo.find(palabraGreen);
            posBlue = subLineaArchivo.find(palabraBlue);

            if (posRed != std::string::npos) {
                red = std::stoi(subLineaArchivo.substr(posRed - 3, 2));
                if (red > redMax) {
                    max = true;
                    break;
                }
                if (minRed < red) {
                    minRed = red;
                }
            }
            else {
                red = 0;
            }

            if (posGreen != std::string::npos) {
                green = std::stoi(subLineaArchivo.substr(posGreen - 3, 2));
                if (green > greenMax) {
                    max = true;
                    break;
                }
                if (minGreen < green) {
                    minGreen = green;
                }
            }
            else {
                green = 0;
            }

            if (posBlue != std::string::npos) {
                blue = std::stoi(subLineaArchivo.substr(posBlue - 3, 2));
                if (blue > blueMax) {
                    max = true;
                    break;
                }
                if (minBlue < blue) {
                    minBlue = blue;
                }
            }
            else {
                blue = 0;
            }

            std::cout << minRed << "  " << minGreen << "  " << minBlue << '\n';
            //std::cout << red << green << blue << '\n';
            //std::cout << subLineaArchivo << '\n';
        }

        if (!max) {
            gameValido += numGame;
        }


        powerMin += minRed * minGreen * minBlue;

        std::cout << powerMin << '\n';
        //subLineaArchivo = lineaArchivo.substr(lineaArchivo.find(":") + 2, lineaArchivo.find(";") + 3);
        //  red
        //red += std::stoi(lineaArchivo.substr(lineaArchivo.find("red") - 2));

        minRed = 0;
        minGreen = 0;
        minBlue = 0;
        max = false;
        separadores.clear();
    }


}
