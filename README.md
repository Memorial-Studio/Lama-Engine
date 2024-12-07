<p align="center">
 <h1 align="center">Lama-Engine</h2>
</p>
  <p align="center">
    <img alt="Project Status: Active – The project is under active delopment!." src="https://www.repostatus.org/badges/latest/active.svg" />
    <img alt="CodeFactor." https://www.codefactor.io/repository/github/memorial-studio/lama-engine/badge/dev>
    <img alt="GitHub Contributors." src="https://img.shields.io/github/contributors/Memorial-Studio/Lama-Engine" />
    <img alt="Issues." src="https://img.shields.io/github/issues/Memorial-Studio/Lama-Engine?color=0088ff" />
    <img alt="Commit Activity." src="https://img.shields.io/github/commit-activity/m/Memorial-Studio/Lama-Engine/dev" />
  </p>

Lama Engine is an ongoing game engine developed in C++. 


## Supported compilers
- [x] MSVC (Stable)
- [ ] MinGW
- [ ] Cygwin
- [ ] Clang
- [ ] GCC

## Supported platforms
- [x] Windows 10
- [ ] Linux X11
- [ ] Linux Wayland
- [ ] Android

## Branches 
 * master - branch for releases
 * dev - active development branch 
 * features/* - branches for new features
 * tmp/* - temporary branches for dangerous experiments

## Building  
 > [!IMPORTANT]
 > ```Requirements:```
 > - 0.1. Visual Studio 2019 or newer
 > - 0.2. Install CMake 3.16.0 or newer
 1. ```Clone repository via the command "git clone https://github.com/Memorial-Studio/Lama-Engine.git"```
 2. ```Switch to the "dev" (or another one) branch via the command "git checkout branch_name"```
 3. ```Run command "git submodule update --init --recursive" in repository folder```
 <details>
 <summary> 4. Working with CMake (if you're using Visual Studio): </summary>
  
    - 4.1 Open CMake GUI
  
    - 4.2 Choose the path to the Lama-Engine folder (where the source code is located).
  
    - 4.3 Choose the path where to build the binaries (Lama-Engine/build)-> You need create build folder.
     
    - 4.4 Press "Configure" and choose your VS version.
    
    - 4.5 Press "Generate"

    - 4.6 Open Visual Studio solution

    - 4.7 Set as startap project SREngine 

    - 4.8 Run build 
    
 </details>
 <summary> 4. Working with CMake on Git Bash (if you're using Visual Studio): </summary>
  
    - 4.1 Open Git Bash & choose the path to the Lama-Engine folder (where the source code is located)
  
    - 4.2 Using the mkdir build command for create build folder(Lama-Engine/build) .
     
    - 4.3 Move to the folder build -> cd build
    
    - 4.4 Run CMakeLists.txt with use cmake .. command.

    - 4.5 Open sln project.  

 </details>
 

## Used libraries
  * [GLAD](https://glad.dav1d.de/)
  * [GLFW](https://github.com/glfw/glfw)
  * [spdlog](https://github.com/gabime/spdlog?ysclid=m4dvxczflx129454677)
  * [glm](https://github.com/g-truc/glm)
  
  
  ## Features
  * Main window ^_^
