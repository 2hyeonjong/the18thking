import cv2

def rotate(event, x, y, flags, param):
		src = cv2.imread('../data/lena.jpg',cv2.IMREAD_GRAYSCALE)
		if event == cv2.EVENT_LBUTTONDOWN:
			height, width= src.shape
			matrix = cv2.getRotationMatrix2D((width/2, height/2), 90, 1)
			dst = cv2.warpAffine(src, matrix, (width, height))
			cv2.imshow('dst', dst)				

src = cv2.resize(src, dsize=(512,512))
print(src.shape)

cv2.imshow('src', src)


#v2.imwrite('../data/rotateLena.jpg', src)
#v2.waitKey(0)
#v2.destroyAllWindows()
