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
    //write_small_image_rs();
    //Mat img = imread("small_image.png",CV_LOAD_IMAGE_COLOR);
    int height = img.rows;
    int width = img.cols;
    cout << "(width,height) = (" << width << ", " << height << ")" << endl;

    // Remember, OpenCV grabs pixel in BGR format!
    int length = width * height;
    uint8_t* arr = new uint8_t[3 * height * width];
    int x, y;
    cout << " - Done with allocating memory" << endl;

    for (y = 0; y < height; y++){
        for (x = 0; x < width; x++) {
            int pixel_num = (width*y + x)*3;
            Vec3b bgr = img.at<Vec3b>(y,x); // NOTE: These arguments need to go (y,x)
            // Remember, OpenCV grabs pixel in BGR format!
            uint8_t b = bgr[0];
            uint8_t g = bgr[1];
            uint8_t r = bgr[2];
            //cout << "bgr pixel #" << pixel_num << " at (" << x << "," << y << ") : [" << to_string(b) << "," << to_string(g) << "," << to_string(r) << "]" << endl;
            *(arr + pixel_num) = b;
            *(arr + pixel_num + 1) = g;
            *(arr + pixel_num + 2) = r;
        }
    }

    const uint8_t *ptr;
    ptr = arr;
    get_image_vector_rs(ptr,width,height);

    delete arr; // NOTE: Always important to delete this pointer
    return 0;
}
