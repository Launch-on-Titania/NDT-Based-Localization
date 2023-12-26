# NDT Based Localization Method

This repository contains a method for localization within a pointcloud map using NDT (Normal Distributions Transform) algorithms. It is designed to work with ROS (Robot Operating System) environments.

## Localization in a Pointcloud Map (.pcd)

This method utilizes .pcd (Point Cloud Data) files for map-based localization.

## How to Use

### Preparation

1. **PCD Map and rosbag(.bag)**:
   - Ensure you have a .pcd map file ready. For this example, we use `map_v1.pcd`.
   - The ROSbag used here is `mapping_lidar.bag`.
   - Place the .pcd file in the `map` folder within your workspace.

2. **Building in Your ROS Workspace**:
   - Clone the entire repository into your own ROS workspace.

### Configuration

1. **Map Loader**:
   - Modify the map loader configuration to point to your .pcd file, like so:

     ```xml
     <arg name="pcd_path" default="$(find ndt_localizer)/map/map_v1.pcd"/>
     ```

2. **Point Cloud Downsampling** (Pre-configured):
   - If using sparse Lidar data (e.g., VLP-16), set a smaller `leaf_size` in `launch/points_downsample.launch` to `2.0`.
   - For denser Lidar point clouds (e.g., VLP-32, Hesai Pandar40P, HDL-64), use a `leaf_size` of `3.0`.

### Running the Package

After completing the above steps:

1. **Start ROScore**:
   ```bash
   roscore
   ```

2. **Navigate to Your Workspace**:
   ```bash
   cd catkin_ws
   source devel/setup.bash
   rosparam set use_sim_time true
   ```

3. **Launch the Package**:
   - To run only the `ndt_localizer` package:
     ```bash
     roslaunch ndt_localizer ndt_localizer.launch
     ```
   - To run both `scan context` and `ndt_localizer`:
     ```bash
     roslaunch ndt_localizer sc_ndt_localizer.launch
     ```
