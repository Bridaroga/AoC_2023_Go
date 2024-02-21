package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
	"log"
	// "time"
)

func main() {
	// fmt.Println("El tiempo es: ", time.Now())

	// Contador
	contador := 0

	// Abrir el archivo, ojalá que sin errores.
	cDocument, err := os.Open("Calibration document.txt")
	if err != nil {
		log.Fatal(err)
	} else {
		fmt.Println("El archivo abrió, :D")
	}
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
		
		// fmt.Println(primerNumero * 10 + ultimoNumero)
		contador += primerNumero * 10 + ultimoNumero	// Porque sí, >:C
	}

	if err := lineaArchivo.Err(); err != nil {
		log.Fatal(err)
	}

	fmt.Println(contador)
	// fmt.Println("El tiempo es: ", time.Now())
}