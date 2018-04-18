# opencv3-examples
This project code is based on Adi Shavit's and Neha Gajakos' tutorial "[OpenCV: Computer Vision with OpenCV 3](https://www.safaribooksonline.com/learning-paths/learning-path-opencv/9781788628419/)"

## How to compile
**Note:** CMake and make are required for compiling
```
git clone https://github.com/nschejtman/opencv3-examples.git
cd opencv3-examples
cmake CMakeLists.txt
make
```

## How to run
`./opencv_examples command arguments*`

Each command corresponds with a different .cpp file. For further details read these files individually.

**Feature extraction**

`./opencv_examples features [path/to/image] [desired feature detector]`

**Homography calculator**

`./opencv_examples homography [feature detector] [path/to/image1] [path/to/image2]`

**Monochromatic Imaging**

`./opencv_examples monochromatic_imaging [path/to/image]*`

*Note: selecting the desired feature detector form the command arguments is currently under development!*
