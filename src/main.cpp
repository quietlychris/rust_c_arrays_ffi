#include <iostream>
#include <string>
#include "rust_arrays.h"

using namespace std;

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

    uint32_t row = 2, col = 3;
    uint32_t length = row*col;
    uint32_t *arr = (uint32_t *)malloc(row * col * sizeof(uint8_t));
    uint32_t i, j;
    for (i = 0; i < row; i++)
       for (j = 0; j < col; j++)
          *(arr + i*col + j) = i + j;

    const uint32_t *ptr;
    ptr = arr;
    get_raw_pointer(ptr,row*col);

    printf("The matrix elements are:\n");
    for (i = 0; i < row; i++) {
       for (j = 0; j < col; j++) {
          printf("%d ", *(arr + i*col + j));
       }
       printf("\n");
    }
    free(arr);
    
    return 0;
}
