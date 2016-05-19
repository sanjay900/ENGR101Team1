# ENGR101Team1
Work for ENGR101 Team1

AVC Documentation

21st April: 1st team meeting
- Set up slack and GitHub, completed plan.
-	Started chassis design
-	TTC(things to consider): 
  -	Camera placement: Do we want it at the pivot point of the chassis? And if so whereabouts is this point (depending on wheel placement and whether the small single wheel is at the front or the back of the chassis).
  -	Single wheel position: what are the pros and cons of it being at the front or back of chassis, how does it affect the manoeuvrability of the robot through the maze?
  -	Positioning of RPi on the chassis: we need a gap between the boards to prevent components from touching & catching fire, but at the same time do we need any height restrictions? How about the size of the chassis as it moves through the maze?


5th May
Software:
- Managed to get the robot to follow a line WITHOUT PID but then it would get stuck when there are multiple possible paths to take. 
- CODE: move one wheel at a time depending on sum (don’t use sum for motor speed). *If(sum< val) →  what would the best value be? Best motor speed? 127 works
- Attempted to apply PID (work in progress)
- MAZE LOGIC: follow left (or right) wall. No left wall: turn left. Both walls: straight. No right wall but nothing in front: straight.
- TO DO: create the rest of the lines in the simulator
Hardware:
- Place camera next to motors because if it was placed at front by the single wheel it would hit the walls when turning in the maze.
- Use two ir sensors at angles off the front of the robot to navigate the maze
- Shorten board

Hardware 2: 
- Disscussed with team to find additional hardware parts for the AVC.
- Started sketching parts for the robot which could be 3D printed.
- Discussed with the software team to find what camera angle would be best suited for the robot itself.
- Sketched final camera mount design with the selected camera angle of 118°.
- Made changes to camera mount design by adding mounts for 2 IR sensors on both sides.
- Sketched new swivel front wheel design to be 3D printed.


12th May
Software:
- Set up IntelliJ, Java3D, GitBash on laptops to edit arena simulation
- Finished constructing lines for quadrants 2 and 3 in the simulator

Hardware:
- 3D printed parts for robot

Hardware 2:
- Converted the sketches to 3D models using Google Sketchup with the extension "CadSpan" to create 3D printable ".stl" files.
- Started printing first 3D model of the swivel wheel.
- Successfully 3D printed swivel wheel.
- Redesigned swivel wheel since the 3D printed part was slighty too large for the wheel size.
- Started converting camera and sensor mount sketch to 3D model.

19th May
Software: 
- Started writing maze solving code
To do: complete maze solving code and test

Hardware:
- Shortened board
- Changed positioning of RPi on board
- Increased height to make room for battery placement
To do: IR sensors
