from util import colors
import sys
import os

FILENAME = 'out.txt'

save = int(sys.argv[1])

img_folder = "./img_results"
for root, dirs, files in os.walk(img_folder):
    for file in files:
        os.remove(os.path.join(root, file))

tab = colors.filereader(FILENAME)

newtab = colors.tab2color(tab)

colors.tabprint(newtab, save, img_folder)

os.rename(FILENAME,'matrice.txt')