#pragma once

#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include<memory>


namespace First {

	int total_nodes = 0;


	/*
		SuffixNode class represents the Node in the suffix Tree and also
		takes care of the Edge strings. Each Suffix Node except Root is
		a Node with a tail(edge string)
	*/
	class SuffixNode {


		// So that SuffixTree can access the private data members
		// friend class SuffixTree;

	public:

		// Constructor for creating the Root Node for a suffix tree
		SuffixNode() :
			suffixLink(*this), startEdgeIndex(-1), endEdgeIndex(std::make_shared<int>(-1)) {
			nodeName = std::to_string(total_nodes);
			total_nodes++;
		}

		SuffixNode(int start_EdgeIndex, std::shared_ptr<int>& end_EdgeIndex, SuffixNode& suffix_Link) :
			startEdgeIndex(start_EdgeIndex), endEdgeIndex(end_EdgeIndex), suffixLink(suffix_Link) {
			nodeName = std::to_string(total_nodes);
			total_nodes++;
		}

		// Checks if a edge exists starting with specified character from the node
		bool linkNodeExists(char charLinkNode) {
			return (linkedNodes.find(charLinkNode) != linkedNodes.end());
		}

		// Returns the pair of start and end index for the edge
		// Returns -1, -1 in case the 
		bool charExistsOnLinkedNodes(int activeEdgeChar) {

		}


		std::string& get_string() {

		}


		// Creates a new edge link from the node
		void addEdgeNode(char edgeChar, const std::shared_ptr<SuffixNode>& node) {
			linkedNodes[edgeChar] = node;

		}

		// Prints the Node and further connected nodes 
		// using the Tree structure template
		// the Suffix String has to be specified when calling, in order to save space
		void print(std::string& suffixString, std::string indent = " ") {
			using namespace std;
			std::string curr_string;


			if (startEdgeIndex != -1) {
				// Only add if we have a valid start edge index

				// endEdgeIndex is inclusive index, so if we have a pair 0,0 for index "hello"
				// it should consider 0 as inclusive, so substr should be called like substr(0,1)
				curr_string += ("+-{" + suffixString.substr(startEdgeIndex, (*endEdgeIndex) + 1) + "}-");
			}

			curr_string += (nodeName + ">" + suffixLink.nodeName);

			cout << indent.substr(0, indent.size() - 1) << curr_string << endl;

			// child nodes have a deeper indentation
			indent += std::string((*endEdgeIndex - startEdgeIndex + nodeName.length()), ' ');

			int i = 0;
			for (auto& edge : linkedNodes) {
				// edge.first is the first character for the edge 
				// edge.second is the SuffixNode Reference

				cout << indent << "|" << endl;
				if (i == linkedNodes.size() - 1) {
					edge.second->print(suffixString, indent + " ");
				}
				else {
					edge.second->print(suffixString, indent + "|");
				}

			}


		}

		void splitEdge() {

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


	class SuffixTree {

	public:

		SuffixTree(std::string _suffixString) :
			suffixString(_suffixString),
			activeNode(rootNode),   // Root node is the Active Node initially
			activeLength(0),    // 
			activeEdge(-1),  // Index of the character which represents the currently active character edge on the currently active node
			globalEndString(std::make_shared<int>(-1)), // The global End is initially -1, meaning no characters are present in suffix Tree
			remainingCharacters(0) {     //

			buildTree();
		}


		void addPrefix(int characterIndex) {
			remainingCharacters++;
			(*globalEndString)++;


			//Keep doing this if we have characters left
			while (remainingCharacters > 0) {

				// First Check if the 

				if (!activeNode.linkNodeExists(suffixString[characterIndex])) {
					//the character doesn't exists
					activeNode.addEdgeNode(suffixString[characterIndex], std::make_shared<SuffixNode>(characterIndex, globalEndString, rootNode));
					rule1_extension();
					remainingCharacters--;
				}
				else {
					// the character already exists

				}


			}

		}

		void print() {
			rootNode.print(suffixString);
		}

		void rule1_extension() {
			// Just by incrementing End, this gets taken care of

		}

		void rule2_extension() {

		}

		void rule3_extension() {

		}


		void buildTree() {

			for (int i = 0; i < suffixString.length(); i++) {
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


}

namespace Second {

	int total_nodes = 0;


	/*
		SuffixNode class represents the Node in the suffix Tree and also
		takes care of the Edge strings. Each Suffix Node except Root is
		a Node with a tail(edge string)
	*/
	struct SuffixNode {


		// So that SuffixTree can access the private data members
		// friend class SuffixTree;

	//public:

		// Constructor for creating the Root Node for a suffix tree
		SuffixNode() :
			suffixLink(this), stringStartOffset(-1), edgeLength(std::make_shared<int>(-1)) {
			nodeName = std::to_string(total_nodes);
			total_nodes++;
		}

		SuffixNode(int start_EdgeIndex, std::shared_ptr<int> end_EdgeIndex, SuffixNode* suffix_Link) :
			stringStartOffset(start_EdgeIndex), edgeLength(end_EdgeIndex), suffixLink(suffix_Link) {
			nodeName = std::to_string(total_nodes);
			total_nodes++;
		}

		// Checks if a edge exists starting with specified character from the node
		bool linkNodeExists(char charLinkNode) {
			return (childrenNodes.find(charLinkNode) != childrenNodes.end());
		}




		// Creates a new edge link from the node
		void addEdgeNode(char edgeChar, const std::shared_ptr<SuffixNode>& node) {
			childrenNodes[edgeChar] = node;

		}

		// Prints the Node and further connected nodes 
		// using the Tree structure template
		// the Suffix String has to be specified when calling, in order to save space
		void print(std::string& suffixString, std::string indent = " ") {
			using namespace std;
			std::string curr_string;


			if (stringStartOffset != -1) {
				// Only add if we have a valid start edge index

				// edgeLength is inclusive index, so if we have a pair 0,0 for index "hello"
				// it should consider 0 as inclusive, so substr should be called like substr(0,1)
				curr_string += ("+-{" + suffixString.substr(stringStartOffset, (*edgeLength) /*+ 1*/) + "}-"); // TODO check if +1 has to be removed now
			}

			curr_string += (nodeName + ">" + suffixLink->nodeName);

			cout << indent.substr(0, indent.size() - 1) << curr_string << endl;

			// child nodes have a deeper indentation
			indent += std::string((*edgeLength - stringStartOffset + nodeName.length()), ' ');

			int i = 0;
			for (auto& edge : childrenNodes) {
				// edge.first is the first character for the edge 
				// edge.second is the SuffixNode Reference

				cout << indent << "|" << endl;
				if (i == childrenNodes.size() - 1) {
					edge.second->print(suffixString, indent + " ");
				}
				else {
					edge.second->print(suffixString, indent + "|");
				}

			}


		}

		void splitEdge() {

		}

		//protected:
			// Starting index of the Edge String
		int stringStartOffset;

		// Ending inclusive index for the SuffixString
		std::shared_ptr<int>edgeLength;

		// Suffix Link for the Suffix tree
		SuffixNode* suffixLink;

		// Hash Map which stores all the further linked nodes of the Suffix Tree
		// shared_ptr is used because the children nodes can change like when we split an edge to form a new Node and 2 Edges 
		std::unordered_map<char, std::shared_ptr<SuffixNode>> childrenNodes;

		// TODO Separate the printable elements helpers
		std::string nodeName;

	};


	class SuffixTree {

	public:

		SuffixTree(std::string _suffixString) :
			suffLinkNeeded(nullptr),
			suffixString(_suffixString),
			activeNode(rootNode),   // Root node is the Active Node initially
			activeLength(0),    // 
			activeEdge(-1),  // Index of the character which represents the currently active character edge on the currently active node
			globalEndString(std::make_shared<int>(-1)), // The global End is initially -1, meaning no characters are present in suffix Tree
			remainingCharacters(0) {     //

			buildTree();
		}

	private:


		/*
			@node	: suffix node that needs a suffix link

			@return	: void
		
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
			@characterIndex	: Index of the character that we want to insert as extra leaf by splitting the edge

			@return			: void

			@description	:
				
		*/
		void splitEdge(int characterIndex, std::shared_ptr<SuffixNode>&nextNode) {

			auto splitEdgeNode = std::make_shared<SuffixNode>(
				nextNode->stringStartOffset,
				std::make_shared<int>(nextNode->stringStartOffset + activeLength),
				rootNode
				);

			auto leafNode = std::make_shared<SuffixNode>(
				characterIndex,
				globalEndString,
				rootNode
				);

			splitEdgeNode->addEdgeNode(characterIndex, leafNode);

			nextNode->stringStartOffset += activeLength;
			splitEdgeNode->addEdgeNode(suffixString[nextNode->stringStartOffset], nextNode);

			addSuffixLink(&(*nextNode));
		}

		void addPrefix(int characterIndex) {
			remainingCharacters++;

			(*globalEndString)++;

			suffLinkNeeded = nullptr;

			//Keep doing this if we have characters left
			while (remainingCharacters > 0) {

				if (activeLength == 0) {
					activeEdge = characterIndex;
				}



				// First Check if there is an outgoing adge with activeEdge index character

				if (!activeNode.linkNodeExists(suffixString[activeEdge])) {
					//the character link edge doesn't exist

					activeNode.addEdgeNode(suffixString[characterIndex], std::make_shared<SuffixNode>(characterIndex, globalEndString, rootNode));


				}
				else {
					// the character already exists as a edge link
					auto nextNode = activeNode.childrenNodes[suffixString[activeEdge]];

					// Walk down if necessary
					// if we walk down, continue
					if (walkDown()) {
						continue;
					}

					if (nextNode->stringStartOffset + activeLength == characterIndex) {
						activeLength++;
						addSuffixLink(&activeNode);
						break;
					}

					// We don't have same character  at the activeLength, so we try to split the edge
					splitEdge(characterIndex, nextNode);

				}
					
					remainingCharacters--;



			}

		}

		bool walkDown() {
			return false;
		}

		void print() {
			rootNode.print(suffixString);
		}

		void rule1_extension() {
			// Just by incrementing End, this gets taken care of

		}

		void rule2_extension() {

		}

		void rule3_extension() {

		}


		void buildTree() {

			for (int i = 0; i < suffixString.length(); i++) {
				addPrefix(i);
			}
		}

	private:

		std::string suffixString;

		// Number of characters left to be inserted
		int remainingCharacters;

		// the offset we have to insert the next character from the active node
		int activeLength;

		// the index of the character that is the active Edge from the Active Node
		// This stores the index of the character from the suffixString, not the character itself
		int activeEdge;


		SuffixNode& activeNode;

		std::shared_ptr<int>globalEndString; // Represents the global end of the suffix string that we are building

		SuffixNode rootNode;

		SuffixNode* suffLinkNeeded;
	};


}
