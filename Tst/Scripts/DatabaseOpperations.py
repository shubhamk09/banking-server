import zmq
import json

def main():
    context = zmq.Context()
    socket = context.socket(zmq.REQ)
    socket.connect("tcp://localhost:5502")

    # Example request matching your C++ server expectations
    request = {
        "Operation": "Account",
        "OperationType": "get",
        "ColumnName": "Account_balance",
        "Data": ["20230809MYS00101"]
    }
    print("Sending request:", request)
    # Send the request as a JSON string
    socket.send_string(json.dumps(request))

    # Wait for the reply from the server
    print("Waiting for reply...")
    reply = socket.recv_string()
    print("Received reply:", reply)

if __name__ == "__main__":
    main()