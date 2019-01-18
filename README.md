# Mini Gimp


En langage C, nous avons créer un programme qui effectue des traitements d'image : il peut appliquer différents `LUT`. Il affiche ensuite l'histogramme de l'image.


## Membres :


* Clara Daigmorte
* Andréa Guillot


### Commande de l'exécutable :


````
$ bin/minigimp images/mon_image.ppm [-h] [-histo] [<LUT> <Paramètre>] [-o image_sortie.ppm]
```` 


Il faut fournir une image source à l'exécutable, ici : **mon_image.ppm**. Il va pouvoir lui appliquer une ou plusieurs **LUT**. Il faut donc fournir au programme le code de la [LUT désiréé](#les-lut), ansi qu'un paramètre (si la LUT le permet). Les crochets **[]** indiquent un bloc.
L’option -histo demande au programme de générer l’histogramme de l'image. Enfin l’option -o permet de spécifier l’image de sortie qui sera l’image initiale sur laquelle s’applique l’ensemble des LUT.


### Les LUT :

> Note : Les pixels de l'image sont rangés dans un tableau allant de 0 à 255.

* [ADDLUM](#addlum)
* [DIMLUM](#dimlum)
* [ADDCON](#addcon)
* [DIMCON](#dimcon)
* [INVERT](#invert)
* [SEPIA](#sepia)
* [NOIRBLANC](#noirblanc) 
* [SEUI](#seuil)




#### ADDLUM


* Permet d'augmenter la luminosité de l'image 
* Nécessite un paramètre
* La fonction ajoute la valeur de ce paramètre à tous les pixels


#### DIMLUM

* Permet de diminuer la luminosité de l'image 
* Nécessite un paramètre
* La fonction soustrait la valeur de ce paramètre à tous les pixels


#### ADDCON


* Permet d'augmenter le contraste de l'image 
* Nécessite un paramètre
* 

#### DIMCON


* Permet de diminuer le contraste de l'image 
* Nécessite un paramètre
* 

#### INVERT


* Permet d'inverser les couleurs de l'image 
* Soustrait la valeur de chaque pixel à 255


#### SEPIA


* Permet de créer un effet sépia 
* La fonction parcourt les pixels de l'image et les convertit en niveau de brun


#### NOIRBLANC


* Permet de créer un effet noir et blanc
* La fonction parcourt les pixels de l'image et les convertit en niveau de gris grâce à la [formule suivante](https://www.dcode.fr/grayscale-image) :


````
Gris = Rouge*0.299 + Vert*0.587 + Bleu*0.114;
````


#### SEUIL 


* Permet de créer un effet de seuil
* La fonction sépare les pixels de l'image en deux catégories : **sombres** ou **clairs**. Tous les pixels sombres deviennent noirs et tous les pixels clairs deviennent blancs.