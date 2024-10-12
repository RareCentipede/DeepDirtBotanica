from picamera2 import Picamera2

class CameraDriver:
  
    def __init__(self):
        picam2 = Picamera2()

    def take_video(self):
        self.picam2.start_and_record_video("./resources/test.mp4", duration=5)
    

camera_driver = CameraDriver()

def main:
    camera_driver.take_video()

if __name__ == “__main__”:
    main()



     




