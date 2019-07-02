import cv2

src= cv2.imread('./data/cap.PNG', cv2.IMREAD_COLOR)
#src2= cv2.imread('./data/lena.jpg', cv2.IMREAD_GRAYSCALE)
src= cv2.resize(src, dsize=(512,512))
#src2= cv2.resize(src2, dsize=(512,512))
hsv = cv2.cvtColor(src, cv2.COLOR_BGR2HSV)
#hsv2 = cv2.cvtColor(src2, cv2.COLOR_BGR2HSV)
#cv2.imshow('hsv',src2)
h, s, v =cv2.split(hsv)
#h2, s2, v2 = cv2.split(hsv2)
lower_red = cv2.inRange(hsv, (0,100,100), (6,255,255))
upper_red = cv2.inRange(hsv, (150,100,100), (180,255,255))
added_red = cv2.addWeighted(lower_red, 1.0, upper_red, 1.0, 0.0)
#gray = cv2.inRange(hsv2, (1,1,1), (255,255,255))
#red_highlight =cv2.addWeighted(added_red, 1.0, gray, 1.0, 0.0)
#cv2.imshow("gray", gray)
red=cv2.bitwise_and(hsv, hsv, mask = added_red)
red = cv2.cvtColor(red, cv2.COLOR_HSV2BGR)

cv2.imshow("red",red)
cv2.waitKey(0)
cv2.destroyAllWindows()
