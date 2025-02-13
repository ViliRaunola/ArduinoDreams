# ArduinoDreams

## Problem, idea, solution
During the winter air humidity can drop drastically leading to dry nose and throat which can cause sleepless nights. To combat this one might buy an air humidifier but for a novice user getting the humidity just right might be a challenge. To help me with this problem I decided to create an environment tracking device! 

## V1.0

In the first version the main idea was to create an air monitoring device. The data gathered from the device could be used to determine the optimal settings for an air humidifier for a particular room and person. In this version an extremely simple solution is presented which tracks the air humidity and temperature which are saved to a SD-card in a CSV format. The data can then be examined and studied to see what the air humidity had been during the night and based on the data the air humidifier's setting can be adjusted to reach the optimal end goal.

### Schema
![circuit_image](https://github.com/user-attachments/assets/23978540-f758-4b51-b1ab-ffa1f3aadd92)

### Example graph plotted from the gathered data
![temp in C ja humidity in _](https://github.com/user-attachments/assets/3dd90ad6-5273-4c30-885e-63765dd2805b)

During this night the air humidifier ran out of water just before 04:00 leading to the sudden drop of airhumidity.


## Future
The end goal is to automate the controlling of the air humidifier using another arduino but another step before that is to establish a wireless connection between two arduinos; the sensor and a one with the task of displaying the current humidity and temperature from a screen.
