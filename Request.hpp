#ifndef REQUEST_HPP
#define REQUEST_HPP

class Request {
 public: 
    static void InsertProperties(int sockfd);
    static void DisplayProperties();
    static void UpdateProperties();
    static void DeleteProperties();
};

#endif