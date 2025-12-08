# QR Detector ROS 2 Package

GPU-accelerated QR code detection node for Jetson Xavier NX.

## Features

- ✅ GPU-accelerated image processing using OpenCV CUDA
- ✅ Subscribes to `/state` topic - activates on "kamikaze" command
- ✅ Subscribes to `/image_raw` topic for camera images
- ✅ Publishes debug images to `/vision/qr_debug_image`
- ✅ Publishes QR code data to `/vision/qr_data`
- ✅ Automatic fallback to CPU if CUDA is unavailable

## Dependencies

- ROS 2 Humble
- OpenCV with CUDA support
- cv_bridge
- image_transport
- std_msgs
- sensor_msgs
- px4_msgs

## Building

```bash
cd ~/your_ros2_workspace/src
# Copy this package to src directory
colcon build --packages-select qr_detector
source install/setup.bash
```

## Usage

### Launch the node:

```bash
ros2 launch qr_detector qr_detection.launch.py
```

### Or run directly:

```bash
ros2 run qr_detector qr_detection_node
```

## Topics

### Subscriptions:
- `/state` (std_msgs/String): State command. Node activates when receives "kamikaze"
- `/image_raw` (sensor_msgs/Image): Camera image input

### Publications:
- `/vision/qr_debug_image` (sensor_msgs/Image): Debug image with QR code detection overlay (if detected)
- `/vision/qr_data` (std_msgs/String): Detected QR code text (only published when QR is detected)

## Behavior

1. Node starts in inactive state
2. When `/state` topic receives "kamikaze" message, node becomes active
3. While active, processes images from `/image_raw`
4. If QR code detected:
   - Draws green bounding box around QR code
   - Draws red corner points
   - Adds text label with QR content
   - Publishes debug image to `/vision/qr_debug_image`
   - Publishes QR text to `/vision/qr_data`
5. If no QR code detected:
   - Publishes original image to `/vision/qr_debug_image`
   - Does not publish to `/vision/qr_data`

## GPU Acceleration

The node uses OpenCV CUDA for image preprocessing:
- Image upload to GPU memory
- Color conversion (BGR to Grayscale) on GPU
- Optional Gaussian blur on GPU (currently commented out)

If CUDA is not available, the node automatically falls back to CPU processing.

## Testing

1. Start the camera node (publishes to `/image_raw`)
2. Start this QR detection node
3. Send "kamikaze" to `/state` topic:
   ```bash
   ros2 topic pub /state std_msgs/msg/String "data: 'kamikaze'"
   ```
4. View debug images:
   ```bash
   ros2 run rqt_image_view rqt_image_view /vision/qr_debug_image
   ```
5. View QR data:
   ```bash
   ros2 topic echo /vision/qr_data
   ```

