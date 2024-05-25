
<h1 align="center"> Projet Capteur graphite </h1>
<h2 align="center"> TLILI Maxime - SISTEEDHUR Lakshitaa </h2>
<h3 align="center"> INSA Toulouse - département Génie Physique - 2024 </h3>

![Shield2](https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP-TLILI-SISTEEDHUR/assets/160028091/3b883434-9bf2-4699-a6b0-e92848faf7fb)



## Introduction au projet

&nbsp;&nbsp;&nbsp;&nbsp;Ce projet se construit dans le cadre de l'UF "Du capteur au banc de test" de la 4ème année du parcours Génie Physique à l'Institut National des Sciences Appliquées (INSA) de Toulouse. Il permet une approche novatrice et lowtech dans la mesure de contrainte en se basant sur les propriétés du graphite. Il s’appuie sur l’étude de capteurs de contrainte en graphite (système granulaire) dont la résistance varie suivant la déformation du capteur (Pencil Drawn Strain Gauges and Chemiresistors on Paper Cheng-Wei Lin*, Zhibo Zhao*, Jaemyung Kim & Jiaxing Huang Department of Materials Science and Engineering, Northwestern University 2220 Campus Drive, Evanston, IL, 60208, USA).

&nbsp;&nbsp;&nbsp;&nbsp;Au cours de ce projet, nous avons réalisé un dispositif permettant de relever des mesures de contrainte à partir d'une feuille en papier sur laquelle était déposée du graphène. En déformant le capteur, sa résistance est modifiée.. Il est donc possible de réaliser un capteur de déformation low-tech, que nous appellerons par la suite "capteur graphite". Dans un premier temps, nous avons simulé le comportement du circuit analogique sur le logiciel LTSpice. Ce circuit a le double rôle d’amplifier (via un amplificateur transimpédance) et de filtrer le signal délivré par le capteur. Ensuite, un code Arduino permettant la mesure de résistance et le contrôle des différents éléments du circuit (écran OLED, module Bluetooth et potentiomètre digital) a été réalisé. Nous avons préalablement testé notre circuit et le code en montant les différents éléments sur une breadboard. Ensuite, nous avons designé un PCB grâce au logiciel KiCad constituant le shield qui se fixe sur une carte Arduino UNO.

## Livrables

Les livrables du projet sont :
    - [] Le PCB du Shield Arduino
    - [] Le code Arduino permettant de faire la mesure de la résistance du capteur graphite
    - [] L'application Android pour un pilotage bluetooth du système
    - [] le banc de test du capteur
    - [] Le datasheet du capteur
    
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

![Circuit LTSpice](https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP-TLILI-SISTEEDHUR/assets/160028091/72815b30-4935-402f-a908-8267fd9944b3)

La résistance variable de notre capteur étant de l'ordre du GigaOhm, le courant généré est très faible (de l'ordre de quelques nA). Afin de délivrer une tension suffisante au niveau du convertisseur analogique-numérique d'une carte Arduino UNO, il est nécessaire d'amplifier le signal en amont de la mesure. On réalise donc un amplificateur opérationnel transimpédance. Nous avons choisi le circuit amplificateur LTC 1050 au vu de ses paramètres de tension d'offset faible. Celle-ci ne doit pas fausser les valeurs de tensions que reçoit l'Arduino. Il est aussi nécessaire de réaliser un traitement du bruit lié à l'environnement de la mesure. C'est le rôle des différents filtres qui atténuent les bruits du réseau électrique et des horloges des composants.

Cette simulation nous permet de savoir que l'Arduino UNO est capable de mesurer le signal du capteur.

## 2. PCB via KiCad

### a. Création du PCB
&nbsp;&nbsp;&nbsp;&nbsp;Cette partie concerne la conception du circuit transimpédance sur Kicad 8.0 avec l'ajout de divers composants : 
- La résistance R2 a été remplacé par le potentiomètre digital MPC-41050. Il permet d'ajuster le gain du montage en simulant une résistance variable entre 0 et 50kOhms 
- Un module bluetooth HC-05 a été ajouté pour rendre possible une communication avec une application mobile
- Un écran OLED permet de faire l'interface homme-machine en affichant les informations
- Un flexsensor a été ajouté en tant que capteur témoin
- Un encodeur rotatoire ajoute des fonctionalités pour interagir avec les autres composants. ça permet de naviguer dans les menus de l'écran OLED et de lancer la mesure

A partir d'un template d'une carte Arduino UNO, il a fallu :
- Concevoir le schématique du circuit en important et en créant les symbôles pour chaque composant
- Corréler chaque composant à une empreinte réelle en fonction de ses caractéristiques physiques (nombre de pins, distance entre deux pins,...)
- Placer les composants sur la partie schématique et réaliser le routage du circuit
- Poser un plan de masse pour faire le référencement au GND
Afin de s'assurer de la validité du PCB, nous avons été contraint à l'utilisation de deux vias.

Nous avons listé ci-dessous les symbôles et empreintes des composants, ainsi que le schématique et son PCB final

### b. Symbôles et empreintes

- amplificateur transimpédance

<img width="725" alt="Amplificateur transimpédance Symbol" src="https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP-TLILI-SISTEEDHUR/assets/160028091/f7d4f774-d1d9-4564-8336-052f677aaf81">

- Capteur graphite

<img width="200" alt="Capteur Graphite Symbol" src="https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP-TLILI-SISTEEDHUR/assets/160028091/cbb62b4e-f330-4168-bd7c-5a76ede47328">
<img width="300" alt="Capteur Graphite footprint" src="https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP-TLILI-SISTEEDHUR/assets/160028091/8eea6ca6-3443-42be-b696-0f6972295d96">

- Amplificateur LTC1050

<img width="244" alt="LTC 1050 Symbol" src="https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP-TLILI-SISTEEDHUR/assets/160028091/d6c14044-a05b-4a3f-9cc0-f3d23c4517ff">
<img width="307" alt="LTC 1050 footprint" src="https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP-TLILI-SISTEEDHUR/assets/160028091/0ba751cc-f90e-44a8-82f5-1862c255b713">

- Flexsensor

<img width="206" alt="Flexsensor Symbol" src="https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP-TLILI-SISTEEDHUR/assets/160028091/79fee225-752f-4528-834f-6cb9a5089cbd">
<img width="95" alt="Flexsensor footprint" src="https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP-TLILI-SISTEEDHUR/assets/160028091/28ef03c5-0100-4a5d-a988-2855d52418dd">

- Module bluetooth HC-05

<img width="265" alt="Bluetooth HC-05 Symbol" src="https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP-TLILI-SISTEEDHUR/assets/160028091/6585eabf-a721-4d61-b4d2-874c487238cc">
<img width="407" alt="Bluetooth HC-05 footprint" src="https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP-TLILI-SISTEEDHUR/assets/160028091/5b31df3c-196d-45ff-ad24-d554ee008f47">

- Potentiomètre digital MPC41050

<img width="337" alt="MPC41050 Symbol" src="https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP-TLILI-SISTEEDHUR/assets/160028091/47f35640-5838-44ca-872b-f00afaa73429">
<img width="286" alt="MCP41050 footprint" src="https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP-TLILI-SISTEEDHUR/assets/160028091/626fd323-5b0a-420a-8397-585692d39b40">

- Encodeur rotatoire KY-040
<img width="260" alt="KY-040 Symbol" src="https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP-TLILI-SISTEEDHUR/assets/160028091/1b3d5876-5aa9-4fbc-bd7b-8f11b2a7ffdb">
<img width="458" alt="KY-040 footprint" src="https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP-TLILI-SISTEEDHUR/assets/160028091/c84aa96a-26ac-4f96-80fc-007bb2f875a1">

- Ecran OLED
<img width="233" alt="OLED Screen Symbol" src="https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP-TLILI-SISTEEDHUR/assets/160028091/d9514485-3465-423c-8292-08957c128541">
<img width="194" alt="OLED Screen footprint" src="https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP-TLILI-SISTEEDHUR/assets/160028091/2a8beca9-7d73-4c3b-b4a2-2b7009c63491">

### c. Schématique et PCB final
- Schéma complet

    <img width="564" alt="Schematics" src="https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP-TLILI-SISTEEDHUR/assets/160028091/deafd78a-4320-425b-bd57-98c48dd6a36f">

- PCB

    <img width="352" alt="PCB2" src="https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP-TLILI-SISTEEDHUR/assets/160028091/42b379e2-6010-4f00-8085-ad19b7d0f4e1">
    <img width="353" alt="PCB1" src="https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP-TLILI-SISTEEDHUR/assets/160028091/4e16fac2-0dff-4b41-843b-5481c81e709a">

- Modèle 3D

<img width="583" alt="Top view" src="https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP-TLILI-SISTEEDHUR/assets/160028091/85aa3b43-392b-4d39-aebb-ee1a0b34bc54">
<img width="484" alt="Angle view" src="https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP-TLILI-SISTEEDHUR/assets/160028091/391d6e67-1731-49b1-a825-bc81c995102b">


## 3. Réalisation du Shield

&nbsp;&nbsp;&nbsp;&nbsp;Une fois le schéma PCB réalisé, nous avons sorti le circuit sur un calque à l'échelle 1:1. Il a joué le rôle de masque dans la gravure chimique sur une plaquette d'époxy recouverte d'une couche de cuivre d'une épaisseur d'environ 60um. La plaquette a été couverte d'une résine positive, puis elle a été insolé aux UVs. Nous avons plongé la plaquette dans un révélateur et dans du perchlorure de fer pour s'affranchir de la partie de la résine non isolée et du cuivre non protégé. Cette opération s'est déroulée au sein du bâtiment du département du Génie Electrique et Informatique de l'INSA Toulouse.

&nbsp;&nbsp;&nbsp;&nbsp;L'étape suivante a été le perçage mécanique des trous sur la plaquette, et la soudure des différents composants. Nous avons utilisés deux forets mécaniques : un de diamètre 1mm pour les broches de connexion avec la carte Arduino, et un de diamètre 0.8mm pour tout autre trou. Pour ce qui est de nos deux vias, nous avons soudé des fils sur la partie non visible du PCB.

![Shield1](https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP-TLILI-SISTEEDHUR/assets/160028091/f1b9de01-721b-4c23-8c9d-96a2ccf74746)


## 4. Code Arduino

&nbsp;&nbsp;&nbsp;&nbsp;Pour faire la mesure de la résistance, nous avons créé un programme Arduino. Lorsqu'on maintient appuyé le bouton de l'encodeur rotatoire, la mesure de résistance se fait à un intervalle d'environ une seconde. La valeur nous est transmise par le biais de l'écran OLED.

&nbsp;&nbsp;&nbsp;&nbsp;Nous avons fournis trois fichiers de code :

- Capteur2024V1.0.1 : c'est la version qui fournit trois menus sur l'écran OLED permettant de choisir entre le mode Mesureflex, le mode MesureCG, et le mode calibration. Ce programme ne permet pas de faire de mesures. Dès lors que nous demandons de lire une mesure, l'écran OLED ne s'initialise plus et le programme plante
- Capteur2024V2 : C'est la version qui marche. Elle décrit le protocole présenté au dessus.
- Test Components : c'est un programme permettant de tester l'écran OLED.

![Affichage_ecran_OLED](https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP-TLILI-SISTEEDHUR/assets/160028091/64b1982c-205a-4675-a157-9cda475d73cd)


## 5. Application Android

&nbsp;&nbsp;&nbsp;&nbsp;Nous avons réalisé une application android nommée FlexiGraphite.apk. Elle permet d'interagir par bluetooth avec le capteur graphite et de relever notamment la valeur de la résistance du capteur graphite.

Logo :
![FlexiGraphite](https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP-TLILI-SISTEEDHUR/assets/160028091/7c38440b-949a-4dc4-8029-9af95b14c321)

Menu de l'application :
![Menu FlexiGraphite](https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP-TLILI-SISTEEDHUR/assets/160028091/c6960297-d50b-4254-94ba-b93e48a60743)

On retrouve 3 parties sur le menu : 
- La connexion bluetooth au dessus, avec la possibilité de voir l'état de la connexion et de se déconnecter de tout appareil.
- L'onglet "Mesure" servant à y afficher les mesures de la résistance graphite.
- L'onglet "Calibration" qui permet de piloter le lancement de la calibration du gain transimpédance.


## 6. Banc de test

&nbsp;&nbsp;&nbsp;&nbsp;Afin de tester notre capteur, nous avons réalisé un banc de test. Le support est un ensemble de demi-cercles dont le rayon varie. 

<img width="346" alt="BancDeTest" src="https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP-TLILI-SISTEEDHUR/assets/160028091/98a916a7-1da0-43fb-a2a3-288d378f2cd6">
<img width="118" alt="Formule" src="https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP-TLILI-SISTEEDHUR/assets/160028091/97fae09c-94eb-4481-885f-2dab62c62ed3">



Pour les crayons B et HB, on calcule la déformation en fonction du rayon du banc de test et on fait la mesure de résistance. On reporte les valeurs dans un graphe pour tracer l'évolution de la variation de résistance en fonction de la déformation.

IMG
<img width="421" alt="deformation en compression" src="https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP-TLILI-SISTEEDHUR/assets/160028091/f036d267-9802-4e99-b8b8-a010185172af">

<img width="436" alt="Déformation en tension" src="https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP-TLILI-SISTEEDHUR/assets/160028091/7b301c41-d938-4d1c-88d3-4bc00529ca94">

<img width="442" alt="Deformation flexsensor" src="https://github.com/MOSH-Insa-Toulouse/2023-2024-4GP-TLILI-SISTEEDHUR/assets/160028091/5587d8d2-0f29-4868-9ae9-66988d0cb13a">


## Datasheet
Le datasheet de notre capteur se trouve ici. 


## **Contact:**
- Maxime Tlili : tlili@insa-toulouse.fr
- Lakshitaa Devi Sisteedhur : sisteedh@insa-toulouse.fr
