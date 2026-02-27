To train the model you need one arduino UNO and one arduino nicla vision. Upload the "trainingScript.py" to the arduino nicla vision via openmv ide. Upload the "runCar.ino" to the arduino uno via arduino ide. 

<h3>connect the following pins on the nicla vision to the following pins on the Arduino Uno.</h3>
Nicla   Arduino     Direction
D1   ->   5         Right
D2   ->   6         Left
D3   ->   7         Forwards


<h3>Connect the Relays signal to the following ports on both the Arduino uno and Nicla Vision.</h3>
Right motor signal -> CS & 4
Left motor signal -> D0 & 3


Hex codes for ir remote. 
FFE01F = Left
FF906F = Right
FF9867 = Stop(down)