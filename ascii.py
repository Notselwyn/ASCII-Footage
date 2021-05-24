import time
import cv2
import numpy as np
import os
ascii_chars = tuple(reversed('$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/|()1{}[]?-_+~<>i!lI;:,"^`\'.    '))

file_path = input("Enter the file path: ")
if file_path == "0":
    file_path = 0
fps = int(input("Enter FPS: "))

vc = cv2.VideoCapture(file_path)
while True:
    rval, frame = vc.read()
    resized_frame = cv2.resize(frame, (tuple(os.get_terminal_size())[0]-1, tuple(os.get_terminal_size())[1]))
    img_array = np.asarray(cv2.flip(cv2.cvtColor(resized_frame, cv2.COLOR_BGR2GRAY), 1))
    print('\n'.join(''.join(ascii_chars[round((len(ascii_chars) - 1) * color / 255)] for color in row) for row in img_array), end="\r")
    time.sleep(1/fps)
vc.release()