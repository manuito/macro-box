package modes

import (
	"encoding/json"
	"fmt"
	"os"
)

/*
 * Uses file "conf.json" for configuration definition
 */
var AppConfig = loadConfiguration()

// Configuration : full app configuration holder
type Configuration struct {
	SerialDevice string
	SerialSpeed  int
}

func loadConfiguration() Configuration {
	file, _ := os.Open("conf.json")
	defer file.Close()
	decoder := json.NewDecoder(file)
	configuration := Configuration{}
	err := decoder.Decode(&configuration)
	if err != nil {
		fmt.Println("error:", err)
	}
	return configuration
}
