pull request the  Code or download zip file
compile and run the as.cpp file on any C++ IDE (codeBlock, visualStudio, DevCpp).
a console window shows up. The console allows for  robot movement simulation.
press r : right, f : forward, b : backward, l: left.
as the robot it will sense it environment, so you will have to press  p to show a passage, b  to show blockage. M: to show that a landmark.
The robot can move from   i. Landmark to landmarks ii. from a landmarks to a point in the map  iii. from a point on the map to a landmark.
The robot can't move from a point in the map to another point on map.

to move from a landmark to another landmark, change the astar.pathPlanner(x, y , j , 2);
  x  is the present landmark , and y is the target landmark. j is default . and the last parameter must be 2 . to show landmark to landmark movement.
  
  to move from a landmark to a point in space , change the astar.pathPlanner(x,y,j,1) ; x is the landmarks.  (y,j) are coordinates  to move to. 
  
  to move from a point in space   to a landmark, change the astar.pathPlanner(x,y,j,0) ;  (x,y) is the coordinates; j is the landmarks.  
  
  
  end the mapping with w.
  
  Map is done is Printed on console.
  
type 'x' for each  the last  four user  prompt.


the shortest distance is found, and the motion is planned towards the point.

  
