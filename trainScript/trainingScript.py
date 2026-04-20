import sensor  # type: ignore
import time
import os
from machine import Pin  # type: ignore
from machine import LED  # type: ignore


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
    sensor.skip_frames(time=2000)


# Checks which buttons are pressed. 1=on 0=off  0 = stop 1 = forward 2 = left 3 = right
def buttonPress():
    global img_id
    led.on()
    if pHog.value() == 1 and pFra.value() == 1:
        return 0

    if pFra.value() == 1:
        target_folder = "fram"
    elif pVan.value() == 1:
        target_folder = "vanster"
    elif pHog.value() == 1:
        target_folder = "hoger"
    else:
        return 0

    img = sensor.snapshot()
    path = target_folder + "/" + target_folder + str(img_id) + ".jpg"
    img.save(path)
    print(path)
    img_id += 1


# Global setup
makeDir()
sensorSetup()

# Global variables
clock = time.clock()
img_id = 0

# pin setup:
pVan = Pin("D3", Pin.IN, Pin.PULL_UP)
pFra = Pin("D2", Pin.IN, Pin.PULL_UP)
pHog = Pin("D1", Pin.IN, Pin.PULL_UP)
led = LED("LED_BLUE")

# Run loop
while (True):
    clock.tick()
    buttonPress()
    led.off()
    print(clock.fps())
