# Mini station de contrôle de la qualité de l’eau

| | |
|-|-|
|`Author` | Popescu-Cristea Antonio-Alexandru

## Description

Le projet consiste en une mini station de surveillance de la qualité de l’eau utilisant un Arduino Nano et plusieurs capteurs. Le système mesure la température, la turbidité et la conductivité électrique de l’eau, puis affiche les valeurs sur un écran OLED.

## Motivation

L’objectif est de créer un système simple, accessible et éducatif permettant de tester rapidement la qualité de l’eau sans dépendre de solutions commerciales coûteuses.

## Architecture

Le système est basé sur un microcontrôleur Arduino Nano qui collecte les données des capteurs et les affiche sur un écran OLED.

### Block diagram

![Block Diagram](schematics/block_diagram.png)

### Schematic

![Schematic](schematics/kicad_schematic.png)

### Components

| Device | Usage | Price |
|--------|--------|-------|
| Arduino Nano | Microcontrôleur | - |
| DS18B20 | Capteur de température | - |
| Turbidity V1.3 | Capteur de turbidité | - |
| EC Sensor | Capteur de conductivité | - |
| OLED (I2C) | Affichage des données | - |
| L9110S | Module H-Bridge | - |

### Libraries

| Library | Description | Usage |
|---------|-------------|-------|
| Wire.h | Communication I2C | Utilisé pour l’écran OLED |
| LiquidCrystal_I2C.h | Affichage LCD via I2C | Affichage des données |
| OneWire.h | Protocole OneWire | Communication avec le DS18B20 |
| DallasTemperature.h | Lecture de température | Utilisé pour le capteur DS18B20 |

## Log

<!-- write every week your progress here -->

### Week 6 - 12 May

### Week 7 - 19 May

### Week 20 - 26 May


## Reference links

<!-- Fill in with appropriate links and link titles -->

[Tutorial 1](https://www.youtube.com/watch?v=wdgULBpRoXk&t=1s&ab_channel=BenEater)

[Article 1](https://www.explainthatstuff.com/induction-motors.html)

[Link title](https://projecthub.arduino.cc/)
