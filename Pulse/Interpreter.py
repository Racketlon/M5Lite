import os

class PulseInterpreter:
    SCREEN_WIDTH = 540
    SCREEN_HEIGHT = 960

    def __init__(self, file):
        self.file = file
        self.app_name = None
        self.app_logo = None
        self.labels = []
        self.buttons = []

    def interpret(self):
        """
        Interpret the Pulse file and provide debugging output.
        """
        with open(self.file, "r") as pulse_file:
            lines = pulse_file.readlines()

        current_component = None
        for line in lines:
            line = line.strip()

            # Skip empty lines and comments
            if not line or line.startswith("//"):
                continue

            # App metadata
            if line.startswith("App "):
                self.app_name = line.split('"')[1]

            elif line.startswith("App.name"):
                self.app_name = line.split("=")[1].strip().strip('"')

            elif line.startswith("App.logo"):
                self.app_logo = line.split("=")[1].strip().strip('"')

            # UI Components
            elif line.startswith("label"):
                current_component = {
                    "type": "label",
                    "name": line.split()[1].strip(":"),
                    "properties": {}
                }
                self.labels.append(current_component)

            elif line.startswith("button"):
                current_component = {
                    "type": "button",
                    "name": line.split()[1].strip(":"),
                    "properties": {}
                }
                self.buttons.append(current_component)

            elif line.startswith("fn on_click()"):
                current_component["properties"]["on_click"] = []

            elif current_component and line:
                # Parse properties
                if ":" in line:
                    key, value = map(str.strip, line.split(":", 1))
                    if key == "position":
                        value = tuple(
                            self.parse_position_component(v.strip()) for v in value.split(",")
                        )
                    elif value.isdigit():
                        value = int(value)
                    else:
                        value = value.strip('"')
                    current_component["properties"][key] = value

        self.debug()

    def parse_position_component(self, value):
        """
        Parse individual components of a position (e.g., 'center' or a number).
        """
        if value == "center":
            return "center"
        try:
            return int(value)
        except ValueError:
            return value

    def debug(self):
        """
        Display debugging information about the parsed .pls file.
        """
        print(f"App Name: {self.app_name}")
        print(f"App Logo: {self.app_logo}")

        if self.labels:
            print("Labels:")
            for label in self.labels:
                print(f"  {label}")
                if "position" in label["properties"]:
                    print(f"    Position: {label['properties']['position']}")
                else:
                    print("    Position: Not defined")

        if self.buttons:
            print("Buttons:")
            for button in self.buttons:
                print(f"  {button}")
                if "position" in button["properties"]:
                    print(f"    Position: {button['properties']['position']}")
                else:
                    print("    Position: Not defined")
