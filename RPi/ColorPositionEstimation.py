import numpy as np
import cv2
import time

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
        self.picam2.configure(self.picam2.create_preview_configuration(main={"format": 'XRGB8888', "size": (640, 480)}))
        self.picam2.start()
        time.sleep(0.1)
        i = 0
        while True:
            self.image = self.picam2.capture_array()

            #filter the green colour
            self.filter_green()

            cv2.imwrite(f'./resources/image_{i}.jpg', self.image)
            cv2.imwrite(f'./resources/mask_{i}.jpg', self.mask)
            cv2.imwrite(f'./resources/frame_{i}.jpg', self.res)

            i += 1
            if i == 10:
                break

    def filter_green(self):
        #create a mask for green colour using inRange function
        for row in self.image:
            for pixel in row:
                pixel = pixel[:3]

        self.image_hsv = cv2.cvtColor(self.image, cv2.COLOR_RGB2HSV)
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
    color_position.get_video_frame()

if __name__ == "__main__":
    main()