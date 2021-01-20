#include <iostream>
#include <random>
#include <algorithm>
#include <ctime>

#include "chatlogic.h"
#include "graphnode.h"
#include "graphedge.h"
#include "chatbot.h"
#include <iostream> /*Isoni*/
// constructor WITHOUT memory allocation
ChatBot::ChatBot()
{    /*Isoni*/ std::cout <<"Enter Constructor ChatBot()"<< std::endl;
    // invalidate data handles
    _image = nullptr;
    _chatLogic = nullptr;
    _rootNode = nullptr;
    /*Isoni*/ std::cout <<"ChatBot _image _chatLogic, _rootNode = nullptr"<< std::endl;
    /*Isoni*/ std::cout <<"Exit Constructor ChatBot()"<< std::endl;
}

// constructor WITH memory allocation
ChatBot::ChatBot(std::string filename)
{    /*Isoni*/ std::cout <<"Enter Constructor ChatBot(string)" << std::endl;
    std::cout << "ChatBot Constructor" << std::endl;
    
    // invalidate data handles
    _chatLogic = nullptr;
    _rootNode = nullptr;
    /*Isoni*/ //std::cout <<"_chatLogic, _rootNode = nullptr"<< std::endl;
    // load image into heap memory
    _image = new wxBitmap(filename, wxBITMAP_TYPE_PNG);
    /*Isoni*/ std::cout <<"Allocates _image "<< &_image << ": on address: " << _image << std::endl;
    /*Isoni*/ std::cout <<"Exit Constructor ChatBot(string)" << std::endl;
}

ChatBot::~ChatBot()
{   /*Isoni*/ std::cout <<"Enter Destructor ChatBot()" << std::endl;
    std::cout << "ChatBot Destructor" << std::endl;

    // deallocate heap memory
    if(_image != NULL) // Attention: wxWidgets used NULL and not nullptr
    {   /*Isoni*/ std::cout <<"Deallocates _image "<< &_image << ": on address: " << _image << std::endl;
        delete _image;
        _image = NULL;
    }
    /*Isoni*/ std::cout <<"Exit Destructor ChatBot(string)" << std::endl;
}

//// STUDENT CODE
////
    ChatBot::ChatBot(ChatBot &chatbot)
    {
/*        std::cout << "ChatBot Copy Constructor" << std::endl;
        _image = new wxBitmap();
        *_image = *chatbot._image;
        _currentNode = new GraphNode(chatbot._currentNode->GetID());
        *_currentNode = *chatbot._currentNode;
        _rootNode = new GraphNode(chatbot._rootNode->GetID());
        *_rootNode = *chatbot._rootNode;
        _chatLogic = new ChatLogic();
        *_chatLogic = *chatbot._chatLogic;*/

        _image = chatbot._image;
        chatbot._image = nullptr;
        _currentNode = chatbot._currentNode;
        chatbot._currentNode = nullptr;
        _rootNode = chatbot._rootNode;
        chatbot._rootNode = nullptr;
        _chatLogic = chatbot._chatLogic;;
        chatbot._chatLogic = nullptr;
    }

    ChatBot& ChatBot::operator=(ChatBot &chatbot)
    {
        std::cout << "ChatBot Copy assignment Constructor" << std::endl;
        
        _image = chatbot._image;
        chatbot._image = nullptr;
        _currentNode = chatbot._currentNode;
        chatbot._currentNode = nullptr;
        _rootNode = chatbot._rootNode;
        chatbot._rootNode = nullptr;
        _chatLogic = chatbot._chatLogic;;
        chatbot._chatLogic = nullptr;
        return *this;
    }     
    

    ChatBot::ChatBot(ChatBot &&chatbot)
    {
        std::cout << "ChatBot Move Constructor" << std::endl;
        _image = chatbot._image;
        chatbot._image = NULL;
        _currentNode = chatbot._currentNode;
        chatbot._currentNode = nullptr;
        _rootNode = chatbot._rootNode;
        chatbot._rootNode = nullptr;
        _chatLogic = chatbot._chatLogic;
        chatbot._chatLogic = nullptr;
    }
    ChatBot& ChatBot::operator=(ChatBot &&chatbot)
    {
        std::cout << "ChatBot Move Assignment Constructor" << std::endl;
        if(this == &chatbot)
            return *this;
        delete _image;
        delete _currentNode;
        delete _rootNode;
        delete _chatLogic;
        

        _image = new wxBitmap();
        _image = chatbot._image;
        chatbot._image = NULL;
        _currentNode = new GraphNode(chatbot._currentNode->GetID());
        _currentNode = chatbot._currentNode;
        chatbot._currentNode = nullptr;
        _rootNode = new GraphNode(chatbot._rootNode->GetID());
        _rootNode = chatbot._rootNode;
        chatbot._rootNode = nullptr;
        _chatLogic = new ChatLogic();
        _chatLogic = chatbot._chatLogic;
        chatbot._chatLogic = nullptr;
        return *this;
    }
////
//// EOF STUDENT CODE

void ChatBot::ReceiveMessageFromUser(std::string message)
{   /*Isoni*/ std::cout <<"Enter ReceiveMessageFromUser(string)" << std::endl;
    // loop over all edges and keywords and compute Levenshtein distance to query
    typedef std::pair<GraphEdge *, int> EdgeDist;
    std::vector<EdgeDist> levDists; // format is <ptr,levDist>

    for (size_t i = 0; i < _currentNode->GetNumberOfChildEdges(); ++i)
    {
        GraphEdge *edge = _currentNode->GetChildEdgeAtIndex(i);
        for (auto keyword : edge->GetKeywords())
        {
            EdgeDist ed{edge, ComputeLevenshteinDistance(keyword, message)};
            levDists.push_back(ed);
        }
    }

    // select best fitting edge to proceed along
    GraphNode *newNode;
    if (levDists.size() > 0)
    {
        // sort in ascending order of Levenshtein distance (best fit is at the top)
        std::sort(levDists.begin(), levDists.end(), [](const EdgeDist &a, const EdgeDist &b) { return a.second < b.second; });
        newNode = levDists.at(0).first->GetChildNode(); // after sorting the best edge is at first position
    }
    else
    {
        // go back to root node
        newNode = _rootNode;
        /*change*/ //_rootNode = nullptr;
    }

    // tell current node to move chatbot to new node
    _currentNode->MoveChatbotToNewNode(newNode);
    /*Isoni*/ std::cout <<"Exit ReceiveMessageFromUser(string)" << std::endl;
}

void ChatBot::SetCurrentNode(GraphNode *node)
{  /*Isoni*/ std::cout <<"SetCurrentNode(GraphNode *)" << std::endl;
    // update pointer to current node
    _currentNode = node;
    /*change*/ //node = nullptr;
    /*Isoni*/ std::cout <<"Shared _currentNode on address: " << _currentNode << std::endl; 
    // select a random node answer (if several answers should exist)
    std::vector<std::string> answers = _currentNode->GetAnswers();
    std::mt19937 generator(int(std::time(0)));
    std::uniform_int_distribution<int> dis(0, answers.size() - 1);
    std::string answer = answers.at(dis(generator));

    // send selected node answer to user
    _chatLogic->SendMessageToUser(answer);
    /*Isoni*/ //std::cout <<"Exit ReceiveMessageFromUser(string)" << std::endl;
}

int ChatBot::ComputeLevenshteinDistance(std::string s1, std::string s2)
{   /*Isoni*/ std::cout <<"Enter ComputeLevenshteinDistance(string, string)" << std::endl;
    // convert both strings to upper-case before comparing
    std::transform(s1.begin(), s1.end(), s1.begin(), ::toupper);
    std::transform(s2.begin(), s2.end(), s2.begin(), ::toupper);

    // compute Levenshtein distance measure between both strings
    const size_t m(s1.size());
    const size_t n(s2.size());

    if (m == 0)
        return n;
    if (n == 0)
        return m;

    size_t *costs = new size_t[n + 1];
    /*Isoni*/ std::cout <<"Allocates costs "<< &costs << ": on address: "<< costs << std::endl;
    for (size_t k = 0; k <= n; k++)
        costs[k] = k;

    size_t i = 0;
    for (std::string::const_iterator it1 = s1.begin(); it1 != s1.end(); ++it1, ++i)
    {
        costs[0] = i + 1;
        size_t corner = i;

        size_t j = 0;
        for (std::string::const_iterator it2 = s2.begin(); it2 != s2.end(); ++it2, ++j)
        {
            size_t upper = costs[j + 1];
            if (*it1 == *it2)
            {
                costs[j + 1] = corner;
            }
            else
            {
                size_t t(upper < corner ? upper : corner);
                costs[j + 1] = (costs[j] < t ? costs[j] : t) + 1;
            }

            corner = upper;
        }
    }

    int result = costs[n];
    /*Isoni*/ std::cout <<"Deallocates costs "<< &costs<< ": on address: "<< costs << std::endl;  
    delete[] costs;
 
    /*Isoni*/ std::cout <<"Exit ComputeLevenshteinDistance(string, string)" << std::endl;
    return result;
}