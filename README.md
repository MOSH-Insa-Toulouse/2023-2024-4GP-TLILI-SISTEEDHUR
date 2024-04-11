
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
Pour notre projet, nous avons opté pour ajouter un écran OLED servant de menu, du flex sensor commercial pour avoir un comparatif avec notre capteur, ainsi que d'un encodeur rotatoire pour différentes fonctionnalités.

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

 /Photo/

La résistance variable de notre capteur étant de l'ordre du GigaOhm, le courant généré est très faible (de l'ordre de quelques nA). Afin de délivrer une tension suffisante au niveau du convertisseur analogique-numérique d'une carte Arduino UNO, il est nécessaire d'amplifier le signal en amont de la mesure. On réalise donc un amplificateur opérationnel transimpédance. Nous avons choisi le circuit amplificateur LTC 1050 au vu de ses paramètres de tension d'offset faible. Celle-ci ne doit pas fausser les valeurs de tensions que reçoit l'Arduino. Il est aussi nécessaire de réaliser un traitement du bruit lié à l'environnement de la mesure. C'est le rôle des différents filtres qui atténuent les bruits du réseau électrique et des horloges des composants.

Cette simulation nous permet de savoir que l'Arduino UNO est capable de mesurer le signal du capteur.

## 2. PCB via KiCad

### a. Création du PCB
&nbsp;&nbsp;&nbsp;&nbsp;Cette partie concerne la conception du circuit transimpédance sur Kicad 8.0 avec l'ajout de divers composants : 
- La résistance R2 a été remplacé par le potentiomètre digital MPC-41050. Il permet d'ajuster le gain du montage en simulant une résistance variable entre 0 et 50kOhms 
- Un module bluetooth HC-05 a été ajouté pour rendre possible une communication avec une application mobile
- Un écran OLED permet de faire l'interface homme-machine en affichant les informations
- Un flexsensor a été ajouté en tant que capteur témoin
- Un encodeur rotatoire ajoute des fonctionalités pour interagir avec les autres composants

A partir d'un template d'une carte Arduino UNO, il a fallu :
- Concevoir le schématique du circuit en important et en créant les symbôles pour chaque composant
- Corréler chaque composant à une empreinte réelle en fonction de ses caractéristiques physiques (nombre de pins, distance entre deux pins,...)
- Placer les composants sur la partie schématique et réaliser le routage du circuit
- Poser un plan de masse pour faire le référencement au GND
Afin de s'assurer de la validité du PCB, nous avons été contraint à l'utilisation de deux vias.

Nous avons listé ci-dessous les symbôles et empreintes des composants, ainsi que le schématique et son PCB final

### b. Symbôles et empreintes
- Capteur graphite 
- Flexsensor
- Amplificateur LTC1050
- Module bluetooth HC-05
- Potentiomètre digital MPC41050
- Encodeur rotatoire KY-040
- Ecran OLED

### c. Schématique et PCB final
- Schéma complet
- PCB

## 3. Réalisation du Shield

&nbsp;&nbsp;&nbsp;&nbsp;Une fois le schéma PCB réalisé, nous avons sorti le circuit sur un calque à l'échelle 1:1. Il a joué le rôle de masque dans la gravure chimique sur une plaquette d'époxy recouverte d'une couche de cuivre d'une épaisseur d'environ 60um. La plaquette a été couverte d'une résine positive, puis elle a été insolé aux UVs. Nous avons plongé la plaquette dans un révélateur et dans du perchlorure de fer pour s'affranchir de la partie de la résine non isolée et du cuivre non protégé. Cette opération s'est déroulée au sein du bâtiment du département du Génie Electrique et Informatique de l'INSA Toulouse.

&nbsp;&nbsp;&nbsp;&nbsp;L'étape suivante a été le perçage mécanique des trous sur la plaquette, et la soudure des différents composants. Nous avons utilisés deux forets mécaniques : un de diamètre 1mm pour les broches de connexion avec la carte Arduino, et un de diamètre 0.8mm pour tout autre trou. Pour ce qui est de nos deux vias, nous avons soudé des fils sur la partie non visible du PCB.

## 4. Code Arduino

## 5. Application Android

## 6. Banc de test

## Datasheet

## **Contact:**
- Maxime Tlili : tlili@insa-toulouse.fr
- Lakshitaa Sisteedhur : sisteedh@insa-toulouse.fr
