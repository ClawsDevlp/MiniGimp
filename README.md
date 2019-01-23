# Mini Gimp


En langage C, nous avons créer un programme qui effectue des traitements d'image : il peut appliquer différents `LUT`. Il affiche ensuite l'histogramme de l'image de départ et de l'image finale.


## Membres :


* Clara Daigmorte
* Andréa Guillot


### Commande de l'exécutable :


````
$ bin/minigimp images/mon_image.ppm [-histo] [<LUT> <Paramètre>] [-o image_sortie.ppm]
```` 


Il faut fournir une image source à l'exécutable, ici : **mon_image.ppm**. Il va pouvoir lui appliquer une ou plusieurs **LUT**. Il faut donc fournir au programme le code de la LUT désiréé, ansi qu'un paramètre (si la LUT le permet). Les crochets **[]** indiquent un bloc.
L’option -histo demande au programme de générer l’histogramme de l'image. Enfin l’option -o permet de spécifier l’image de sortie qui sera l’image initiale sur laquelle s’applique l’ensemble des LUT.


### Les LUT :


* [ADDLUM](#addlum)
* [DIMLUM](#dimlum)
* [ADDCON](#addcon)
* [DIMCON](#dimcon)
* [INVERT](#invert)
* [SEPIA](#sepia)
* [NOIRBLANC](#noirblanc) 
* [SEUIL](#seuil)


> Note : RVB sont rangés dans des tableaux allant de 0 à 255.


#### ADDLUM (+ paramètre)


````
$ bin/minigimp images/mon_image.ppm -histo ADDLUM 50 -o image_sortie.ppm
```` 


* Permet d'augmenter la luminosité de l'image
* La fonction ajoute la valeur de ce paramètre à tous les pixels


#### DIMLUM (+ paramètre)


````
$ bin/minigimp images/mon_image.ppm -histo DIMLUM 50 -o image_sortie.ppm
```` 


* Permet de diminuer la luminosité de l'image 
* La fonction soustrait la valeur de ce paramètre à tous les pixels


#### ADDCON (+ paramètre)


````
$ bin/minigimp images/mon_image.ppm -histo ADDCON 50 -o image_sortie.ppm
```` 


* Permet d'augmenter le contraste de l'image 
* La fonction ajoute la valeur de ce paramètre aux pixels les plus clairs et la soustrait aux pixels les plus sombres

#### DIMCON (+ paramètre)


````
$ bin/minigimp images/mon_image.ppm -histo DIMCON 50 -o image_sortie.ppm
```` 


* Permet de diminuer le contraste de l'image 
* La fonction soustrait la valeur de ce paramètre aux pixels les plus clairs et l'ajoute aux pixels les plus sombres

#### INVERT


````
$ bin/minigimp images/mon_image.ppm -histo INVERT -o image_sortie.ppm
```` 


* Permet d'inverser les couleurs de l'image 
* Soustrait la valeur de chaque pixel à 255


#### SEPIA


````
$ bin/minigimp images/mon_image.ppm -histo SEPIA -o image_sortie.ppm
```` 


* Permet de créer un effet sépia 
* La fonction parcourt les pixels de l'image et les convertit en niveau de brun


#### NOIRBLANC


````
$ bin/minigimp images/mon_image.ppm -histo NOIRBLANC -o image_sortie.ppm
```` 


* Permet de créer un effet noir et blanc
* La fonction parcourt les pixels de l'image et les convertit en niveau de gris grâce à la formule suivante (source : https://www.dcode.fr/grayscale-image) :


> Gris = Rouge*0.299 + Vert*0.587 + Bleu*0.114;


#### SEUIL 


````
$ bin/minigimp images/mon_image.ppm -histo SEUIL -o image_sortie.ppm
```` 


* Permet de créer un effet de seuil
* La fonction sépare les pixels de l'image en deux catégories : **sombres** ou **clairs**. Tous les pixels sombres deviennent noirs et tous les pixels clairs deviennent blancs.