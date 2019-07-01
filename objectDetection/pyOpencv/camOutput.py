import cv2

cap = cv2.VideoCapture('https://192.168.1.48:4747/video')
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)

frame_size =(int(cap.get(cv2.CAP_PROP_FRAME_WIDTH)),
				int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT)))
print('frame_size=',frame_size)

while True:
	ret, frame = cap.read()
#v2.imshow("VidieoFrame",frame)
#f cv2.waitKey(1)==ord('q') > 0: break
	if not ret:
		break
	cv2.imshow('frame', frame)

	key = cv2.waitKey(25)
	if key==27: break

if cap.isOpened():
		cap.release()
cv2.destroyAllWindows()
	
#apture.relese()
#cv2.destoyAllwindows()
