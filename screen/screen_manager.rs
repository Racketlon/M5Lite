pub struct ScreenManager;

impl ScreenManager {
    pub fn switch_screen(screen_name: &str) {
        println!("Switched to screen: {}", screen_name);
    }
}
