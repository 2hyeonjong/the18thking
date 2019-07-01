import cv2

imageFile ='./data/lena.jpg'

img = cv2.imread(imageFile) #cv2.IMREAD_COLOR

cv2.imwrite('./data/Lena.bmp',img)

cv2.imwrite('./data/Lena.png',img)
#Lena2.png 이름으로 파일을 저장, 0~9사이로 압출률 지정, 디폴트 =3
cv2.imwrite('./data/Lena2.png', img, [cv2.IMWRITE_PNG_COMPRESSION,9])
#Lena.jpg 이름으로 파일을 저장, jpg의 품질을 90%로 지정, 디폴트 = 95%
cv2.imwrite('./data/Lena2.jpg', img, [cv2.IMWRITE_JPEG_QUALITY, 90])
