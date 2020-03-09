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
#define STOPS          0x73

// Velocity Controls
#define INCREASE_VEL   0x57
#define DECREASE_VEL   0x58

// Arm Controls
#define RAISE_ARM      0x6F
#define LOWER_ARM      0x6C

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
  Moving around:\n\
          w\n\
     a    s    d\n\
          x\n\
  \n\
  w/x : increase/decrease linear velocity\n\
  a/d : increase/decrease angular velocity\n\
  \n\
  s : force stop\n\
  \n\
  CTRL-C to quit\n\
  ";

  ROS_INFO("%s", msg.c_str());

  ros::Rate loop_rate(100);

  while(ros::ok())
  {
    if (kbhit())
    {
      char c = getch();

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
      else if (c == STOPS)
      {
        controls.goal_direction  = 0.0f;
        controls.goal_direction = 0.0f;
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
        controls.about_face  = 1;
        ROS_INFO("about_face: %d", controls.about_face);
      }
      else if (c == LOWER_ARM)
      {
        controls.about_face  = 0;
        ROS_INFO("about_face: %d", controls.about_face);
      }
      else
      {
        controls.goal_direction  = controls.goal_direction;
      }
    }

    controls_pub.publish(controls);

    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
