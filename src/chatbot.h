#ifndef CHATBOT_H_
#define CHATBOT_H_

#include <wx/bitmap.h>
#include <string>
#include <iostream> /*isoni*/

class GraphNode; // forward declaration
class ChatLogic; // forward declaration

class ChatBot
{
private:
    // data handles (owned)
    wxBitmap *_image; // avatar image

    // data handles (not owned)
    GraphNode *_currentNode;
    GraphNode *_rootNode;
    ChatLogic *_chatLogic;

    // proprietary functions
    int ComputeLevenshteinDistance(std::string s1, std::string s2);

public:
    // constructors / destructors
    ChatBot();                     // constructor WITHOUT memory allocation
    ChatBot(std::string filename); // constructor WITH memory allocation
    ~ChatBot();

    //// STUDENT CODE
    ////
    ChatBot(const ChatBot&); // copy constructor
    ChatBot &operator=(const ChatBot&); // copy assignment constructor
    ChatBot(ChatBot&&); // move constructor
    ChatBot &operator=(ChatBot&&); // move assignment constructor
    ////
    //// EOF STUDENT CODE

    // getters / setters
    void SetCurrentNode(GraphNode *node);
    void SetRootNode(GraphNode *rootNode) { _rootNode = rootNode;
    /*Isoni*/std::cout <<"_rootNode: " << &_rootNode <<": receives chatBot: "<< &rootNode <<": on address: "<< rootNode << std::endl; }
    void SetChatLogicHandle(ChatLogic *chatLogic) { _chatLogic = chatLogic;
     /*Isoni*/std::cout <<"_chatLogic: " << &_chatLogic <<": receives chatBot: "<< &chatLogic <<": on address: "<< chatLogic << std::endl;}
    wxBitmap *GetImageHandle() { return _image; }

    // communication
    void ReceiveMessageFromUser(std::string message);
};

#endif /* CHATBOT_H_ */