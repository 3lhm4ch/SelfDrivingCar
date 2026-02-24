# Normal edge impulse, not arduino edge impulse
# elias.christensen@elev.ntig.se
#
# Pins:
# D1 = Fram knapp
# D2 = Höger knapp
# D3 = vänster knapp
# 
# D0 = Vänster motor
# CS = Höger motor
# 
# Relay with motor functions by outputting a HIGH or LOW signal to the relay. 


# create an output pin on pin LEDB
p0 = Pin("LEDB", Pin.OUT)

# set the value low then high
p0.value(0)  alternativt  p0.off()
p0.value(1)  alternativt  p0.on()

# create an input pin on pin #2, with a pull up resistor
p2 = Pin(2, Pin.IN, Pin.PULL_UP)

# read and print the pin value
print(p2.value())