import sensor # type: ignore
import time
import os
from machine import Pin # type: ignore


# Checks if the right directories are included on the nicla vision. If not then add the directory
def makeDir():
    if "vanster" not in os.listdir():
        os.mkdir("vanster")
    if "hoger" not in os.listdir():
        os.mkdir("hoger")
    if "fram" not in os.listdir():
        os.mkdir("fram")
    if "stop" not in os.listdir():
        os.mkdir("stop")


# Setup for the camera
def sensorSetup():
    sensor.reset()
    sensor.set_pixformat(sensor.RGB565)
    sensor.set_framesize(sensor.QVGA)
    sensor.set_windowing((240, 240))  # just to test
    sensor.skip_frames(time=2000)


# Takes a picture and sends it to the internal storage of the nicla vision
def takePic(target_folder, img_id):
    img = sensor.snapshot()
    path = target_folder + "/" + target_folder + str(img_id) + ".jpg"
    img.save(path)
    print(path)


# Checks which buttons are pressed. 1=on 0=off
def buttonPress():
    if pFra.value() == pHog.value() and pHog.value() == pVan.value():
        return "stop"
    else:
        if pFra.value() == 1:
            return "fram"
        elif pHog.value() == 1:
            return "hoger"
        elif pVan.value() == 1:
            return "vanster"
        else:
            return "stop"


# Global setup
makeDir()
sensorSetup()

# Global variables
clock = time.clock()
img_id = 0
direction = "stop"

# pin setup:
pVan = Pin("D3", Pin.IN, Pin.PULL_UP)
pFra = Pin("D2", Pin.IN, Pin.PULL_UP)
pHog = Pin("D1", Pin.IN, Pin.PULL_UP)

# Run loop
while (True):
    clock.tick()

    direction = buttonPress()
    if direction != "stop":
        takePic(direction, img_id)
        img_id += 1

    print(clock.fps())
