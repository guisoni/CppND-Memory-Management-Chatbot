#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <iterator>
#include <tuple>
#include <algorithm>

#include "graphedge.h"
#include "graphnode.h"
#include "chatbot.h"
#include "chatlogic.h"
#include <iostream> /*isoni*/

ChatLogic::ChatLogic()
{    /*Isoni*/ std::cout <<"Enter Constructor ChatLogic()"<< std::endl;
    //// STUDENT CODE
    ////

    // create instance of chatbot
    _chatBot = new ChatBot("../images/chatbot.png");
    /*Isoni*/ std::cout <<"Allocates _chatBot: " << &_chatBot << ": on address: "<< _chatBot << std::endl;
    // add pointer to chatlogic so that chatbot answers can be passed on to the GUI
    _chatBot->SetChatLogicHandle(this);
    
    /*Isoni*/ std::cout <<"Exit Constructor ChatLogic()"<< std::endl;
    ////
    //// EOF STUDENT CODE
}

ChatLogic::~ChatLogic()
{    /*Isoni*/ std::cout <<"Enter Destructor ChatLogic()"<< std::endl;
    //// STUDENT CODE
    ////

    // delete chatbot instance
    /*Isoni*/ std::cout <<"Deallocates _chatBot: "<< &_chatBot <<": on address: "<< _chatBot << std::endl;
    delete _chatBot;

    // delete all nodes
    for (auto it = std::begin(_nodes); it != std::end(_nodes); ++it)
    {    /*Isoni*/ std::cout <<"Deallocates _nodes[i] it: "<< &it <<": on adress: "<< *it << std::endl;
        delete *it;
        
    }
    

    // delete all edges
    for (auto it = std::begin(_edges); it != std::end(_edges); ++it)
    {    /*Isoni*/ std::cout <<"Deallocates _edges[i] it: "<< &it <<": on adress: "<< *it << std::endl;
        delete *it;
    }
    
    /*Isoni*/ std::cout <<"Exit Destructor ChatLogic()"<< std::endl;
    ////
    //// EOF STUDENT CODE
}

template <typename T>
void ChatLogic::AddAllTokensToElement(std::string tokenID, tokenlist &tokens, T &element)
{    /*Isoni*/ std::cout <<"Enters AddAllTokensToElement(string, tokenlist &, T &)"<< std::endl;
    // find all occurences for current node
    auto token = tokens.begin();
    while (true)
    {
        token = std::find_if(token, tokens.end(), [&tokenID](const std::pair<std::string, std::string> &pair) { return pair.first == tokenID;; });
        if (token != tokens.end())
        {
            element.AddToken(token->second); // add new keyword to edge
            token++;                         // increment iterator to next element
        }
        else
        {
            break; // quit infinite while-loop
        }
    }
    /*Isoni*/ std::cout <<"Exits AddAllTokensToElement(string, tokenlist &, T &)"<< std::endl;
}

void ChatLogic::LoadAnswerGraphFromFile(std::string filename)
{    /*Isoni*/ std::cout <<"Enters LoadAnswerGraphFromFile(string)"<< std::endl;
    // load file with answer graph elements
    std::ifstream file(filename);

    // check for file availability and process it line by line
    if (file)
    {
        // loop over all lines in the file
        std::string lineStr;
        while (getline(file, lineStr))
        {
            // extract all tokens from current line
            tokenlist tokens;
            while (lineStr.size() > 0)
            {
                // extract next token
                int posTokenFront = lineStr.find("<");
                int posTokenBack = lineStr.find(">");
                if (posTokenFront < 0 || posTokenBack < 0)
                    break; // quit loop if no complete token has been found
                std::string tokenStr = lineStr.substr(posTokenFront + 1, posTokenBack - 1);

                // extract token type and info
                int posTokenInfo = tokenStr.find(":");
                if (posTokenInfo != std::string::npos)
                {
                    std::string tokenType = tokenStr.substr(0, posTokenInfo);
                    std::string tokenInfo = tokenStr.substr(posTokenInfo + 1, tokenStr.size() - 1);

                    // add token to vector
                    tokens.push_back(std::make_pair(tokenType, tokenInfo));
                }

                // remove token from current line
                lineStr = lineStr.substr(posTokenBack + 1, lineStr.size());
            }

            // process tokens for current line
            auto type = std::find_if(tokens.begin(), tokens.end(), [](const std::pair<std::string, std::string> &pair) { return pair.first == "TYPE"; });
            if (type != tokens.end())
            {
                // check for id
                auto idToken = std::find_if(tokens.begin(), tokens.end(), [](const std::pair<std::string, std::string> &pair) { return pair.first == "ID"; });
                if (idToken != tokens.end())
                {
                    // extract id from token
                    int id = std::stoi(idToken->second);

                    // node-based processing
                    if (type->second == "NODE")
                    {
                        //// STUDENT CODE
                        ////

                        // check if node with this ID exists already
                        auto newNode = std::find_if(_nodes.begin(), _nodes.end(), [&id](GraphNode *node) { return node->GetID() == id; });

                        // create new element if ID does not yet exist
                        if (newNode == _nodes.end())
                        {
                            _nodes.emplace_back(new GraphNode(id));
                            /*Isoni*/ std::cout <<"Allocates memory on _nodes "<< &_nodes[_nodes.size()-1] <<" on address: "<< _nodes.back() << std::endl;
                            newNode = _nodes.end() - 1; // get iterator to last element

                            // add all answers to current node
                            AddAllTokensToElement("ANSWER", tokens, **newNode);
                        }

                        ////
                        //// EOF STUDENT CODE
                    }

                    // edge-based processing
                    if (type->second == "EDGE")
                    {
                        //// STUDENT CODE
                        ////

                        // find tokens for incoming (parent) and outgoing (child) node
                        auto parentToken = std::find_if(tokens.begin(), tokens.end(), [](const std::pair<std::string, std::string> &pair) { return pair.first == "PARENT"; });
                        auto childToken = std::find_if(tokens.begin(), tokens.end(), [](const std::pair<std::string, std::string> &pair) { return pair.first == "CHILD"; });

                        if (parentToken != tokens.end() && childToken != tokens.end())
                        {
                            // get iterator on incoming and outgoing node via ID search
                            auto parentNode = std::find_if(_nodes.begin(), _nodes.end(), [&parentToken](GraphNode *node) { return node->GetID() == std::stoi(parentToken->second); });
                            auto childNode = std::find_if(_nodes.begin(), _nodes.end(), [&childToken](GraphNode *node) { return node->GetID() == std::stoi(childToken->second); });

                            // create new edge
                            GraphEdge *edge = new GraphEdge(id);
                            std::cout << "Allocates edge: "<< &edge <<" on address: " << edge << std::endl;
                            edge->SetChildNode(*childNode);
                            edge->SetParentNode(*parentNode);
                            _edges.push_back(edge);

                            // find all keywords for current node
                            AddAllTokensToElement("KEYWORD", tokens, *edge);

                            // store reference in child node and parent node
                            (*childNode)->AddEdgeToParentNode(edge);
                            (*parentNode)->AddEdgeToChildNode(edge);
                        }

                        ////
                        //// EOF STUDENT CODE
                    }
                }
                else
                {
                    std::cout << "Error: ID missing. Line is ignored!" << std::endl;
                }
            }
        } // eof loop over all lines in the file

        file.close();

    } // eof check for file availability
    else
    {
        std::cout << "File could not be opened!" << std::endl;
        return;
    }

    //// STUDENT CODE
    ////

    // identify root node
    GraphNode *rootNode = nullptr;
    for (auto it = std::begin(_nodes); it != std::end(_nodes); ++it)
    {
        // search for nodes which have no incoming edges
        if ((*it)->GetNumberOfParents() == 0)
        {

            if (rootNode == nullptr)
            {
                rootNode = *it; // assign current node to root
                std::cout <<"rootNode: " << &rootNode <<": receives *it: "<< &it <<":on address: "<< *it << std::endl;                
            }
            else
            {
                std::cout << "ERROR : Multiple root nodes detected" << std::endl;
            }
        }
         }

    // add chatbot to graph root node
    _chatBot->SetRootNode(rootNode);
    rootNode->MoveChatbotHere(_chatBot);
    /*Isoni*/ std::cout <<"Exit LoadAnswerGraphFromFile(string)"<< std::endl;
   
    ////
    //// EOF STUDENT CODE
}

void ChatLogic::SetPanelDialogHandle(ChatBotPanelDialog *panelDialog)
{    /*Isoni*/ //std::cout <<"Enter $etPanelDialogHandle(ChatBotPanelDialog *)"<< std::endl;
    _panelDialog = panelDialog;
    /*change*/ //panelDialog = nullptr;
    /*Isoni*/ std::cout <<"_panelDialog: " << &_panelDialog <<": receives panelDialog: "<< &panelDialog <<": on address: "<< panelDialog << std::endl;
    /*Isoni*/ //std::cout <<"Exit SetPanelDialogHandle(ChatBotPanelDialog *)"<< std::endl;
}

void ChatLogic::SetChatbotHandle(ChatBot *chatbot)
{    /*Isoni*/ //std::cout <<"Enter SetChatbotHandle(ChatBot *)"<< std::endl;
    _chatBot = chatbot;
    /*change*/ //chatbot = nullptr;
    /*Isoni*/ std::cout <<"_chatBot: " << &_chatBot <<": receives chatBot: "<< &chatbot <<":on address: "<< chatbot << std::endl;
    /*Isoni*/ //std::cout <<"Exit SetChatbotHandle(ChatBot *)"<< std::endl;
}

void ChatLogic::SendMessageToChatbot(std::string message)
{   /*Isoni*/ //std::cout <<"Enter SetChatbotHandle(ChatBot *)"<< std::endl;
    _chatBot->ReceiveMessageFromUser(message);
    /*Isoni*/ //std::cout <<"Exit SetChatbotHandle(ChatBot *)"<< std::endl;
}

void ChatLogic::SendMessageToUser(std::string message)
{   /*Isoni*/ //std::cout <<"Enter SendMessageToUser(string)"<< std::endl;
    _panelDialog->PrintChatbotResponse(message);
    /*Isoni*/ //std::cout <<"Exit SendMessageToUser(string)"<< std::endl;
}

wxBitmap *ChatLogic::GetImageFromChatbot()
{    /*Isoni*/ //std::cout <<"Enter GetImageFromChatbot()"<< std::endl;
    return _chatBot->GetImageHandle();
    /*Isoni*/ //std::cout <<"Exit GetImageFromChatbot()"<< std::endl;
}
