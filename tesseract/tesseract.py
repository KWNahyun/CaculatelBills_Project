from PIL import Image
import numpy as np
import pytesseract

filename = '/Users/jeon-yuli/Desktop/숭실대학교/1학년 2학기/프로그래밍2/프로젝트/img.png'
img = np.array(Image.open(filename))
text = pytesseract.image_to_string(img, lang = 'eng+kor')
print(text)
