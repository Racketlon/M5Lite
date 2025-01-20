pub struct NotificationManager;

impl NotificationManager {
    pub fn notify(message: &str) {
        println!("Notification: {}", message);
    }
}
