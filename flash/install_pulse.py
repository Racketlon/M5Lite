import os

# Define the content to be added to the shell configuration file
PULSE_SETUP = """
# Pulse Environment Setup
export PULSE_HOME="$(pwd)/Pulse"
export PATH="$PULSE_HOME:$PATH"
alias pulse="python3 $PULSE_HOME/main.py"
"""

def get_shell_config_file():
    """Determine the user's shell configuration file."""
    shell = os.getenv("SHELL", "").split("/")[-1]
    if shell == "zsh":
        return os.path.expanduser("~/.zshrc")
    elif shell == "bash":
        return os.path.expanduser("~/.bashrc")
    else:
        print(f"Unsupported shell: {shell}. Please manually update your shell configuration.")
        return None

def append_to_shell_config(config_file, content):
    """Append content to the shell configuration file if not already present."""
    if not config_file:
        return

    try:
        with open(config_file, "r") as file:
            lines = file.readlines()
            if any("PULSE_HOME" in line or "alias pulse" in line for line in lines):
                print("Pulse is already configured in your shell configuration file.")
                return

        with open(config_file, "a") as file:
            file.write(content)
            print(f"Pulse environment added to {config_file}. Please restart your terminal or source the file.")
    except Exception as e:
        print(f"Failed to update {config_file}: {e}")

def main():
    config_file = get_shell_config_file()
    if config_file:
        append_to_shell_config(config_file, PULSE_SETUP)

if __name__ == "__main__":
    main()
