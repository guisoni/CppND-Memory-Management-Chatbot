#include "graphedge.h"
#include "graphnode.h"
#include <iostream> /*Isoni*/

GraphNode::GraphNode(int id)
{    /*Isoni*/ //std::cout <<"Enters Constructor GraphNode(int) " << std::endl;
    _id = id;
    /*Isoni*/ //std::cout <<"Exits Constructor GraphNode(int) " << std::endl;
}

GraphNode::~GraphNode()
{   /*Isoni*/ std::cout <<"Enters Destructor GraphNode(int) " << std::endl;
    //// STUDENT CODE
    ////
    /*Isoni*/ //std::cout <<"Deallocates _chatBot: " << &_chatBot <<": on address: "<< _chatBot << std::endl;
    /*change*///delete _chatBot; 
    
    
    
    /*Isoni*/ //std::cout <<"Exit destructor GraphNode(int) " << std::endl;
    ////
    //// EOF STUDENT CODE
}

void GraphNode::AddToken(std::string token)
{   /*Isoni*/ //std::cout <<"Enter AddToken(string) " << std::endl;
    _answers.push_back(token);
    /*Isoni*/ //std::cout <<"Exit AddToken(string) " << std::endl;
}

void GraphNode::AddEdgeToParentNode(GraphEdge *edge)
{    /*Isoni*/ //std::cout <<"Enter AddEdgeToParentNode(GraphEdge *) " << std::endl;
    _parentEdges.push_back(edge);
    /*change*/ //edge = nullptr;
    /*Isoni*/ //std::cout <<"Shares edge address: to _parentEdges "<< edge << std::endl;
    /*Isoni*/ //std::cout <<"Exit AddEdgeToParentNode(GraphEdge *) " << std::endl;
}

void GraphNode::AddEdgeToChildNode(GraphEdge *edge)
{   /*Isoni*/ //std::cout <<"Enter AddEdgeToChildNode(GraphEdge *) " << std::endl;
    _childEdges.push_back(edge);
    /*change*/ //edge = nullptr;
    /*Isoni*/ //std::cout <<"Shares edge to childEdges "<< edge << std::endl;
    /*Isoni*/ //std::cout <<"Exit AddEdgeToChildNode(GraphEdge *) " << std::endl;
}

//// STUDENT CODE
////
void GraphNode::MoveChatbotHere(ChatBot *chatbot)
{   /*Isoni*/ std::cout <<"Enter MoveChatbotHere(ChatBot *) " << std::endl;
    _chatBot = chatbot;
    /*change*/ //chatbot = nullptr;
    /*Isoni*/ std::cout <<"_chatBot "<< &_chatBot <<": receives: "<< &chatbot <<": on address: " << _chatBot << std::endl;
    _chatBot->SetCurrentNode(this);
    /*Isoni*/ //std::cout <<"Exit MoveChatbotHere(ChatBot *) " << std::endl;
}

void GraphNode::MoveChatbotToNewNode(GraphNode *newNode)
{    /*Isoni*/ std::cout << "Enter MoveChatbotToNewNode(GraphNode *) " << std::endl;
    newNode->MoveChatbotHere(_chatBot);
    /*Isoni*/ std::cout <<"_chatBot "<< &_chatBot <<" = nullptr" << std::endl; 
    _chatBot = nullptr; // invalidate pointer at source

    /*Isoni*/ //std::cout << "Exit MoveChatbotToNewNode(GraphNode *) " << std::endl;
}
////
//// EOF STUDENT CODE

GraphEdge *GraphNode::GetChildEdgeAtIndex(int index)
{   /*Isoni*/ std::cout << "Enter GetChildEdgeAtIndex(int) " << std::endl;
    //// STUDENT CODE
    ////
    /*Isoni*/ //std::cout << "Exit GetChildEdgeAtIndex(int) " << std::endl;
    return _childEdges[index];

    ////
    //// EOF STUDENT CODE
}