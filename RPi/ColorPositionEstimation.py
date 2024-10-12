import numpy as np
import cv2
import time

from CameraDriver import CameraDriver
from picamera.array import PiRGBArray
from picamera import PiCamera

class EstimateColorPostition:
    def __init__(self, camera: CameraDriver):
        # Define camera object
        self.picam2 = camera.picam2

        #set the lower and upper bounds for the green hue
        self.lower_green = np.array([50,100,50])
        self.upper_green = np.array([70,255,255])

    def get_video_frame(self):
        rawCapture = PiRGBArray(self.picam2)
        time.sleep(0.1)
        self.picam2.capture(rawCapture, format="bgr")
        self.image = rawCapture.array

    def filter_green(self):
        #create a mask for green colour using inRange function
        self.image_hsv = cv2.cvtColor(self.image, cv2.COLOR_BGR2HSV)
        self.mask = cv2.inRange(self.image_hsv, self.lower_green, self.upper_green)

        #perform bitwise and on the original image arrays using the mask
        self.res = cv2.bitwise_and(self.image, self.image, mask=self.mask)

    def show_image(self):
        cv2.imshow('image', self.image)
        cv2.imshow('mask', self.mask)
        cv2.imshow('res', self.res)
        cv2.waitKey(0)
        cv2.destroyAllWindows()

def main():
    camera_driver = CameraDriver()
    color_position = EstimateColorPostition(camera_driver)
    color_position.filter_green()
    color_position.show_image()