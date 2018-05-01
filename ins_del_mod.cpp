
#include <bits/stdc++.h>
using namespace std;

const int ALPHABET_SIZE = 26;

// trie node
struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];

    bool isEndOfWord;
};

// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode(void)
{
    struct TrieNode *pNode =  new TrieNode;

    pNode->isEndOfWord = false;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;

    return pNode;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just
// marks leaf node
void insert(struct TrieNode *root, string key)
{
    struct TrieNode *pCrawl = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
    }

    pCrawl->isEndOfWord = true;
}

// Returns true if key presents in trie, else
// false
/*bool search(struct TrieNode *root, string key)
{
    struct TrieNode *pCrawl = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!pCrawl->children[index])
            return false;

        pCrawl = pCrawl->children[index];
    }

    return (pCrawl != NULL && pCrawl->isEndOfWord);
}*/


// function to check if current node is leaf node or not
bool isLeafNode(struct TrieNode* root)
{
    return root->isEndOfWord != false;
}


void display(struct TrieNode* root, char str[], int level)
{
    // If node is leaf node, it indiicates end
    // of string, so a null charcter is added
    // and string is displayed
    if (isLeafNode(root))
    {
        str[level] = '\0';
        cout << str << endl;
    }

    int i;
    for (i = 0; i < ALPHABET_SIZE; i++)
    {
        // if NON NULL child is found
        // add parent key to str and
        // call the display function recursively
        // for child node
        if (root->children[i])
        {
            str[level] = i + 'a';
            display(root->children[i], str, level + 1);
        }
    }
}


// Driver
int main()
{
    // Input keys (use only 'a' through 'z'
    // and lower case)
    cout<<"Enter no. of names(<20)"<<endl;
    int n;
    cin>>n;
    string name[n];

    for(int i=0;i<n;i++)
    {
        cout<<"Enter "<< i+1<<"th name:"<<endl;
        cin>>name[i];
    }

    struct TrieNode *root = getNode();


        for (int i = 0; i < n; i++)
        insert(root, name[i]);
        cout<<"\n\n"<<endl;

        int level = 0;
        char str[20];
        display(root, str, level);


        return 0;
}
