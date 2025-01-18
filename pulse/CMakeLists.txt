idf_component_register(SRCS "main.py"
                            "interpreter/Interpreter.py"
                            "interpreter/vm.py"
                    INCLUDE_DIRS "."
                    REQUIRES lib)
