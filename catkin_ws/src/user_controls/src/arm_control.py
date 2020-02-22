#!/usr/bin/env python
import rospy
import serial
import time
from beginner_tutorials.msg import Test
ser = serial.Serial('/dev/ttyACM0', 9600)

def callback(data):
    rospy.loginfo(rospy.get_caller_id() + "I heard %s", data.speed)
    if data.speed == 5:
        ser.write('u')
    elif data.speed == 0:
        ser.write('d')

def arm_control():

    # In ROS, nodes are uniquely named. If two nodes with the same
    # name are launched, the previous one is kicked off. The
    # anonymous=True flag means that rospy will choose a unique
    # name for our 'listener' node so that multiple listeners can
    # run simultaneously.
    rospy.init_node('am_control', anonymous=True)

    rospy.Subscriber("Test", Test, callback)

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

if __name__ == '__main__':
    arm_control()
    ser.close()
