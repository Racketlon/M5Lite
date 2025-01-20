pub struct TaskManager;

impl TaskManager {
    pub fn add_task(task_name: &str) {
        println!("Task '{}' added.", task_name);
    }

    pub fn remove_task(task_name: &str) {
        println!("Task '{}' removed.", task_name);
    }
}
