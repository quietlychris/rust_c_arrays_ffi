// When `hello_from_rust()` is commented out, we don't have a problem; the return_a_four() function works fine
mod test;

use libc::*;

pub const TEN_U32: u32 = 10;

//#[derive(Debug, Clone, Copy)]
//#[repr(C)]
pub type Pixel = [u8;3];
#[repr(C)]
pub struct LargeArray {
    boxed_array: [u32; 10000],
}

/*#[no_mangle]
pub extern "C" fn CreatePixel(r: u8, g: u8, b: u8) -> Pixel {
    [r,g,b]
}*/

#[no_mangle]
pub extern "C" fn hello_from_rust() {
    println!("hello, world! -- from a Rust function!");
}

#[no_mangle]
pub extern "C" fn return_a_four() -> i32 {
    4
}

#[no_mangle]
pub unsafe extern "C" fn get_raw_pointer(ptr: *const u32,length: u32) {
    let length: usize = length as usize;
    let val = std::slice::from_raw_parts(ptr,length);
    println!("{:?}",val);
}
