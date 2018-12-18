#!/usr/bin/env python
# -*- coding: utf-8 -*-
from util import matr

apply_temp = 300

print "Script utilitaire pour générer des matrices."
print "Ce script génère une matrice à une temperature ambiante avec des zones à températures choisies"
print "Les zones de chaleurs sont rectangulaires et sont definies par 2 points qui forment une diagonale"
print "Pour générer un seul point de chaleur mettre des valeurs identiques pour les couples x1,y1 et x2,y2"
print "Les matrices générées ont leur origine en haut a gauche."

nb_ligne = matr.intinput('le nombre de ligne')
nb_colonne = matr.intinput('le nombre de colonne')
temp_global = matr.floatinput('la température ambiante')
duree = matr.intinput('la durée de la simulation')
nb_zone = matr.intinput('le nombre de zone de chaleur à créer')

start_x = []
start_y = []
end_x = []
end_y = []
apply_temp = []

for zone in range(nb_zone):
    print "Définition de la zone N°" + str(zone+1) +"\n"
    err = 1
    while err == 1:
        x1 = matr.pointtinput("l'abscisse x1 du point de départ de la zone : x1=")
        if 0 <= x1 <= nb_ligne:
            err = 0
        else:
            print "La valeur saisie doit être comprise entre 0 et " + str(nb_ligne)
    err = 1
    while err == 1:
        y1 = matr.pointtinput("l'ordonnée y1 du point de départ de la zone : y1=")
        if 0 <= y1 <= nb_colonne:
            err = 0
        else:
            print "La valeur saisie doit être comprise entre 0 et " + str(nb_colonne)
    err = 1
    while err ==1:
        x2 = matr.pointtinput("l'abscisse x2 du point de fin de la zone : x2=")
        if x1 <= x2 <= nb_ligne:
            err = 0
        else:
            print "La valeur saisie doit être comprise entre " + str(x1) + " et " + str(nb_ligne)
    err = 1
    while err == 1:
        y2 = matr.pointtinput("l'abscisse y2 du point de fin de la zone : y2=")
        if y1 <= y2 <= nb_colonne:
            err = 0
        else:
            print "La valeur saisie doit être comprise entre " + str(y1) + " et " + str(nb_colonne)
    err = 1
    apply_temp.append(matr.floatinput('la température de la zone définie precedemment'))
    start_x.append(x1)
    end_x.append(x2)
    start_y.append(y1)
    end_y.append(y2)



file = open('tmp.txt','w')
file.write(str(nb_ligne)+";"+str(nb_colonne) + "\n")
file.write(str(duree)+ "\n")
file.write(str(float(temp_global))+"\n")

for ligne in range(nb_ligne):
    for colonne in range(nb_colonne):
        write = 0
        for zone in range(nb_zone):
            if( ( start_x[zone] <= ligne <= end_x[zone]) and ( start_y[zone] <= colonne <= end_y[zone] ) ):
                if (nb_colonne == colonne + 1):
                    file.write(str(apply_temp[zone]) + ";\n")
                else:
                    file.write(str(apply_temp[zone]) + ";")
                write = 1
        if write == 0 :
            if (nb_colonne == colonne +1):
                file.write(str(temp_global) + ";\n")
            else:
                file.write(str(temp_global)+";")

file.close()
