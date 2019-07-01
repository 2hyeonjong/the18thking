import cv2

from matplotlib import pyplot as plt

path='./data/'

imgBGR1=cv2.imread(path+'orange.jpg')
imgBGR1=cv2.resize(imgBGR1, dsize=(512,512),interpolation=cv2.INTER_AREA)
imgBGR2=cv2.imread(path+'apple.jpg')
imgBGR2=cv2.resize(imgBGR2, dsize=(512,512),interpolation=cv2.INTER_AREA)

imgBGR3=cv2.imread(path+'baboon.jpg')
imgBGR3=cv2.resize(imgBGR3, dsize=(512,512),interpolation=cv2.INTER_AREA)
imgBGR4=cv2.imread(path+'lena.jpg')
imgBGR4=cv2.resize(imgBGR4, dsize=(512,512),interpolation=cv2.INTER_AREA)

imgRGB1=cv2.cvtColor(imgBGR1, cv2.COLOR_BGR2RGB)
imgRGB2=cv2.cvtColor(imgBGR2, cv2.COLOR_BGR2RGB)
imgRGB3=cv2.cvtColor(imgBGR3, cv2.COLOR_BGR2RGB)
imgRGB4=cv2.cvtColor(imgBGR4, cv2.COLOR_BGR2RGB)

fig, ax = plt.subplots(2,2, figsize=(10,10), sharey=True)
fig.canvas.set_window_title('Ssmaple Pictures')

ax[0][0].axis('off')
ax[0][0].imshow(imgRGB1, aspect='auto')


ax[0][1].axis('off')
ax[0][1].imshow(imgRGB2, aspect='auto')


ax[1][0].axis('off')
ax[1][0].imshow(imgRGB3, aspect='auto')


ax[1][1].axis('off')
ax[1][1].imshow(imgRGB4, aspect='auto')

plt.subplots_adjust(left=0, bottom=0, right=1, top=1, wspace=0.05, hspace=0.05)
plt.savefig("./data/0206.png", bbox_inches='tight')
plt.show()
