import numpy as np
import cv2

a = []
a.append(cv2.imread("data/a1.jpg"))
a.append(cv2.imread("data/a2.jpg"))
a.append(cv2.imread("data/a3.jpg"))
a.append(cv2.imread("data/a4.jpg"))
a.append(cv2.imread("data/a5.jpg"))
a.append(cv2.imread("data/a6.jpg"))
a.append(cv2.imread("data/a7.jpg"))
a.append(cv2.imread("data/a8.jpg"))
a.append(cv2.imread("data/a9.jpg"))

gray = [cv2.cvtColor(i, cv2.COLOR_BGR2GRAY) for i in a]

# Convert back to uint8
gray = [np.uint8(np.clip(i,0,255)) for i in gray]

# Denoise 3rd frame considering all the 5 frames
dst = cv2.fastNlMeansDenoisingMulti(gray, 4, 9, None, 3, 7, 21)

cv2.imshow("noise reduction", dst)
cv2.waitKey(0)