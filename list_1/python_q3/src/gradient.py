import numpy
import cv2

img = numpy.ones((300,300,1),numpy.uint8)

alpha = 255/300.0
value = 0
for x in range(0, img.shape[0]):
    for y in range(0, img.shape[1]):
        img[x, y] = value
    value += alpha
        
cv2.imshow('image',img)
cv2.waitKey(0)
cv2.destroyAllWindows()