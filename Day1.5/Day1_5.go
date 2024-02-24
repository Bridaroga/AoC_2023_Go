package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
	"strconv"
	"log"
	// "time"
)

func main() {
	// fmt.Println("El tiempo es: ", time.Now())

	// map de los números escritos en letras.
	numerosLetras := map[string]string{
		"one": "1",
		"two": "2",
		"three": "3",
		"four": "4",
		"five": "5",
		"six": "6",
		"seven": "7",
		"eight": "8",
		"nine": "9",
	}

	// Contador
	contador := 0

	// Abrir el archivo, ojalá que sin errores.
	cDocument, err := os.Open("Calibration document.txt")
	if err != nil {
		log.Fatal(err)
	} /*else {
		fmt.Println("El archivo abrió, :D")
	}*/
	// Posterga el cierre del archivo hasta que terminan las demás líneas.
	defer cDocument.Close()

	lineaArchivo := bufio.NewScanner(cDocument)
	for lineaArchivo.Scan() {
		// fmt.Println(lineaArchivo.Text())
		primerIndice := strings.IndexAny(lineaArchivo.Text(), "1234567890")
		primerNumero := int([]rune(lineaArchivo.Text())[primerIndice] - '0')
		ultimoIndice := strings.LastIndexAny(lineaArchivo.Text(), "1234567890")
		ultimoNumero := int([]rune(lineaArchivo.Text())[ultimoIndice] - '0')
		// fmt.Println(primerIndice, ultimoIndice, primerNumero, ultimoNumero)

		for numLetra, digito := range numerosLetras {
			primerLetraIndice := strings.Index(lineaArchivo.Text(), numLetra)
			if primerLetraIndice == -1 {
				continue
			} else {
				if primerLetraIndice < primerIndice {
					primerIndice = primerLetraIndice
					primerNumero, err = strconv.Atoi(digito)
					if err != nil {
						log.Fatal(err)
					}
				}
			}

			ultimaLetraIndice := strings.LastIndex(lineaArchivo.Text(), numLetra)
			if ultimoIndice < ultimaLetraIndice {
				ultimoIndice = ultimaLetraIndice
				ultimoNumero, err = strconv.Atoi(digito)
				if err != nil {
					log.Fatal(err)
				}
			}
		}

		// fmt.Println(primerNumero * 10 + ultimoNumero)
		contador += primerNumero * 10 + ultimoNumero	// Porque sí, >:C
	}

	if err := lineaArchivo.Err(); err != nil {
		log.Fatal(err)
	}

	fmt.Println(contador)
	// fmt.Println("El tiempo es: ", time.Now())
}