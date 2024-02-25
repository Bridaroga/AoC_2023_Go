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
	var cubosRojos int
	var cubosAzules int
	var cubosVerdes int
	const maxCubosRojos int = 12
	const maxCubosVerdes int = 13
	const maxCubosAzules int = 14
	var manoImposible bool
	var sumaJuegos int

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
		
		// Arrays de la línea separados por ;
		manoCubos := strings.Split(lineaArchivo.Text(), "; ")
		// El primer array viene con el "Game ##:", se lo quitamos acá
		manoCubos[0] = strings.Split(manoCubos[0], ": ")[1]
		for i := range manoCubos {
			// Array de cubos de colores
			cubos := strings.Split(manoCubos[i], ", ")
			for j := range cubos {
				switch {
				case strings.Contains(cubos[j], "red"):
					indiceNumero := strings.Split(cubos[j], " ")
					cubosRojos, err = strconv.Atoi(indiceNumero[0])
					if err != nil {
						log.Fatal(err)
					} else if maxCubosRojos < cubosRojos {
						manoImposible = true
					}
				case strings.Contains(cubos[j], "blue"):
					indiceNumero := strings.Split(cubos[j], " ")
					cubosAzules, err = strconv.Atoi(indiceNumero[0])
					if err != nil {
						log.Fatal(err)
					} else if maxCubosAzules < cubosAzules {
						manoImposible = true
					}
				case strings.Contains(cubos[j], "green"):
					indiceNumero := strings.Split(cubos[j], " ")
					cubosVerdes, err = strconv.Atoi(indiceNumero[0])
					if err != nil {
						log.Fatal(err)
					} else if maxCubosVerdes < cubosVerdes {
						manoImposible = true
					}
				default:
					fmt.Println("No hay cubos, :(")
				}
			}
			//fmt.Println(manoCubos)
		}
		if manoImposible {
			manoImposible = false
		} else {
			// Número del juego
			indiceNumeroJuego := strings.IndexAny(lineaArchivo.Text(), "0123456789")
			indiceDosPuntos := strings.Index(lineaArchivo.Text(), ":")
			letraJuego := lineaArchivo.Text()[indiceNumeroJuego:indiceDosPuntos]
			numeroJuego, err := strconv.Atoi(letraJuego)
			if err != nil {
				log.Fatal(err)
			} else {
				sumaJuegos += numeroJuego
			}
		}
		// fmt.Println(numeroJuego, manoCubos)
	}
	fmt.Println(sumaJuegos)
}