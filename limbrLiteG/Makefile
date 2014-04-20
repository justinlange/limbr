#
# embedXcode
# ----------------------------------
# Embedded Computing on Xcode
#
# Copyright © Rei VILO, 2010-2014
# All rights reserved
# http://embedxcode.weebly.com
#
# Last update: Mar 01, 2014 release 136


# Libraries
# ----------------------------------
# Declare application Arduino/chipKIT/Digispark/Energia/Maple/Microduino/Teensy/Wiring
# and user's libraries used 
# Short-listing libraries speeds-up building
# Typing = 0 takes none (default for application and user)
# Otherwise, leaving empty considers all (default for local)

# List application Arduino/chipKIT/Digispark/Energia/Maple/Microduino/Teensy/Wiring libraries here
# default = 0 = none
#
# ARDUINO = EEPROM Esplora Ethernet Firmata GSM 
#	LiquidCrystal LiquidCrystalFast Robot_Control Robot_Motor SD Servo 
#	SoftwareSerial SPI Stepper TFT WiFi Wire 
# TEENSY = AccelStepper Adafruit_GFX Adafruit_ILI9340 
#	Adafruit_RA8875 Adafruit_SSD1306 Adafruit_ST7735 AltSoftSerial Bounce 
#	CapacitiveSensor DmxSimple DogLcd DS1307RTC EEPROM Encoder Entropy 
#	Esplora Ethernet FastLED Firmata FlexiTimer2 FreqCount
#	FreqMeasure FrequencyTimer2 GSM IRremote Keypad ks0108 LedControl 
#	LedDisplay LiquidCrystal LiquidCrystalFast LowPower Metro MIDI 
#	MsTimer2 NeoPixel NewSoftSerial OctoWS2811 OneWire OSC Ping 
#	PS2Keyboard PWMServo Robot_Control Robot_Motor SD Servo ShiftPWM 
#	SoftPWM SoftwareSerial SPI ST7565 Stepper TFT Time TimeAlarms 
#	TimerOne TimerThree TinyGPS Tlc5940 UTFT VirtualWire WiFi Wire 
#	x10 XBee 
#
APP_LIBS_LIST = Metro FastLED Wire

# List user's libraries here 
# default = 0 = none
#
# USER = Adafruit_NeoPixel adxl345driver AFmotor 
#	ArduinoWebsocketClient BlinkyTape_Arduino bma180 bmp085driver color DebugUtils 
#	FastLED FreeIMU HMC58X3 I2Cdev i2cdevlib itg3200filv05 LPD8806 
#	MPU60X0 MS561101BA Spacebrew 
#
USER_LIBS_LIST = Adafruit_Sensor Adafruit_LSM303DLHC Adafruit_L3GD20_U Adafruit_9DOF T3Libs

# List local libraries here
# default = empty = all
#
LOCAL_LIBS_LIST = 0

# List core, application and user's libraries to be excluded
# For example, WiFi may crash on Arduino 1.0.2, Esplora on Arduino 1.0.3, Firmata on Teensy 3.0,
#   OneWire on MPIDE 0023, HardwareSerial may conflict with MarlinSerial
#
#EXCLUDE_LIBS = Firmata WiFi Esplora OneWire Robot_Control Robot_Control/utility Robot_Motor


# Warning options
# ----------------------------------
# Contrary to errors, warnings don't stop compilation but they point at possible cause of errors.
# For example, unused variables with unused-variable.
#
# If 0, no warnings
# If empty, all warnings, same as WARNING_OPTIONS = all
# WARNING_OPTIONS = all no-missing-braces no-conversion-null no-pointer-arith
# WARNING_OPTIONS = unused-variable unused-function unused-label unused-value no-conversion-null no-pointer-arith
#
WARNING_OPTIONS = all unused-variable unused-function unused-label unused-value no-conversion-null no-pointer-arith


# Parameters
# ----------------------------------
# Xcode takes BOARD_TAG and BOARD_PORT from the .xcconfig file
# For other IDEs than Xcode,

# BOARD_TAG is required
# If not defined, error BOARD_TAG not defined
#
#BOARD_TAG  = mega2560

# BOARD_PORT is optional
# If not defined, BOARD_PORT = /dev/tty.usb* (default)
#
#BOARD_PORT = /dev/tty.usbmodem*

# Xcode takes SKETCHBOOK_DIR from preferences.txt
# If not defined, each IDE has its own SKETCHBOOK_DIR (default)
# To share the same SKETCHBOOK_DIR along all IDEs, define
#
#SKETCHBOOK_DIR =

# SERIAL_BAUDRATE for the serial console, 9600 by default
# Uncomment and specify another speed
#
#SERIAL_BAUDRATE = 19200


# Miscellaneous
# ----------------------------------
# Manage path with space in the name
#
CURRENT_DIR   := $(shell pwd)
CURRENT_DIR   := $(shell echo '$(CURRENT_DIR)' | sed 's/ /\\\ /g')

# C-compliant project name
#
PROJECT_NAME_AS_IDENTIFIER = limbrLiteG

MAKEFILE_PATH  = $(CURRENT_DIR)/Makefiles
UTILITIES_PATH = $(CURRENT_DIR)/Utilities

include $(MAKEFILE_PATH)/Step1.mk


