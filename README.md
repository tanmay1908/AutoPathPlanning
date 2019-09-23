# Home Service Robot

This repo simulates a turtlebot in a Gazebo environment and simulates a home service robot. 
The program creates a pickup object, a red cube in this case, and the robot navigates to it to pick it up
The square disappears once the robot reaches the pickup position and then moves to the drop off location

A SLAM algorithm was also implemented for the robot using the gmapping ROS package 
The generated map can be found in the src/maps directory, also seen below:

![generated map](map1.pgm)
