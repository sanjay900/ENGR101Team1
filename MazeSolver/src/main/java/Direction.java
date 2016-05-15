import java.util.Arrays;
import java.util.List;

/**
 * Created by sanjay on 22/04/16.
 */
public class Direction {
    //A list of directions
    static Direction NORTH = new Direction(0,1),SOUTH = new Direction(0,-1),EAST= new Direction(1,0),WEST = new Direction(-1,0);
    Direction(int x, int y) {
        this.x = x;
        this.y = y;
    }
    int x,y;
    //Return all the valid directions
    public static List<Direction> values() {
        return Arrays.asList(NORTH,SOUTH,EAST,WEST);
    }
    //a nice way to display a tile
    @Override
    public String toString() {
        return "Direction{" +
                "x=" + x +
                ", y=" + y +
                '}';
    }
    //Check if two tiles are equal
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Direction direction = (Direction) o;

        if (x != direction.x) return false;
        return y == direction.y;

    }
    //Generate a unique hashcode for each direction
    @Override
    public int hashCode() {
        int result = x;
        result = 31 * result + y;
        return result;
    }
    //Get the opposite direction
    public Direction reversed() {
        return new Direction(x == 1? -1: x == -1?1:0,y == 1? -1: y == -1?1:0);
    }
    //Rotate this direction counter clock-wise
    public Direction ccw() {
        return new Direction(-y,x);
    }
    //Rotate this direction clock-wise
    public Direction cw() {
        return new Direction(y,-x);
    }
}
