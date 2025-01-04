import argparse
from Interpreter import PulseInterpreter
from vm import PulseVM

def main():
    # Set up argument parsing with "pulse" as the program name
    parser = argparse.ArgumentParser(
        description="Pulse Interpreter for .pls files.",
        prog="pulse"  # Set the program name to "pulse"
    )
    parser.add_argument("file", help="The .pls file to interpret and execute.")
    args = parser.parse_args()

    # Pass the argument to the Pulse interpreter
    interpreter = PulseInterpreter(args.file)
    interpreter.interpret()

    # Create and run the VM using the parsed data
    vm = PulseVM(interpreter)
    vm.create_app()

if __name__ == "__main__":
    main()
