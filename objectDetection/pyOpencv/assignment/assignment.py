import cv2

def mouse_callback(event, x, y, flags, param):
		if event == cv2.EVENT_FLAG_LBUTTON:
			def forRotation(src, height, width):
				cv2.getRotationMatrix2D((width/2, heigth/2),90, 1)
				dst =cv2.warpAffine(src, matrix, (width, height)
				return dst


src=cv2.imread('../data/lena.jpg', cv2.IMREAD_COLOR)

cv2.namedWindow('image')
cv2.setMouseCallback('image', mouse_callback)

src =cv2.resize(image, dsize=(512,512))
height, width, chnnel = src.shape
while True:
	dst=forRotation(src,height, width)
	cv2.imshow('dst', dst)

	cv2.waitKey(0)
	cv2.destroyAllWindows()
