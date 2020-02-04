execute_process(COMMAND "/home/samuel/Desktop/MARV2/catkin_ws/build/Dynamixel_SDK/ros/catkin_generated/python_distutils_install.sh" RESULT_VARIABLE res)

if(NOT res EQUAL 0)
  message(FATAL_ERROR "execute_process(/home/samuel/Desktop/MARV2/catkin_ws/build/Dynamixel_SDK/ros/catkin_generated/python_distutils_install.sh) returned error code ")
endif()
