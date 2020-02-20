#!/usr/bin/env python

from __future__ import print_function
import readchar
import rospy

from User_Controls.msg import movement
from User_Controls.msg import Test
from User_Controls.msg import Shield

import sys, select, termios, tty

global e_stop
global e_linear
e_stop = 0
e_linear = 0

msg = """
Controls via Keyboard
---------------------------

GENERIC MOTION CONTROLS

w : advance @ set velocity
s : retreat @ set velocity
a : turn tires 90 degrees left
d : turn tires 90 degrees right

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
#change the velocity used in advance_retreat
velocity_dict = {
    readchar.key.UP : 10,
    readchar.key.DOWN : -10,
}

#set angle of tires
turn_precise_dict = {
    readchar.key.LEFT : -10,
    readchar.key.RIGHT : 10,
}

#90 degree turn around (May just be one direction)
turn_90_dict = {
    'a': 90,
    'd': -90,
}

#Move Forward/Backward
advance_retreat_dict = {
    'w': 1,
    's': -1,
}

#180 degree about-face
about_face_dict = {
    'r' : 1,
}

#Arm raising/lowering
arm_dict = {
    'o' : 1,
    'l' : 1,
}

def values(vel, ang):
    return "currently:\tvelocity: %s\tangle: %s " % (vel, ang)

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

    velocity = rospy.get_param("~velocity", 0)
    angle = rospy.get_param("~angle", 0)
    motion = 0;
    arm_speed = 0
    up_down = 0;
    try:
        print(msg)
        print(values(velocity, angle))
        while 1:
            key = readchar.readkey()
            aboutface = 0
            if key in velocity_dict:
                velocity += velocity_dict[key]
                if velocity > 100:
		           velocity = 100
                elif velocity < -100:
		           velocity = -100
                print("Velocity Set to: " + str(velocity) + "\n")
            elif key in advance_retreat_dict:
                motion = advance_retreat_dict[key];
                if motion == 1:
                    print("Robot Is Moving Forward\n")
                else:
                    print("Robot Is Moving Backward\n")
            elif key in turn_precise_dict:
                angle += turn_precise_dict[key]
                if angle > 90:
                    angle = 90
                elif angle < -90:
                    angle = -90
                print("Angle is Set to: " + str(angle) + " degrees\n")
            elif key in turn_90_dict:
                angle = turn_90_dict[key]
                print("Angle is Set to: " + str(angle) + " degrees\n")
            elif key in about_face_dict:
                aboutface = 1
                print("Turning Robot Around\n")
            elif key in arm_dict:
                if arm_dict[key] == 1:
                    arm_speed = 5
                else:
                    arm_speed = 0
            else:
                velocity = 0
                angle = 0
                motion = 0
                aboutface = 0
                if key == '\x03':
                    break
            move = movement()
            move.velocity = velocity
            move.angle = angle
            move.motion = motion
            move.about_face = aboutface
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
        move.motion = 0
        move.about_face = 0
        pub1.publish(move)

        arm = Test()
        arm.speed = 0
        pub2.publish(arm)

        termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
