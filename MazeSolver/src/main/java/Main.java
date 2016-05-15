import ecs100.UI;

import java.awt.*;
import java.util.HashSet;
import java.util.Stack;

/**
 * Created by sanjay on 22/04/16.
 */
public class Main {
    static int width = 20;
    static int height = 20;
    static Main instance;
    //A list of current tiles
    //Why a hash set? Speed. comparing by hash is a lot faster than comparing two values
    HashSet<Tile> tiles = new HashSet<>();
    public static void main(String[] args) {
       new Main();
    }
    public Main() {
        instance = this;
        while (true) {
            //Add the first tile to the list
            Tile t = new Tile(0, 0);
            //Random color for the tile
            Tile.color = Color.WHITE;
            tiles.clear();
            //Create a stack of tiles, this is a first in last out list
            Stack<Tile> stack = new Stack<>();
            stack.push(t);
            tiles.add(t);
            Tile random;
            //We push each tile on, but as we go, the current tile will slowly branch out but then track backwards
            //The stack is empty once we reach the last tile
            while (!stack.isEmpty()) {
                t = stack.peek();
                //If randomwall returns null, pop a new tile from the stack, this will backtrack to the last tile
                //And then check all its directions until we find a tile with free directions
                //If the stack is empty we have backtracked to the start.
                while ((random = t.randomWall()) == null) {
                    if (stack.isEmpty()) break;
                    stack.pop();
                    if (stack.isEmpty()) break;
                    t = stack.peek();
                }
                if (stack.isEmpty()) break;
                t = random;
                tiles.add(t);
                stack.push(t);
            }

            tiles.forEach(Tile::draw);
            solve();
            UI.sleep(1000);
            UI.clearGraphics();
        }
    }
    //Solving function
    private void solve() {
        new Thread(()-> {
            Tile current = tiles.stream().filter(t -> t.equals(new Tile(0, height - 1))).findAny().get();
            Direction currentDir = current.closed.contains(new Direction(0, -1)) ? new Direction(1, 0) : new Direction(0, -1);
            while (!current.equals(new Tile(0, 0))) {
                current.fill();
                //Try ccw, then forward then cw, effectively prioritizing ccw and following that wall.
                if (current.isOpen(currentDir.ccw())) {
                    currentDir = currentDir.ccw();
                    current = current.getRelativeReal(currentDir);
                } else if (current.isOpen(currentDir)) {
                    current = current.getRelativeReal(currentDir);
                } else if (current.isOpen(currentDir.cw())) {
                    currentDir = currentDir.cw();
                    current = current.getRelativeReal(currentDir);
                } else {
                    currentDir = currentDir.ccw();
                }
            }
            current.fill();
        }).start();
    }
}
