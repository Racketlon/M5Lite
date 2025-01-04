import os

class Installation:
    def __init__(self):
        # Read the SHELL environment variable directly
        self.shell = os.environ.get("SHELL", "")
        self.install_command = ""
        self.source_command = ""

    def get_shell_command(self):
        if "zsh" in self.shell:
            self.install_command = f"echo \"alias pulse='$(pwd)/./pulse'\" >> $HOME/.zshrc"
            self.source_command = "source $HOME/.zshrc"
        elif "bash" in self.shell:
            self.install_command = f"echo \"alias pulse='$(pwd)/./pulse'\" >> $HOME/.bashrc"
            self.source_command = "source $HOME/.bashrc"
        else:
            print(f"Unknown shell: {self.shell}")

    def install(self):
        # Optionally call self.get_shell_command() here or do it inline
        self.get_shell_command()

        print("Compiling Pulse")
        os.system("make")

        # Only run if we have a recognized shell
        if self.install_command and self.source_command:
            print("Adding Pulse to source file")
            os.system(self.install_command)
            print(f"Installation done! To use Pulse you need to run:\n{self.source_command}\nNow you can use Pulse to create your custom apps for the M5Paper")
        else:
            print("Error occured while installing Pulse on your machine :(")

if __name__ == "__main__":
    Installer = Installation()
    Installer.install()
