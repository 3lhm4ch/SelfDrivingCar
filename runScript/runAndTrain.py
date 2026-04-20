import sensor  # type: ignore
import time
import os
from machine import Pin  # type: ignore
import image, tf

labels, net = tf.load_builtin_model('trained')


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

    for obj in tf.classify(net, img, min_scale=1.0, scale_mul=0.8, x_overlap=0.5, y_overlap=0.5):
        print("**********\nPredictions at [x=%d,y=%d,w=%d,h=%d]" % obj.rect())
        img.draw_rectangle(obj.rect())
        # This combines the labels and confidence values into a list of tuples
        predictions_list = list(zip(labels, obj.output()))

        for i in range(len(predictions_list)):
            confidence = predictions_list[i][1]
            label = predictions_list[i][0]
            print("%s = %f" % (label, confidence))

            if confidence > 0.9 and label != "unknown":
                direction = label

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
    if direction == "forward":
        pVan.on()
        pHog.on()
        pSto.off()
    elif direction == "left":
        pVan.off()
        pHog.on()
        pSto.off()
    elif direction == "right":
        pVan.on()
        pHog.off()
        pSto.off()
    else:
        pVan.off()
        pHog.off()
        pSto.on()


# Global setup

makeDir()
sensorSetup()

# Global variables

clock = time.clock()
img_id = 0

# pin setup:

pVan = Pin("D3", Pin.OUT)
pHog = Pin("D2", Pin.OUT)
pSto = Pin("D1", Pin.OUT)   

# Run loop
while (True):
    clock.tick()

    direction = ai()
    runCar(direction)  # When running the car
    # takePic(direction)  # When running the car + training

    if pON.value() == 1:
        break
    
    print(clock.fps())
