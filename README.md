# Starter Project: **Cloud Point Field Mapping on Ros Open3D (C++)**
## Environment Setup
Three libraries are used in this project:
* [Intel RealSense Camera SDK](https://github.com/IntelRealSense/realsense-ros/tree/ros1-legacy) (built from source)
* [Open3D](http://www.open3d.org/docs/release/compilation.html) (built from source)
* [RostoOpen3D package: ROS interface for Open3D](https://github.com/ntnu-arl/open3d_ros) (now ros-perception/perception_open3d)

The VM that this project is built on is Ubuntu 20.04. ROS 1 noetic is installed onto the VM. In order to successfully install the three libararies, the system must have [ddynamic_reconfiguration](https://github.com/pal-robotics/ddynamic_reconfigure/tree/kinetic-devel) downloaded to the `src` folder of the catkin workspace. Furthermore, `libc++` is required to setup the packages by running `sudo apt install libc++`. Sourcing commands has been added to `/.bashrc` file to automate sourcing every time one opens a new terminal.

In order to successfully build the `src` folder of the catkin workspace, RealSense Camera SDK is built with `catkin_make -DCATKIN_ENABLE_TESTING=False -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON`. In addition, Open3D library should be built with `-DCMAKE_INSTALL_PREFIX=$HOME/open3d_install` for the `CMakeLists.txt` file to build the executable successfully.
## Usage
The camera is launched using the customized launch file for pointcloud provided by Intel Realsense Camera sdk. Note that I have included a number of parameters in `starter.launch`. `starter.launch` is a ros node launch file that launches the Realsense camera node and the Open3D subsriber/processing node together. The pointcloud data that is published in the Realsense camera node is then processed by `starter_proj_node`. 

In `starter_proj_node`, the pointcloud data is downsampled before converting from `ros::sensor_msgs` type to `open3d::geometry::PointCloud` type using the helper library `RostoOpen3D`. The cloudpoint data is displayed in `open3d::visualization::Visualizer`. Since add geometry option resets views, the camera view of previous state is restored in every frame. In each subsriber callback function the old geometry is deleted while the new one is added to the Visualizer. 
## Demo

To be updated

## Future Directions
The visualizer class can be customized to isolate a specific frame, or to render frames differently. Additionally, the program can be tuned into analyzing a rosbag file through reconstructive pipeline so that the scanning is more comprehensive. Such details can be implemented in the near future. 
