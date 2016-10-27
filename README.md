Simple Augmented Reality
===

Simple Augmented Reality pipeline using C++ and OpenCV 2.4.x.

Concrete tasks
---
* Detect the AR marker in the image.
  
* Calculate the 6DOF pose of the marker, making an assumption on it's size and the camera intrinsics.
   
* Draw a 3D cube above the marker on the image.


* Support multiple markers.
  
![alt tag](http://virtual.vtt.fi/virtual/proj2/multimedia/media/images/MultiMarker.jpg)
 
Building and Running
---
A standard OpenCV-oriented Makefile was created for easy building in a linux-esque environment.
For Windows - you are on your own. CMake may come in handy, or use cygwin / mingw.

