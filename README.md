# 2022_2023_4G_Kerleau_Cassagne
Projet Capteur 4GP

---
# 1.Présentation du projet 

1.1 Cadre du projet 

Ce projet de réalisation d’un capteur se basant sur une technologie low tech nous a été proposé dans le cadre du cours intitulé “du capteur au banc de test en open source hardware” que nous avons suivi lors de notre 2ème année de cycle ingénieur à l’INSA Toulouse au sein du département Génie Physique. 

Afin de récupérer les données de déformation à partir du capteur, nous avons utilisé une carte Arduino UNO. L’affichage des données se fait d’une part sur un écran OLED, et de l’autre sur un ordinateur via une interface python. Cette dernière reçoit des valeurs de déformation par une communication série établie entre l’ordinateur et la Arduino. De plus, un encodeur rotatoire permet de sélectionner les données que l’on souhaite afficher sur l’écran OLED (courbe représentant la déformation en fonction du temps, valeur de la déformation, la résistance du capteur mesurée). Enfin, nous avons ajouté un flex sensor, permettant la comparaison des données de notre capteur graphite. 

1.2 Principe physique

La technologie low-tech utilisée ici consiste en des traces de crayon réalisées sur un papier. Ces dernières peuvent alors servir de jauge de détection de compression et d’extension. 

Lors de la friction entre le papier et la mine de crayon, des particules de graphite restent accrochées aux fibres du papier, organisées sous forme d’un fin réseau granulaire conducteur. Lors de la contraction ou de l’extension du capteur et donc du réseau de particules de graphite, les intéractions inter-moléculaires de contact sont modifiées. En résulte une modification de la conductivité électrique globale. C’est cette variation de conductivité et donc de résistance que nous mesurons, nous donnant par un simple calcul la valeur de la déformation. Cela offre ainsi la possibilité de réaliser des capteurs de façon rapide et avec des matériaux facilement accessibles.


1.3.1 Livrables 

- PCB supportant le capteur graphite, l’écran OLED, l'émetteur bluetooth, l’encodeur rotatoir, le flex sensor.
- Code Arduino 
- Banc de test
- Datasheet
- Application Android récupérant les données du capteur bluetooth

1.3.2 Rectification des livrables 

Ne disposant pas d’appareil Android mais ayant quand même pour objectif de transmettre les données afin de réaliser une interface graphique, nous nous sommes tournés vers la réalisation d’une interface python. Cette dernière récupère les données de la Arduino via une communication série et permet d’afficher la courbe représentant la valeur de la déformation au cours du temps ainsi que la valeur de la déformation.

---
# 2. Matériel nécessaire

Pour utiliser le capteur graphite, sont nécessaires : 
Une arduino 
Un capteur graphite
2 pinces crocodile 
(matériel AOP) 
Logiciel : Arduino, Python 

---
# 3.Arduino 

Pour traiter l’information nous utilisons un microcontrôleur Arduino UNO

3.1 Librairies 

Pour la réalisation de ce programme nous nous sommes servis de la librairie « SSD1306 » de Adafruit (https://github.com/adafruit/Adafruit_SSD1306) pour pouvoir utiliser l’OLED

3.2 Code 

Le code complet est disponible ici. Il gère le calibrage du capteur, l’affichage de différentes données sur l’écran OLED, la gestion de choix sur l’OLED à l’aide d’un encodeur rotatoire et enfin un envoi des données en série pour les récupérer via Python

---
# 4.Python


---
# 5.KiCad

Nous avons utilisé le logiciel KiCad dans sa version 6.0 afin de pouvoir réaliser notre PCB, pour cela nous avons dans un premier temps fait la schématique de notre montage, puis nous avons défini les empreintes de nos différents composants pour ensuite pouvoir les disposer de façon optimale sur notre PCB

5.1 Schématique 

5.2 Empreintes


5.3 Composants

---
# 6. Shield 
6.1 PCB

Avec le logiciel KiCad, nous avons pu réalisé un typon. Ce typon a été tiré par Catherine Crouzet sur un film transparent afin que les pistes et les pastilles de notre PCB agissent comme un masque UV. Nous allons venir insolé notre circuit imprimé en le couvrant avec le typon. Par la suite nous avons révélé le circuit imprimé dans une cuve puis nous l'avons plongé dans du perchlorure de fer pour venir oxyder le cuivre.

6.2 Perçage et soudure

Enfin, nous avons à l'aide d'une perceuse trouer notre circuit imprimé pour pouvoir venir y souder nos différents composants.

---
# 7. Simulation sur LTspice 

Pour vérifier le bon fonctionnement de notre montage, une étude sur le logiciel LTspice XVII (17.0.36.0) a été menée au préalable.

---
# 8. Tests
8.1 Objectifs



8.2 banc de test

Pour réaliser nos mesures nous avons utilisé une pièce imprimée en 3D composée de plusieurs demi cercle, chacun ayant un rayon de courbure différent. Cela nous permet d'avoir la valeur de la déformation avec la formule suivante

8.3 résultats 

Suite à nos relevées de mesures, nous avons approximé la variation de la résistance relative en fonction de la déformation par une droite affine d'équation y = 38.79*x en tension et y = 54.90*x en déformation

8.4 analyse 


8.5 amélioration

Nous aurions pu utiliser différents types de crayon à papier pour voir l’influence du type de crayon sur le capteur mais nous n’avons pas eu le temps pour cela.

---
# 9. Datasheet

La datasheet de notre capteur est disponible ici

---
# 10. Contacts 

Pour toutes questions ou remarques concernant ce projet, n'hésitez pas à nous contacter : 
Lucie Kerleau : lkerleau@insa-toulouse.fr
Maixent Cassagne : mcassagn@insa-toulouse.fr
