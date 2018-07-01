import select
import socket
import sys


class Connection:
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    host = None
    port = None
    generator = None
    has_next = False

    def __init__(self, host, port):
        self.host = host
        self.port = port
        try:
            self.sock.connect((host, port))
        except socket.error:
            sys.stderr.write("Error: socket can't connect\n")
            sys.exit(84)

    def __del__(self):
        self.sock.close()

    def receive(self, buffer_size=4096, delim="\n"):
        buffer = ""
        data = True
        while data:
            data = self.sock.recv(buffer_size)
            buffer += data.decode("ascii")
            while buffer.find(delim) != -1:
                line, buffer = buffer.split(delim, 1)
                try:
                    buffer.index(delim)
                    self.has_next = True
                except ValueError:
                    self.has_next = False
                yield line
        return

    def next(self, buffer_size=4096, delim="\n"):
        if self.generator is None:
            self.generator = self.receive(buffer_size, delim)
        try:
            return next(self.generator)
        except StopIteration:
            sys.exit(0)

    def send(self, buffer):
        buffer += "\n"
        while buffer:
            length = self.sock.send(buffer.encode())
            buffer = buffer[length:]

    def wait_message(self):
        readable, _, exceptional = select.select([self.sock], [], [self.sock])
        return not bool(len(exceptional))
