# Starter Project: **Cloud Point Field Mapping on Ros Open3D (C++)**
## Environment Setup
Three libraries are used in this project:
* [Intel RealSense Camera SDK](https://github.com/IntelRealSense/realsense-ros/tree/ros1-legacy) (built from source)
* [Open3D](http://www.open3d.org/docs/release/compilation.html) (built from source)
* [RostoOpen3D package: ROS interface for Open3D](https://github.com/ntnu-arl/open3d_ros) (now ros-perception/perception_open3d)

The VM that this project is built on is Ubuntu 20.04. ROS 1 noetic is installed onto the VM. In order to successfully install the three libararies, the system must have [ddynamic_reconfiguration](https://github.com/pal-robotics/ddynamic_reconfigure/tree/kinetic-devel) downloaded to the `src` folder of the catkin workspace. Furthermore, `libc++` is required to setup the packages by running `sudo apt install libc++`. Sourcing commands has been added to `/.bashrc` file to automate sourcing every time one opens a new terminal.

In order to successfully build the `src` folder of the catkin workspace, RealSense Camera SDK is built with `catkin_make -DCATKIN_ENABLE_TESTING=False -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON`. In addition, Open3D library should be built with `-DCMAKE_INSTALL_PREFIX=$HOME/open3d_install` for the `CMakeLists.txt` file to build the executable successfully.
## Usage
