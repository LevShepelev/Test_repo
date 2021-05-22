#ifndef _DIFFERENTIATOR_H
#define _DIFFERENTIATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#include <cstring>
#include <sys/stat.h>
#include <cmath>

const unsigned word_size = 50;


typedef struct Node {
                    char lexemm[word_size];
                    Node* left; 
                    Node* right;
                    int Type;
                    } Node;


class Diff
    {
    private:
        char* Input;
        char lexemm_buf[word_size];
        unsigned read_index;

        void Addition_handler(Node* node, Node** node_res);
        void Subtraction_handler(Node* node, Node** node_res);
        void Multiplication_handler(Node* node, Node** node_res);
        void Degree_handler(Node* node, Node** node_res);
        void Sin_handler(Node* node, Node** node_res);
        void Cos_handler(Node* node, Node** node_res);
        char Get_bracket(char type_of_bracket);
        char* Get_lexemm(char a[word_size]);

    public:
        Node* root;
        Node* df_root;
        unsigned Input_size;

        Diff(const char* Input_file_name);
        ~Diff();
        Node* Create_node(const char* word);
        void Reading_tree(Node* node);
        void Visit_Nodes(Node* node, void (*action) (Node* Node));
        void Visit_Nodes(Node*& node, void (*action) (Node*& Node));
        void Visit_Nodes(Node* node, void (*action) (void* ptrmem));
        void Visit_Nodes(Node* node, FILE* fout, void (*action) (Node* node, FILE* fout));
        void Graphiz_translation(Node* node, FILE* fout);
        void Print_tree_to_graphiz();
        Node* Copy_tree(Node* node);
        Node* Finding_df(Node* node);
    };


void Print_tree(Node* node);
void Print_tree_to_file(Node* node, FILE* fout);
void Calculator(Node*& node);
void math_reduction_right(Node*& node);
void math_reduction_left(Node*& node);
void Simpificator(Node*& node);



#endif
