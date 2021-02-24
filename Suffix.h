#pragma once

#include<iostream>
#include<string>
#include<unordered_map>
#include<memory>

// To name the nodes
int total_nodes = 0;

/*
	SuffixNode class represents the Node in the suffix Tree and also
	takes care of the Edge strings. Each Suffix Node except Root is
	a Node with a tail(edge string)
*/
struct SuffixNode {


	/*

		@description:
			Constructor used to make Root Nodes

	*/
	SuffixNode() :
		suffixLink(this), stringStartOffset(-1), stringEndOffset(std::make_shared<int>(-1)) {
		nodeName = std::to_string(total_nodes);
		total_nodes++;
	}

	/*

		@startOffset:	the starting index of the edge
		@endOffset:		the ending index of the edge
		@suffix_Link:	the node that will be pointed by this node's suffixLink

		@description:
			Creates a Suffix Node

	*/
	SuffixNode(int startOffset, std::shared_ptr<int> endOffset, SuffixNode* suffix_Link) :
		stringStartOffset(startOffset), stringEndOffset(endOffset), suffixLink(suffix_Link) {
		nodeName = std::to_string(total_nodes);
		total_nodes++;
	}

	/*

		@charLinkNode:	the character for which we are checking the NodeLink, the starting character for the edge that we are searching

		@return:	boolean value stating whether edge link starting with character exists from the node

		@description:
			Checks if a edge exists starting with specified character from the node

	*/
	bool linkNodeExists(char charLinkNode) {
		return (childrenNodes.find(charLinkNode) != childrenNodes.end());
	}


	/*

		@edgeChar:	the starting character for the edge of the child node
		@node:		the child node that you want to add

		@description:
			Simply stores the shared_ptr of the child node into the hash table for this node

	*/
	void addEdgeNode(char edgeChar, const std::shared_ptr<SuffixNode>& node) {
		childrenNodes[edgeChar] = node;
	}

	/*
		@return:	number of characters present on the edge of the node

		@description:
			Simply return the edge character length
	*/
	int edgeLength() {

		// edgeLength is inclusive index, so if we have a pair 0,0 for index "hello", it means 'h' character
		// it should consider 0 as inclusive, so substr should be called like substr(0,1)

		return (*stringEndOffset) - stringStartOffset + 1;
	}


	// Starting index of the Edge String
	int stringStartOffset;

	// Ending inclusive index for the SuffixString
	std::shared_ptr<int>stringEndOffset;

	// Suffix Link for the Suffix tree
	SuffixNode* suffixLink;

	// Hash Map which stores all the further linked nodes of the Suffix Tree
	// shared_ptr is used because the children nodes can change like when we split an edge to form a new Node and 2 Edges 
	std::unordered_map<char, std::shared_ptr<SuffixNode>> childrenNodes;

	// TODO Separate the printable elements helpers
	std::string nodeName;

};

/*
	SuffixTree implements the Suffix Tree and all the components needed
	This class handles all the apending of the characters into the suffix tree
*/
class SuffixTree {

public:

	/*

		@description:
			Simply initializes the SuffixTree Object, string or characters should be added using +=operator into tree

	*/
	SuffixTree() :
		suffLinkNeeded(nullptr),
		activeNode(&rootNode),   // Root node is the Active Node initially
		activeLength(0),    // 
		activeEdge(-1),  // Index of the character which represents the currently active character edge on the currently active node
		globalEndString(std::make_shared<int>(-1)), // The global End is initially -1, meaning no characters are present in suffix Tree
		remainingCharacters(0) {     //

	}

	/*
		@c:		the character you want to insert into SuffixTree

		@description:
			Adds the character into our suffix tree
	*/
	SuffixTree& operator+=(char c) {
		suffixString += c;
		addPrefix(suffixString.length() - 1);
		return *this;
	}

	/*
		@c:		the character you want to insert into SuffixTree

		@description:
			Adds the character into our suffix tree
	*/
	SuffixTree& operator+=(std::string str) {

		for (auto& c : str) {
			*this += c;
		}
		return *this;
	}


protected:

	/*
		@node:		suffix node that needs a suffix link

		@return:	void

		@description:
			This Function acts like a chain
			If no node was assigned to suffLinkNeeded, this function saves the node in that place
			If some node was saved in suffLinkNeeded, that node's suffixLink is updated with supplied function arguement node and
			that node is stored inside suffLinkNeeded
	*/
	void addSuffixLink(SuffixNode* node) {

		if (suffLinkNeeded) {
			suffLinkNeeded->suffixLink = (node);
		}

		suffLinkNeeded = node;
	}

	/*
		@characterIndex:	Index of the character that we want to insert as extra leaf by splitting the edge
		@nextNode:			The Node whose parent edge we want to split

		@return:			void

		@description:
			When we have to insert a new character as a leaf node into already existing edge string,
			we call this function with the character we want to insert and the Node whose parent edge has to be split
			The Edge is split and the new node has two children, the new leaf node with edge as characterIndex and
			old edge that was split

	*/
	void splitEdge(int characterIndex, std::shared_ptr<SuffixNode>& nextNode) {

		/*

			Example of how the Edge is split

														 (7,7)
														+---$
														|
			abcdefg					=>			abcd----+
			   0-6  							(0,3)   |
														+---efg$
														  (4,7)


		*/

		auto splitEdgeNode = std::make_shared<SuffixNode>(
			nextNode->stringStartOffset,	// Spliting Node's edge starts with the old node's start 
			std::make_shared<int>(nextNode->stringStartOffset + activeLength - 1),	// 
			&rootNode	//Default suffix link points to root
			);

		auto leafNode = std::make_shared<SuffixNode>(
			characterIndex,	// Edge starts with the new characterIndex 
			globalEndString,	// Has the globalEnd because it is a leaf node
			&rootNode
			);

		splitEdgeNode->addEdgeNode(suffixString[characterIndex], leafNode);

		nextNode->stringStartOffset += activeLength;

		splitEdgeNode->addEdgeNode(suffixString[nextNode->stringStartOffset], nextNode);

		activeNode->addEdgeNode(suffixString[activeEdge], splitEdgeNode);

		addSuffixLink(&(*splitEdgeNode));
	}


	/*

		@characterIndex:	the index of the character we want to insert into our suffix tree

		@description:
			Ukkonen's Suffix Tree algorithm to insert a character into our suffix tree
	*/
	void addPrefix(int characterIndex) {


		// Increase the number of characters that we have to add into suffix tree
		remainingCharacters++;

		// Rule 1 Extension gets taken care here, all the suffix leaf edges get the new suffix character automatically appended
		(*globalEndString)++;

		// Shifted the place of doing this
		// This was shifted because if we are walking down, we may flush this link unintentionally
		//suffLinkNeeded = nullptr;

		//Keep doing this if we have characters left
		while (remainingCharacters > 0) {


			if (activeLength == 0) {
				// It means we have to create a new node and add it as a childNode with the character as a start
				activeEdge = characterIndex;
			}



			// First Check if there is an outgoing adge with activeEdge index character

			if (!activeNode->linkNodeExists(suffixString[activeEdge])) {
				//the character link edge doesn't exist

				// create a new leaf node and save it as a child of the current active node
				activeNode->addEdgeNode(suffixString[characterIndex], std::make_shared<SuffixNode>(characterIndex, globalEndString, &rootNode));

				// The newly created leaf edge needs suffix link
				addSuffixLink(activeNode);

			}
			else {
				// the character already exists as a edge link
				auto nextNode = activeNode->childrenNodes[suffixString[activeEdge]];

				// Walk down if necessary
				// Walk down happens if we have activeLength more than the edge length of the activeEdge from Active Node,
				// We walk down further the links till active length becomes smaller than the edge length
				if (walkDown(*nextNode)) {
					// if we walk down, continue
					continue;
				}

				// Check if the the next character is same as the character we are trying to insert
				if (suffixString[nextNode->stringStartOffset + activeLength] == suffixString[characterIndex]) {

					// We have same character, so this is a show stopper, we don't have to do much in this iteration

					// Increment our activeLength because we found another common character on adge
					activeLength++;

					// We should add activeNode as the suffixLink for node that requires suffixLink in current iteration
					// This seems logical and is taken from this stackoverflow answer advice https://stackoverflow.com/a/14580102
					// Observation 3
					addSuffixLink(activeNode);
					break;
				}

				// We don't have same character at the activeLength, so we try to split the edge
				splitEdge(characterIndex, nextNode);

			}

			// We have inserted a character, so decrement the value
			remainingCharacters--;


			if (activeNode == &rootNode && activeLength > 0) {

				// If after insert the activeNode is RootNode and we still have a activeLength>0
				// We decrement activeLength for one place
				// shift the activeEdge character to right

				activeLength--;
				activeEdge = characterIndex - remainingCharacters + 1;
				//activeEdge++;
			}
			else {
				activeNode = &*(activeNode->suffixLink);
			}


		}
		// flush out any old pointer that maybe stored from previous iteration
		// TODO check if this safe to do here
		suffLinkNeeded = nullptr;

	}

	/*

		@Node:		the node whose edge is smaller than the activeLength and we want to go down the tree chain

		@return:	boolean value whether we walked down the tree chain or not

		@description:
			Checks if the Node Edge length is smaller than the active length
			If it is the case we adjust the activeNode, activeLength, activeEdge according to the chain we followed
			This keeps going till we have activeLength smaller than node edge length

	*/
	bool walkDown(SuffixNode& Node) {

		if (activeLength >= Node.edgeLength()) {

			// we skipped the character present in the edge, so adjust  the activeEdge too (shift it right to later characters)
			activeEdge += Node.edgeLength();

			// we skipped the characters present in the edge, so adjust the activeLength too
			activeLength -= Node.edgeLength();

			// We walked down to one of the children node, so make it active node now
			activeNode = &Node;

			return true;
		}

		return false;
	}


	/*virtual void loopStepFunction() {

	}*/

	//Stores the actual string that is used to make the suffix tree
	std::string suffixString;

	// Number of characters left to be inserted
	int remainingCharacters;

	// the offset we have to insert the next character from the active node
	int activeLength;

	// the index of the character that is the active Edge from the Active Node
	// This stores the index of the character from the suffixString, not the character itself
	int activeEdge;

	// Our currently activeNode, the place we insert new nodes during extensions
	SuffixNode* activeNode;

	// Represents the global end of the suffix string that we are building
	std::shared_ptr<int>globalEndString;

	// The Root Node for our suffix tree
	SuffixNode rootNode;

	// Stores the nodes that need suffixLink
	SuffixNode* suffLinkNeeded;
};

// Inorder to pause the console
void PauseConsole() {
	std::cout << "\n Press Enter to Continue\n\n";
	
	getchar();
}

/*
	PrintableSuffixTree Handles the Printing of the Suffix Tree just like tree command in linux for directories
*/
class PrintableSuffixTree : public SuffixTree {
public:

	// Same constructors are used
	using SuffixTree::SuffixTree;

	// Simply prints the Suffix Tree starting from RootNode
	void print() {
		print(rootNode);
	}

	//void loopStepFunction() {
	//	print();
	//}

	/*

		@_suffixString:	the string that you want to append into the suffix tree

		@description:
			This functions adds the string into suffix tree but also prints the tree after each insert of character

	*/
	void addStepWise(const std::string& _suffixString) {
		for (auto& ch : _suffixString) {
			(*this) += ch;
			print();
			PauseConsole();
		}
	}

private:

	/*

		@Node: the node to print

		@highlightLen: the amount to highlight the edge of the node

		@indent:	the indent amount for the node

		@description:
			this simply prints the node and also its children nodes too

	*/
	void print(SuffixNode& Node, int highlightLen = 0, std::string indent = " ") {
		using namespace std;

		// Stores the string to print the edge and the node, its suffix link relationship
		string curr_string;


		if (Node.stringStartOffset != -1) {
			// This if condition is to skip the root node, because root node has no edge
			// Only add if we have a valid start edge index

			if (highlightLen > 0) {
				// If we want to highlight edge of a node, we hightlight that amount using black text, red background
				// and whole edge string is highlighted with red text

				// NOTE if the print function is used when the hightlightLen is larger than the edgeLength,
				// whole string gets printed with highlightLen part highlighted

				curr_string += "\033[31m+-{";
				curr_string += ("\033[7m" + suffixString.substr(Node.stringStartOffset, highlightLen) + "\033[0m\033[31m");
				curr_string += suffixString.substr(Node.stringStartOffset + highlightLen - 1, Node.edgeLength() - highlightLen);
				curr_string += "}-\033[0m";
			}

			else {
				curr_string += ("+-{" + suffixString.substr(Node.stringStartOffset, Node.edgeLength()) + "}-"); // TODO check if +1 has to be removed now
			}


		}


		if (activeNode == &Node) {
			// If the node is the ActiveNode, hightlight the Node
			curr_string += ("\033[31;7m" + Node.nodeName + "\033[0m" + ">" + Node.suffixLink->nodeName);
		}
		else {
			curr_string += (Node.nodeName + ">" + Node.suffixLink->nodeName);
		}

		// Print the indent, so that tree gets printed with good formating
		// indent for printing the node edge string has to be smaller by one unit because, edge string has extra character '+' to be printed
		cout << indent.substr(0, indent.size() - 1) << curr_string << endl;



		// child nodes have a deeper indentation
		indent += string((Node.edgeLength() + Node.nodeName.length() + (Node.stringStartOffset > -1 ? 4 : -2)), ' ');

		// to check when we hit the last child node
		int i = 0;
		for (auto& edge : Node.childrenNodes) {
			// edge.first is the first character for the edge 
			// edge.second is the SuffixNode Reference

			if (activeNode == &Node && suffixString[activeEdge] == edge.first) {
				// if the node we are printing is active node, and we are going to print the node which is linked as ActiveEdge,
				// we print the child node with hightlightLen as the activeLen
				highlightLen = activeLength;
			}
			else {
				// Simple node, no hightlighting needed
				highlightLen = 0;
			}

			// Just for empty horizontal spacing line 
			cout << indent << "|" << endl;


			if (i == Node.childrenNodes.size() - 1)
				// If the child node is the last node, indent dones't need '|'
				print(*(edge.second), highlightLen, indent + " ");

			else
				// else we need to include this '|' in the children indent
				print(*(edge.second), highlightLen, indent + "|");


			i++;

		}


	}

};