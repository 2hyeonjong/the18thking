from PIL import Image
import cv2

image1 = Image.open('./data/apple.jpg')
image2 = Image.open('./data/orange.jpg')
image1 =image1.resize((512,512))
image2 =image2.resize((512,512))
image5 = image1.convert("RGBA")
image6 = image2.convert("RGBA")

alphaBlended1 = Image.blend(image5,image6,alpha=.4)
alphaBlended2 = Image.blend(image5,image6,alpha=.6)

alphaBlended1.show()
alphaBlended2.show()
