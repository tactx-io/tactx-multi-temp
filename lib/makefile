# get the config file
# include ./src/$(PROJECT)/config.mk

# include the libraries
ARDUINO_VERSION=10805

ARDUINO_CORE = lib/arduino/cores/arduino
ARDUINO_LIB = lib/arduino/libraries
ARDUINO_VARIANT = lib/arduino/variants/$(VARIANT)



# arduino c sources
# from core
ARDUINO_CSRC += $(ARDUINO_CORE)/WInterrupts.c
ARDUINO_CSRC += $(ARDUINO_CORE)/hooks.c
ARDUINO_CSRC += $(ARDUINO_CORE)/wiring.c
ARDUINO_CSRC += $(ARDUINO_CORE)/wiring_analog.c
ARDUINO_CSRC += $(ARDUINO_CORE)/wiring_digital.c
ARDUINO_CSRC += $(ARDUINO_CORE)/wiring_pulse.c
ARDUINO_CSRC += $(ARDUINO_CORE)/wiring_shift.c
#ARDUINO_ASRC += $(ARDUINO_CORE)/wiring_pulse.S
# from libraries
ARDUINO_CSRC += $(ARDUINO_LIB)/Wire/src/utility/twi.c

# arduino cpp sources 
# from core

ARDUINO_CPPSRC += $(ARDUINO_CORE)/HardwareSerial.cpp
ARDUINO_CPPSRC += $(ARDUINO_CORE)/HardwareSerial0.cpp
ARDUINO_CPPSRC += $(ARDUINO_CORE)/HardwareSerial1.cpp
ARDUINO_CPPSRC += $(ARDUINO_CORE)/HardwareSerial2.cpp
ARDUINO_CPPSRC += $(ARDUINO_CORE)/HardwareSerial3.cpp
ARDUINO_CPPSRC += $(ARDUINO_CORE)/IPAddress.cpp
ARDUINO_CPPSRC += $(ARDUINO_CORE)/PluggableUSB.cpp
ARDUINO_CPPSRC += $(ARDUINO_CORE)/Print.cpp
ARDUINO_CPPSRC += $(ARDUINO_CORE)/Stream.cpp
ARDUINO_CPPSRC += $(ARDUINO_CORE)/Tone.cpp
ARDUINO_CPPSRC += $(ARDUINO_CORE)/USBCore.cpp
ARDUINO_CPPSRC += $(ARDUINO_CORE)/CDC.cpp
ARDUINO_CPPSRC += $(ARDUINO_CORE)/WMath.cpp
ARDUINO_CPPSRC += $(ARDUINO_CORE)/WString.cpp
ARDUINO_CPPSRC += $(ARDUINO_CORE)/abi.cpp
ARDUINO_CPPSRC += $(ARDUINO_CORE)/main.cpp
ARDUINO_CPPSRC += $(ARDUINO_CORE)/new.cpp
# from libraries
ARDUINO_CPPSRC += $(ARDUINO_LIB)/Wire/src/Wire.cpp
ARDUINO_CPPSRC += $(ARDUINO_LIB)/SPI/src/SPI.cpp 
ARDUINO_CPPSRC += $(ARDUINO_LIB)/SD/src/File.cpp
ARDUINO_CPPSRC += $(ARDUINO_LIB)/SD/src/SD.cpp
ARDUINO_CPPSRC += $(ARDUINO_LIB)/SD/src/utility/Sd2Card.cpp
ARDUINO_CPPSRC += $(ARDUINO_LIB)/SD/src/utility/SdFile.cpp
ARDUINO_CPPSRC += $(ARDUINO_LIB)/SD/src/utility/SdVolume.cpp

#arduino include directories
ARDUINO_INC += $(ARDUINO_CORE)
ARDUINO_INC += $(ARDUINO_VARIANT)
ARDUINO_INC += $(ARDUINO_LIB)/EEPROM/src/
ARDUINO_INC += $(ARDUINO_LIB)/SPI/src/
ARDUINO_INC += $(ARDUINO_LIB)/Wire/src
ARDUINO_INC += $(ARDUINO_LIB)/Wire/src/utility
ARDUINO_INC += $(ARDUINO_LIB)/SD/src/
ARDUINO_INC += $(ARDUINO_LIB)/SD/src/utility/





CPPSRC += lib/contributed/Adafruit_GFX_Library/Adafruit_GFX.cpp
CSRC += lib/contributed/Adafruit_GFX_Library/glcdfont.c
INC += lib/contributed/Adafruit_GFX_Library/

# Library to drive Nokia 5510 Display
CPPSRC 	  += lib/contributed/Adafruit_PCD8544/Adafruit_PCD8544.cpp
INC       += lib/contributed/Adafruit_PCD8544/

# Dallas temperature sensor ds18b20 (requires one wire)
CPPSRC    += lib/contributed/DallasTemperature/DallasTemperature.cpp
INC       += lib/contributed/DallasTemperature/

# Dallas temperature sensor ds18b20 (requires one wire)
CPPSRC            += lib/contributed/OneWire/OneWire.cpp
INC               += lib/contributed/OneWire/
INC               += lib/contributed/OneWire/util/


