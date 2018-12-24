#!/usr/bin/env python3

import cv2
import numpy as np
import sys

src = cv2.imread(sys.argv[1])
hid = cv2.imread(sys.argv[2])

carrier = cv2.resize(src, (1080 * 3, 1080 * 3))
embed = cv2.resize(hid, (1080, 1080))
carrier[1::3, 1::3, :] = embed

cv2.imwrite("out.png", carrier)
