
#include <stdio.h>
#include <stdlib.h>
#define ALPHASET_SIZE 26
#define ARRAY_SIZE 1010
#define STRING_SIZE 25
using namespace std;
typedef struct trie_node
{
    int count;
    trie_node *children[ALPHASET_SIZE];
}*trie;

trie_node* create_trie_node()
{
    trie_node* pNode = (trie_node* )malloc(sizeof(trie_node));
    pNode->count = 0;
    for(int i = 0; i < ALPHASET_SIZE; i++)
        pNode->children[i] = NULL;
    return pNode;
}

void trie_insert(trie root,char * key)
{
    trie_node* node = root;
    char * p = key;
    while(*p)
    {
        if(node->children[*p-'a'] == NULL)
        {
            node->children[*p-'a'] = create_trie_node();
        }
        node = node->children[*p-'a'];
        node->count += 1;
        p++;
    }
}

int trie_search(trie root,char* key)
{
    trie_node* node = root;
    char *p = key;
    while(*p && node != NULL)
    {
        node = node->children[*p-'a'];
        p++;
    }
    if(node == NULL)
        return 0;
    else
        return node->count;
}

void my_search(trie root, char *key)
{
    trie_node* node = root;
    char *p = key;
    while(*p && node != NULL)
    {
        node = node->children[*p-'a'];
        if(node->count==1)
        {
            printf("%c",*p);
            break;
        }
        else
        {
            printf("%c",*p);
        }
        p++;
    }
    printf("\n");
}

int main()
{
    int g = 0;
    char s[ARRAY_SIZE][STRING_SIZE]={{0}};
    trie root = create_trie_node();
    while(scanf(" %s",s[g]) != EOF)
    {
        trie_insert(root, s[g]);
        g++;
    }
    for(int i = 0; i < g; i++)
    {
        printf("%s ",s[i]);
        my_search(root,s[i]);
    }
    return 0;
}

