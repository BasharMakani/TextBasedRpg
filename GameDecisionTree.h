#ifndef GAMEDECISIONTREE_H
#define GAMEDECISIONTREE_H


#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Node.h"
#include "Story.h"
#include <vector>
using namespace std;


template <typename T>
class GameDecisionTree
{
private:
   Node<T> *root;


   unordered_map<int, Node<T> *> decisionTreeMap;


public:
   GameDecisionTree() : root(nullptr) {}


   // Function to load story data from a text file and build the binary tree
   void loadStoryFromFile(const string &filename, char delimiter)
   {
       string line;
       ifstream file(filename);


       while (getline(file, line))
       {


           stringstream ss(line); // converts the line to a stringstream
           string item;
           vector<string> components;


           while (getline(ss, item, delimiter))
           { // fill the vector with the various parts from our line
               components.push_back(item);
           }


           if (components.size() != 4)
           {
               continue;
           }


           int eventNumber = stoi(components[0]);
           string description = components[1];
           int rightEventNumber = stoi(components[2]);
           int leftEventNumber = stoi(components[3]);


           Story decision(description, eventNumber, leftEventNumber, rightEventNumber);


           Node<T>* newNode = new Node<T>(decision);


           decisionTreeMap[eventNumber] = newNode;


           if (eventNumber == 1) {
               root = newNode; // Set root if this is the root event
           }
       }


       file.close();


       for (auto &pair : decisionTreeMap) // asign the left and right nodes for all nodes in the tree
       {
           Node<T> *currentNode = pair.second;
           int leftDecision = currentNode->data.leftEventNumber;
           int rightDecision = currentNode->data.rightEventNumber;


           if (leftDecision != -1 && decisionTreeMap.count(leftDecision))
           {
               currentNode->left = decisionTreeMap[leftDecision];
           }
           if (rightDecision != -1 && decisionTreeMap.count(rightDecision))
           {
               currentNode->right = decisionTreeMap[rightDecision];
           }
       }
   }


   // Function to start the game and traverse the tree based on user input
   void playGame()
   {
       if (!root)
       {
           cout << "Error encountered The tree is empty load data" << endl;
           return;
       }


       Node<T>* currentNode = root;


       while (currentNode)
       {
           cout << currentNode->data.description << endl;


           if (currentNode->data.leftEventNumber == -1 && currentNode->data.rightEventNumber == -1)
           {
               cout << "End of Story." << endl;
               break;
           }


           cout << "Option 1 or Option 2 (1/2)";
           string userChoice;
           cin >> userChoice;


           while (userChoice != "1" && userChoice != "2") {
               cout << "Invalid input. Please enter 1 or 2: ";
               cin >> userChoice;
           }


           if (userChoice == "2" && currentNode->left) {
               currentNode = currentNode->left;
           } else if (userChoice == "1" && currentNode->right) {
               currentNode = currentNode->right;
           } else {
               cout << "Invalid path selection. Ending game." << endl;
               break;
       }
       }
   }
};


#endif // GAMEDECISIONTREE_H

