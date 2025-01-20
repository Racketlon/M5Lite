pub struct Network;

impl Network {
    pub fn connect(ssid: &str) {
        println!("Connected to network: {}", ssid);
    }

    pub fn disconnect() {
        println!("Disconnected from network.");
    }
}
