import cv2, pafy
url ='https://www.youtube.com/watch?v=UiwRSGNM1Ho'
video = pafy.new(url)
best=video.getbest(preftype='webm')

cap= cv2.VideoCapture(best.url)
while(True):
		retval,fram = cap.read()
		if not retval:
				break
		cv2.imshow('frame',frame)
		gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
		edges=cv2.Canny(gray, 100,200)
		cv2.imshow('edges', edges)

		key =cv2.waitKey(25)
		if key == 27: break

cv2.destroyAllWindows()





