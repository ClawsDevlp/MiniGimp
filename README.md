# Mini Gimp


En langage C, nous avons créer un programme qui effectue des traitements d'image : il peut appliquer différents `LUT`. Il affiche ensuite l'`histogramme` de l'image.


#### Membres :


* Clara Daigmorte
* Andréa Guillot


#### Commande de l'exécutable :


````
$ bin/minigimp images/mon_image.ppm [-h] [-histo] [<LUT> <Paramètre>] [-o image_sortie.ppm]
```` 


Il faut fournir une image source à l'exécutable, ici : **mon_image.ppm**. Il va pouvoir lui appliquer une ou plusieurs **<LUT>**. Il faut donc fournir au programme le code de la LUT désiréé, ansi qu'un paramètre. Les crochets **[]** indiquent un bloc.
L’option -histo demande au programme de générer l’histogramme de l'image. Enfin l’option -o permet de spécifier l’image de sortie qui sera l’image initiale sur laquelle s’applique l’ensemble des LUT.


#### Les LUT :


* ADDLUM
* DIMLUM
* ADDCON
* DIMCON
* INVERT
* SEPIA
* NOIRBLANC
* SEUIL