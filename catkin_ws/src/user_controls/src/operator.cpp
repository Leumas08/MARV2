/*
  operator.cpp

  Definition: Node for controlling the motors on the MARV2
*/
#include <fcntl.h>
#include <termios.h>

#include <ros/ros.h>
#include <user_controls/movement.h>

// Definitions for Valid Controls
#define ESC_ASCII_VALUE   0x1b

// Directional Controls
#define NORTH          0x77
#define SOUTH          0x78
#define WEST           0x61
#define EAST           0x64

// Velocity Controls
#define INCREASE_VEL   0x57
#define DECREASE_VEL   0x58

// Arm Controls
#define RAISE_ARM      0x6F
#define LOWER_ARM      0x6C

// Special Controls
#define ABOUTFACE      0x62
#define STOP1          0x73
#define STOP2          0x53

// Controls for turning dynamixels
#define DYNA1          0x31
#define DYNA2          0x32
#define DYNA3          0x33
#define DYNA4          0x34

#define INCREASE_POS   0x41
#define DECREASE_POS   0x44

int getch(void)
{
  struct termios old_terminal, new_terminal;
  int ch;

  tcgetattr( STDIN_FILENO, &old_terminal );
  new_terminal = old_terminal;
  new_terminal.c_lflag &= ~(ICANON | ECHO);
  new_terminal.c_cc[VMIN] = 0;
  new_terminal.c_cc[VTIME] = 1;
  tcsetattr( STDIN_FILENO, TCSANOW, &new_terminal );
  ch = getchar();
  tcsetattr( STDIN_FILENO, TCSANOW, &old_terminal );

  return ch;
}

int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if (ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }
  return 0;
}

int main(int argc, char **argv)
{
  // Init ROS node
  ros::init(argc, argv, "operator");
  ros::NodeHandle node_handle("");

  double lin_vel_step = 0.01;
  double ang_vel_step = 0.1;

  ROS_INFO("You can set '-lin_vel_step' and  '-ang_vel_step' arguments (default is 0.01 and 0.1)");

  if (argc > 1)
  {
    lin_vel_step = atof(argv[1]);
    ang_vel_step = atof(argv[2]);
  }

  ros::Publisher controls_pub = node_handle.advertise<user_controls::movement>("controls", 10);
  user_controls::movement controls;

  std::string msg =
  "\n\
  Control Your Mobile Robot! \n\
  --------------------------- \n\
  Compass Direction:\n\
          w\n\
     a         d\n\
          x\n\
  \n\
  w: North\n\
  d: East\n\
  x: South\n\
  a: West\n\
  \n\
  Speed Controls: \n\
  W/X : increase/decrease base velocity\n\
  \n\
  Arm Controls: \n\
  o: raise arm\n\
  l: lower arm\n\
  \n\
  Unique Controls: \n\
  b: aboutface\n\
  s/S: STOP\n\
  CTRL-C: quit\n\
  ";

  ROS_INFO("%s", msg.c_str());

  ros::Rate loop_rate(100);

  while(ros::ok())
  {
    // Reset about_face
    if(controls.about_face == 1) {
      controls.about_face = 0;
    }
    controls.dyna_id = 0;
    controls.dyna_pos = 0;
    // If character available
    if (kbhit())
    {
      // Get New Character
      char c = getch();

      // Evaluate Input
      if (c == NORTH)
      {
        controls.goal_direction = 8;
        ROS_INFO("goal_direction: %d", controls.goal_direction);
      }
      else if (c == SOUTH)
      {
        controls.goal_direction = 2;
        ROS_INFO("goal_direction: %d", controls.goal_direction);
      }
      else if (c == WEST)
      {
        controls.goal_direction = 1;
        ROS_INFO("goal_direction: %d", controls.goal_direction);
      }
      else if (c == EAST)
      {
        controls.goal_direction = 4;
        ROS_INFO("goal_direction: %d", controls.goal_direction);
      }
      else if (c == INCREASE_VEL)
      {
        controls.velocity  = controls.velocity + 1;
        ROS_INFO("velocity: %d", controls.velocity);
      }
      else if (c == DECREASE_VEL)
      {
        controls.velocity  = controls.velocity - 1;
        ROS_INFO("velocity: %d", controls.velocity);
      }
      else if (c == RAISE_ARM)
      {
        controls.arm_controls  = 1;
        ROS_INFO("arm is being raised");
      }
      else if (c == LOWER_ARM)
      {
        controls.arm_controls  = 2;
        ROS_INFO("arm is being lowered");
      }
      else if (c == ABOUTFACE)
      {
        controls.goal_direction = 0;
        controls.about_face = 1;
      }
      else if (c == STOP1 || c == STOP2)
      {
        controls.goal_direction  = 0;
        controls.arm_controls = 0;
        ROS_INFO("goal_direction: %d", controls.goal_direction);
        ROS_INFO("arm has stopped moving");
      }
      else if (c == DYNA1)
      {
        controls.dyna_id = 1;
      }
      else if (c == DYNA2)
      {
        controls.dyna_id = 2;
      }
      else if (c == DYNA1)
      {
        controls.dyna_id = 3;
      }
      else if (c == DYNA1)
      {
        controls.dyna_id = 4;
      }
      else if (c == INCREASE_POS){
        controls.dyna_pos = 2;
      }
      else if (c == INCREASE_POS){
        controls.dyna_pos = -2;
      }
    }

    controls_pub.publish(controls);

    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
