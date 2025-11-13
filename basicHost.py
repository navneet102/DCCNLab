import socket

HOST = '127.0.0.1'  # same as server
PORT = 65432

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    while True:
        msg = input("You: ")
        if msg.lower() in ['exit', 'quit']:
            break
        s.sendall(msg.encode())
        data = s.recv(1024)
        print(f"Echo: {data.decode()}")
