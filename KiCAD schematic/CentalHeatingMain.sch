EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:Sensor_Temperature
LIBS:wemos_mini
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L DS18B20 U?
U 1 1 5B7DB8F7
P 5250 4350
F 0 "U?" V 5500 4200 50  0000 C CNN
F 1 "DS18B20" V 5000 4350 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 4250 4100 50  0001 C CNN
F 3 "" H 5100 4600 50  0001 C CNN
	1    5250 4350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4950 4350 4750 4350
Wire Wire Line
	4750 4350 4750 3800
Wire Wire Line
	5950 4350 5550 4350
Wire Wire Line
	5750 3700 5950 3700
Wire Wire Line
	4750 3100 4650 3100
Wire Wire Line
	4650 3100 4650 3300
Wire Wire Line
	4650 3300 4750 3300
$Comp
L R R?
U 1 1 5B7DBA76
P 5000 4050
F 0 "R?" V 5080 4050 50  0000 C CNN
F 1 "R" V 5000 4050 50  0000 C CNN
F 2 "" V 4930 4050 50  0001 C CNN
F 3 "" H 5000 4050 50  0001 C CNN
	1    5000 4050
	0    1    1    0   
$EndComp
Wire Wire Line
	5250 4050 5150 4050
Wire Wire Line
	4850 4050 4750 4050
Connection ~ 4750 4050
Wire Wire Line
	5250 3950 5250 4050
Wire Wire Line
	4650 3400 4750 3400
Connection ~ 5250 4050
Wire Wire Line
	5250 3950 4650 3950
Wire Wire Line
	4650 3950 4650 3400
$Comp
L SANYOU_SRD_Form_C K?
U 1 1 5B7DBAED
P 6750 3800
F 0 "K?" H 7200 3950 50  0000 L CNN
F 1 "SANYOU_SRD_Form_C" H 7200 3850 50  0000 L CNN
F 2 "Relays_THT:Relay_SPDT_SANYOU_SRD_Series_Form_C" H 8200 3750 50  0001 C CNN
F 3 "" H 6750 3800 50  0001 C CNN
	1    6750 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7050 3500 7050 3150
Wire Wire Line
	7050 3150 7500 3150
Text Label 7050 3150 0    60   ~ 0
Furnace1
Wire Wire Line
	6950 4100 6950 4500
Wire Wire Line
	6950 4500 7500 4500
Text Label 6950 4500 0    60   ~ 0
Furnace2
Wire Wire Line
	4750 3800 4250 3800
Wire Wire Line
	4250 3800 4250 2750
Wire Wire Line
	4250 2750 6200 2750
Wire Wire Line
	6200 2750 6200 3750
Wire Wire Line
	6200 3750 6350 3750
Wire Wire Line
	5950 3900 6350 3900
Wire Wire Line
	5950 2450 5950 4350
Wire Wire Line
	4750 3600 4500 3600
Wire Wire Line
	4500 3600 4500 2850
Wire Wire Line
	4500 2850 5850 2850
Wire Wire Line
	5850 2850 5850 3500
Wire Wire Line
	5850 3500 6550 3500
Text Label 6350 3500 0    60   ~ 0
CH1
NoConn ~ 6550 4100
NoConn ~ 6850 3500
NoConn ~ 5750 3600
NoConn ~ 5750 3500
NoConn ~ 5750 3400
NoConn ~ 5750 3300
NoConn ~ 4750 3200
NoConn ~ 4750 3500
NoConn ~ 4750 3700
$Comp
L WeMos_mini U?
U 1 1 5B7DB82B
P 5250 3450
F 0 "U?" H 5250 3850 60  0000 C CNN
F 1 "WeMos_mini" H 5250 2950 60  0000 C CNN
F 2 "" H 5800 2750 60  0000 C CNN
F 3 "" H 5800 2750 60  0000 C CNN
	1    5250 3450
	-1   0    0    1   
$EndComp
Wire Bus Line
	8450 1900 8450 2750
Wire Bus Line
	8450 2750 9550 2750
Wire Bus Line
	9550 2750 9550 1900
Wire Bus Line
	9550 1900 8450 1900
Text Label 8750 2350 0    60   ~ 0
NEXTION
Text Label 8450 2150 0    60   ~ 0
Vcc
Text Label 8450 2250 0    60   ~ 0
RX
Text Label 8450 2350 0    60   ~ 0
TX
Text Label 8450 2450 0    60   ~ 0
GND
Wire Wire Line
	8450 2450 5950 2450
Connection ~ 5950 3700
Wire Wire Line
	8450 2100 6050 2100
Wire Wire Line
	6050 2100 6050 3800
Wire Wire Line
	6050 3800 5750 3800
Connection ~ 5950 3900
Wire Wire Line
	8450 2200 6500 2200
Wire Wire Line
	6500 2200 6500 3100
Wire Wire Line
	6500 3100 5750 3100
Wire Wire Line
	5750 3200 6650 3200
Wire Wire Line
	6650 3200 6650 2350
Wire Wire Line
	6650 2350 8450 2350
$EndSCHEMATC
