import socket

# Define the server's IP address and port
SERVER_IP = '127.0.0.1'  # Use your server's IP address
SERVER_PORT = 12345

# Create a socket object
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Bind the socket to the IP address and port
server_socket.bind((SERVER_IP, SERVER_PORT))

# Listen for incoming connections
server_socket.listen(5)
print(f"Server is listening on {SERVER_IP}:{SERVER_PORT}")

while True:
    # Accept a connection from a client
    client_socket, client_address = server_socket.accept()
    print(f"Accepted connection from {client_address}")

    # Handle the client
    while True:
        data = client_socket.recv(1024)
        if not data:
            break
        print(f"Received data from {client_address}: {data.decode('utf-8')}")

        # Echo the data back to the client
        client_socket.send(data)

    # Close the client socket
    client_socket.close()
    print(f"Connection with {client_address} closed")
