# CameraAcquisition

A C++ application using Qt, OpenCV, and the Pylon SDK to capture and record video streams from:
- Laptop webcams
- Basler industrial cameras

## Overview

This application provides an interface to:
- Select a camera (USB or Basler)
- Visualize the live stream
- Record the video

---

## Requirements

This project uses the same dependencies as the main BluePoint repository:

- **Qt 6.8.2**
- **OpenCV 4.11.0**
- **Pylon SDK 8.1.0**

You can find installation instructions and environment configuration in the [root README](../README.md).

---

## Visual Studio Setup

Ensure the following settings in your Visual Studio project:

1. `C/C++ > General > Additional Include Directories`
- For OpenCV:
```
C:\opencv\build\include
```
- For Pylon:
```
C:\Program Files\Basler\pylon 8\Development\include
```

2. `Linker > General > Additional Library Directories`
- For OpenCV:
```
C:\opencv\build\x64\vc16\lib
```
- For Pylon:
```
C:\Program Files\Basler\pylon 8\Development\lib\x64
```

3. `Linker > Input > Additional Dependencies`

- For OpenCV:
  - For **Debug**:
```
opencv_world4110d.lib
```
  - For **Release**:
```
opencv_world4110.lib
```
- For Pylon:
```
PylonBase_v10.lib
PylonC_v10.lib
GCBase_MD_VC141_v3_1_Basler_pylon_v3.lib
GenApi_MD_VC141_v3_1_Basler_pylon_v3.lib
```

Adapt with the libs you have, depending on your installed version.

---

## Notes

- If you face issues with `.lib` files or unresolved symbols, double-check the library versions and adjust accordingly.
