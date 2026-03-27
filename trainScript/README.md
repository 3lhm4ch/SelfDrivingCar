<h1>To train the model you need one arduino UNO and one arduino nicla vision. Upload the "trainingScript.py" to the arduino nicla vision via openmv ide. Upload the "runCar.ino" to the arduino uno via arduino ide. </h1>

<h3>Connect the following pins on the nicla vision to the following ports on the Arduino Uno.</h3>
Nicla   Arduino     Direction<br>
D3   ->   7         Left<br>
D2   ->   6         Forwards<br>
D1   ->   5         Right

<h3>Connect the Relays signal to the following ports on the Arduino Uno</h3>
Right motor signal -> 3<br>
Left motor signal -> 4<br>

<h3>Connect the ir sensor to the following ports on the Arduino Uno</h3>
IR signal -> 2

<h3>Hex codes for ir remote.</h3> 
FFE01F = Left<br>
FF906F = Right<br>
FF9867 = Stop(down)<br>
FFA857 = Forward(settings)
