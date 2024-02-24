package main

import (
	"fmt"
	"bufio"
	"os"
	"log"
	"strings"
	// "tuples", :'v
)

func main() {
	// Abrir el archivo, ojalá que sin errores.
	cDocument, err := os.Open("Games.txt")
	if err != nil {
		log.Fatal(err)
	} /*else {
		fmt.Println("El archivo abrió, :D")
	}*/
	// Posterga el cierre del archivo hasta que terminan las demás líneas.
	defer cDocument.Close()

	
}