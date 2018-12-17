import numpy
import math
import cv2
import os

def wave2rgb(wavelength):

    '''This converts a given wavelength of light to an
    approximate RGB color value. The wavelength must be given
    in nanometers in the range from 380 nm through 750 nm
    (789 THz through 400 THz).

    Based on code by Dan Bruton
    http://www.physics.sfasu.edu/astro/color/spectra.html
    '''

    gamma = 0.8

    wavelength = float(wavelength)
    if wavelength >= 380 and wavelength <= 440:
        attenuation = 0.3 + 0.7 * (wavelength - 380) / (440 - 380)
        R = ((-(wavelength - 440) / (440 - 380)) * attenuation) ** gamma
        G = 0.0
        B = (1.0 * attenuation) ** gamma
    elif wavelength >= 440 and wavelength <= 490:
        R = 0.0
        G = ((wavelength - 440) / (490 - 440)) ** gamma
        B = 1.0
    elif wavelength >= 490 and wavelength <= 510:
        R = 0.0
        G = 1.0
        B = (-(wavelength - 510) / (510 - 490)) ** gamma
    elif wavelength >= 510 and wavelength <= 580:
        R = ((wavelength - 510) / (580 - 510)) ** gamma
        G = 1.0
        B = 0.0
    elif wavelength >= 580 and wavelength <= 645:
        R = 1.0
        G = (-(wavelength - 645) / (645 - 580)) ** gamma
        B = 0.0
    elif wavelength >= 645 and wavelength <= 750:
        attenuation = 0.3 + 0.7 * (750 - wavelength) / (750 - 645)
        R = (1.0 * attenuation) ** gamma
        G = 0.0
        B = 0.0
    else:
        R = 0.0
        G = 0.0
        B = 0.0
    R *= 255
    G *= 255
    B *= 255
    return (int(B), int(G), int(R))

def deg2color(deg, min, max):
    wmax = 700
    wmin = 440
    ndeg = float(deg) / float((max-min)) * float((wmax-wmin)) + float(wmin)
    return wave2rgb(ndeg)

def tab2color(tab):
    tabinfo = numpy.shape(tab)
    min = numpy.amin(tab)
    max = numpy.amax(tab)
    tab = numpy.add(tab, -min)
    tabcolor = numpy.zeros((tabinfo[0], tabinfo[1], tabinfo[2], 3), int)
    for matrice in range(tabinfo[0]):
        for line in range(tabinfo[1]):
            for col in range(tabinfo[2]):
                tabcolor[matrice][line][col] = deg2color(tab[matrice][line][col], min, max)
    return tabcolor

def filereader(filename):
    reader = open(filename,"r")
    header = reader.readline().rstrip("\n\r")
    nbmat = int(float(header))
    matheader = reader.readline().rstrip("\n\r")
    matinfo = [int(x) for x in matheader.split(";")]
    tabmatrice = numpy.zeros((nbmat, matinfo[0], matinfo[1]),float)
    for matrice in range(nbmat):
        for line in range(matinfo[0]):
            strline = reader.readline().rstrip('\n\r')
            tabmatrice[matrice][line] = [float(x) for x in strline.split(";")]
    reader.close()
    return tabmatrice

def getstep(reso):
    defaultres = 800 * 800
    step = 1
    if(reso < defaultres ):
        step = int(math.sqrt(math.floor(defaultres/reso)))
    print reso
    print step
    return step

def tabprint(tab,save):
    tabinfo = numpy.shape(tab)
    step = getstep(tabinfo[1]*tabinfo[2])
    image = numpy.zeros((int(tabinfo[1]) * step, int(tabinfo[2]) * step, 3), numpy.uint8)
    for matrice in range(0, tabinfo[0]):
        for line in range(0, tabinfo[1] * step, step):
            for col in range(0, tabinfo[2] * step, step):
                image[line:line + step, col:col + step] = tab[matrice][line / step, col / step]
        cv2.imshow("Evolution de la temperature", image)
        cv2.waitKey(0)
        if( save == 1):
            if( not os.path.isdir('./img_results')):
                os.makedirs('./img_results')
            cv2.imwrite("./img_results/tempimg_t"+str(matrice)+".jpg", image);
