// When `hello_from_rust()` is commented out, we don't have a problem; the return_a_four() function works fine
mod test;
use image::{ImageBuffer, RgbImage,Rgb};

#[no_mangle]
pub unsafe extern "C" fn get_image_vector_rs(ptr: *const u8,width: u32,height: u32) {
    let length: usize = (width * height * 3) as usize; // This is 3 since it's an RGB pixel
    let v = std::slice::from_raw_parts(ptr,length);

    println!("Imported image vector has a length of {}",v.len());

    parse_image(v,width,height);
}

fn parse_image(v: &[u8],w: u32,h: u32) {
    let mut img: RgbImage = ImageBuffer::new(w,h);
    println!("The length of the read-in slice is: {}",v.len());
    for y in 0..h {
        for x in 0..w {
            let pixel_num = ((w*y + x) * 3) as usize;
            if pixel_num < ((w*h*3) as usize - 2) {
                let b = v[pixel_num] as u8;
                let g =  v[pixel_num + 1] as u8;
                let r =  v[pixel_num + 2] as u8;
                //println!("bgr #{} at ({},{}): [{},{},{}]",pixel_num,x,y,b,g,r);
                img.put_pixel(x,y,Rgb([r,g,b]));
            }
            else {
                img.put_pixel(x,y,Rgb([0,0,0]));
            }
        }
    }
    img.save("rebuilt.png").expect("Couldn't save the image");
}

#[no_mangle]
pub extern "C" fn write_small_image_rs() {
    let mut img: RgbImage = ImageBuffer::new(10,5);
    let (w,h) = img.dimensions();
    for y in 0..h {
        for x in 0..w {
            let position_u8: u8 = (w*y + x) as u8;
            img.put_pixel(x,y,Rgb([position_u8,position_u8,position_u8]));
        }
    }
    img.save("small_image.png").expect("Couldn't save the small image");
}
