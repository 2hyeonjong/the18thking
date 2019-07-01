import cv2

from matplotlib import pyplot as plt

imageFile ='./data/lena.jpg'

img =cv2.imread(imageFile)

#X,Y 축을 표시하지 않는다.
plt.axis('off')
#plt.imshow(imgBGR)
#plt.show()

#plot에 그리기 위해서는 RGB 순서의 포맷
imgRGB =cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
plt.imshow(imgRGB)
plt.show()
