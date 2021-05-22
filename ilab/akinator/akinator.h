#ifndef _AKINATOR_H
#define _AKINATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#include <cstring>
#include <sys/stat.h>
#include "../CPU_c++/stack_cpp.cpp"

const unsigned word_size = 50;

typedef struct Node {
                    char lexemm[word_size];
                    Node* left; 
                    Node* right;
                    } Node;

class Akinator
        {
        public:
            Node* root;
            FILE* tree_file;

            ~Akinator();
            Akinator(const char* Input_file_name);
            void Visit_Nodes(Node* node, void (*action) (Node* node));
            void Visit_Nodes(Node* node, void (*action) (void* ptrmem));
            void Visit_Nodes(Node* node, FILE* fin, void (*action) (Node* node, FILE* fin));
            
            void print_tree_to_graphiz();

            void reading_tree(Node* node);
            void menu();
            
        private:
            char* Input;
            unsigned Input_size;
            unsigned read_index;
            Stack<Node*>* stack;

            Akinator operator = (const Akinator& obj) = delete;
            Akinator (Akinator const& obj) = delete;
            void graphiz_translation(Node* node, FILE* fout);
            Node* Add_elem(char* word);
            char get_bracket(char type_of_bracket);
            char* get_lexemm(char a[word_size]);
            void Create_new_obj(Node* node);
            void Game_process(Node* node);
            int object_searching(Node* node, const char object[word_size]);
            void object_description(Node* node, char object[word_size]);
            void object_comparing();
            void printing_part_of_tree(int first, int end);
            void printing_of_appereance(int i);
        };
        
void print_tree_to_file(Node* node, FILE* fin);
void print_tree(Node* node);
void aligment_of_cmd(int n);
#endif
