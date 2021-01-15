#include "graphnode.h"
#include "graphedge.h"
#include <iostream> /*Isoni*/
GraphEdge::GraphEdge(int id)
{   /*Isoni*/ std::cout <<"Enter Constructor GraphEdge(int) " << std::endl;
    _id = id;
    /*Isoni*/ //std::cout <<"Exit Constructor GraphEdge(int) " << std::endl;
}

void GraphEdge::SetChildNode(GraphNode *childNode)
{    /*Isoni*/ std::cout <<"Enter SetChildNode(GraphNode *) " << std::endl;
    _childNode = childNode;
    /*change*///childNode = nullptr;
    /*Isoni*/ std::cout <<"_childNode: " << &_childNode <<": receives childNode: "<< &childNode <<": on address: "<< childNode << std::endl;
    /*Isoni*/ //std::cout <<"Exit SetChildNode(GraphNode *) " << std::endl;
}

void GraphEdge::SetParentNode(GraphNode *parentNode)
{    /*Isoni*/ //std::cout <<"SetParentNode(GraphNode *) " << std::endl;
    _parentNode = parentNode;
    std::cout <<"_parentNode: " << &_parentNode <<": receives childNode: "<< &parentNode <<": on address: "<< parentNode << std::endl;
    /*change*///parentNode = nullptr;
    /*Isoni*/ //std::cout <<"Shares parentNode adress  " << parentNode << std::endl;
    /*Isoni*/ //std::cout <<"Exit SetParentNode(GraphNode *) " << std::endl;
}

void GraphEdge::AddToken(std::string token)
{    /*Isoni*/ //std::cout <<"Enters AddToken(string) " << std::endl;
    _keywords.push_back(token);
    /*Isoni*/ //std::cout <<"Exit AddToken(string) " << std::endl;
}