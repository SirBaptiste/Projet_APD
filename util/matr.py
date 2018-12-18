#!/usr/bin/env python
# -*- coding: utf-8 -*-

def intinput(descr):
    while 1 :
        userinput = raw_input('Veuillez saisir '+ descr +' (int) : ')
        try:
            val = int(userinput)
            return val
        except ValueError:
            print "La valeur saisie n'est pas un entier"

def pointtinput(descr):
    while 1 :
        userinput = raw_input('Veuillez saisir '+ descr)
        try:
            val = int(userinput)
            return val
        except ValueError:
            print "La valeur saisie n'est pas un entier"

def floatinput(descr):
    while 1 :
        userinput = raw_input('Veuillez saisir '+ descr +' (float) : ')
        try:
            val = float(userinput)
            return val
        except ValueError:
            print "La valeur saisie n'est pas un nombre flotant"