#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>
#include <iostream>
#include "features.h"

using namespace cv;

int features::run(int argc, const char **argv) {
    if (argc < 3) {
        std::cout << "Incorrect number of arguments" << std::endl;
        std::cout << "Usage: ./opencv features [path/to/image] [desired feature detector]" << std::endl;
        return -1;
    }

    const char * imagePath = argv[2];
    const char * detectorName = argv[3];

    std::cout << "Using " << detectorName << " feature detector" << std::endl;

    Mat img = imread(imagePath);

    // Feature detection
    Ptr<Feature2D> detector = AKAZE::create();
    std::vector<KeyPoint> keypoints;
    detector->detect(img, keypoints);

    // Display the results
    Mat displayImg;
    drawKeypoints(img, keypoints, displayImg);

    imshow("AKAZE features", displayImg);
    waitKey();

}
