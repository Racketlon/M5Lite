// lib/Bluetooth/Bluetooth.rs

use esp32_hal::bluetooth::{Bluetooth, BluetoothConfig};

pub fn init_bluetooth() -> Bluetooth {
    let config = BluetoothConfig::default();
    Bluetooth::init(config).unwrap()
}
