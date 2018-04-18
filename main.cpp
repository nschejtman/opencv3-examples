#include <iostream>
#include "features.h"
#include "homography.h"
#include "monochromatic_imaging.h"

using namespace std;

int main(int argc, const char *argv[]) {
    // Check for correct arguments
    if (argc < 2) {
        cout << "Incorrect number of arguments" << endl;
    } else {
        string command = argv[1];
        if (command == "features") {
            features::run(argc, argv);

        } else if (command == "homography") {
            homography::run(argc, argv);
        } else if (command == "monochromatic_imaging") {
            monochromaticImaging::run(argc, argv);
        }
    }

    return 1;
}