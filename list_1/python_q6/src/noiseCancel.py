import sys
import cv2
import numpy as np
import glob

images = []
for file in glob.glob(sys.argv[2]):
    images.append(cv2.imread(file))

for x in range(0, images[0].shape[0]):
    for y in range(0, images[0].shape[1]):
                aux2 = images[i][x][y][0]
                print(aux2)
        