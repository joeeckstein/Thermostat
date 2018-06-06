# Thermostat
Arduino based window fan thermostat using an I2C altimeter and Digital Loggers relay unit.

## Parts
- Arduino Uno
- [Digital Loggers IoT Power Relay](https://www.adafruit.com/product/2935)
- [MPL3115A2 - I2C Barometric Pressure/Altitude/Temperature Sensor](https://www.adafruit.com/product/1893)

## Implimentation
Sets relay to on causing the fan to run between the low and high setpoints. Deadband of 2 degrees to reduce constant cycling of the fan. All operations are performed in Celcius.

## Installing
This code relies upon the Adafruit MPL3115A2 Arduino Library.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Adafruit Libraries
