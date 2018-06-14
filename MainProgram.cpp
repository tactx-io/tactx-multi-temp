#include "string.h"
#include <Arduino.h>
#include <WString.h>
#include <SPI.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#define MESSAGEBUFFER_SIZE 0x3FF // quite big... who cares
#define SAMPLETIME_MS 4000
#define ONE_WIRE_BUS 2
#define SENSOR_COUNT 5

// Software SPI (slower updates, more flexible pin options):
// pin 15 - Serial clock out (SCLK)
// pin 16 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 14 - LCD reset (RST)
#define DIPLAY_SCLK 15
#define DIPLAY_DIN 16
#define DIPLAY_DC 5
#define DIPLAY_CS 4
#define DIPLAY_RST 14

// Run Modes
#define REAL 0
#define FAKE 1
#define ADDRESS 2

//#define RUNMODE REAL
#define RUNMODE FAKE
//#define RUNMODE ADDRESS

// Include C headers (ie, non C++ headers) in this block
extern "C"{
#include <util/delay.h>
}

// Needed for AVR to use virtual functions
extern "C" void __cxa_pure_virtual(void);
//void __cxa_pure_virtual(void) {}

void measure(void);

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
Adafruit_PCD8544 display = Adafruit_PCD8544(DIPLAY_SCLK, DIPLAY_DIN, DIPLAY_DC, DIPLAY_CS, DIPLAY_RST);

char msgbuf[MESSAGEBUFFER_SIZE];
uint32_t lasttime = 0;
float sensorvalues[SENSOR_COUNT];

/*
 * Hard coded device addresses
 * In order to find out the right addresses compile the program
 * with RUNMODE set to ADDRESS. Right after startup the program
 * retrieves the addresses of all the sensors connected to the
 * serial bus.
 * The output represents the hexadecimal address as string. For instance
 * if one sensor has address "28FF902BB21702D6" it should be
 * set to {0x28, 0xFF, 0x90, 0x2B, 0xB2, 0x17, 0x02, 0xD6} in the
 * sensordevs array
 */

DeviceAddress sensordevs[] ={
		{0x28, 0xFF, 0xEE, 0x1C, 0xB2, 0x17, 0x02, 0xD7}, // Air temperature
		{0x28, 0xFF, 0x90, 0x2B, 0xB2, 0x17, 0x02, 0xD6}, // -0.5m
		{0x28, 0xFF, 0x20, 0x31, 0xB2, 0x17, 0x02, 0xBA}, // -1.0m
		{0x28, 0xFF, 0x46, 0x32, 0xB2, 0x17, 0x02, 0xBF}, // -1.5m
		{0x28, 0xFF, 0xD8, 0x2A, 0xB2, 0x17, 0x02, 0x8E}  // -2.0m
};

void setup(){
	Serial.begin(115200);
#if (RUNMODE == REAL)
	sensors.begin();
	display.begin();
	display.setContrast(50);
	display.clearDisplay();
	display.setTextSize(1);
	display.setTextColor(BLACK);
	display.setCursor(0,0);
	display.println("Sensorbox");
	display.display();
#endif
}

void loop(){
	if( (millis()-lasttime) > SAMPLETIME_MS){
		measure();
		lasttime = millis();
	}
}

/*
 * These are the functions that actually generate
 * the JSON formatted string containing the measured values or list
 * the addresses depending on the RUNMODE
 */
#if (RUNMODE == REAL)
/* Measure real values */
void measure(void){
	int c = 0;
	lasttime = millis();
	sensors.requestTemperatures();

	for(c = 0; c < SENSOR_COUNT; c++)
		sensorvalues[c] = sensors.getTempC(sensordevs[c]);

	Serial.print("{");
	Serial.print("\"topic-name\":\"water-temperatures\",");
	Serial.print("\"values\": [");
	Serial.print("\"");Serial.print(sensorvalues[0]);Serial.print("\",");
	Serial.print("\"");Serial.print(sensorvalues[1]);Serial.print("\",");
	Serial.print("\"");Serial.print(sensorvalues[2]);Serial.print("\",");
	Serial.print("\"");Serial.print(sensorvalues[3]);Serial.print("\",");
	Serial.print("\"");Serial.print(sensorvalues[4]);Serial.print("\"");
	Serial.print("]");
	Serial.print("}");
	Serial.println();

	display.clearDisplay();
	display.setTextSize(1);
	display.setTextColor(BLACK);

	for(c = 0; c < SENSOR_COUNT; c++){
		display.setCursor(0,c * 10);
		if(sensorvalues[c] == -127.00){
			display.print("No Sensor");
		}else{
			display.print(sensorvalues[c]);
			display.print(" C");
		}
	}
	display.display();
}


#elif (RUNMODE == ADDRESS)
// function to print the temperature for a device
void printTemperature(DeviceAddress deviceAddress){
	float tempC = sensors.getTempC(deviceAddress);
	Serial.print("Temp C: ");
	Serial.print(tempC);
}
// function to print a device address
void printAddress(DeviceAddress deviceAddress){
	for (uint8_t i = 0; i < 8; i++)	{
		// zero pad the address if necessary
		if (deviceAddress[i] < 16) Serial.print("0");
		Serial.print(deviceAddress[i], HEX);
	}
}

// actually lists the sensors
void measure(){
	uint8_t i = 0;
	uint8_t deviceCount = sensors.getDeviceCount();
	// locate devices on the bus
	Serial.print("Locating devices...");
	Serial.print("Found ");
	Serial.print(deviceCount, DEC);
	Serial.println(" devices.");

	for(i = 0; i < deviceCount; i++){
		DeviceAddress thermometer;
		Serial.print("Sensor ");
		Serial.println(i, DEC);
		if (!sensors.getAddress(thermometer, i)) Serial.println("Unable to find address for Device 1");
		printAddress(thermometer);
		Serial.println(" ");
		printTemperature(thermometer);
		Serial.println();
		Serial.println();
	}
}
#elif (RUNMODE == FAKE)
// fake some values
void measure(){
	uint16_t c = 0;
	for(c = 0; c < SENSOR_COUNT; c++)
		sensorvalues[c] = 22.55F;

	Serial.print("{");
	Serial.print("\"topic-name\":\"water-temperatures\",");
	Serial.print("\"values\": [");
	Serial.print("\"");Serial.print(sensorvalues[0]);Serial.print("\",");
	Serial.print("\"");Serial.print(sensorvalues[1]);Serial.print("\",");
	Serial.print("\"");Serial.print(sensorvalues[2]);Serial.print("\",");
	Serial.print("\"");Serial.print(sensorvalues[3]);Serial.print("\",");
	Serial.print("\"");Serial.print(sensorvalues[4]);Serial.print("\"");
	Serial.print("]");
	Serial.print("}");
	Serial.println();
}

#else
#error "RUNMODE not defined"
#endif
