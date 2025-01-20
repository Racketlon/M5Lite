// lib/System/System.rs

use esp32_hal::system::{SystemControl, Reset};

pub fn reset_device() {
    let sys_ctrl = SystemControl::take().unwrap();
    sys_ctrl.reset_device(Reset::SystemReset);
}
