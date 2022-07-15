## A repo for 4wd mobile robot, with *Macanum Wheel*, by teamwork.

- Controller:  
    - Raspberry Pi 4B (with RAM of 2GB)
    - STM32F405

- Motor:  
    - BLDC motor  
    - HS-485 motor driver

- Sensor:
    - LDLIDAR: LD06

- Protocol:  
    - RS-485  
 
- Test Environment  
    - Ubuntu20.04 mate  
    - ROS Noetic

## ROS on Raspberry Pi 4B

### Lidar SDK

- See [ldlidar_stl_ros](https://github.com/ldrobotSensorTeam/ldlidar_stl_ros)

### ROS-Odom

- [laser_scan_matcher](https://github.com/CCNYRoboticsLab/scan_tools/tree/indigo/laser_scan_matcher)  
- [rf2o_laser_odometry](https://github.com/MAPIRlab/mapir-ros-pkgs/tree/master/src/rf2o_laser_odometry)

## robot control on STM32F405

We deploy on a 4-**mecanum-wheel**-drive vehicle. Inverse and direct kinematics can be easily googled

Further info see files under `stm32_car_control/` directory.

## Communication between RPI 4B and STM32, through ROS

### MODIFY

* STM32
  
Set baudrate same as below or configure yourself.
```
 115200  8bits 1stop no parity
```

* ROS node

Set baudrate in `/ros_ws/src/ros_rpi_to_stm32/my_serial_node/src/my_serial_node.cpp`, in line 80. Make sure it's the same as STM32's
  
ROS node is named `my_serial_node` ，which needs `serial` library. Clone [serial](https://github.com/wjwwood/serial) and place it under the same directory as `my_serial_node`.

Go back to `~/ros_ws$` and compile `my_serial_node` only:

```
$ catkin_make -DCATKIN_WHITELIST_PACKAGES="my_serial_node"
```

If you want to compile all the packages at the same time, do:

```
$ catkin_make
```

Now, `my_serial_node` node is generated.

### TEST

First make sure RPi serial port is set to `a+x` right, e.g.

```
 $sudo chmod a+x /dev/ttyAMAO
```

Caution: `ttyAMA0` should be set to your own serial port name, e.g. `ttyUSB0`.


Then make sure `roscore` and lidar SDK are both already turned up.

You can also run those nodes by `roslaunch`.

```
$ cd ~/ros_ws

$ source devel/setup.bash

$ roslaunch ldlidar_stl_ros ld06.launch
```

Then run `my_serial_node`.

```
$ rosrun my_serial_node my_serial_node
```


New 2 terminal at the same time and enter respectively(make sure `roscore` is already running):

```
$ rosrun turtlesim turtlesim_node
```

```
$ rosrun turtlesim turtle_teleop_key
```

Now you can send `Twists` message through the **arrow keys of your keyboard**.

You can **also** directly publish the `cmd_vel` topic by doing:

```
$ rostopic pub -r 1 turtle1/cmd_vel geometry_msgs/Twist -- '[1.0, 0, 0]' '[0, 0, 0.8]'
```

note that only $v_x$, $v_y$ and $\omega_z$ can be set to not zero.

---

> More details coming in few days.