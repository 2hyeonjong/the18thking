import cv2

img = cv2.imread("../data/lena.jpg", cv2.IMREAD_COLOR)
img = cv2.resize(img, dsize=(512,512), interpolation=cv2.INTER_AREA)
flip = cv2.flip(img, 0)

cv2.imshow("img", img)
cv2.imshow("flip", flip)
cv2.waitKey(0)
cv2.destroyAllWindows()
