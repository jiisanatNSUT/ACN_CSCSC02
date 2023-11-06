import socket

# Define the server's IP address and port
SERVER_IP = '127.0.0.1'  # Use the server's IP address
SERVER_PORT = 12345

# Create a socket object
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect to the server
client_socket.connect((SERVER_IP, SERVER_PORT))
print(f"Connected to the server at {SERVER_IP}:{SERVER_PORT}")

while True:
    message = input("Enter a message (or 'exit' to quit): ")
    if message.lower() == 'exit':
        break

    # Send the message to the server
    client_socket.send(message.encode('utf-8'))

    # Receive and print the server's response
    data = client_socket.recv(1024)
    print(f"Server response: {data.decode('utf-8')}")

# Close the client socket
client_socket.close()
