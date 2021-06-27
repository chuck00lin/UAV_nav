VOXEL_SIZE = 5e-2

XY_TRANSFORM =  {
  translation = { 0., 0., 0. },
  rotation = { 0., -math.pi / 2., 0., },
}

options = {
  tracking_frame = "base_link",
  pipeline = {
    {
      action = "min_max_range_filter",
      min_range = 1.,
      max_range = 15.,
    },
    {
      action = "write_ros_map",
      range_data_inserter = {
        insert_free_space = true,
        hit_probability = 0.55,
        miss_probability = 0.49,
      },
      filestem = "map",
      resolution = 0.02,
    },
    -- 
    {
      action = "dump_num_points",
    },
    -- Gray X-Rays. These only use geometry to color pixels.
    -- {
    --  action = "write_xray_image",
    --  voxel_size = VOXEL_SIZE,
    --  filename = "xray_xy_all",
    -- transform = XY_TRANSFORM,
    --},

    -- We now use the intensities to color our points. We apply a linear
    -- transform to clamp our intensity values into [0, 255] and then use this
    -- value for RGB of our points. Every stage in the pipeline after this now
    -- receives colored points.
    --
    -- We write xrays again. These now use geometry and the intensities to
    -- color pixels - they look quite similar, just a little lighter.
    --{
    --  action = "intensity_to_color",
    --  min_intensity = 0.,
    --  max_intensity = 4095.,
    --},

    --{
    --  action = "write_xray_image",
    --  voxel_size = VOXEL_SIZE,
    --  filename = "xray_xy_all_intensity",
    --  transform = XY_TRANSFORM,
    --},
    -- We also write a PLY file at this stage, because gray points look good.
    -- The points in the PLY can be visualized using
    -- https://github.com/cartographer-project/point_cloud_viewer.
    {
      action = "write_ply",
      filename = "points.ply",
    },

    -- Now we recolor our points by frame and write another batch of X-Rays. It
    -- is visible in them what was seen by the horizontal and the vertical
    -- laser.
    -- origin: frame_id= horizontal_laser_link
    {
      action = "color_points",
      frame_id = "base_link",
      color = { 255., 0., 0. },
    },

    {
      action = "write_xray_image",
      voxel_size = VOXEL_SIZE,
      filename = "xray_xy_all_color",
     transform = XY_TRANSFORM,
    },
  }
}

return options
