To train the model you need one arduino UNO and one arduino nicla vision. Upload the "trainingScript.py" to the arduino nicla vision via openmv ide. Upload the "runCar.ino" to the arduino uno via arduino ide. 

<h3>connect the following pins on the nicla vision to the following pins on the Arduino Uno.</h3>
Nicla   Arduino     Direction
D3   ->   7         Left
D2   ->   6         Forwards
D1   ->   5         Right


<h3>Connect the Relays signal to the following ports on the Arduino Uno</h3>
Right motor signal -> 3
Left motor signal -> 4


Hex codes for ir remote. 
FFE01F = Left
FF906F = Right
FF9867 = Stop(down)