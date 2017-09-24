EESchema Schematic File Version 2
LIBS:power
LIBS:device
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
LIBS:Qi-Coil switch-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Qi coil multiplexer board"
Date "2017-08-31"
Rev "1"
Comp "Pero"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L 4066 U1
U 1 1 59A738E3
P 7000 2800
F 0 "U1" H 7150 3050 50  0000 C CNN
F 1 "4066" H 7200 2950 50  0000 C CNN
F 2 "SMD_Packages:SSOP-14" H 7000 2800 60  0001 C CNN
F 3 "" H 7000 2800 60  0001 C CNN
	1    7000 2800
	1    0    0    -1  
$EndComp
$Comp
L 4066 U1
U 2 1 59A73A4E
P 7400 3200
F 0 "U1" H 7550 3450 50  0000 C CNN
F 1 "4066" H 7600 3350 50  0000 C CNN
F 2 "SMD_Packages:SSOP-14" H 7400 3200 60  0001 C CNN
F 3 "" H 7400 3200 60  0001 C CNN
	2    7400 3200
	1    0    0    -1  
$EndComp
$Comp
L 4066 U1
U 4 1 59A73C1B
P 8200 4000
F 0 "U1" H 8350 4250 50  0000 C CNN
F 1 "4066" H 8400 4150 50  0000 C CNN
F 2 "SMD_Packages:SSOP-14" H 8200 4000 60  0001 C CNN
F 3 "" H 8200 4000 60  0001 C CNN
	4    8200 4000
	1    0    0    -1  
$EndComp
$Comp
L D_Schottky D1
U 1 1 59A742BD
P 4650 5300
F 0 "D1" H 4650 5400 50  0000 C CNN
F 1 "D_Schottky" H 4650 5200 50  0001 C CNN
F 2 "Diodes_SMD:D_SMB_Handsoldering" H 4650 5300 50  0001 C CNN
F 3 "" H 4650 5300 50  0001 C CNN
	1    4650 5300
	-1   0    0    1   
$EndComp
$Comp
L C C1
U 1 1 59A74A78
P 4900 5050
F 0 "C1" H 4925 5150 50  0000 L CNN
F 1 "C" H 4925 4950 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 4938 4900 50  0001 C CNN
F 3 "" H 4900 5050 50  0001 C CNN
	1    4900 5050
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 59A74B40
P 5400 5050
F 0 "C3" H 5425 5150 50  0000 L CNN
F 1 "C" H 5425 4950 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 5438 4900 50  0001 C CNN
F 3 "" H 5400 5050 50  0001 C CNN
	1    5400 5050
	1    0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 59A74B71
P 5650 5050
F 0 "C4" H 5675 5150 50  0000 L CNN
F 1 "C" H 5675 4950 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 5688 4900 50  0001 C CNN
F 3 "" H 5650 5050 50  0001 C CNN
	1    5650 5050
	1    0    0    -1  
$EndComp
$Comp
L L L1
U 1 1 59A74DD4
P 3250 2950
F 0 "L1" V 3200 2950 50  0000 C CNN
F 1 "L" V 3325 2950 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 3250 2950 50  0001 C CNN
F 3 "" H 3250 2950 50  0001 C CNN
	1    3250 2950
	-1   0    0    1   
$EndComp
$Comp
L L L2
U 1 1 59A7525D
P 3250 3350
F 0 "L2" V 3200 3350 50  0000 C CNN
F 1 "L" V 3325 3350 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 3250 3350 50  0001 C CNN
F 3 "" H 3250 3350 50  0001 C CNN
	1    3250 3350
	-1   0    0    1   
$EndComp
$Comp
L L L3
U 1 1 59A7538D
P 3250 3750
F 0 "L3" V 3200 3750 50  0000 C CNN
F 1 "L" V 3325 3750 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 3250 3750 50  0001 C CNN
F 3 "" H 3250 3750 50  0001 C CNN
	1    3250 3750
	-1   0    0    1   
$EndComp
$Comp
L L L4
U 1 1 59A754B0
P 3250 4150
F 0 "L4" V 3200 4150 50  0000 C CNN
F 1 "L" V 3325 4150 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 3250 4150 50  0001 C CNN
F 3 "" H 3250 4150 50  0001 C CNN
	1    3250 4150
	-1   0    0    1   
$EndComp
$Comp
L D_Schottky D2
U 1 1 59A75F49
P 4650 5500
F 0 "D2" H 4650 5600 50  0000 C CNN
F 1 "D_Schottky" H 4650 5400 50  0001 C CNN
F 2 "Diodes_SMD:D_SMB_Handsoldering" H 4650 5500 50  0001 C CNN
F 3 "" H 4650 5500 50  0001 C CNN
	1    4650 5500
	-1   0    0    1   
$EndComp
$Comp
L D_Schottky D3
U 1 1 59A75F92
P 4650 5700
F 0 "D3" H 4650 5800 50  0000 C CNN
F 1 "D_Schottky" H 4650 5600 50  0001 C CNN
F 2 "Diodes_SMD:D_SMB_Handsoldering" H 4650 5700 50  0001 C CNN
F 3 "" H 4650 5700 50  0001 C CNN
	1    4650 5700
	-1   0    0    1   
$EndComp
$Comp
L D_Schottky D4
U 1 1 59A75FDC
P 4650 5900
F 0 "D4" H 4650 6000 50  0000 C CNN
F 1 "D_Schottky" H 4650 5800 50  0001 C CNN
F 2 "Diodes_SMD:D_SMB_Handsoldering" H 4650 5900 50  0001 C CNN
F 3 "" H 4650 5900 50  0001 C CNN
	1    4650 5900
	-1   0    0    1   
$EndComp
$Comp
L R R4
U 1 1 59A7A75C
P 4650 4300
F 0 "R4" V 4550 4300 50  0000 C CNN
F 1 "0R" V 4650 4300 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4580 4300 50  0001 C CNN
F 3 "" H 4650 4300 50  0001 C CNN
	1    4650 4300
	0    1    1    0   
$EndComp
$Comp
L R R3
U 1 1 59A7AD5A
P 4650 3900
F 0 "R3" V 4550 3900 50  0000 C CNN
F 1 "0R" V 4650 3900 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4580 3900 50  0001 C CNN
F 3 "" H 4650 3900 50  0001 C CNN
	1    4650 3900
	0    1    1    0   
$EndComp
$Comp
L R R2
U 1 1 59A7ADAC
P 4650 3500
F 0 "R2" V 4550 3500 50  0000 C CNN
F 1 "0R" V 4650 3500 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4580 3500 50  0001 C CNN
F 3 "" H 4650 3500 50  0001 C CNN
	1    4650 3500
	0    1    1    0   
$EndComp
$Comp
L R R1
U 1 1 59A7AE05
P 4650 3100
F 0 "R1" V 4550 3100 50  0000 C CNN
F 1 "0R" V 4650 3100 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4580 3100 50  0001 C CNN
F 3 "" H 4650 3100 50  0001 C CNN
	1    4650 3100
	0    1    1    0   
$EndComp
$Comp
L CONN_01X02 J1
U 1 1 59A94EDC
P 9650 4050
F 0 "J1" H 9650 4200 50  0000 C CNN
F 1 "CONN_01X02" V 9750 4050 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 9650 4050 50  0001 C CNN
F 3 "" H 9650 4050 50  0001 C CNN
	1    9650 4050
	1    0    0    -1  
$EndComp
$Comp
L 4066 U1
U 3 1 59A73B13
P 7800 3600
F 0 "U1" H 7950 3850 50  0000 C CNN
F 1 "4066" H 8000 3750 50  0000 C CNN
F 2 "SMD_Packages:SSOP-14" H 7800 3600 60  0001 C CNN
F 3 "" H 7800 3600 60  0001 C CNN
	3    7800 3600
	1    0    0    -1  
$EndComp
$Comp
L C C5
U 1 1 59AA043A
P 9000 2600
F 0 "C5" H 9025 2700 50  0000 L CNN
F 1 "C" H 9025 2500 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 9038 2450 50  0001 C CNN
F 3 "" H 9000 2600 50  0001 C CNN
	1    9000 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 2800 6700 2800
Wire Wire Line
	3250 3100 4500 3100
Wire Wire Line
	3250 3200 7100 3200
Wire Wire Line
	3250 3500 4500 3500
Wire Wire Line
	3250 3600 7500 3600
Wire Wire Line
	3250 3900 4500 3900
Wire Wire Line
	3250 4000 7900 4000
Connection ~ 4900 4300
Connection ~ 5400 4300
Wire Wire Line
	4250 3600 4250 5500
Wire Wire Line
	3850 5500 4500 5500
Wire Wire Line
	3850 5700 4500 5700
Wire Wire Line
	4150 5700 4150 3200
Connection ~ 4150 3200
Wire Wire Line
	3850 5900 4500 5900
Wire Wire Line
	4050 5900 4050 2800
Connection ~ 4050 2800
Connection ~ 4350 4000
Connection ~ 4250 3600
Wire Wire Line
	4800 5300 7900 5300
Wire Wire Line
	4900 5300 4900 5200
Wire Wire Line
	5150 5500 5150 5200
Wire Wire Line
	4800 5700 7100 5700
Wire Wire Line
	5400 5700 5400 5200
Wire Wire Line
	4800 5900 6700 5900
Wire Wire Line
	5650 5900 5650 5200
Wire Wire Line
	3850 5300 4500 5300
Wire Wire Line
	4350 4000 4350 5300
Wire Wire Line
	3250 4300 4500 4300
Wire Wire Line
	4800 4300 9450 4300
Connection ~ 4900 5300
Connection ~ 5150 5500
Connection ~ 5400 5700
Connection ~ 5650 5900
Wire Wire Line
	4800 5500 7500 5500
Wire Wire Line
	8200 4300 8200 4250
Connection ~ 5650 4300
Wire Wire Line
	7800 3850 7800 4300
Connection ~ 7800 4300
Wire Wire Line
	7400 3450 7400 4300
Connection ~ 7400 4300
Wire Wire Line
	7000 3050 7000 4300
Connection ~ 7000 4300
Wire Wire Line
	7300 2800 8650 2800
Wire Wire Line
	8650 2800 8650 4000
Wire Wire Line
	8500 4000 9450 4000
Wire Wire Line
	8100 3600 8650 3600
Connection ~ 8650 3600
Wire Wire Line
	7700 3200 8650 3200
Connection ~ 8650 3200
Connection ~ 8650 4000
Connection ~ 8200 4300
Wire Wire Line
	4800 3900 4900 3900
Wire Wire Line
	4900 3900 4900 4900
Wire Wire Line
	4800 3500 5150 3500
Wire Wire Line
	4800 3100 5400 3100
Wire Wire Line
	5400 3100 5400 4900
Wire Wire Line
	9450 4300 9450 4100
Wire Wire Line
	7100 5700 7100 3350
Wire Wire Line
	7500 5500 7500 3750
Wire Wire Line
	6700 5900 6700 2950
Wire Wire Line
	7900 5300 7900 4150
Wire Wire Line
	7000 2550 7000 2350
Wire Wire Line
	7000 2350 9000 2350
Wire Wire Line
	9000 2350 9000 2450
Wire Wire Line
	9000 2750 9000 4300
Connection ~ 9000 4300
$Comp
L GND #PWR01
U 1 1 59AA3872
P 9000 4300
F 0 "#PWR01" H 9000 4050 50  0001 C CNN
F 1 "GND" H 9000 4150 50  0000 C CNN
F 2 "" H 9000 4300 50  0001 C CNN
F 3 "" H 9000 4300 50  0001 C CNN
	1    9000 4300
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR02
U 1 1 59AA3BB4
P 9000 2350
F 0 "#PWR02" H 9000 2200 50  0001 C CNN
F 1 "VCC" H 9000 2500 50  0000 C CNN
F 2 "" H 9000 2350 50  0001 C CNN
F 3 "" H 9000 2350 50  0001 C CNN
	1    9000 2350
	1    0    0    -1  
$EndComp
Connection ~ 9000 2350
$Comp
L D_Schottky D5
U 1 1 59AA57BF
P 3700 5300
F 0 "D5" H 3700 5400 50  0000 C CNN
F 1 "D_Schottky" H 3700 5200 50  0001 C CNN
F 2 "Diodes_SMD:D_SMB_Handsoldering" H 3700 5300 50  0001 C CNN
F 3 "" H 3700 5300 50  0001 C CNN
	1    3700 5300
	1    0    0    -1  
$EndComp
$Comp
L D_Schottky D6
U 1 1 59AA5942
P 3700 5500
F 0 "D6" H 3700 5600 50  0000 C CNN
F 1 "D_Schottky" H 3700 5400 50  0001 C CNN
F 2 "Diodes_SMD:D_SMB_Handsoldering" H 3700 5500 50  0001 C CNN
F 3 "" H 3700 5500 50  0001 C CNN
	1    3700 5500
	1    0    0    -1  
$EndComp
$Comp
L D_Schottky D7
U 1 1 59AA59B6
P 3700 5700
F 0 "D7" H 3700 5800 50  0000 C CNN
F 1 "D_Schottky" H 3700 5600 50  0001 C CNN
F 2 "Diodes_SMD:D_SMB_Handsoldering" H 3700 5700 50  0001 C CNN
F 3 "" H 3700 5700 50  0001 C CNN
	1    3700 5700
	1    0    0    -1  
$EndComp
$Comp
L D_Schottky D8
U 1 1 59AA5A15
P 3700 5900
F 0 "D8" H 3700 6000 50  0000 C CNN
F 1 "D_Schottky" H 3700 5800 50  0001 C CNN
F 2 "Diodes_SMD:D_SMB_Handsoldering" H 3700 5900 50  0001 C CNN
F 3 "" H 3700 5900 50  0001 C CNN
	1    3700 5900
	1    0    0    -1  
$EndComp
Connection ~ 4050 5900
Connection ~ 4150 5700
Connection ~ 4250 5500
Connection ~ 4350 5300
Wire Wire Line
	3550 5300 3300 5300
Wire Wire Line
	3300 5300 3300 6000
Wire Wire Line
	3300 5900 3550 5900
Wire Wire Line
	3550 5700 3300 5700
Connection ~ 3300 5700
Wire Wire Line
	3550 5500 3300 5500
Connection ~ 3300 5500
$Comp
L C C6
U 1 1 59AA603E
P 3300 6150
F 0 "C6" H 3325 6250 50  0000 L CNN
F 1 "C" H 3325 6050 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 3338 6000 50  0001 C CNN
F 3 "" H 3300 6150 50  0001 C CNN
	1    3300 6150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 59AA64DD
P 3300 6300
F 0 "#PWR03" H 3300 6050 50  0001 C CNN
F 1 "GND" H 3300 6150 50  0000 C CNN
F 2 "" H 3300 6300 50  0001 C CNN
F 3 "" H 3300 6300 50  0001 C CNN
	1    3300 6300
	1    0    0    -1  
$EndComp
Connection ~ 3300 5900
$Comp
L VCC #PWR04
U 1 1 59AA7F92
P 3300 5300
F 0 "#PWR04" H 3300 5150 50  0001 C CNN
F 1 "VCC" H 3300 5450 50  0000 C CNN
F 2 "" H 3300 5300 50  0001 C CNN
F 3 "" H 3300 5300 50  0001 C CNN
	1    3300 5300
	1    0    0    -1  
$EndComp
Connection ~ 3300 5300
Text Label 3500 2800 0    60   ~ 0
L1+
Text Label 3500 3200 0    60   ~ 0
L2+
Text Label 3500 3600 0    60   ~ 0
L3+
Text Label 3500 4000 0    60   ~ 0
L4+
Text Label 3500 3100 0    60   ~ 0
L1-
Text Label 3500 3500 0    60   ~ 0
L2-
Text Label 3500 3900 0    60   ~ 0
L3-
Text Label 3500 4300 0    60   ~ 0
L4-
Text Label 9100 4000 0    60   ~ 0
COM
Connection ~ 5150 4300
Wire Wire Line
	5650 4900 5650 4300
Wire Wire Line
	5150 3500 5150 4900
$Comp
L C C2
U 1 1 59A74AF3
P 5150 5050
F 0 "C2" H 5175 5150 50  0000 L CNN
F 1 "C" H 5175 4950 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 5188 4900 50  0001 C CNN
F 3 "" H 5150 5050 50  0001 C CNN
	1    5150 5050
	1    0    0    -1  
$EndComp
Text Label 6050 5900 0    60   ~ 0
en_1
Text Label 6050 5700 0    60   ~ 0
en_2
Text Label 6050 5500 0    60   ~ 0
en_3
Text Label 6050 5300 0    60   ~ 0
en_4
$EndSCHEMATC
