import cv2
import numpy as np
src = cv2.imread("./data/lena.jpg", cv2.IMREAD_COLOR)
print(src.shape)
src = cv2.resize(src, dsize = (512,512),interpolation = cv2.INTER_AREA)
height, width, channel = src.shape
zero= np.zeros((height, width, 1), dtype = np.uint8)
b,g,r =cv2.split(src)
b = src[:,:,0]
g = src[:,:,0]
r = src[:,:,2]
inversebgr=cv2.merge((zero,zero,r))


cv2.imshow("b",b)
cv2.imshow("g",g)
cv2.imshow("r",r)
cv2.imshow("inverse",inversebgr)
cv2.waitKey(0)
cv2.destroyAllWindows()
