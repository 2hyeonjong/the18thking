import cv2 
src =cv2.imread('../data/lena.jpg', cv2.IMREAD_COLOR)

dst = src.copy()
dst = src[100:600, 200:700]

cv2.imshow("src", src)
cv2.imshow("dst", dst)
cv2.imwrite('./data/sliceLena.jpg', dst)
cv2.waitKey(0)
cv2.destrotAllWinodw()
