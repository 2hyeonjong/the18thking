import cv2
from matplotlib import pyplot as plt

def on_press(event,x,y,flags,param):
	global img
	if event== cv2.EVENT_FLAG_LBUTTON:
		print('you pressed')
		height,width = img.shape
		matrix = cv2.getRotationMatrix2D((width/2, height/2), 90,1)
		img =cv2.warpAffine(img, matrix, (width, height))
		cv2.imshow('img',img)
			
					

#cv2.namedWindow('image')
cv2.setMouseCallback('image', on_press)

image = cv2.imread("../data/lena.jpg",cv2.IMREAD_GRAYSCALE)
img=cv2.resize(image, dsize=(512,512))
cv2.imshow('img',img)


cv2.waitKey(0)
cv2.destroyAllWindows()

transform(img)	
#hile True:
#cv2.imshow('image', img)
