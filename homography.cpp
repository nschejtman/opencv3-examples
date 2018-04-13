#include "homography.h"
#include <opencv2/opencv.hpp>

using namespace cv;

int homography::run(int argc, const char **argv) {

    // Check correct number of arguments
    if (argc < 5) {
        std::cout << "Incorrect number of arguments" << std::endl;
        std::cout << "Usage: ./opencv homography [feature detector] [path/to/image1] [path/to/image2]" << std::endl;
        return -1;
    }

    // Read arguments
    std::string detectorName = argv[2], img1Path = argv[3], img2Path = argv[4];


    Mat img1 = imread(img1Path), img2 = imread(img2Path);                           // Read input images
    imshow("Image 1", img1);
    imshow("Image 2", img2);
    waitKey(0);                   // display images

    std::vector<KeyPoint> keypoints1, keypoints2;
    Mat descImg1, descImg2, matchesImg, disp;

    Ptr<Feature2D> detector = BRISK::create();                                      // create the feature detector
    detector->detectAndCompute(img1, {}, keypoints1,
                               descImg1);                     // detect and compute feature descriptors for img1
    detector->detectAndCompute(img2, {}, keypoints2,
                               descImg2);                     // detect and compute feature descriptors for img2

    auto matcher = DescriptorMatcher::create("BruteForce");                         // create the descriptor matcher

    std::vector<DMatch> matches;
    matcher->match(descImg1, descImg2, matches);

    auto topCount = int(0.1 * matches.size());                                         // top 10% of matches
    std::sort(matches.begin(), matches.end(), [](auto &lhs, auto &rhs) { return lhs.distance < rhs.distance; });

    matches.resize(topCount);

    // Display feature matches
    drawMatches(img1, keypoints1, img2, keypoints2, matches, matchesImg);
    imshow("Top matches", matchesImg);

    // Select top match keypoints
    std::vector<Point2f> matchedKP1(topCount), matchedKP2(topCount);
    std::transform(matches.begin(), matches.end(), matchedKP1.begin(),
                   [&](auto &match) { return keypoints1[match.queryIdx].pt; });
    std::transform(matches.begin(), matches.end(), matchedKP2.begin(),
                   [&](auto &match) { return keypoints2[match.trainIdx].pt; });

    Mat H = findHomography(matchedKP1, matchedKP2, RANSAC);
    auto w = float(img1.cols), h = float(img1.rows);
    std::vector<Point2f> corners = {{0, 0},
                                    {w, 0},
                                    {w, h},
                                    {0, h}};
    perspectiveTransform(corners, corners, H);
    std::vector<std::vector<Point>> quad = {{corners[0], corners[1], corners[2], corners[3]}};
    polylines(img2, quad, true, Scalar(0, 255, 0), 4, CV_AA);
    imshow("Image 2", img2);
    waitKey(0);
    return 1;
}