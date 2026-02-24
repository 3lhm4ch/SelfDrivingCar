# Dataset Capture Script - By: elias.christensen - Thu Feb 19 2026

# Use this script to control how your OpenMV Cam captures images for your dataset.
# You should apply the same image pre-processing steps you expect to run on images
# that you will feed to your model during run-time.

import sensor, image, time, os
from machine import Pin

# Skapa mappar om de inte finns (görs en gång)
if not "vanster" in os.listdir():
    os.mkdir("vanster")
if not "hoger" in os.listdir():
    os.mkdir("hoger")
if not "fram" in os.listdir():
    os.mkdir("fram")


sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time=2000)

clock = time.clock()
img_id = 0
hoger = False
vanster = False

def trainAI(hoger, vanster, img_id):
    clock.tick()
    img = sensor.snapshot()

    if hoger:  #check if is turning hoger
        target_folder = "hoger"
    elif vanster:  #check if is turning vanster
        target_folder = "vanster"
    else:
        target_folder = "fram"

    path = target_folder + "/image_" + str(img_id) + ".jpg"
    img.save(path)
    print(clock.fps())


while (True):
    hoger = False
    vanster = False

    # all koden här.

    trainAI(hoger, vanster, img_id)
    img_id += 1
