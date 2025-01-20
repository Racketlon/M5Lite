// lib/Network/Network.rs

use esp32_hal::wifi::{Wifi, WifiConfig};

pub fn init_wifi() {
    let config = WifiConfig::default();
    let wifi = Wifi::new(config).unwrap();
    wifi.connect().unwrap();
}
