# MARV2

#Instructions for Start-Up

# U2D2 Setup

# sudo cp ./99-dynamixel-workbench-cdc.rules /etc/udev/rules.d/
# sudo udevadm control --reload-rules
# sudo udevadm trigger
#

# Check Dynamixel Connection

# rosrun dynamixel_workbench_controllers find_dynamixel /dev/ttyUSB0
#

# Wheel Mode

# roslaunch dynamixel_workbench_controllers dynamixel_controllers.launch use_cmd_vel:=true
# roslaunch dynamixel_workbench_operators wheel_operator.launch
#

# LIDAR

# Check Connection: sudo chmod a+rw /dev/ttyUSB0
# roslaunch rplidar_ros view_rplidar.launch

# Webcam

# roslaunch usb_cam usb_cam-test.launch
