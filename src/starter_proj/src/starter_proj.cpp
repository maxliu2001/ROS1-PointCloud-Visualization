#include <librealsense2/rs.hpp>
#include <iostream>
#include <sensor_msgs/PointCloud2.h>
#include <ros/ros.h>
#include <ros/package.h>
#include "open3d/Open3D.h"
#include "open3d_ros/open3d_ros.h"


class Display {
    public:
        static open3d::visualization::Visualizer vis;
        static std::shared_ptr<open3d::geometry::PointCloud> prev;
        static open3d::camera::PinholeCameraParameters prevView;

        Display()
        {
            // open all resources
            vis.CreateVisualizerWindow("Starter window", 920, 580);
            ROS_INFO("Preparing to launch visualizer.");

            // add coordinates
            std::shared_ptr<open3d::geometry::TriangleMesh> coord = open3d::geometry::TriangleMesh::CreateCoordinateFrame();
            vis.AddGeometry(coord);
            vis.Run();

            // save init config
            vis.GetViewControl().SetZoom(2.5);
            open3d::visualization::ViewControl& newParam = vis.GetViewControl();
            newParam.ConvertToPinholeCameraParameters(prevView);
        }
        void static cloud_callback(const sensor_msgs::PointCloud2ConstPtr& cloud_data)
        {
            // preprocess sensor data to Open3D pointcloud
            open3d::geometry::PointCloud pcd;
            open3d_ros::rosToOpen3d(cloud_data, pcd);
            Eigen::Matrix4d m;
            m << 1, 0, 0, 0,
                0, -1, 0, 0,
                0, 0, -1, 0,
                0, 0, 0, 1;
            pcd.Transform(m);
            pcd.VoxelDownSample(0.05);
            auto p = std::make_shared<open3d::geometry::PointCloud>(pcd);

            //deleting previous geometries and add new ones
            vis.RemoveGeometry(prev);
            vis.AddGeometry(p);
            prev = p;

            // restoring previous view control
            open3d::visualization::ViewControl& currView = vis.GetViewControl();
            currView.ConvertFromPinholeCameraParameters(prevView);

            // render views
            vis.UpdateRender();
            vis.PollEvents();
            vis.Run();

            // saving new view control manipulations
            open3d::visualization::ViewControl& newParam = vis.GetViewControl();
            newParam.ConvertToPinholeCameraParameters(prevView);
        }
        ~Display()
        {
            Display::vis.Close();
        }
};

open3d::visualization::Visualizer Display::vis;
std::shared_ptr<open3d::geometry::PointCloud> Display::prev;
open3d::camera::PinholeCameraParameters Display::prevView;

int main(int argc, char **argv)
{
    // // Initialize the camera pipeline

    // rs2::pointcloud pcd;
    // rs2::points points;

    // rs2::pipeline pipeline;
    // rs2::config config;
    // config.enable_stream(rs2_stream::RS2_STREAM_COLOR, 640, 480, rs2_format::RS2_FORMAT_BGR8, 30);
    // config.enable_stream(rs2_stream::RS2_STREAM_DEPTH, 640, 480, rs2_format::RS2_FORMAT_Z16, 30);
    // pipeline.start(config);

    // rs2::colorizer color_map;
    // rs2::align align(rs2_stream::RS2_STREAM_COLOR);
    // std::shared_ptr<open3d::geometry::PointCloud> res;

    // while (true)
    // {
    //     // Wait for a new set of frames from the camera
    //     rs2::frameset frames = pipeline.wait_for_frames();
    //     frames = align.process(frames);
    //     rs2::frame color_frame = frames.get_color_frame();
    //     rs2::frame depth_frame = frames.get_depth_frame();

    //     pcd.map_to(color_frame);
    //     points = pcd.calculate(depth_frame);
    // }

    // pipeline.stop();

    // subscriber node
    ros::init(argc, argv, "starter_proj_node");
    std::string ns = ros::this_node::getNamespace();
    ros::NodeHandle nh(ns);
    Display d;
    Display::prev = NULL;
    ros::Subscriber subCloud = nh.subscribe("/camera/depth/color/points", 1, d.cloud_callback);
    ros::spin();

    return 0;
}