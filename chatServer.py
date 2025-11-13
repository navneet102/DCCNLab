import socket

HOST = '127.0.0.1'
PORT = 65432

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()
    print(f"Server listening on {HOST}:{PORT}...")
    conn, addr = s.accept()
    with conn:
        print(f"Connected by {addr}")
        while True:
            data = conn.recv(1024)
            if not data:
                print("Client disconnected.")
                break
            
            client_msg = data.decode()
            print(f"Client: {client_msg}")
            
            if client_msg.lower() in ['exit', 'quit']:
                break
            
            server_msg = input("Server: ")
            conn.sendall(server_msg.encode())
            
            if server_msg.lower() in ['exit', 'quit']:
                break