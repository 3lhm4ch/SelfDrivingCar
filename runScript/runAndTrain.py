import sensor  # type: ignore
import time
import os
from machine import Pin  # type: ignore


# Checks if the right directories are included on the nicla vision. If not then add the directory
def makeDir():
    if "vanster" not in os.listdir():
        os.mkdir("vanster")
    if "hoger" not in os.listdir():
        os.mkdir("hoger")
    if "fram" not in os.listdir():
        os.mkdir("fram")


# Setup for the camera
def sensorSetup():
    sensor.reset()
    sensor.set_pixformat(sensor.RGB565)
    sensor.set_framesize(sensor.QVGA)
    sensor.set_windowing((240, 240))
    sensor.skip_frames(time=2000)


# outputs the direction as a string
def ai():
    img = sensor.snapshot()
    # mata in img to ai model
    direction = 0  # Directions: 0=stop 1=fram 2=vanster 3=hoger
    return direction


# Takes a picture and sends it to the internal storage of the nicla vision. 
def takePic(target_folder):
    if target_folder == 1:
        target_folder = "fram"
    elif target_folder == 2:
        target_folder = "vanster"
    elif target_folder == 3:
        target_folder = "hoger"
    else:  # if car is standing still then dont save to the folder
        return

    global img_id
    img = sensor.snapshot()
    path = target_folder + "/" + target_folder + str(img_id) + ".jpg"
    img.save(path)
    print(path)
    img_id += 1


# Turns motor on/off
def runCar(direction):
    if direction == 1:
        pMotHog.on()
        pMotVan.on()
    elif direction == 3:
        pMotHog.off()
        pMotVan.on()
    elif direction == 2:
        pMotHog.on()
        pMotVan.off()
    else:
        pMotHog.off()
        pMotVan.off()


# Global setup

makeDir()
sensorSetup()

# Global variables

clock = time.clock()
img_id = 0

# pin setup:

pMotHog = Pin("CS", Pin.OUT)
pMotVan = Pin("D0", Pin.OUT)

# Run loop
while (True):
    clock.tick()

    direction = ai()
    runCar(direction)  # When running ai
    # takePic(direction)  # When running ai + training

    if "stop" == True:
        break
    
    print(clock.fps())
