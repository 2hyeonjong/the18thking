import cv2

src = cv2.imread("./data/lena.jpg", cv2.IMREAD_COLOR)
dst = cv2.resize(src, dsize = (512,512))#,interpolation = cv2.INTER_AREA)
b,g,r =cv2.split(dst)
inversebgr=cv2.merge((r,g,b))


cv2.imshow("b",b)
cv2.imshow("g",g)
cv2.imshow("r",r)
cv2.imshow("inverse",inversebgr)
cv2.waitKey(0)
cv2.destroyAllwindows()
