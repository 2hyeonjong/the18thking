import cv2

src = cv2.imread('../data/lena.jpg', cv2.IMREAD_GRAYSCALE)
src = cv2.resize(src, dsize=(512,512))
print(src.shape)
height, width= src.shape
matrix = cv2.getRotationMatrix2D((width/2, height/2), 90, 1)
dst = cv2.warpAffine(src, matrix, (width, height))

cv2.imshow('src', src)
cv2.imshow('dst', dst)

cv2.imwrite('../data/rotateLena.jpg', src)
cv2.waitKey(0)
cv2.destroyAllWindows()
