import socket

HOST = '127.0.0.1'
PORT = 65432

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    while True:
        msg = input("You: ")
        s.sendall(msg.encode())
        
        if msg.lower() in ['exit', 'quit']:
            break
        
        data = s.recv(1024)
        server_msg = data.decode()
        print(f"Server: {server_msg}")

        if server_msg.lower() in ['exit', 'quit']:
            break