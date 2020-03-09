#!/usr/bin/env python

from __future__ import print_function
import readchar
import rospy

from User_Controls.msg import movement
from User_Controls.msg import Test
from User_Controls.msg import Shield

import sys, select, termios, tty, threading

global e_stop
e_stop = 0

global e_linear
e_linear = 0

global key_pressed
key_pressed = 0

msg = """
Controls via Keyboard
---------------------------

GENERIC MOTION CONTROLS

w : move North (based on starting position)
x : move South
a : move West
d : move East

PERCISE MOTION CONTROLS

UP : increase velocity by  10%
DOWN : decrease velocity by 10%
LEFT : decrease angle by 10 degrees
RIGHT : increase angle by 10 degrees

ARM CONTROLS

o : raise arm by 20 steps
l : lower arm by 20 steps

ABOUT FACE

r : spin the robot around a full 180 degrees

CTRL-C to quit
"""
# Dictionary for Changing Set Velocity
velocity_dict = {
    readchar.key.UP : 10,
    readchar.key.DOWN : -10,
}

# Dictionary for Setting Directional Angle Manually
angular_dict = {
    readchar.key.LEFT : 10,
    readchar.key.RIGHT : -10,
}

# Dictionary for Goal Movement Direction
goal_direction_dict = {
    'w' : 8,
    'd' : 4,
    'x' : 2,
    'a' : 1
}

# Dictionary for Doing and About Face
about_face_dict = {
    'r' : 1
}

# Dictionary for Controlling Arm
arm_dict = {
    'o' : 1,
    'l' : 1,
}

data_ready = threading.Event()

class KeyboardPoller( threading.Thread ) :
    def run( self ) :
        global key_pressed
        ch = sys.stdin.read( 1 )
        if ch == 'K' : # the key you are interested in
            key_pressed = 1
        else :
            key_pressed = 0
        data_ready.set()

def E_STOP(data):
    global e_stop
    global e_linear
    e_stop = data.disable_control
    e_linear = data.velocity

if __name__=="__main__":
    settings = termios.tcgetattr(sys.stdin)

    #sub = rospy.Subscriber('Virtual_Bubble', Shield, E_STOP)
    pub1 = rospy.Publisher('movement', movement, queue_size = 1)
    pub2 = rospy.Publisher('Test', Test, queue_size = 1)
    rospy.init_node('teleop')
    poller = KeyboardPoller()
    poller.start()
    velocity = rospy.get_param("~velocity", 0)
    angle = rospy.get_param("~angle", 0)
    arm_speed = 0
    up_down = 0;
    goal_direction = 0;
    previous_direction = 8;
    aboutface = 0
    try:
        print(msg)
        while 1:
            if(key_pressed):
                #key = readchar.readkey()
                aboutface = 0
                if(goal_direction != 0):
                    previous_direction = goal_direction
                #If Velocity Key Hit
                if key in velocity_dict:
                    velocity += velocity_dict[key]
                    if velocity > 100:
    		           velocity = 100
                    elif velocity < -100:
    		           velocity = -100
                    print("Velocity Set to: " + str(velocity) + "% \n")

                # If Goal Direction Key Hit
                elif key in goal_direction_dict:
                    goal_direction = goal_direction_dict[key];
                    if goal_direction == 8:
                        print("Goal Direction set to North!\n")
                    elif goal_direction == 4:
                        print("Goal Direction set to East!\n")
                    elif goal_direction == 2:
                        print("Goal Direction set to South!\n")
                    else:
                        print("Goal Direction set to West!\n")

                # If Manual Angle Key Hit
                elif key in angular_dict:
                    angle += angular_dict[key]
                    if angle > 90:
                        angle = 90
                    elif angle < -90:
                        angle = -90
                    print("Angle is Set to: " + str(angle) + " degrees\n")

                # If About Face Key Hit
                elif key in about_face_dict:
                    aboutface = 1
                    print("Turning Robot Around\n")

                # If Arm control key Hit
                elif key in arm_dict:
                    if arm_dict[key] == 1:
                        arm_speed = 5
                    else:
                        arm_speed = 0

                # Anything Else Will Stop the Vehicle
                else:
                    velocity = 0
                    angle = 0
                    goal_direction = 0
                    aboutface = 0
                    print("Stopping All Movement!\n")
                    if key == '\x03':
                        break
            move = movement()
            move.velocity = velocity
            move.angle = angle
            move.goal_direction = goal_direction
            move.about_face = aboutface
            #move.previous_direction = previous_direction
            pub1.publish(move)

            arm = Test()
            arm.speed = arm_speed
            pub2.publish(arm)

    except Exception as e:
        print(e)

    finally:
        move = movement()
        move.velocity = 0
        move.angle = 0
        move.goal_direction = 0
        move.about_face = 0
        #move.previous_direction = 0
        pub1.publish(move)

        arm = Test()
        arm.speed = 0
        pub2.publish(arm)

        termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
