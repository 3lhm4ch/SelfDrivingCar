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
    sensor.set_windowing((240, 240))
    sensor.skip_frames(time=2000)


# Checks which buttons are pressed. 1=on 0=off    pHog = motR  pVan = motL   pFra =
def buttonPress():
    led.on()
    if pHog.value() == 1 and pVan.value() == 0 and pSto.value() == 0:
        target_folder = "hoger"
    elif pHog.value() == 0 and pVan.value() == 1 and pSto.value() == 0:
        target_folder = "vanster"
    elif pHog.value() == 1 and pVan.value() == 1 and pSto.value() == 0:
        target_folder = "fram"
    else:
        return 0

    global img_id
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
pHog = Pin("D2", Pin.IN, Pin.PULL_UP)
pSto = Pin("D1", Pin.IN, Pin.PULL_UP)
led = LED("LED_BLUE")

# Run loop
while (True):
    clock.tick()
    buttonPress()
    led.off()
    print(clock.fps())
