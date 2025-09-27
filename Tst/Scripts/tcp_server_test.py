#!/usr/bin/env python3

import socket
import sys
import threading
import time
import argparse
from typing import Dict, List
import json

class TcpServer:
    def __init__(self, host='localhost', port=8090):
        self.host = host
        self.port = port
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.running = False
        self.clients: Dict[socket.socket, threading.Thread] = {}
        self.client_addresses: Dict[socket.socket, str] = {}
        self.message_handlers = []

    def add_message_handler(self, handler):
        """Add a callback function to handle received messages"""
        self.message_handlers.append(handler)

    def start(self):
        try:
            self.server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            self.server_socket.bind((self.host, self.port))
            self.server_socket.listen(5)
            self.running = True
            print(f"Server started on {self.host}:{self.port}")
            
            # Start accepting connections
            self.accept_thread = threading.Thread(target=self._accept_connections)
            self.accept_thread.daemon = True
            self.accept_thread.start()
            return True
        except Exception as e:
            print(f"Server start failed: {e}")
            return False

    def stop(self):
        self.running = False
        # Close all client connections
        for client_socket in list(self.clients.keys()):
            self._close_client(client_socket)
        
        if self.server_socket:
            self.server_socket.close()
        
        if hasattr(self, 'accept_thread') and self.accept_thread.is_alive():
            self.accept_thread.join()
        print("Server stopped")

    def broadcast(self, message: str, exclude_client=None):
        """Send message to all connected clients"""
        for client_socket in list(self.clients.keys()):
            if client_socket != exclude_client:
                self._send_to_client(client_socket, message)

    def _accept_connections(self):
        while self.running:
            try:
                client_socket, address = self.server_socket.accept()
                print(f"New connection from {address}")
                self.client_addresses[client_socket] = f"{address[0]}:{address[1]}"
                
                # Start a new thread for this client
                client_thread = threading.Thread(
                    target=self._handle_client,
                    args=(client_socket,)
                )
                client_thread.daemon = True
                client_thread.start()
                self.clients[client_socket] = client_thread
                
            except Exception as e:
                if self.running:
                    print(f"Accept error: {e}")
                break

    def _handle_client(self, client_socket: socket.socket):
        while self.running:
            try:
                data = client_socket.recv(1024)
                if not data:
                    break
                
                message = data.decode('utf-8')
                client_id = self.client_addresses[client_socket]
                print(f"Received from {client_id}: {message}")
                
                # Process message through handlers
                for handler in self.message_handlers:
                    response = handler(message, client_id)
                    if response:
                        self._send_to_client(client_socket, response)
                
            except Exception as e:
                if self.running:
                    print(f"Client error: {e}")
                break
        
        self._close_client(client_socket)

    def _send_to_client(self, client_socket: socket.socket, message: str):
        try:
            client_socket.send(message.encode('utf-8'))
        except Exception as e:
            print(f"Send error to {self.client_addresses.get(client_socket, 'unknown')}: {e}")
            self._close_client(client_socket)

    def _close_client(self, client_socket: socket.socket):
        if client_socket in self.clients:
            client_addr = self.client_addresses.get(client_socket, 'unknown')
            print(f"Client disconnected: {client_addr}")
            client_socket.close()
            del self.clients[client_socket]
            if client_socket in self.client_addresses:
                del self.client_addresses[client_socket]

def echo_handler(message: str, client_id: str) -> str:
    """Simple echo handler that sends back the received message"""
    return f"Echo [{client_id}]: {message}"

def json_handler(message: str, client_id: str) -> str:
    """Handle JSON messages and return formatted response"""
    try:
        data = json.loads(message)
        return json.dumps({
            "status": "success",
            "client": client_id,
            "received": data,
            "timestamp": time.time()
        })
    except json.JSONDecodeError:
        return json.dumps({
            "status": "error",
            "message": "Invalid JSON format",
            "received": message
        })

def main():
    parser = argparse.ArgumentParser(description='TCP Server Test Script')
    parser.add_argument('--host', default='localhost', help='Server host')
    parser.add_argument('--port', type=int, default=8080, help='Server port')
    parser.add_argument('--json', action='store_true', help='Enable JSON message handling')
    args = parser.parse_args()

    server = TcpServer(args.host, args.port)
    
    # Add message handlers
    server.add_message_handler(json_handler if args.json else echo_handler)
    
    try:
        if server.start():
            print("Server is running. Press Ctrl+C to stop.")
            while True:
                time.sleep(1)
    except KeyboardInterrupt:
        print("\nServer shutdown requested")
    finally:
        server.stop()

if __name__ == "__main__":
    main()
