// kernel.rs
pub struct Kernel;

impl Kernel {
    pub fn init() {
        println!("Kernel initialized.");
    }

    pub fn boot() { println!("Booting M5Lite"); }
}
