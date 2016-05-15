package main;/*
 * Simbad - Robot Simulator Copyright (C) 2004 Louis Hugues
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * -----------------------------------------------------------------------------
 * $Author: sioulseuguh $
 * $Date: 2005/03/17 17:55:54 $ $Revision: 1.6 $ $Source: /cvsroot/simbad/src/simbad/demo/BaseDemo.java,v $
 */

import javax.vecmath.Color3f;
import javax.vecmath.Vector3d;

import simbad.demo.Demo;
import simbad.sim.*;

import java.awt.*;

/** A Basic demo with camera sensor, sonars and bumpers.
 * The robot wanders and stops when it collides.
 *
 */
public class MyArena extends Demo {
    Robot robot;
    CameraSensor camera;
    RangeSensorBelt b;
    public class Robot extends Agent {
        public Robot (Vector3d position, String name) {
            super(position,name);
            this.radius = 0.05f;
            this.height = 0.1f;
            // Add sensors
            double agentHeight = getHeight();
            float cameraBodyRadius = 0.3f;
            camera = new CameraSensor(cameraBodyRadius, 320, 240);

            camera.setUpdatePerSecond(60);
            Vector3d pos = new Vector3d(0.0, (agentHeight / 2)
                    + (cameraBodyRadius * 3) / 4, 0);
            addSensorDevice(camera, pos, 0);
            RangeSensorBelt b = new RangeSensorBelt(0.1f,0f,10f,4,RangeSensorBelt.TYPE_IR,0);

            addSensorDevice(b,new Vector3d(pos.getX(),0,pos.getZ()),Math.PI);
            setKinematicModel(new DifferentialKinematic(getRadius()));
        }

        /** Initialize Agent's Behavior*/
        public void initBehavior() {
            // nothing particular in this case
        }

        /** Perform one step of Agent's Behavior */
        public void performBehavior() {
            //Uncomment when testing to make the robot move without a connected pi
            //robot.setWheelVelocity(1,1);
            //robot.setWheelVelocity(2,1);
        }
        /**
         * Gets a wheels velocity.
         */
        public double getWheelsVelocity(int motor) {
            return motor == 1? ((DifferentialKinematic) kinematicModel).getLeftVelocity():((DifferentialKinematic) kinematicModel).getRightVelocity();
        }
        /**
         * Sets a wheel velocity.
         */
        public void setWheelVelocity(int motor, double value) {
            ((DifferentialKinematic) kinematicModel).setWheelsVelocity(motor==1?value:getWheelsVelocity(1), motor==2?value:getWheelsVelocity(2));
        }

    }
    float size = 1;
    float width = 0.1f;
    float pathWidth = 0.01f;
    public MyArena() {
        worldSize = 2;
        this.floorColor = new Color3f(Color.BLACK);
        this.wallColor = new Color3f(Color.WHITE);
        light1IsOn = true;
        light2IsOn = false;
        Wall w = new Wall(new Vector3d(size, 0, 0), size*2, 0.5f,width, this);
        w.rotate90(1);
        add(w);
        w = new Wall(new Vector3d(-size, 0, 0), size*2, 0.5f,width, this);
        w.rotate90(1);
        add(w);
        w = new Wall(new Vector3d(0, 0, size), size*2, 0.5f,width, this);
        add(w);
        w = new Wall(new Vector3d(0, 0, -size), size*2, 0.5f,width, this);
        add(w);


        //w = new Wall(new Vector3d(-0.5, 0, -1), 3.1f, 0.01f,pathWidth, this);
        //w.collides = false;
        //add(w);

        //w = new Wall(new Vector3d(1, 0, -0.76), 0.5f, 0.01f,pathWidth, this);
        //w.rotateY(-1.8);
        //w.collides = false;
        //add(w);

        w = new Wall(new Vector3d(0.175, 0, 1.8/2), 0.35f, 0.01f,pathWidth, this);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(0.52/2-0.15, 0, 1.7/2-0.8), 0.2f, 0.01f,pathWidth, this);
        w.rotateY(1.5);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(0.54/2-0.15, 0, 1.46/2-0.8), 0.04f, 0.01f,pathWidth, this);
        w.rotateY(1.3);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(0.56/2-0.15, 0, 1.4/2-0.8), 0.04f, 0.01f,pathWidth, this);
        w.rotateY(1.0);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(0.61/2-0.15, 0, 1.35/2-0.8), 0.045f, 0.01f,pathWidth, this);
        w.rotateY(0.6);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(0.67/2-0.15, 0, 1.32/2-0.8), 0.045f, 0.01f,pathWidth, this);
        w.rotateY(0.4);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(0.76/2-0.15, 0, 1.31/2-0.8), 0.045f, 0.01f,pathWidth, this);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(0.85/2-0.15, 0, 1.3/2-0.8), 0.045f, 0.01f,pathWidth, this);
        w.rotateY(0.3);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(0.93/2-0.15, 0, 1.26/2-0.8), 0.045f, 0.01f,pathWidth, this);
        w.rotateY(0.5);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(0.5-0.15, 0, 1.24/2-0.8), 0.05f, 0.01f,pathWidth, this);
        w.rotateY(0.1);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(1.07/2-0.15, 0, 1.24/2-0.8), 0.045f, 0.01f,pathWidth, this);
        w.rotateY(-0.1);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(1.14/2-0.15, 0, 1.26/2-0.8), 0.045f, 0.01f,pathWidth, this);
        w.rotateY(-0.5);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(1.21/2-0.15, 0, 1.29/2-0.8), 0.05f, 0.01f,pathWidth, this);
        w.rotateY(-0.5);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(1.28/2-0.15, 0, 1.34/2-0.8), 0.05f, 0.01f,pathWidth, this);
        w.rotateY(-0.7);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(1.34/2-0.15, 0, 1.4/2-0.8), 0.035f, 0.01f,pathWidth, this);
        w.rotateY(-0.9);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(1.38/2-0.15, 0, 1.45/2-0.8), 0.025f, 0.01f,pathWidth, this);
        w.rotateY(-1.2);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(1.42/2-0.15, 0, 1.48/2-0.8), 0.035f, 0.01f,pathWidth, this);
        w.rotateY(-0.6);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(1.47/2-0.15, 0, 1.5/2-0.8), 0.035f, 0.01f,pathWidth, this);
        w.rotateY(-0.2);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(1.52/2-0.15, 0, 1.5/2-0.8), 0.035f, 0.01f,pathWidth, this);
        w.rotateY(0);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(1.58/2-0.15, 0, 1.49/2-0.8), 0.035f, 0.01f,pathWidth, this);
        w.rotateY(0.3);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(1.64/2-0.15, 0, 1.46/2-0.8), 0.035f, 0.01f,pathWidth, this);
        w.rotateY(0.6);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(1.69/2-0.15, 0, 1.42/2-0.8), 0.035f, 0.01f,pathWidth, this);
        w.rotateY(0.9);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(1.72/2-0.15, 0, 1.38/2-0.8), 0.035f, 0.01f,pathWidth, this);
        w.rotateY(1.1);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(1.74/2-0.15, 0, 1.34/2-0.8), 0.035f, 0.01f,pathWidth, this);
        w.rotateY(1.4);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(1.75/2-0.15, 0, 1.28/2-0.8), 0.035f, 0.01f,pathWidth, this);
        w.rotateY(1.6);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(1.75/2-0.15, 0, 1.24/2-0.8), 0.035f, 0.01f,pathWidth, this);
        w.rotateY(1.8);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(1.73/2-0.15, 0, 1.18/2-0.8), 0.035f, 0.01f,pathWidth, this);
        w.rotateY(2);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(1.71/2-0.15, 0, 1.15/2-0.8), 0.035f, 0.01f,pathWidth, this);
        w.rotateY(2.2);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(1.68/2-0.15, 0, 1.12/2-0.8), 0.035f, 0.01f,pathWidth, this);
        w.rotateY(2.5);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(1.64/2-0.15, 0, 1.1/2-0.8), 0.035f, 0.01f,pathWidth, this);
        w.rotateY(2.8);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(1.57/2-0.15, 0, 1.07/2-0.8), 0.035f, 0.01f,pathWidth, this);
        w.rotateY(2.9);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(1.5/2-0.15, 0, 1.05/2-0.8), 0.035f, 0.01f,pathWidth, this);
        w.rotateY(2.9);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(1.45/2-0.15, 0, 1.03/2-0.8), 0.035f, 0.01f,pathWidth, this);
        w.rotateY(2.8);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(1.4/2-0.15, 0, 0.5-0.8), 0.035f, 0.01f,pathWidth, this);
        w.rotateY(2.3);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(1.36/2-0.15, 0, 0.47-0.8), 0.035f, 0.01f,pathWidth, this);
        w.rotateY(2);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(1.33/2-0.15, 0, 0.44-0.8), 0.035f, 0.01f,pathWidth, this);
        w.rotateY(1.8);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(1.315/2-0.15, 0, 0.40-0.8), 0.045f, 0.01f,pathWidth, this);
        w.rotateY(1.85);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(1.285/2-0.15, 0, 0.37-0.8), 0.035f, 0.01f,pathWidth, this);
        w.rotateY(1.85);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(1.26/2-0.15, 0, 0.35-0.8), 0.035f, 0.01f,pathWidth, this);
        w.rotateY(2.1);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(1.22/2-0.15, 0, 0.32-0.8), 0.035f, 0.01f,pathWidth, this);
        w.rotateY(2.3);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(1.175/2-0.15, 0, 0.305-0.8), 0.035f, 0.01f,pathWidth, this);
        w.rotateY(2.9);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(1.08/2-0.15, 0, 0.3-0.8), 0.08f, 0.01f,pathWidth, this);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(0.37-0.15, 0, 0.15), 0.25f, 0.01f,pathWidth, this);
        //w.rotateY(1.5);
        w.collides = false;
        add(w);

        //DO NOT TOUCH CODE BELOW
        //MORGAN
        w = new Wall(new Vector3d(0.25-0.15, 0, -0.24+0.5), 0.1f, 0.01f,pathWidth, this);
        w.rotateY(1.5);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(-0.25-0.15, 0, -0.5), 1.5f, 0.01f,pathWidth, this);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(0.4-0.15, 0, -0.02+0.5), 0.2f, 0.01f,pathWidth, this);
        w.rotateY(-0.0);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(0.6-0.15, 0, 0.04+0.5), 0.2f, 0.01f,pathWidth, this);
        w.rotateY(-0.0);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(0.45-0.15, 0, 0.1+0.5), 0.1f, 0.01f,pathWidth, this);
        w.rotateY(-0.0);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(0.4-0.15, 0, 0.2+0.5), 0.2f, 0.01f,pathWidth, this);
        w.rotateY(-1.57);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(0.45-0.15, 0, 0.3+0.5), 0.1f, 0.01f,pathWidth, this);
        w.rotateY(-0.0);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(0.5-0.15, 0, 0.3+0.5), 0.2f, 0.01f,pathWidth, this);
        w.rotateY(-1.57);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(0.5-0.15, 0, -0.2+0.5), 0.61f, 0.01f,pathWidth, this);
        w.rotateY(-1.57);
        w.collides = false;
        add(w);


        w = new Wall(new Vector3d(0.5-0.15, 0, -0.15+0.5), 0.5f, 0.01f,pathWidth, this);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(0.5-0.15, 0, -0.25+0.5), 0.5f, 0.01f,pathWidth, this);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(0.25-0.15, 0, 1.8+0.5), 0.5f, 0.01f,pathWidth, this);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(0.52-0.15, 0, 1.7+0.5), 0.4f, 0.01f,pathWidth, this);
        w.rotateY(1.5);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(0.51-0.15, 0, 1.9+0.5), 0.2f, 0.01f,pathWidth, this);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(0.54-0.15, 0, 1.46+0.5), 0.08f, 0.01f,pathWidth, this);
        w.rotateY(1.3);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(0.56-0.15, 0, 1.4+0.5), 0.08f, 0.01f,pathWidth, this);
        w.rotateY(1.0);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(0.61-0.15, 0, 1.35+0.5), 0.09f, 0.01f,pathWidth, this);
        w.rotateY(0.6);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(0.67-0.15, 0, 1.32+0.5), 0.09f, 0.01f,pathWidth, this);
        w.rotateY(0.4);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(0.76-0.15, 0, 1.31+0.5), 0.09f, 0.01f,pathWidth, this);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(0.85-0.15, 0, 1.3+0.5), 0.09f, 0.01f,pathWidth, this);
        w.rotateY(0.3);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(1-0.15, 0, 1.24+0.5), 0.1f, 0.01f,pathWidth, this);
        w.rotateY(0.1);
        w.collides = false;
        add(w);

        w = new Wall(new Vector3d(0.93-0.15, 0, 1.26+0.5), 0.09f, 0.01f,pathWidth, this);
        w.rotateY(0.5);
        w.collides = false;
        add(w);

        //SANJAY

        robot = new Robot(new Vector3d(-0.5, 0.1, -0.5), "robot 1");
        add(robot);
        hasAxis = false;

    }
}