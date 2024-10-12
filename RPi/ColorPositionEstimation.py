import numpy as np
import cv2
import time
import serial

from CameraDriver import CameraDriver

class EstimateColorPostition:
    def __init__(self, camera: CameraDriver):
        # Define camera object
        print("Initializing camera")
        self.picam2 = camera.picam2
        self.picam2.resolution = (640, 480)
        self.picam2.framerate = 32

        #set the lower and upper bounds for the green hue
        self.lower_green = np.array([20,50,20])
        self.upper_green = np.array([70,255,255])

    def get_video_frame(self):
        print("Capturing frame")
        cv2.startWindowThread()
        self.picam2.contrast = 100
        self.picam2.configure(self.picam2.create_preview_configuration(main={"format": 'XRGB8888', "size": (640, 480)}))
        self.picam2.start()
        time.sleep(0.1)

        while True:
            self.image = self.picam2.capture_array()

            #filter the green colour
            self.filter_green()
            self.check_if_green_at_center()

            # cv2.imwrite(f'./resources/image_{i}.jpg', self.image)
            # cv2.imwrite(f'./resources/mask_{i}.jpg', self.mask)
            # cv2.imwrite(f'./resources/frame_{i}.jpg', self.res)

    def filter_green(self):
        #create a mask for green colour using inRange function
        for row in self.image:
            for pixel in row:
                pixel = pixel[:3]

        self.image_hsv = cv2.cvtColor(self.image, cv2.COLOR_RGB2HSV)
        self.mask = cv2.inRange(self.image_hsv, self.lower_green, self.upper_green)

        #perform bitwise and on the original image arrays using the mask
        self.res = cv2.bitwise_and(self.image, self.image, mask=self.mask)

    def check_if_green_at_center(self, threshold=20):
        #get the center of the image
        height, width, _ = self.image.shape
        center = (width//2, height//2)

        # Left average green value
        left_avg_green_value = np.mean(self.mask[:, :width//2].astype(float))
        right_avg_green_value = np.mean(self.mask[:, width//2:].astype(float))

        green_diff = left_avg_green_value - right_avg_green_value

        if green_diff <= threshold:
            print("Both sides are equally green")
        elif green_diff > threshold:
            print("Left side is greener")
        elif green_diff < -threshold:
            print("Right side is greener")

def main():
    camera_driver = CameraDriver()
    color_position = EstimateColorPostition(camera_driver)
    color_position.get_video_frame()

if __name__ == "__main__":
    main()