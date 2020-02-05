#!/usr/bin/env python

from __future__ import print_function

import rospy

from beginner_tutorials.msg import movement

import sys, select, termios, tty

msg = """
Reading from the keyboard  and Publishing to Twist!
---------------------------
Moving around:
        w    
   a    s    d
        x    

anything else : stop

w : increase forward velocity by 10%
a/d: decrease/increase angle from center front by 10 degrees (-90 to 90)

CTRL-C to quit
"""

moveBindings = {
    'w': 10,
    'x': -10,
}

turnBindings = {
    'a': -10,
    'd': 10,
}


def get_key():
    tty.setraw(sys.stdin.fileno())
    select.select([sys.stdin], [], [], 0)
    key = sys.stdin.read(1)
    termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
    return key


def values(vel, ang):
    return "currently:\tvelocity: %s\tangle: %s " % (vel, ang)


if __name__=="__main__":
    settings = termios.tcgetattr(sys.stdin)

    pub = rospy.Publisher('movement', movement, queue_size = 1)
    rospy.init_node('teleop')

    velocity = rospy.get_param("~velocity", 0)
    angle = rospy.get_param("~angle", 0)

    try:
        print(msg)
        print(values(velocity, angle))
        while 1:
            key = get_key()
            if key in moveBindings.keys():
                velocity += moveBindings[key]
		if velocity > 100:
		    velocity = 100
		elif velocity < -100:
		    velocity = -100
		print(values(velocity,angle))
            elif key in turnBindings.keys():
                angle += turnBindings[key]
		if angle > 90:
                    angle = 90
                elif angle < -90:
                    angle = -90
		print(values(velocity,angle))
            else:
		velocity = 0
		angle = 0
                if key == '\x03':
                    break
		print(values(velocity,angle))
            move = movement()
            move.velocity = velocity
            move.angle = angle
            pub.publish(move)

    except Exception as e:
        print(e)

    finally:
        move = movement()
        move.velocity = 0
        move.angle = 0
        pub.publish(move)

        termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
