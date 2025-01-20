mod kernel;

use kernel::Kernel;

fn main() {
    Kernel::init();
    println!("Core OS started!");
}
