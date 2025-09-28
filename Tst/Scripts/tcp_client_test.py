#!/usr/bin/env python3

import socket
import sys
import threading
import time
import argparse
import json

class TcpClient:
    def __init__(self, host='localhost', port=8080):
        self.host = host
        self.port = port
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.running = False
        self.receive_thread = None

    def connect(self):
        try:
            self.sock.connect((self.host, self.port))
            self.running = True
            print(f"Connected to {self.host}:{self.port}")
            
            # Start receive thread
            self.receive_thread = threading.Thread(target=self._receive_messages)
            self.receive_thread.daemon = True
            self.receive_thread.start()
            return True
        except Exception as e:
            print(f"Connection failed: {e}")
            return False

    def disconnect(self):
        self.running = False
        
        # Wait for receive thread to finish first
        if self.receive_thread and self.receive_thread.is_alive():
            self.receive_thread.join(timeout=2.0)
        
        if self.sock:
            try:
                # Shutdown the socket properly
                self.sock.shutdown(socket.SHUT_RDWR)
            except Exception as e:
                # Socket might already be closed, ignore this error
                pass
            try:
                self.sock.close()
            except Exception as e:
                print(f"Error during socket close: {e}")
        
        print("Disconnected from server")

    def send_message(self, message):
        try:
            self.sock.send(message.encode('utf-8'))
            return True
        except Exception as e:
            print(f"Failed to send message: {e}")
            return False

    def _receive_messages(self):
        while self.running:
            try:
                data = self.sock.recv(1024)
                if not data:
                    break
                print(f"Server response: {data.decode('utf-8')}")
            except Exception as e:
                if self.running:
                    print(f"Receive error: {e}")
                break
        self.running = False

def send_automated_messages(client, messages, interval=1.0):
    """Send a list of messages with a specified interval between them."""
    for msg in messages:
        if not client.running:
            break
        print(f"\nSending: {msg}")
        if not client.send_message(msg):
            break
        time.sleep(interval)

def main():
    parser = argparse.ArgumentParser(description='TCP Client Test Script')
    parser.add_argument('--host', default='localhost', help='Server host')
    parser.add_argument('--port', type=int, default=8080, help='Server port')
    parser.add_argument('--interval', type=float, default=1.0, 
                      help='Interval between messages in seconds')
    args = parser.parse_args()

    request = {
        "Operation": "Account",
        "OperationType": "get",
        "ColumnName": "Account_balance",
        "Data": ["20230809MYS00101"]
    }
    # Sample messages to send
    test_messages = [
        json.dumps(request),
        # json.dumps({"message": "Testing automated message 1"}),
        # json.dumps({"message": "Testing automated message 2"}),
        # json.dumps({"message": "This is a longer message to test buffer handling"}),
        # json.dumps({"message": "Final test message"})
    ]

    client = TcpClient(args.host, args.port)
    
    try:
        if client.connect():
            print("\nStarting automated message test...")
            send_automated_messages(client, test_messages, args.interval)
            print("\nTest completed successfully")
            time.sleep(0.5)  # Brief wait for any final responses
            print("Closing connection...")
            client.disconnect()
            print("Test program completed")
            sys.exit(0)  # Ensure clean exit
    except KeyboardInterrupt:
        print("\nTest interrupted by user")
    finally:
        client.disconnect()
        sys.exit(0)  # Ensure program exits

if __name__ == "__main__":
    main()
