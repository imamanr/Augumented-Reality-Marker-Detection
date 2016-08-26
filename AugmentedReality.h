//
//  AugmentedReality.h
//  AugumentedReality
//
//  Created by Imama Noor on 8/25/16.
//  Copyright © 2016 Imama. All rights reserved.
//

#ifndef AugmentedReality_h
#define AugmentedReality_h


#endif /* AugmentedReality_h */

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/calib3d.hpp>
#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>


using namespace cv;
using namespace std;

struct pose {
public:
    Mat rotationMatrix = Mat::zeros(3,3,CV_32FC1);
    Mat rvec = Mat::zeros(1,3,CV_32FC1);
    Mat tvec = Mat::zeros(1,3,CV_32FC1);
    
};

class AugmentedReality {
public:
    AugmentedReality();
    ~AugmentedReality();
    int processVideo(VideoCapture& vc);
    int readFromFileCP(string path)throw(cv::Exception);
    void _getSingleMarkerObjectPoints(float markerLength,vector<Vec3d> & _objPoints);
    int writePose(ofstream &myfile, pose &poseMat, int markerNum);
    void _get3DMarkerObjectPoints(float markerLength,vector<Vec3d> & _objPoints);
    void draw(Mat & image, vector<Point2d> & projectedPoints);
    Size CamSize;
private:
    Mat  CameraMatrix = Mat::eye(3,3,CV_32F);
    const Mat distCoeffs = Mat::zeros(1,8,CV_32F);
    vector<Vec3d> markerObjPoints;
    vector<Vec3d> markerCubePoints;
    
};



AugmentedReality::AugmentedReality() {
    
}
AugmentedReality::~AugmentedReality() {
    
}
void AugmentedReality::draw(Mat & image, vector<Point2d> & projectedPoints){
    
    for(int i=0; i<4;i++) {
        if(i<=2) line(image, projectedPoints[i],projectedPoints[i+1],Scalar( 255, 255, 0 ),1,4);
        if (i>2) line(image, projectedPoints[i],projectedPoints[0],Scalar( 255, 255, 0 ),1,4);}
    
    for(int i=0,j=4; i<4;i++,j++) {
        line(image, projectedPoints[i],projectedPoints[j],Scalar( 0, 0, 255 ),1,4);}
    
    for(int i=4; i<8;i++) {
        if(i<=6) line(image, projectedPoints[i],projectedPoints[i+1],Scalar( 0, 255, 0 ),1,4);
        if(i>6) line(image, projectedPoints[i],projectedPoints[4],Scalar( 0, 255, 0 ),1,4);}
    
    
}

void AugmentedReality::_getSingleMarkerObjectPoints(float markerLength, vector<Vec3d> &_objPoints) {
    
    CV_Assert(markerLength > 0);
    
    // set coordinate system in the middle of the marker, with Z pointing out
    _objPoints.push_back(Vec3f(-markerLength / 2.f, markerLength/ 2.f, 0)); // (-3,3,0)
    _objPoints.push_back(Vec3f(markerLength / 2.f, markerLength/ 2.f , 0)); // (3,3,0)
    _objPoints.push_back(Vec3f(markerLength / 2.f, -markerLength/ 2.f, 0));// (3,-3,0)
    _objPoints.push_back(Vec3f(-markerLength / 2.f, -markerLength/ 2.f , 0));//(-3,-3,0)
    
    
}


void AugmentedReality::_get3DMarkerObjectPoints(float markerLength, vector<Vec3d> &_objPoints) {
    
    CV_Assert(markerLength > 0);
    
    // set coordinate system in the middle of the marker, with Z pointing out
    _objPoints.push_back(Vec3f(-markerLength / 2.f , -markerLength / 2.f , 0)); // (0,0,0)
    _objPoints.push_back(Vec3f(markerLength / 2.f , -markerLength / 2.f , 0));// (3,-3,0)
    _objPoints.push_back(Vec3f(markerLength / 2.f , markerLength / 2.f , 0)); // (3,3,0)
    _objPoints.push_back(Vec3f(-markerLength / 2.f , markerLength / 2.f , 0));//(-3,-3,0)
    
    _objPoints.push_back(Vec3f(-markerLength / 2.f , -markerLength / 2.f, -markerLength / 2.f)); // (-3,3,0)
    _objPoints.push_back(Vec3f(markerLength / 2.f, -markerLength / 2.f , - markerLength / 2.f )); // (3,3,0)
    _objPoints.push_back(Vec3f(markerLength / 2.f , markerLength / 2.f, -markerLength / 2.f ));// (3,-3,0)
    _objPoints.push_back(Vec3f(-markerLength / 2.f , markerLength / 2.f, -markerLength / 2.f ));//(-3,-3,0)
    
    
}

int AugmentedReality::readFromFileCP(string path)throw(cv::Exception){
    cv::FileStorage fs(path, cv::FileStorage::READ);
    int w=-1,h=-1;
    cv::Mat MCamera;
    
    fs["image_width"] >> w;
    fs["image_height"] >> h;
    fs["camera_matrix"] >> MCamera;
    
    if (MCamera.cols==0 || MCamera.rows==0)throw cv::Exception(9007,"File :"+path+" does not contains valid camera matrix","CameraParameters::readFromXML",__FILE__,__LINE__);
    if (w==-1 || h==0)throw cv::Exception(9007,"File :"+path+" does not contains valid camera dimensions","CameraParameters::readFromXML",__FILE__,__LINE__);
    
    if (MCamera.type()!=CV_32FC1) {
        CameraMatrix = MCamera.clone();}
    else CameraMatrix = MCamera;
    
    CamSize.width=w;
    CamSize.height=h;
    return 0;
}

int AugmentedReality::writePose(ofstream &myfile, pose &poseMat, int markerNum) {
    myfile << "translation for 6dof" << markerNum/4 << "marker\n";
    myfile << poseMat.rvec.at<double>(0,0) << " " << poseMat.rvec.at<double>(1,0) << " " << poseMat.rvec.at<double>(2,0)<<"\n";
    myfile << "rotation vector for 6dof"<< markerNum/4 << "marker\n";
    myfile << poseMat.tvec.at<double>(0,0) << " " << poseMat.tvec.at<double>(1,0) << " " << poseMat.tvec.at<double>(2,0)<<"\n";
    return 0;
}
int AugmentedReality::processVideo(VideoCapture& vc) {
    int count = 0;
    ofstream myfile;
    myfile.open ("6DOF_PoseEstimation.txt"); // create a file for translation and rotation values for each frame
    if(!myfile.is_open()) { cout<< "!!! Output text file could not be opened" << std::endl;
        return -1;}
    
    VideoWriter outputVideo;                 // create a video object for writing frames with cube
    int ex = static_cast<int>(vc.get(CV_CAP_PROP_FOURCC));
    Size S = Size((int) vc.get(CV_CAP_PROP_FRAME_WIDTH),    //Acquire input size
                  (int) vc.get(CV_CAP_PROP_FRAME_HEIGHT));
    outputVideo.open("output.avi" , ex, vc.get(CV_CAP_PROP_FPS),S, true);
    if (!outputVideo.isOpened()) {  // check is object is created successfully
        cout << "!!! Output video could not be opened" << std::endl;
        return -1;}

    float markerLength = 700;
    this->_getSingleMarkerObjectPoints(markerLength,markerObjPoints);//get 2d rectangle points
    this->_get3DMarkerObjectPoints(markerLength,markerCubePoints);//get 3d-cube points
    
    for(;;) { // loop over video
        
        myfile << "frame num: " << count+1 << "\n";
        
        Mat frame;
        vc >> frame; // get a new frame
        if (frame.empty()) {
            cerr << "Unable to read frame or end  of file" << endl;
            break;
        }
        vector<Vec4i> hierarchy; // define variables for detecting rectangles in the frame
        vector<vector<Point2i> > contours;
        Mat gray;
        cvtColor(frame, gray, CV_BGR2GRAY); // convert to grayscale
        threshold(gray, gray, 95, 255, THRESH_BINARY); // binarize the image using threshold 95
        bitwise_not(gray, gray);
        vector<Point2d> MarkerContour; // object to hold contour points of rectangles
        findContours(gray, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
        for(size_t i=0; i<contours.size(); i++)
        {
            Rect rect = boundingRect(contours[i]);
            vector<Point> approxCurve;
            approxPolyDP(contours[i],approxCurve,arcLength(Mat(contours[i]), true) * 0.01, true); //estimate the shape of contour
            double k = (rect.height+0.0)/rect.width;
            if(0.7<k && k<1.5 && rect.area()>100 && approxCurve.size()>3 && approxCurve.size() < 5)
                // checks if the contour is a rectangle of significant size
            {
                drawContours(frame, contours, i, Scalar(0,0,255));
                MarkerContour.push_back(approxCurve[0]);
                MarkerContour.push_back(approxCurve[1]);
                MarkerContour.push_back(approxCurve[2]);
                MarkerContour.push_back(approxCurve[3]);
            }
        }
        // define varibales to find pose of camera w.r.t the marker and draw cube on frame
        
        for(int l=0;l<MarkerContour.size();l+=4) { // loop over each marker, estimate pose and draw cube and store pose info
            
            pose poseMat;
            vector<Point2d> projectedPoints;
            vector<Point2d> subMarkerCont(&MarkerContour[l],&MarkerContour[l+4]);
            solvePnP(markerObjPoints, subMarkerCont, CameraMatrix, distCoeffs,poseMat.rvec, poseMat.tvec);//get pose info
            Rodrigues(poseMat.rvec,poseMat.rotationMatrix);
            projectPoints(markerCubePoints, poseMat.rvec, poseMat.tvec, CameraMatrix, distCoeffs, projectedPoints);
            this->draw(frame, projectedPoints);
            writePose(myfile, poseMat, l);
        }
        count += 1;
        imshow("result", frame);
        outputVideo << frame;
        if (waitKey(1) == 27) {
            break;
        }
        
    }
    myfile.close();
    vc.release();
    outputVideo.release();
    return 0;
}