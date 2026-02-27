import sensor
import time
import os
from machine import Pin


# Functions not in use
def irRemote():
    # find irremote and decode.
    direction = "fram"
    return direction


# outputs the direction as a string
def ai():
    img = sensor.snapshot()
    # mata in img to ai model


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
    sensor.skip_frames(time=2000)


# Takes a picture and sends it to the internal storage of the nicla vision
def takePic(target_folder, img_id):
    if target_folder == "stop":  # if car is standing still then dont save to the folder
        return

    img = sensor.snapshot()
    path = target_folder + "/" + target_folder + str(img_id) + ".jpg"
    img.save(path)
    print(path)


# Turns dc motor on/off
def runCar(direction):
    if direction == "fram":
        pMotHog.on()
        pMotVan.on()
        print("driving forward")
    elif direction == "hoger":
        pMotHog.off()
        pMotVan.on()
        print("driving right")
    elif direction == "vanster":
        pMotHog.on()
        pMotVan.off()
        print("driving left")
    else:
        pMotHog.off()
        pMotVan.off()
        print("Stop")


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

    # runCar(ai())  # When running ai
    # takePic(ai(), img_id)  # When running ai + training

    img_id += 1
    print(clock.fps())
