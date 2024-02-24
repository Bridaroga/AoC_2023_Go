package main

import (
	"fmt"
	"bufio"
	"os"
	"log"
	"strings"
	"strconv"
)

func main() {
	// Variables
	var cubosRojos, maxCubosRojos int
	var cubosAzules, maxCubosAzules int
	var cubosVerdes, maxCubosVerdes int
	var sumaMultiplicaciones int

	// Abrir el archivo, ojalá que sin errores.
	cDocument, err := os.Open("Games.txt")
	if err != nil {
		log.Fatal(err)
	}
	// Posterga el cierre del archivo hasta que terminan las demás líneas.
	defer cDocument.Close()

	// Scanner para leer cada línea del archivo
	lineaArchivo := bufio.NewScanner(cDocument)
	for lineaArchivo.Scan() {
		// fmt.Println(lineaArchivo.Text())
		// Número del juego
		// indiceNumeroJuego := strings.IndexAny(lineaArchivo.Text(), "0123456789")
		// indiceDosPuntos := strings.Index(lineaArchivo.Text(), ":")
		// numeroJuego := lineaArchivo.Text()[indiceNumeroJuego:indiceDosPuntos]
		
		// Arrays de la línea separados por ;
		manoCubos := strings.Split(lineaArchivo.Text(), "; ")
		// El primer array viene con el "Game ##:", se lo quitamos acá
		manoCubos[0] = strings.Split(manoCubos[0], ": ")[1]
		for i := range manoCubos {
			cubos := strings.Split(manoCubos[i], ", ")
			for j := range cubos {
				switch {
				case strings.Contains(cubos[j], "red"):
					indiceNumero := strings.Split(cubos[j], " ")
					cubosRojos, err = strconv.Atoi(indiceNumero[0])
					if err != nil {
						log.Fatal(err)
					} else if maxCubosRojos < cubosRojos {
						maxCubosRojos = cubosRojos
					}
				case strings.Contains(cubos[j], "blue"):
					indiceNumero := strings.Split(cubos[j], " ")
					cubosAzules, err = strconv.Atoi(indiceNumero[0])
					if err != nil {
						log.Fatal(err)
					} else if maxCubosAzules < cubosAzules {
						maxCubosAzules = cubosAzules
					}
				case strings.Contains(cubos[j], "green"):
					indiceNumero := strings.Split(cubos[j], " ")
					cubosVerdes, err = strconv.Atoi(indiceNumero[0])
					if err != nil {
						log.Fatal(err)
					} else if maxCubosVerdes < cubosVerdes {
						maxCubosVerdes = cubosVerdes
					}
				default:
					fmt.Println("No hay cubos, :(")
				}
			}
			//fmt.Println(manoCubos)
		}
		sumaMultiplicaciones += maxCubosRojos * maxCubosAzules * maxCubosVerdes
		// fmt.Println(numeroJuego, manoCubos, sumaMultiplicaciones)
		maxCubosRojos = 0
		maxCubosAzules = 0
		maxCubosVerdes = 0
	}
	fmt.Println(sumaMultiplicaciones)
}