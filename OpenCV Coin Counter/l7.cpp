#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;

const int cannyThreshold = 120;
const int accumulatorThreshold = 16;
int pennies, nickels, quarters, dimes, half_dollars;

void HoughDetection(const Mat& src_gray, const Mat& src_display, int cannyThreshold, int accumulatorThreshold)
{
    vector<Vec3f> circles;
    HoughCircles( src_gray, circles, HOUGH_GRADIENT, 1, src_gray.rows/55, cannyThreshold, accumulatorThreshold, 16, 46);

    Mat display = src_display.clone();
    for( size_t i = 0; i < circles.size(); i++ )
    {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        //coins1
//            if(radius < 25){
//                pennies++;
//            }
//            else if(radius < 28){
//                nickels++;
//            }
//            else{
//                quarters++;
//            }

        //coins2
//        if(radius < 23){
//            pennies++;
//        }
//        else if(radius < 26){
//            nickels++;
//        }
//        else{
//            quarters++;
//        }

        //coins3
        if(radius < 20){
            dimes++;
        }
        else if(radius < 24){
            pennies++;
        }
        else if(radius < 28){
            nickels++;
        }
        else if(radius < 39){
            quarters++;
        }
        else{
            half_dollars++;
        }

        circle( display, center, 3, Scalar(0,255,0), -1, 8, 0 );
        circle( display, center, radius, Scalar(0,0,255), 3, 8, 0 );
    }
    imwrite("imagec.jpg", display);
}


int main(int argc, char** argv)
{
    Mat src, src_gray;

    String imageName("coins1.jpg");
    src = imread( samples::findFile( imageName ), IMREAD_COLOR );

    cvtColor( src, src_gray, COLOR_BGR2GRAY );

    GaussianBlur( src_gray, src_gray, Size(9, 9), 2, 2 );

    HoughDetection(src_gray, src, cannyThreshold, accumulatorThreshold);
    double total = pennies * .01 + nickels * .05 + dimes * .1 + quarters * .25 + half_dollars * .5;
    cout<<"There are "<< pennies << " pennies, " << nickels << " nickels, " << dimes << " dimes, " << quarters <<" quarters, and " << half_dollars <<" half dollars for a total of $" << total;
    ofstream myFile;
    myFile.open("results.txt");
    myFile << "There are "<< pennies << " pennies, " << nickels << " nickels, " << dimes << " dimes, " << quarters <<" quarters, and " << half_dollars <<" half dollars for a total of $" << total;
    myFile.close();
    return 0;
}