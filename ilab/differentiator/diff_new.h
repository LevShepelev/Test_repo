#ifndef _DIFFERENTIATOR_H
#define _DIFFERENTIATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#include <cstring>
#include <sys/stat.h>

const unsigned word_size = 50;



typedef struct Node {
                    int lexemm;
                    Node* left; 
                    Node* right;
                    int type_lexemm;
                    } Node;

class Diff
    {
    private:
        char* Input;
        char lexemm_buf[word_size];
        unsigned read_index;

    public:
        Node* root;
        unsigned Input_size;
        Diff(const char* Input_file_name);
        ~Diff();
        Node* Get_N();
        Node* Get_E();
        void General();



        Node* Add_elem(int word, int type_lexemm);

        void print_tree_to_graphiz();
        void graphiz_translation(Node* node, FILE* fout);

        void Visit_Nodes(Node* node, void (*action) (Node* Node));
        void Visit_Nodes(Node* node, void (*action) (void* ptrmem));
    };


void print_tree(Node* node);



#endif
