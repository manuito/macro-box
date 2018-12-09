package modes

import (
	"bufio"
	"fmt"
	"robotoby/application"

	"github.com/tarm/serial"
)

var port *serial.Port

// Init Serial
func openSerial() *serial.Port {
	c := &serial.Config{Name: AppConfig.SerialDevice, Baud: AppConfig.SerialSpeed}
	s, err := serial.OpenPort(c)
	if err != nil {
		fmt.Println(err)
	}

	fmt.Println("Serial connection up on " + application.State.Config.SerialDevice)

	return s
}

// sendSerial : Send the given raw value using serial
func sendSerial(value string) error {

	if port == nil {
		port = openSerial()
	}

	_, err := port.Write([]byte(value))

	return err
}

// receiveSerial : Get the last received value in serial connect
func receiveSerial() (string, error) {

	if port == nil {
		port = openSerial()
	}

	// Here receive

	buf := make([]byte, 128)
	_, err := port.Read(buf)

	reader := bufio.NewReader(port)
	reply, err := reader.ReadBytes('\r')
	result := string(reply[:])

	return result, err
}
