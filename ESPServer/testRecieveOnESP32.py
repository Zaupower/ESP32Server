import socket

sock = socket.socket()

host = "10.42.0.1"  # ESP32 IP in local network
port = 5555  # ESP32 Server Port

sock.connect((host, port))

message = "Hello World"
sock.send(message)

data = ""
