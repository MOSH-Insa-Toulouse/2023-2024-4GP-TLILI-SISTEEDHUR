
<h1 align="center"> Projet Capteur graphite </h1>
<h2 align="center"> TLILI Maxime - SISTEEDHUR Lakshitaa </h2>
<h3 align="center"> INSA Toulouse - département Génie Physique - 2024 </h3>


## Introduction au projet

&nbsp;&nbsp;&nbsp;&nbsp;Ce projet se construit dans le cadre de l'UF "Du capteur au banc de test" de la 4ème année du parcours Génie Physique à l'Institut National des Sciences Appliquées (INSA) de Toulouse. Il permet une approche novatrice et lowtech dans la mesure de contrainte en se basant sur les propriétés du graphite. Il fait référence à l'article "Pencil Drawn Strain Gauges and Chemiresistors on Paper" de Cheng-Wei Lin, Zhibo Zhao, Jaemyung Kim et Jiaxing Huang.

&nbsp;&nbsp;&nbsp;&nbsp;Au cours de ce projet, nous avons réalisé un dispositif permettant de relever des mesures de contrainte à partir d'une feuille en papier sur laquelle était déposée du graphène. Par déformation du papier, il y a variation du nombre de particules de graphite déposé sur le papier, et ainsi la résistance est modifiée. Il est donc possible de réaliser un capteur de déformation low-tech, que nous appellerons par la suite "capteur graphite".

## Livrables

Les livrables du projet sont :
    - [] Le PCB du Shield Arduino
    - [] Le code Arduino permettant de faire la mesure de la résistance du capteur graphite
    - [] L'application Android pour un pilotage bluetooth du système
    - [] Le banc de test du capteur
    - [] La datasheet du capteur
Pour notre projet, nous avons opté pour ajouter un écran OLED servant de menu, du flex sensor commercial pour avoir un comparatif avec notre capteur, ainsi que d'un potentiomètre digital pour différentes fonctionnalités.

## Sommaire
***
    - [Matériel nécéssaire](#matériel-nécéssaire)
    - [1. Simulation électronique du capteur graphite sous LTSpice](#1-simulation-électronique-du-capteur-graphite-sous-ltspice)
    - [2. PCB via KiCad](#2-pcb-via-kicad)
    - [3. Réalisation du Shield](#3-réalisation-du-shield)
    - [4. Code Arduino](#4-code-arduino)
    - [5. Application Android](#5-application-android)
    - [6. Banc de test](#6-banc-de-test)
    - [Datasheet](#datasheet)
    - [Contact](#contact)


## Matériel nécéssaire

 - 1 Carte [Arduino UNO](https://store.arduino.cc/products/arduino-uno-rev3)
 - 1 Ecran [OLED-01](https://www.gotronic.fr/art-afficheur-oled-0-96-i2c-oled01-31506.htm)  128x64
 - 1 Amplificateur Opérationnel [LTC1050](https://www.analog.com/en/products/ltc1050.html)
 - 1 Potentiomètre Digital [MCP-41050](https://www.microchip.com/en-us/product/mcp41050)
 - 1 Module Bluetooth [HC-05](https://www.gotronic.fr/art-module-bluetooth-hc05-26097.htm)
 - 1 Encodeur Rotatoire [KY-040](https://www.az-delivery.de/fr/products/drehimpulsgeber-modul)
 - 1 Capteur [FLEXSENSOR](https://store.spectrasymbol.com/products/flex-sensor)
 - 5 Résistances (X2 100kOhm, X1 47kOhm, X1 10kOhm, X1 1kOhm)
 - 4 Condensateurs (X3 100nF, X1 1uF)
 - Crayons (HB, 2B,...)
 - Modèle papier du capteur graphite

## 1. Simulation électronique du capteur graphite sous LTSpice

&nbsp;&nbsp;&nbsp;&nbsp;Sur le logiciel LTSpice, nous avons réalisé une simulation électrique du circuit par application du schéma suivant :

La résistance variable de notre capteur étant de l'ordre du GigaOhm,...

## 2. PCB via KiCad

## 3. Réalisation du Shield

## 4. Code Arduino

## 5. Application Android

## 6. Banc de test

## Datasheet

## Contact
