#include "monochromatic_imaging.h"
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace cv;

int monochromaticImaging::run(int argc, const char **argv) {
    // Check correct number of arguments
    if (argc < 3) {
        std::cout << "Incorrect number of arguments" << std::endl;
        std::cout << "Usage: ./opencv monochromatic_imaging [path/to/image]*" << std::endl;
        return -1;
    }

    std::vector<std::string> vectorizedArguments(argv + 1, argv + argc);
    for (const auto &imageName : vectorizedArguments) {
        Mat img = imread(imageName);
        if (img.empty()) continue; // Skip invalid images

        imshow("Color", img);

        // Display each channel independently
        Mat channels[3], all;
        split(img, channels);
        hconcat(channels, 3, all);
        imshow("B :: G :: R", all);
        waitKey();

        // Apply the different gray scale converting algorithms
        Mat gray, luv, lightness, decolored, unused, hsv, desaturated3C;
        cvtColor(img, gray, CV_BGR2GRAY);   // convert img to gray scale
        decolor(img, decolored, unused);    // apply the decolor algorithm to img

        cvtColor(img, luv, CV_BGR2Luv);     // convert img to LUV color space
        extractChannel(luv, lightness, 0);  // take the L channel from Luv image

        hconcat(std::vector<Mat>({gray, lightness, decolored}), all);
        imshow("Grayscale :: LUV lightness :: Decolored", all);

        cvtColor(img, hsv, CV_BGR2HSV);                                 // convert img to HSV
        cvtColor(hsv & Vec3b(255, 0, 255), desaturated3C, CV_HSV2BGR);  // zero out saturation channel
        imshow("Desaturated BGR", desaturated3C);
        waitKey();
        destroyAllWindows();

        return 0;
    }




    // Read arguments
    std::string detectorName = argv[2], img1Path = argv[3], img2Path = argv[4];
}
