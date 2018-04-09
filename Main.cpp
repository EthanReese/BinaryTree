//An algorithm to create a binary search tree
//Created by: Ethan Reese
//March 13, 2017

#include <cstring>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <deque>
#include <list>
#include <queue>

struct Node{
     int data;
     Node* left;
     Node* right;
};

struct Node* addTree(int element, Node* &current);
void printTree(Node* head);
bool deleteElement(Node* &head, int element);
struct Node* newNode(int element);
void fixTree(Node* &current);

using namespace std;

int main(){
     bool going = true;
     //Keep getting inputs until the user asks to stop
     int counter = 0;
     char* input;
     Node* head = NULL;
     cout << "Enter the character I if you would like to be prompted for input: " << endl;
     char* input_1;
     input_1 = new char[80];
     cin >> input_1;
     if(strcmp(input_1, "I") == 0){
          cout << "Enter your numbers and enter the character N when done." << endl;
             while(going){
                  cout << "Number: ";
                  input = new char[80];
                  cin >> input;
                  //If the user inputs the N then it needs to stop
                  if(strcmp(input, "N") == 0){
                       going = false;
                       delete input;
                       printTree(head);
                  }
                  else if(counter == 100){
                       going = false;
                       delete input;
                       printTree(head);
                  }
                  else if(strcmp(input, "0") == 0){
                       //If its zero is screws things up so just ignore it since its not in the range anyway.
                  }
                  else{
                          //put the input into a string stream to convert it into aninteger for comparison
                          stringstream convert;
                          convert << input;
                          int element = 0;
                          convert >> element;
                          counter++;
                          delete input;
                          head = addTree(element, head);
                  }
             }
     }
     else{
          cout << "Please enter the filename of the file you would like to read in: ";
          input = new char[1000];
          cin >> input;
          //Create a stream to open the file
          ifstream inFile;
          inFile.open(input);
          if(!inFile){
               return 1;
          }
          int x;
          while(inFile >> x){
               head = addTree(x, head);
          }
          printTree(head);
          delete input;
     }
         cout << "Enter any integers that you would like to delete from the tree and type 'done' to quit and 'print' to print";
     while(true){
          cout << "Command: ";
          char* input = new char[80];
          cin >> input;
          //If the user wants to quit let them
          if(strcmp(input, "done") == 0){
               return 1;
               delete input_1;
          }
          else if(strcmp(input, "print") == 0){
               printTree(head);
          }
          else{
               stringstream convert;
               convert << input;
               int number = 0;
               convert >> number;
               delete[] input;
               //If the number is in the tree then we're all good, but if it isn't give the user a heads up
               if(!deleteElement(head, number)){
                    cout << "That value is not in the tree" << endl;
               }
          }
     }
}

//Add an input element into the tree
struct Node* addTree(int element, Node* &current){
     //If there isn't anything in the tree yet
     if(current == NULL){
          return(newNode(element));
     }
     //Keep going down the tree until it finds the right spot
     else{
          //If the new element is less than the current node then it needs to go down
          if(element <= current->data){
               current->left = addTree(element, current->left);
          }
          //Otherwise it needs to go left
          else{
               current->right = addTree(element, current->right);
          }
          //return the node pointer to make the recursion work
          return current;
     }
         
}
//Shortcut to initialize new nodes as they are created
struct Node* newNode(int data){
     struct Node* node = new struct Node();
     node->data = data;
     node->right = NULL;
     node->left = NULL;
     return node;
}
//Print out the tree in nice tree form
void printTree(Node* node){
     queue<Node*> q;
     q.push(node);
     cout << "Tree: " << endl;

     bool moreonlevel = true;
     //Keep going while there are still nodes on the level.
     while(moreonlevel){
          int levelCount = q.size();
          moreonlevel = false;
          while(levelCount > 0){
                  Node* n = q.front();
                  q.pop();
                  if(n == NULL){
                         cout << "_ ";
                         q.push(NULL);
                         q.push(NULL);
                  }
                  else{
                          //Say that there are more nodes that can be checked and add the proper nodes to the tree.
                          moreonlevel = true;
                          cout << n->data << " ";
                          q.push(n->left);
                          q.push(n->right);
                  }
                  //It went through one of the levels so take the counter down.
                  levelCount--; 
          }
          //End of a tree level
          cout << endl;

     }
}
//Remove a single element from the tree
bool deleteElement(Node* &current, int element){
     //If there is nothing in the tree
     if(current == NULL){
          return false;
     }
     //Otherwise check the element of the tree for the value
     else{
          //Check the current node for the value
          if(current->data == element){
               current->data = 0;
               fixTree(current);
               return true;
          }
          //Keep going down the tree looking for the value
          else{
               //Go down the correct sides of the subtree looking for the value
               if(element < current->data){
                    return deleteElement(current->left, element);
               }
               else{
                       return deleteElement(current->right, element);
               }
          }
     }

}
//Fix tree so that its right
void fixTree(Node* &current){
        int minimum = 0;
        Node* min = current;
        Node* node = current;
        Node* minPar = current;
        //If there exists a right subtree than bring up the min value from that subtree
        if(current->right != NULL){
             minimum = current->right->data;
             min = current->right;
             node = current->right;
             minPar = current;
             while(node != NULL){
                     //Find the minimum value from the right subtree
                     if(node->left != NULL){
                         Node* temp = node;
                          node = node->left;
                          if(node->data < minimum){
                                  minimum = node->data;
                                  min = node;
                                  minPar = temp;
                         }
                     }
                     else{
                             break;
                     }
             }
        }
        //Otherwise its going to have to take the max value from the left subtree
        else if(current->left != NULL){
               minimum = current->left->data;
               min = current->left;
               node = current->left;
               minPar = current;
               while(node->right != NULL){
                    Node* temp = node;
                    node = node->right;
                    //The min is backwards but its fine it makes it easier
                    if(node->data > minimum){
                         minPar = temp;
                         minimum = node->data;
                         min = node;
                    }
               }
        }
        //Otherwise its the very bottom so it can just delete
        else{
               delete current;
               current = NULL;
               return;
        }
    //Go through and take the data from the min node and put it into the current node and maybe readjust
    current->data = minimum;
    min -> data = 0;
    //If there are children readjust it otherwise just destroy the node
     if(min->left != NULL || min->right != NULL){ 
             fixTree(min);
     }
     else{
          //In hindsight if I had thought this through better it would all be redundant
          if(minPar->left == min) minPar->left = NULL;
          if(minPar->right == min) minPar->right = NULL;
          delete min;
          min = NULL;
     }
}
