#!/usr/bin/env python
import rospy

from beginner_tutorials.msg import Test

def main():
	rospy.init_node("Test_publisher")
	pub = rospy.Publisher("Test", Test, queue_size=1)
	r = rospy.Rate(1)

	msg = Test()
	while not rospy.is_shutdown():
		msg.direction = 1
		msg.turn = 85
		msg.speed = 5
		pub.publish(msg)
		r.sleep()

if __name__ == "__main__":
	try:
		main()
	except rospy.ROSInterruptException:
		pass
