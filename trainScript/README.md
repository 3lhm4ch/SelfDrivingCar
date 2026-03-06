To train the model you need one arduino UNO and one arduino nicla vision. Upload the "trainingScript.py" to the arduino nicla vision via openmv ide. Upload the "runCar.ino" to the arduino uno via arduino ide. 

<h3>Connect the following pins on the nicla vision to the following pins on the Arduino Uno.</h3>
Nicla   Arduino     Direction\n
D3   ->   7         Left\n
D2   ->   6         Forwards\n
D1   ->   5         Right


<h3>Connect the Relays signal to the following ports on the Arduino Uno</h3>
Right motor signal -> 3\n
Left motor signal -> 4


<h3>Hex codes for ir remote.</h3> 
FFE01F = Left\n
FF906F = Right\n
FF9867 = Stop(down)\n
FFA857 = Forward(settings)