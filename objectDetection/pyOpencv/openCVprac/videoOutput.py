import cv2

cap = cv2.VideoCapture("res.avi")

while True:
	if(cap.get(cv2.CAP_PROP_POS_FRAMES) == cap.get(cv2.CAP_PROP_FRAME_COUNT)):
			cap.open("res.avi")

	ret, frame = cap.read()
	cv2.imshow("videoFrame", frame)
	if cv2.waitKey(25) >0 : break

cap.release()
cv2.destroyAllWindows()
