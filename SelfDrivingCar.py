# Dataset Capture Script - By: elias.christensen - Thu Feb 19 2026

# Use this script to control how your OpenMV Cam captures images for your dataset.
# You should apply the same image pre-processing steps you expect to run on images
# that you will feed to your model during run-time.

import sensor, time, os, pyb
from machine import Pin

# Skapa mappar om de inte finns (görs en gång)
if "vanster" not in os.listdir():
    os.mkdir("vanster")
if "hoger" not in os.listdir():
    os.mkdir("hoger")
if "fram" not in os.listdir():
    os.mkdir("fram")


sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time=2000)

clock = time.clock()
img_id = 0
hoger = False
vanster = False

# test:

p0 = Pin("PF_4", Pin.OUT)

# test end


def trainAI(target_folder, img_id):
    clock.tick()
    img = sensor.snapshot()
    path = target_folder + "/image_" + str(img_id) + ".jpg"
    img.save(path)
    print(clock.fps())


while (True):
    hoger = False
    vanster = False
    fram = False

    # all koden här.
    p0.value(0)
    pyb.delay(1000)
    p0.value(1)
    pyb.delay(1000)

    if hoger:  # check if is turning hoger
        trainAI("hoger", img_id)
    elif vanster:  # check if is turning vanster
        trainAI("vanster", img_id)
    elif fram:
        trainAI("fram", img_id)

    img_id += 1
