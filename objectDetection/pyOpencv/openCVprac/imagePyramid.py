import cv2

src = cv2.imread('../data/rotateLena.jpg', cv2.IMREAD_COLOR)

hight, width = src.shape
dst = cv2.pyrUp(src, dstsize=width*2, height*2), borderType=cv2.BORDER_DEFAULT))
dst2 = cv2.pyrDown(src);

cv2.imshow('src', src)
cv2.imshow('dst', dst)
cv2.imshow('dst2', dst2)
cv2.waitkey(0)
cv2.destroyAllWindows()
