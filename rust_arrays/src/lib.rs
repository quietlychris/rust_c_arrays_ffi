// When `hello_from_rust()` is commented out, we don't have a problem; the return_a_four() function works fine
mod test;

use libc::*;
use image::{GenericImage, GenericImageView, ImageBuffer, RgbImage,Rgb};

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
pub unsafe extern "C" fn get_image_vector(ptr: *const u32,width: u32,height: u32) {
    let length: usize = (width * height) as usize;
    let val = std::slice::from_raw_parts(ptr,length);
    println!("val has a length of {}",val.len());
    println!("Vector value at (0,0): {:?}",val[0]);

    println!("Vector value at ({},{}): {:?}",width,height,val[(width*height - 1) as usize]);
    parse_image(val,width,height);
}

fn parse_image(v: &[u32],w: u32,h: u32) {
    let mut img: RgbImage = ImageBuffer::new(w,h);
    for y in 0..(h) {
        for x in 0..(w) {
            let pixel_num = w*y + x;
            if pixel_num < (w*h - 2) {
                println!("We're on pixel number: {}",pixel_num);
                let b = v[(w*y + x) as usize] as u8;
                let g =  v[((w*y + x) + 1) as usize] as u8;
                let r =  v[((w*y + x)+ 2) as usize] as u8;
                //println!("bgr #{}: [{},{},{}]",x*y,b,g,r);
                img.put_pixel(x,y,image::Rgb([r,g,b]));
            }
            else {
                img.put_pixel(x,y,image::Rgb([0,0,0]));
            }
        }
    }
    img.save("test.png").expect("Couldn't save the image");
}
