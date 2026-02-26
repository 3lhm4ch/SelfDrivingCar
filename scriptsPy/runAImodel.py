import sensor
import time
import os
from machine import Pin


# Setup for the camera
def sensorSetup():
    sensor.reset()
    sensor.set_pixformat(sensor.RGB565)
    sensor.set_framesize(sensor.QVGA)
    sensor.skip_frames(time=2000)


def ai():
    img = sensor.snapshot()
    # mata in img to ai model

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

    runCar(ai())  # When training, run car via Arduino Uno. 

    img_id += 1
    print(clock.fps())
