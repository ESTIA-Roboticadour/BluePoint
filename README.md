# 🌊 BluePoint

**BluePoint ToolKit** is a C++ solution developed with Visual Studio, Qt 6, OpenCV, and the Pylon SDK.  
It contains all the components and tools for the BluePoint project, including Qt Designer plugins, libraries, and applications.

## 📦 Projects

Some projects are shared libraries and Qt Designer plugins. They **must be compiled first** using Qt Creator.  
They provide reusable widgets and logic that are dynamically loaded by other applications.

### 🔧 Qt Creator Projects (Plugins & Libraries)

- `FrameViewer`: Widget to display a still image / video frame as large as possible on a user-defined background colour while always preserving the original aspect-ratio.
- `LayeredWidget`: Composite container that stacks a *background* widget, an optional colour-filter overlay and a *foreground* widget. The background opacity and filter (colour + alpha) can be changed at run-time or in Qt Designer.
- `LogoWidget`: Convenience widget that loads a pixmap from a file or Qt resource, keeps the original copy, and shows a scaled version inside a centred `QLabel`. Size and image path are exposed as Designer properties.
- `LogTool`: Tiny logging library made of `LogDispatcher` (Qt global message handler), `LogModel` (table model) and `LogWidget` (viewer). It captures every ``qDebug/qInfo/...`` message, streams them to a file if requested, and displays them live in a colour-coded table.
- `NavigationWidgets`: A set of widgets (branch / breadcrumb / tree classes) used to navigate through a hierarchical `NavigationTree` of nodes.
- `ParametersCustomWidgets`: Factory that builds, at run-time, the appropriate Qt editor (spin box, checkbox, line edit, combo, colour picker…) for each parameter type: integers, floats, booleans, strings, enums, etc.
- `TogglePanel`: Slide-in/slide-out side panel with a hamburger button. Useful for toolboxes or mobile-style menus.
- `TransparentScrollArea`: A scrollable widget with a semi-transparent background, ideal for overlay panels and modern glass-effect UIs.
- `XAppLayout`: Legacy one-stop “application shell” that assembles `NavigationWidgets`, `TogglePanel`, `LayeredWidget`, `LogoWidget` and `LogTool` into a ready-to-use main-window layout (navbar + sidebar + background + log pane). Superseded by **AppLayout** but kept for backward compatibility. Requires the five plugins to be compiled first.
- `XNavigationLayout`: Original layout widget that wires `NavigationWidgets` with a `TogglePanel` to build multi-page UIs. Requires the two plugins to be compiled first.

👉 **Required to be compiled**, as they provide headers `.h`, `.lib` and `.dll` files used by other projects.

A helper script is provided to **prepare and install these libraries** correctly (see `🧰 Setup Instructions > 🏗️ Building Projects` section).

### 🖥️ Visual Studio Projects

These are the main applications of the BluePoint project:

- `CameraHeight` — Estimates the height of a camera.
- `CameraAcquisition` — Opens and records video streams from a laptop webcam or Basler camera.
- `LightControl` — Tool to identify the COM Port and relay used to control the light.
- `Vision` — Handles the computer vision logic for the BluePoint robotic system.

---

## ⚙️ General Setup

All projects rely on the following libraries. Make sure they are correctly installed and configured.

### ✅ Requirements

- **Qt** – [We use Qt 6.8.2](https://www.qt.io/download-dev)
- **OpenCV** – [We use OpenCV 4.11.0](https://opencv.org/releases/)
- **Pylon SDK** – [We use Pylon 8.1.0](https://www.baslerweb.com/en/downloads/software/?downloadCategory.values.label.data=pylon)

### 🧰 Setup Instructions

1. **Clone the repository**:
```bash
git clone https://github.com/ESTIA-Roboticadour/BluePoint
```

2. Install `OpenCV`:
- Download from: https://opencv.org/releases/
- Extract and set system PATH to include:
```
C:\opencv\build\x64\vc16\bin
C:\opencv\build\x64\vc16\lib
```
- Restart your computer if needed.

3. Install `Qt`
- Download `Qt 6.8.2` from: https://www.qt.io/download-dev.
- Install `Qt Visual Studio Tools` (from the Visual Studio extension manager).
- Set the appropriate Qt Kit in Qt Creator to compile Qt-based libraries.

4. Install `Balser Pylon SDK`
- Download and install from: https://www.baslerweb.com/en/downloads/software/?downloadCategory.values.label.data=pylon
- This includes `Pylon Viewer` and the `SDK`.
- Make sure the `pylon` `bin` and `lib` folders are in your `PATH`.
- Restart your computer if needed.
- We recommend you to test your camera with `Pylon Viewer`. Make sure you have plugged your camera into a **USB 3 port**. 

---

## 🏗️ Building Projects

To build the project, you first need to setup all plugins and shared librairies. To do that, there is 2 ways.
1) Use the `installer.ps1` script to do everything automatically.
2) Do it manually.

After the setup done, the project structure would be as bellow:

```
BluePoint/
├── Plugins/                          # Qt Designer plugins and shared libraries
│   ├── ParametersWidgets/
│   ├── other plugins to compile ...
│   ...
├── CameraAcquisition/                # Visual Studio app: capture and record video
├── Vision/                           # Visual Studio app: computer vision logic
├── other projects...
├── Libraries/                        # Auto-generated by setup script
│   ├── ParametersWidgets/
│   │   ├── include/                  # Headers copied from shared libs
│   │   ├── lib/                      # .lib files for linking
│   │   └── bin/                      # .dll files for runtime
│   ├── other librairies...
|   ...
├── x64/                              # Auto-generated by setup script (and by Visual Studio)
│   ├── Debug/
│   │   ├── ParametersWidgetsd.dll
│   │   ├── other debug dll...
│   ├── Release/
│   │   ├── ParametersWidgets.dll
│   │   ├── other release dll...
├── scripts/                          # Scripts folder
│   │   ├── installer.ps1             # Script to setup shared libs
├── installer-?.ps1.lnk               # Links to use to execute the script: scripts/installer.sh with specified options
└── README.md                         # This file
```

### 🪄 installer.ps1

#### ⚙️ Configuration

Open the script `scripts/installer.ps1` in a text editor, then edit / check the configurations paths (in the editable section).

Default values are:
```bash
$QMAKE_EXE = "C:\Qt\6.8.2\msvc2022_64\bin\qmake.exe"
$MAKE_EXE = "C:\Qt\Tools\QtCreator\bin\jom\jom.exe"
$QT_DESIGNER_PLUGIN_DIR = "C:\Qt\Tools\QtCreator\bin\plugins\designer\"
```

You still have to select a `qmake.exe` from an `msvc` compiler.

#### ▶️ Run

Run the script `installer-plugins.ps1.lnk` (the link).
```bash
./installer-plugins.ps1.lnk
```

This script will:
- **Compile** all plugin projects (from `Plugins` folder) in `debug` and `release`.
- **Install** the plugins for Qt Designer.
- **Create** the `Librairies` folder for shared librairies. It will also create folders for each plugin, and `bin`, `lib` and `include` subfolders for each of them. These subfolders will be feed with `.h`, `.lib` and `.dll` files.
- **Create** the `x64\Debug` and `x64\Release` folders and copy `debug` and `release` `dll` files.

Then you can open the `.sln` solution and compile project you want. See `🧱 Build Visual Studio Applications` section.

### 🔌 Manual install
For each polugin project contained in `Plugin` folder, you have to:
- Compile them in Qt Creator.
- Copy `.h`, `.lib` and `.dll` files to right destinations.

For all projects in `Plugins` folder:
1. Open a project in folder in **Qt Creator**.
2. Create the config. You need to select `msvc2022_64` compilator. Then check the compiler steps. By default you have **2 steps** for both configuration `debug` and `release`. You need to add an additional step for `release`: add a `Make` step, with `install` as argument.
3. Compile the project in `Debug` then in `Release` to generate debug and release `.lib` and `.dll` files.
4. Copy `.dll` (release only) to you designer plugin folder (e.g.: `C:\Qt\Tools\QtCreator\bin\plugins\designer`).
5. Create folder `Librairies` and project subfolder, and `include`, `lib` and `bin` folders → **Create the structure showed above**.
6. Copy `debug` and `release` `.lib` generated files and past into `lib` folder.
7. Copy `debug` and `release` `.dll` generated files and past into `bin` folder. Copy them into `x64/Debug` and `x64/Release` folders as well.
8. Copy `.h` files into `include`. You don't have to copy header file that ends with `Plugin.h`. 

### 🧱 Build Visual Studio Applications

1. Open the `.sln` file in **Visual Studio**.
2. Make sure the `Libraries/` folder is properly filled (see).
3. For each project, check the following in **Configuration Properties**:
   - `C/C++ > General > Additional Include Directories` (should be okay)
   - `Linker > General > Additional Library Directories` (should be okay)
   - `Linker > Input > Additional Dependencies`  
     ⚠️ Make sure to use the correct `.lib` files depending on your versions of extern libraires (OpenCV, Pylon, etc.) for both configuration (**Debug** or **Release**).
     E.g.: With `OpenCV 4.11.0`, used lib is `opencv_world4110d.lib` for `Debug` and `opencv_world4110.lib` for `Release`. It could change if you use another version.
4. Build and run the application.

### 🚀 Qt Deployment

Once you have compiled the Visual Studio projects you want (**especially Release compilation**, Debug compilation is not necessarily mandatory), you can run the script `installer-qtdeploy.ps1.lnk` to easily deploy the Qt libraries and have an application ready to deploy.

#### 📌 Notes

- See each project's `README.md` for specific usage and build instructions.

## ❓ FAQ
**Q: I get missing .lib or .dll errors when building in Visual Studio.**
A: If the missing file is related to our librairies, run `installer-plugins.ps1.lnk`. If not, check the configuration of your project (include directories, lib directories, input lib).

**Q: My Basler camera is not readable.**
A: Ensure you plugged it on the **USB 3 port**. You can also install `Pylon Viewer` (if it's not already done) to test your camera.

**Q: How do I debug Qt UIs in Visual Studio?**
A: Use `Qt Visual Studio Tools` to integrate Qt Designer, or test the UI in Qt Creator first.
