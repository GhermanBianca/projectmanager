#ifndef CLIENT_HPP
#define CLIENT_HPP

class Client {
 public:
    static void InsertProperties(int client_socket);
    static void DisplayProperties(int client_socket);
    static void DeleteProperties(int client_socket);
    static void UpdateProperties(int client_socket);
};

#endif