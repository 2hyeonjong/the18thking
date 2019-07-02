import cv2
src = cv2.imread('./lena.jpg', cv2.IMREAD_COLOR)
src = cv2.resize(src, dsize=(512,512))
cv2.imshow('src',src)

cv2.imwrite('./lena.jpg',src)

