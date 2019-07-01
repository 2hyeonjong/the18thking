import cv2

src = cv2.imread('../data/lena.jpg', cv2.IMREAD_COLOR)

dst = src.copy()
roi = src[100:600 , 200: 700]
dst[0:500, 0:500] =roi

cv2.imshow("src", src)
cv2.imshow('dst', dst)
cv2.waitKey(0)
cv2.destroyAllWindows()

