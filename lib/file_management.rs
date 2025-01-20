pub struct FileManager;

impl FileManager {
    pub fn create_file(name: &str) {
        println!("File '{}' created.", name);
    }

    pub fn delete_file(name: &str) {
        println!("File '{}' deleted.", name);
    }
}
