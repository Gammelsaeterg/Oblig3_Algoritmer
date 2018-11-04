// Fra obligatorisk oppgave 2
#ifndef BINARYNODE_H
#define BINARYNODE_H
#include <iostream>
#include <math.h>
#include <ctime>

using namespace std;


//Binary search tree  /////////

namespace TheBinaryTree
{

template <class T>
class BinarySearchTree
{

private:

    struct Node
    {
        T key;
        Node* left;
        Node* right;
    };

    //Adds leaf
    void AddLeafPrivate(T key, Node* Ptr)
    {
        if(root == nullptr)
        {
            root = CreateLeaf(key);
        }
        else if(key < Ptr->key)
        {
            if(Ptr->left != nullptr)
            {
                AddLeafPrivate(key, Ptr->left);
            }
            else
            {
                Ptr->left = CreateLeaf(key);
            }
        }
        else if(key > Ptr->key)
        {
            if(Ptr->right != nullptr)
            {
                AddLeafPrivate(key, Ptr->right);
            }
            else
            {
                Ptr->right = CreateLeaf(key);
            }
        }
        else
        {
            std::cout << "The key " << key << " has already been added to the tree\n";
        }
    }


    Node* CreateLeaf(T key)
    {
        Node* n = new Node;
        n->key = key;
        n->left = nullptr;
        n->right = nullptr;

        return n;
    }


    Node* ReturnNode(T key)
    {
        return ReturnNodePrivate(key, root);
    }

    //Prints tree from left to right, which means from lowest to highest values
    void PrintInOrderPrivate(Node* Ptr)
    {
        if(root != nullptr)
        {
            //In-order traversal
            if (Ptr->left != nullptr)
            {
                PrintInOrderPrivate(Ptr->left);
            }

            std::cout << Ptr->key << ", ";

            if (Ptr->right != nullptr)
            {
                PrintInOrderPrivate(Ptr->right);
            }
        }
        else
        {
            std::cout << "The tree is empty \n";
        }
    }

    //Prints in pre-order
    void PrintInPreOrderPrivate(Node* Ptr)
    {
        if(root != nullptr)
        {
            //Pre-order traversal
            std::cout << Ptr->key << ", ";
            if (Ptr->left != nullptr)
            {
                PrintInOrderPrivate(Ptr->left);
            }

            if (Ptr->right != nullptr)
            {
                PrintInOrderPrivate(Ptr->right);
            }
        }
        else
        {
            std::cout << "The tree is empty \n";
        }
    }


    Node* ReturnNodePrivate(T key, Node* Ptr)
    {
        if(Ptr != nullptr)
        {
            if(Ptr->key == key)
            {
                return Ptr;
            }
            else
            {
                if(key < Ptr->key)
                {
                    return ReturnNodePrivate(key, Ptr->left);
                }
                else
                {
                    return ReturnNodePrivate(key, Ptr->right);
                }
            }
        }
        else
        {
            return nullptr;
        }
    }

    //Finds smallest node by recursing to the left
    T FindSmallestPrivate(Node* Ptr)
    {
        if(root == nullptr)
        {
            std::cout << "The tree is empty\n";
            return -1000;
        }
        else
        {
            if(Ptr->left != nullptr)
            {
                return FindSmallestPrivate(Ptr->left);
            }
            else
            {
                return Ptr->key;
            }
        }
    }

    //Searches for node to remove
    void RemoveNodePrivate(T key, Node* parent)
    {
        if (root != nullptr)
        {
            if(root->key == key)
            {
                RemoveRootMatch();
            }
            else
            {
                if (key < parent->key && parent->left != nullptr)
                {
                    parent->left->key == key ?
                    RemoveMatch(parent, parent->left, true) :
                    RemoveNodePrivate(key, parent->left);
                }
                else if (key > parent->key && parent->right != nullptr)
                {
                    parent->right->key == key ?
                    RemoveMatch(parent, parent->right, false) :
                    RemoveNodePrivate(key, parent->right);
                }
                else
                {
                    std::cout << "The key " << key << " was not found in the tree\n";
                }
            }
        }
        else
        {
            std::cout << "The tree is empty\n";
        }
    }


    void RemoveRootMatch()
    {
        if (root != nullptr)
        {
            Node* delPtr = root;
            int rootKey = root->key;
            int smallestKeyInRightSubTree;

            // Case 0 - 0 children, deletes the leaf
            if(root->left == nullptr && root->right == nullptr)
            {
                root = nullptr;
                delete delPtr;
            }

            // Case 1 - 1 child, sets the lower right or left pointer to be root, then deletes old pointer
            else if(root->left == nullptr && root->right != nullptr)
            {
                root = root->right;
                delPtr->right = nullptr;
                delete delPtr;
                std::cout << "The root node conatining key " << rootKey << " was deleted. "
                          << "The new root contains key " << root->key << std::endl;
            }
            else if(root->left != nullptr && root->right == nullptr)
            {
                root = root->left;
                delPtr->left = nullptr;
                delete delPtr;
                std::cout << "The root node with key " << rootKey << " was deleted. "
                          << "The new root contains key " << root->key << std::endl;
            }

            // Case 2 - 2 children, finds smallest node in the right subtree, replaces node to be deleted with it, and then removes
            // the node to be deleted by recursing
            else
            {
                smallestKeyInRightSubTree = FindSmallestPrivate(root->right);
                RemoveNodePrivate(smallestKeyInRightSubTree, root);
                root->key = smallestKeyInRightSubTree;
                std::cout << "The root node containing key " << rootKey
                          << " was overwritten with key " << root->key << std::endl;
            }
        }
        else
        {
            std::cout << "Cannot remove root. The tree is empty\n";
        }
    }


    void RemoveMatch(Node* parent, Node* match, bool left)
    {
        if (root != nullptr)
        {
            Node* delPtr;
            int matchKey = match->key;
            int smallestKeyInRightSubTree;

            //Case 0 - 0 Children, deletes the leaf
            if(match->left == nullptr && match->right == nullptr)
            {
                delPtr = match;
                left == true ? parent->left = nullptr : parent->right = nullptr;
                delete delPtr;
                std::cout << "The node containing key " << matchKey
                          << " was removed\n";
            }

            // Case 1 - 1 child, sets the lower right or left pointer to replace the node that is to be deleted
            else if (match->left == nullptr && match->right != nullptr)
            {
                left == true ? parent->left = match->right : parent = match->right;
                match->right = nullptr;
                delPtr = match;
                delete delPtr;
                std::cout << "The node containing key " << matchKey
                          << " was removed\n";
            }
            else if (match->left != nullptr && match->right == nullptr)
            {
                left == true ? parent->left = match->left : parent = match->left;
                match->left = nullptr;
                delPtr = match;
                delete delPtr;
                std::cout << "The node containing key " << matchKey
                          << " was removed\n";
            }

            // Case 2 - 2 Children, finds smallest node in the right subtree, replaces node to be deleted with it, and then removes
            // the node to be deleted by recursing
            else
            {
                smallestKeyInRightSubTree = FindSmallestPrivate(match->right);
                RemoveNodePrivate(smallestKeyInRightSubTree, match);
                match->key = smallestKeyInRightSubTree;
                std::cout << "The node containing key " << matchKey
                          << " was removed\n";
            }
        }
        else
        {
            std::cout << "Cannot remove root. The tree is empty\n";
        }
    }

    //Post-order traversing to delete the tree
    void RemoveSubtree(Node* Ptr)
    {
        if(Ptr != nullptr)
        {
            //Post-order traversing
            if (Ptr->left != nullptr)
            {
                RemoveSubtree(Ptr->left);
            }
            if (Ptr->right != nullptr)
            {
                RemoveSubtree(Ptr->right);
            }
            //std::cout << "Deleting the node containing key " << Ptr->key << std::endl;
            delete Ptr;
        }
    }

public:
    Node* root;

    clock_t Begin;
    clock_t End;

    BinarySearchTree()
    {
        Begin = clock();
        root = nullptr;
    }

    ~BinarySearchTree()
    {
        End = clock();
        double ElapsedSecs = double(End - Begin) / CLOCKS_PER_SEC;
        cout << endl << "Time elapsed: " << ElapsedSecs << endl;
        RemoveSubtree(root);
    }

    void AddLeaf(T key)
    {
        AddLeafPrivate(key, root);
    }

    void PrintInOrder()
    {
        PrintInOrderPrivate(root);
    }

    void PrintPreOrder()
    {
        PrintInPreOrderPrivate();
    }

    T ReturnRootKey()
    {
        return root->key;
    }

    void PrintChildren(T key)
    {
        Node* Ptr = ReturnNode(key);

        if(Ptr != nullptr)
        {
            std::cout << "Parent Node = " << Ptr->key << std::endl;

            Ptr->left == nullptr ?
                        std::cout << "Left child = NULL\n" :
                        std::cout << "Left child = " << Ptr->left->key << std::endl;

            Ptr->right == nullptr ?
                        std::cout << "Right child = NULL\n" :
                        std::cout << "Right child = " << Ptr->right->key << std::endl;
            std::cout << std::endl;
        }
        else
        {
            std::cout << "Key " << key << " is not in the tree\n";
        }
    }

    T FindSmallest()
    {
        return FindSmallestPrivate(root);
    }

    void RemoveNode(T key)
    {
        RemoveNodePrivate(key, root);
    }


    //Borrowed and edited code 2: https://stackoverflow.com/a/50650932
    void PrintTree(Node* root)
    {
            if (root == nullptr)
            {
                    return;
            }

            cout << root->key << endl;
            PrintSubtree(root, "");
            cout << endl;
    }

    void PrintSubtree(Node* root, const string& prefix)
    {
            if (root == nullptr)
            {
                    return;
            }


            bool hasLeft = (root->left != nullptr);
            bool hasRight = (root->right != nullptr);

            if (!hasLeft && !hasRight)
            {
                    return;
            }

            cout << prefix;
            cout << ((hasLeft  && hasRight) ? "├── " : "");
            cout << ((!hasLeft && hasRight) ? "└── " : "");

            if (hasRight)
            {
                    bool printStrand = (hasLeft && hasRight && (root->right->right != nullptr || root->right->left != nullptr));
                    string newPrefix = prefix + (printStrand ? "│   " : "    ");
                    cout << root->right->key << endl;
                    PrintSubtree(root->right, newPrefix);
            }

            if (hasLeft)
            {
                    cout << (hasRight ? prefix : "") << "└── " << root->left->key << endl;
                    PrintSubtree(root->left, prefix + "    ");
            }
    }
    //End of borrowed code 2
};
}

#endif // BINARYNODE_H
