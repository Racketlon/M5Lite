import tkinter as tk

class PulseVM:
    def __init__(self, interpreter):
        self.interpreter = interpreter

    def create_app(self):
        """
        Create and run the Tkinter app based on the parsed structure.
        """
        root = tk.Tk()
        root.title(self.interpreter.app_name)
        root.geometry("540x960")
        root.resizable(False, False)

        # Create a dictionary to store label variables
        label_vars = {}

        # Add labels
        for label in self.interpreter.labels:
            props = label["properties"]
            text = props.get("text", "")
            position = props.get("position", (0, 0))
            font_size = props.get("font_size", 12)

            x, y = self.calculate_position(position)

            # Create a StringVar for dynamic text updates
            var = tk.StringVar(value=text)
            label_vars[label["name"]] = var

            tk.Label(root, textvariable=var, font=("Arial", font_size)).place(x=x, y=y, anchor="center")

        # Add buttons
        for button in self.interpreter.buttons:
            props = button["properties"]
            text = props.get("text", "")
            position = props.get("position", (0, 0))
            size = props.get("size", (100, 30))

            x, y = self.calculate_position(position)
            size = tuple(int(dim.strip()) for dim in size.split(","))  # Properly split and convert to integers

            def button_command(btn_name=button["name"]):
                if btn_name == "increment_button" and "counter_label" in label_vars:
                    current_value = int(label_vars["counter_label"].get())
                    label_vars["counter_label"].set(current_value + 1)
                elif btn_name == "reset_button" and "counter_label" in label_vars:
                    label_vars["counter_label"].set(0)

            btn = tk.Button(root, text=text, width=size[0] // 10, height=size[1] // 20,
                            command=lambda bname=button["name"]: button_command(bname))
            btn.place(x=x, y=y, anchor="center")

        root.mainloop()

    def calculate_position(self, position):
        """
        Convert 'center' to appropriate pixel values.
        """
        x, y = position
        if x == "center":
            x = 540 // 2
        if y == "center":
            y = 960 // 2
        return int(x), int(y)

if __name__ == "__main__":
    print("This module is not meant to be run directly.")
