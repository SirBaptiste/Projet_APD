from util import colors
import sys
import os

FILENAME = 'out.txt'

save = sys.argv[1]

tab = colors.filereader(FILENAME)

newtab = colors.tab2color(tab)

colors.tabprint(newtab, save)

os.rename(FILENAME,'matrices.txt')