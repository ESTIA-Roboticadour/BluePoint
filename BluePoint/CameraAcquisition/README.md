# CameraAcquisition
A C++ (with Qt, OpenCV and Pylon) application to open a laptop webcam and Basler cameras and record it.

## Required libraries
- Qt (We used Qt 6.8.2)
- OpenCV (We used OpenCV 4.11.0)
- Pylon SDK (We used Pylon 8.1.0)

## Setup
- Use `git clone https://github.com/ESTIA-Roboticadour/BluePoint` to clone this project. You need to be a contributor to modify this repo.
- Install `OpenCV` for Windows (https://opencv.org/releases/)
- Add the `bin` and `lib` folder to the PATH. (e.g.: `C:\opencv\build\x64\vc16\bin` and `C:\opencv\build\x64\vc16\lib`). Reboot your computer to apply the changes.
- Install Qt.
- Install the `Qt Visual Studio Tools` extension for Visual Studio.
- Install the `Pylon Suite Tools for Windows` from Basler (https://www.baslerweb.com/fr-fr/downloads/software/2012599532/?downloadCategory.values.label.data=pylon) that includes the software Pylon Viewer (to test your Basler camera) and the Pylon SDK.

### Setup Visual Studio
Development was carried out using Visual Studio 2022.
Check the following parameters are correct / added:

#### OpenCV

- C/C++ > General > Additional Include Directories : `C:\opencv\build\include`
- Linker > General > Additional Library Directories : `C:\opencv\build\x64\vc16\lib`
- Linker > Input > Additional Dependencies : `opencv_world4110d.lib` (for Debug) and `opencv_world4110.lib` (for Release). Adapte the version according yours.

#### Pylon

- C/C++ > General > Additional Include Directories : `C:\Program Files\Basler\pylon 8\Development\include`
- Linker > General > Additional Library Directories : `C:\Program Files\Basler\pylon 8\Development\lib\x64`
- Linker > Input > Additional Dependencies :
```
PylonBase_v10.lib
PylonC_v10.lib
GCBase_MD_VC141_v3_1_Basler_pylon_v3.lib
GenApi_MD_VC141_v3_1_Basler_pylon_v3.lib
PylonDataProcessing_v3.lib
```
