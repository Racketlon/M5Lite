App {
    init {
        name: "Simple Button";
        logo: "B";
    }

    label click_me_text {
        text: "Click the button underneath";
        size: 10;
        position: center, 100; // x: center, y: 100
    }

    button click_me {
        text: "Click me :)";
        size: 200, 100; // width: 200, height: 100
        position: center, 200; // x: center, y: 200
        function: pop_up;
    }

    fn pop_up {
        label {
            text: "You clicked me :)";
            position: center, 400; // x: center, y: 400
            size: 13;
            time: 3s; // Display for 3 seconds
        }
    }
}
