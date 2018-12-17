from util import colors
import sys

FILENAME = 'out.txt'

save = int(sys.argv[1])

prate = int(sys.argv[2])

img_folder = "./img_results"


colors.purgefolder(img_folder)

tab = colors.filereader(FILENAME)

newtab = colors.tab2color(tab)

colors.tabprint(newtab, save, img_folder, prate)

os.rename(FILENAME,'matrice.txt')
