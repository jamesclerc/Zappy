
import sys

def print_help(program_name):
    """Function that print the usage"""
    print("USAGE:\t" + program_name + " -p port -n name - h machine")
    print("\tport\tis the port number")
    print("\tname\tis the name of the team")
    print("\tmachine\tis the the name of the machine; localhost by default")


def parse_arguments(argv):
    """Parse the arguments to retrieve the port, the name and the machine"""
    argv = argv[1:]
    port = None
    name = None
    machine = "localhost"
    if len(argv) % 2:
        sys.stderr.write("Error: wrong arguments\n")
        sys.exit(84)
    for i in range(0, len(argv), 2):
        if (argv[i] == "-p"):
            try:
                port = int(argv[i + 1])
                if port <= 0 or port > 65535:
                    sys.stderr.write("Error: wrong port value\n")
                    sys.exit(84)
            except ValueError:
                sys.stderr.write("Error: wrong port value\n")
                sys.exit(84)
        elif argv[i] == "-n":
            name = argv[i + 1]
        elif argv[i] == "-h":
            machine = argv[i + 1]
        else:
            sys.stderr.write("Error: wrong argument\n")
            sys.exit(84)
    if port is None:
        sys.stderr.write("Error: port not entered\n")
        sys.exit(84)
    if name is None:
        sys.stderr.write("Error: name not entered\n")
        sys.exit(84)
    return port, name, machine

def parse_args():
    port = None
    name = None
    machine = None
    if (len(sys.argv) >= 2 and sys.argv[1] == "-help"):
        print_help(sys.argv[0])
        sys.exit(0)
    else:
        port, name, machine = parse_arguments(sys.argv)
    return port, name, machine

