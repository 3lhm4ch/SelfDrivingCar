<h1>Newest version of the training script</h1>

To train the model you need one arduino UNO and one arduino nicla vision. Upload the "trainingScript.py" to the arduino nicla vision via openmv ide. Upload the "runCar.ino" to the arduino uno via arduino ide.

<h3>Connect the following pins on the nicla vision to the following ports on the Arduino Uno.</h3>
Nicla   Arduino<br>
D3   ->   5<br>
D2   ->   4<br>
D1   ->   3

<h3>Connect the Relays signal to the following ports on the Arduino Uno</h3>
Left motor signal -> 4<br>
Right motor signal -> 3<br>

<h3>Connect the ir sensor to the following ports on the Arduino Uno</h3>
IR signal -> 11

<h3>Ir Remote</h3>
Use a xxx remote<br>
To go forward press the cogwheel<br>
To turn press the left or right button <br>
To stop the vehicle press down button