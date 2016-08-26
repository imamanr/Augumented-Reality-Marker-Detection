//============================================================================
// Name        : vision-ar.cpp
// Author      : ...
// Date        : Feb 2016
// Description : Augmented Reality in OpenCV
//============================================================================

#include "testAR.hpp"

#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

using namespace cv;
using namespace std;
using namespace CppUnit;



int main(int argc, const char * argv[]) { // this program takes two arguments -v absolute path to video file -c absolute path to camera parameter xml
    cout << "Hello Augmented Reality" << endl;
    string videopath;
    String pathCamParam;
    for (int i = 1; i < argc; i+=2) {
        if(i+1 != argc) {
            std::string tmp = argv[i];
            if(tmp=="-v") {
                videopath = argv[i+1];
            }
            else if(tmp == "-c") {
                pathCamParam = argv[i+1];
            }
            else {
                cout << "Not enough or invalid arguments, please try again.\n";
                return -1;
            }
        }
    }
    
    VideoCapture cap(videopath); // open the default camera
    if (!cap.isOpened()) { // check if we succeeded
        cerr << "Unable to open video file" << endl;
        return -1;
        }
    
    AugmentedReality ar;
    ar.readFromFileCP(pathCamParam); // read camera parameter file
    cout << "Process video" << endl;

    ar.processVideo(cap); // process video and detect and draw cube
    cout << "Goodbye!" << endl;
    
    // Update video and cam parameter file paths in testAR.hpp
    
    CppUnit::TextUi::TestRunner runner;
    
    cout << "Creating Test Suites:" << endl;
    runner.addTest(TestAR::suite());
    
    cout<< "Running the unit tests."<<endl;
    runner.run();
    
    return 0;
}
