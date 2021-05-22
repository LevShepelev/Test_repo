#include "diff_new.h"

Diff::Diff(const char* Input_file_name) : root(NULL),  read_index (0)
    {
    char lexemm_buf[word_size];

    FILE* tree_file = fopen (Input_file_name, "r");
    struct stat statistica;
    int stat_error = stat (Input_file_name, &statistica);
    assert(stat_error == 0);
    Input = (char*) calloc (statistica.st_size + 1, sizeof(char));
    Input_size = statistica.st_size + 1;
    fread ((void*) Input, sizeof(char), statistica.st_size, tree_file);
    fclose(tree_file);
    }



Diff::~Diff()
    {
    free(Input);
    Visit_Nodes(root, free);
    }    



Node* Diff::Add_elem(int lexemm, int type_lexemm)
    {
    assert(this);
    Node* tmp = (Node*) calloc(1, sizeof(Node));
    assert(tmp);
    tmp -> lexemm = lexemm;
    tmp -> left   = NULL;
    tmp -> right  = NULL;
    tmp -> type_lexemm = type_lexemm;
    return tmp;
    }


void Diff::General()
    {
    root = Get_E();
    if (Input[read_index] == '$')
        return;
    
    }



Node* Diff::Get_N()
    {
    int value = 0;
    while ('0' <= Input[read_index] && Input[read_index] <= '9')
        {
        value = value * 10 + Input[read_index] - '0';
        read_index++;
        printf("INput = %c\n", Input[read_index]);
        }
    
    return Add_elem(value, 0);//enum для типов 
    }



Node* Diff::Get_E()
    {
    Node* node_left = Get_T();
    Node* node = node_left;
    while (Input[read_index] == '+' || Input[read_index] == '-')
        { 
        node = Add_elem(Input[read_index], 1); // операнд
        node -> left = node_left; 
        read_index++;
        node -> right = Get_E();
        }
    return node;
    }



void print_tree(Node* node)
    {
    assert(node);
    printf("%d\n  ", node -> lexemm);
    if (node -> left)
        printf("left = %d, ", (node -> left) -> lexemm);
    if (node -> right)
        printf("right = %d ", (node -> right) -> lexemm);
    printf("\n");
    }


void Diff::Visit_Nodes(Node* node, void (*action) (void* ptrmem))
    {
    assert(node);
    if (node -> left) 
        Visit_Nodes(node -> left, action);

    if (node -> right)
        Visit_Nodes(node -> right, action);

    action(node);
    }



void Diff::Visit_Nodes(Node* node, void (*action) (Node* Node))
    {
    assert(node);
    action(node);
    if (node -> left) 
        {
        Visit_Nodes(node -> left, action);
        }
    if (node -> right)
        {
        Visit_Nodes(node -> right, action);
        }
    }



void Diff::print_tree_to_graphiz()
    {
    FILE* fout = fopen("graph.txt", "w");
    fprintf(fout, "digraph G{\n");
    graphiz_translation(root, fout);
    fprintf(fout, "}");
    fclose(fout);
    system("dot graph.txt -T png -o graph_visual.png");
    }



void Diff::graphiz_translation(Node* node, FILE* fout)
    {
    fprintf(fout, "%d", node -> lexemm);
    if (node -> left)
        {
        fprintf(fout, "->");
        graphiz_translation(node -> left, fout);
        }
    else 
        {
        fprintf(fout, ";\n");
        return;
        }

    fprintf(fout, "%d", node -> lexemm);
    if (node -> right)
        {
        fprintf(fout, "->");
        graphiz_translation(node -> right, fout);
        }
    
    else fprintf(fout, ";\n");
    }



int main()
    {
    Diff tree("Tree_input.c");
    printf("Reading Input_size = %d\n", tree.Input_size);
    
    tree.General();
    tree.Visit_Nodes(tree.root, print_tree);
    tree.print_tree_to_graphiz();
    }