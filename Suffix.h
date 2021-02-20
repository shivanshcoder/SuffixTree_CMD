#pragma once

#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include<memory>

int total_nodes=0;


/*
    SuffixNode class represents the Node in the suffix Tree and also
    takes care of the Edge strings. Each Suffix Node except Root is
    a Node with a tail(edge string)  
*/
class SuffixNode{


    // So that SuffixTree can access the private data members
    // friend class SuffixTree;

public:

    // Constructor for creating the Root Node for a suffix tree
    SuffixNode():
        suffixLink(*this), startEdgeIndex(-1), endEdgeIndex(std::make_shared<int>(-1)){
            nodeName = std::to_string(total_nodes);
            total_nodes++;
        }

    SuffixNode(int start_EdgeIndex, std::shared_ptr<int>&end_EdgeIndex, SuffixNode& suffix_Link):
        startEdgeIndex(start_EdgeIndex), endEdgeIndex(end_EdgeIndex), suffixLink(suffix_Link){
            nodeName = std::to_string(total_nodes);
            total_nodes++;
    }

    // Checks if a edge exists starting with specified character from the node
    bool linkNodeExists(char charLinkNode){
        return (linkedNodes.find(charLinkNode) != linkedNodes.end());
    }

    bool charOnEdgeExists(){
        
    }

    // Creates a new edge link from the node
    void addEdgeNode(char edgeChar,const std::shared_ptr<SuffixNode>& node){
        linkedNodes[edgeChar]=node;
        
    }

    // Prints the Node and further connected nodes 
    // using the Tree structure template
    // the Suffix String has to be specified when calling, in order to save space
    void print(std::string& suffixString, std::string indent = " "){
        using namespace std;
        std::string curr_string;

        
        if(startEdgeIndex != -1){
            // Only add if we have a valid start edge index

            // endEdgeIndex is inclusive index, so if we have a pair 0,0 for index "hello"
            // it should consider 0 as inclusive, so substr should be called like substr(0,1)
            curr_string +=( "+-{" + suffixString.substr(startEdgeIndex, (*endEdgeIndex)+1) + "}-");
        }

        curr_string += (nodeName + ">" + suffixLink.nodeName);
        
        cout << indent.substr(0, indent.size()-1) << curr_string << endl;

        // child nodes have a deeper indentation
        indent += std::string((*endEdgeIndex - startEdgeIndex + nodeName.length()) , ' ');
        
        int i=0;
        for(auto &edge : linkedNodes){
            // edge.first is the first character for the edge 
            // edge.second is the SuffixNode Reference

            cout << indent << "|" << endl;
            if(i == linkedNodes.size()-1 ){
                edge.second->print(suffixString, indent+" ");
            }
            else{    
                edge.second->print(suffixString, indent+"|");
            }
             
        }
        

    }

    void splitEdge(){

    }

protected:
    // Starting index of the Edge String
    int startEdgeIndex;

    // Ending inclusive index for the SuffixString
    std::shared_ptr<int>endEdgeIndex;

    // Suffix Link for the Suffix tree
    SuffixNode& suffixLink;

    // Hash Map which stores all the further linked nodes of the Suffix Tree
    std::unordered_map<char, std::shared_ptr<SuffixNode>> linkedNodes; 
    
    // TODO Separate the printable elements helpers
    std::string nodeName;

};


class SuffixTree{

public:

    SuffixTree(std::string _suffixString):
        suffixString(_suffixString),   
        activeNode(rootNode),   // Root node is the Active Node initially
        activeLength(0),    // 
        activeEdge(-1),  // Index of the character which represents the currently active character edge on the currently active node
        globalEndString(std::make_shared<int>(-1)), // The global End is initially -1, meaning no characters are present in suffix Tree
        remainingCharacters(0){     //

            buildTree();
    }

    void addPrefix(int characterIndex){
        remainingCharacters++;
        (*globalEndString)++;


        //Keep doing this if we have characters left
        while(remainingCharacters>0){
            if(! activeNode.linkNodeExists(suffixString[characterIndex])){
                //the character doesn't exists
                activeNode.addEdgeNode(suffixString[characterIndex], std::make_shared<SuffixNode>(characterIndex,globalEndString, rootNode));
                rule1_extension();
                remainingCharacters--;
            }
            else{
                // the character already exists

            }


        }

    }

    void print(){
        rootNode.print(suffixString);
    }

    void rule1_extension(){
        // Just by incrementing End, this gets taken care of

    }

    void rule2_extension(){

    }

    void rule3_extension(){

    }


    void buildTree(){

        for(int i = 0; i<suffixString.length(); i++){
            addPrefix(i);
        }
    }

private:

    std::string suffixString;

    int remainingCharacters;
    int activeLength;
    int activeEdge;
    SuffixNode& activeNode;

    std::shared_ptr<int>globalEndString; // Represents the global end of the suffix string that we are building

    SuffixNode rootNode;
};

