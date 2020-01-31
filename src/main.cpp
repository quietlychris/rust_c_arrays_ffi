#include <iostream>
#include <string>
#include "rust_arrays.h"

using namespace std;

int main() {

    cout << "hello, world! -- from c++ main()" << endl;
    hello_from_rust();
    int my_int = 0; // This integer starts as a zero, will change to a four
    my_int = return_a_four();
    cout << "my_int now equals: " << my_int << endl;
    cout << "                   ^ should be a '4' " << endl;

    int length = 2;
    int var[length] = {23,43};
    int *p;
    p = var;

    cout << "*p = " << *p << endl;
    cout << "(*p + 1) = " << *(p+1) << endl;
    for (int i=0;i<2;i++){
        cout << "(*p + " << i << ") = " << *(p+i) << endl;
    }

    uint8_t r = 255;
    uint8_t g = 255;
    uint8_t b = 255;
    Pixel px = {r,g,b};

    cout << "px.r:" << to_string(px[0]) << endl;

    const uint8_t *ptr;
    ptr = px;
    cout << "*ptr = " << to_string(*ptr) << endl;
    get_raw_pointer(ptr);

    return 0;
}
