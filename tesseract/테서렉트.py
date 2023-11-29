from PIL import Image
import numpy as np
import pytesseract

# 이미지 파일 경로
filename = '/Users/jeon-yuli/Desktop/숭실대학교/1학년 2학기/프로그래밍2/프로젝트/KakaoTalk_Photo_2023-11-29-11-02-29.jpeg'

# 이미지를 NumPy 배열로 변환
img = np.array(Image.open(filename))

# 이미지에서 텍스트 추출
text = pytesseract.image_to_string(img, lang='eng+kor')

# 추출된 텍스트를 txt 파일로 저장
output_file_path = '/Users/jeon-yuli/Desktop/숭실대학교/1학년 2학기/프로그래밍2/프로젝트/extracted_text.txt'

with open(output_file_path, 'w', encoding='utf-8') as file:
    file.write(text)

print(f'Text saved to {output_file_path}')
