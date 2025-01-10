use System; // Use the System package for Permissions

App {
    init {
        name: "Terminal"; // The name of the app shown on the Home Menu
        logo: "</>"; // The Logo (supports also emojis since it's a string)
    }

    prompt_position = 20; // Assign 20 (as int) to prompt_position

    // Get input from user
    input prompt {
        text: System.pwd(); // A text
        get_input: command; // Save the input text into command using get_input
        function: System.execute(command); // Execute the command using System.execute()
        position: left, prompt_position; // Set the position to left and 20 (X, Y)
        prompt_position += 20; // Add 20 to prompt_position
    }
}