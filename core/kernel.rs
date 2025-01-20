// core/kernel.rs

#![no_std]
#![no_main]

use esp32_hal::prelude::*;
use esp32_hal::timer::Timer;
use esp32_hal::Peripherals;

#[entry]
fn main() -> ! {
    let peripherals = Peripherals::take().unwrap();
    let mut timer = Timer::new(peripherals.TIMG0);

    loop {
        timer.start(1_000_000); // 1 second delay
        // Your OS logic goes here
    }
}
