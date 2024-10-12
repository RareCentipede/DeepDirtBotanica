from picamera2 import Picamera2
import os

class CameraDriver:
  
    def __init__(self):
        self.picam2 = Picamera2()

    def take_video(self):
        self.picam2.start_and_record_video("./resources/test.mp4", duration=5)
    


def main():
    camera_driver = CameraDriver()
    # Specify the directory path
    directory = "./resources"

    # Create the directory if it doesn't exist
    if not os.path.exists(directory):
        os.makedirs(directory)
    camera_driver.take_video()

if __name__ == "__main__":
    main()