# Python web server
import socket



listening = socket.socket( )
listening.bind(('localhost', 8080))
listening.listen(4)
print(f'connecting through HTTP on port {8080} ...')
print('Access http://localhost:8080')
while True:
    client, caddr = listening.accept()
    print('connected with',caddr)
    request_data = client.recv(1024)
    print(request_data.decode('utf-8'))


    http_response = 'HTTP/1.0 200 OK\n\n<h1 style="color:orange;">Hello World<h1> \n<h1> The server is working </h1>'
    client.sendall(http_response.encode())
    
    client.close()