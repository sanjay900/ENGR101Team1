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

