#include <iostream>
#include <string>
#include <opencv2/highgui.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include "rust_arrays.h"

using namespace std;
using namespace cv;

int main() {
        /*
    //-------------------------------
    // We need to change the get_raw_pointer() function in the Rust lib to accept the right types
    // but otherwise this should all be valid
    uint32_t length = 6;

    uint8_t r = 123;
    uint8_t g = 124;
    uint8_t b = 125;

    uint8_t r2 = 223;
    uint8_t g2 = 224;
    uint8_t b2 = 225;

    Pixel px[length] = {{r,g,b},{r2,g2,b2}};

    const uint8_t *ptr;
    //ptr = px; // GOOD FOR ONE PIXEL
    ptr = px[0]; // Good for an array of pixels
    cout << "*ptr = " << to_string(*ptr) << endl;
    get_raw_pointer(ptr,length);
    */
    //------------------------------
    Mat img = imread("lionfish.jpeg" , CV_LOAD_IMAGE_COLOR);
    //Mat img;
    //cv::resize(orig_img, img, cv::Size(), 0.33, 0.33);
    uint32_t height = img.rows;
    uint32_t width = img.cols;
    //uint32_t row = 100, col = 10;
    cout << "(width,height) = (" << width << ", " << height << ")" << endl;

    // Remember, OpenCV grabs pixel in BGR format!
    //cout << "img[0][0]" << to_string(img.at<Vec3b>(0,0)[2]) << endl;
    uint32_t length = width * height;
    uint32_t* arr = new uint32_t[3 * height * width * sizeof(uint8_t) + 1];
    cout <<  sizeof(*arr) << endl;
    uint32_t x, y;
    cout << " - Done with allocating memory" << endl;


    for (y = 0; y < height; y++){
        for (x = 0; x < width; x++) {
            uint32_t pixel_num = width*y + x;
            Vec3b bgr = img.at<Vec3b>(y,x); // These arguments need to go (y,x)
            cout << "bgr pixel #" << pixel_num << " at (" << x << "," << y << ") : [" << to_string(bgr[0]) << "," << to_string(bgr[1]) << "," << to_string(bgr[2]) << "]" << endl;
            *(arr + pixel_num) = bgr[0];
            *((arr + pixel_num) + 1) = bgr[1];
            *((arr + pixel_num) + 2) = bgr[2];

        }
    }




    /*
    for (x = 0; x < width; x++){
        for (y = 0; y < height; y++) {
            uint32_t pixel_num = width*y + x;
            Vec3b bgr = img.at<Vec3b>(x,y);
            cout << "bgr pixel #" << pixel_num << " at (" << x << "," << y << ") : [" << to_string(bgr[0]) << "," << to_string(bgr[1]) << "," << to_string(bgr[2]) << "]" << endl;
            *(arr + pixel_num) = uint8_t (bgr[0]);
            *((arr + pixel_num) + 1) = uint8_t (bgr[1]);
            *((arr + pixel_num) + 2) = uint8_t (bgr[2]);
        }
    }
    */

    const uint32_t *ptr;
    ptr = arr;
    get_image_vector(ptr,width,height);
    /*
    printf("The matrix elements are:\n");
    for (i = 0; i < row; i++) {
       for (j = 0; j < col; j++) {
          printf("%d ", *(arr + i*col + j));
       }
       printf("\n");
    }
    */

    delete arr; // NOTE: Always important to delete this pointer
    return 0;
}
