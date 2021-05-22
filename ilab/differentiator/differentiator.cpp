#include "differentiator.h"

Diff::Diff(const char* Input_file_name) : root(NULL),  read_index (0), df_root(NULL)
    {
    char lexemm_buf[word_size];

    FILE* tree_file = fopen (Input_file_name, "r");
    struct stat statistica;
    int stat_error = stat (Input_file_name, &statistica);
    assert(stat_error == 0);
    Input = (char*) calloc (statistica.st_size + 1, sizeof(char));
    Input_size = statistica.st_size + 1;
    fread ((void*) Input, sizeof(char), statistica.st_size, tree_file);
    if (Get_lexemm(lexemm_buf))
        root = Create_node(lexemm_buf);
    fclose(tree_file);
    }
    


Diff::~Diff()
    {
    FILE* fout = fopen ("Tree_output.c", "w");
    Visit_Nodes(df_root, fout, Print_tree_to_file);
    fclose (fout);
    free(Input);
    Visit_Nodes(df_root, free);
    Visit_Nodes(root, free);
    }    



Node* Diff::Create_node(const char* word)
    {
    assert(this);
    if (word[0] == '\0')
        return NULL;
    Node* tmp = (Node*) calloc(1, sizeof(Node));
    assert(tmp);
    strcpy(tmp -> lexemm, word);
    tmp -> left   = NULL;
    tmp -> right  = NULL;
    return tmp;
    }



void Diff::Reading_tree(Node* node)
    {
    if (read_index >= Input_size)
        return;
    char lexemm_buf[word_size];
    char symb = Get_bracket('}');
    if (symb == '}' || symb == 0)
        return;

    node -> left = Create_node(Get_lexemm(lexemm_buf));
    Reading_tree(node -> left);

    node -> right = Create_node(Get_lexemm(lexemm_buf));
    Reading_tree(node -> right);
    }



char Diff::Get_bracket(char type_of_bracket)
    {
    int read_index_copy = read_index;
    for (; (Input[read_index] != '{') && (Input[read_index] != '}'); read_index++)
        if (read_index >= Input_size)
            return 0;
        ;
    char bracket = Input[read_index];
    if (bracket != type_of_bracket)
        read_index = read_index_copy;
    return bracket;
    }



char* Diff::Get_lexemm(char a[word_size])
    {
    for (; Input[read_index] != '"'; read_index++)
        if (read_index >= Input_size)
            return "\0";
    read_index++;
    int length = strchr(Input + read_index, '"') - (Input + read_index);
    strncpy(a, Input + read_index, length);
    a[length] = '\0';
    read_index += length + 1;
    return a;
    }



void Print_tree(Node* node)
    {
    assert(node);
    printf("%s\n  ", node -> lexemm);
    if (node -> left)
        printf("left = %s, ", (node -> left) -> lexemm);
    if (node -> right)
        printf("right = %s ", (node -> right) -> lexemm);
    printf("\n");
    }



void Print_tree_to_file(Node* node, FILE* fout)
    {
    assert(node);
    fprintf(fout, "{\n\"%s\"\n", node -> lexemm);
    if (node -> right == NULL && node -> left == NULL)
        fprintf(fout, "}");
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



void Diff::Visit_Nodes(Node* node, FILE* fout, void (*action) (Node* node, FILE* fout))
    {
    assert(node);
    action(node, fout);
    if (node -> left) 
        {
        Visit_Nodes(node -> left, fout, action);
        }

    if (node -> right)
        {
        Visit_Nodes(node -> right, fout, action);
        fprintf(fout, "}");
        }
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



void Diff::Visit_Nodes(Node*& node, void (*action) (Node*& Node))
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



void Diff::Print_tree_to_graphiz()
    {
    FILE* fout = fopen("graph.txt", "w");
    fprintf(fout, "digraph G{\n");
    Graphiz_translation(root, fout);
    fprintf(fout, "}");
    fclose(fout);
    system("dot graph.txt -T png -o graph_visual.png");
    }



void Diff::Graphiz_translation(Node* node, FILE* fout)
    {
    fprintf(fout, "a%sa", node -> lexemm);
    if (node -> left)
        {
        fprintf(fout, "->");
        Graphiz_translation(node -> left, fout);
        }
    else 
        {
        fprintf(fout, ";\n");
        return;
        }

    fprintf(fout, "a%sa", node -> lexemm);
    if (node -> right)
        {
        fprintf(fout, "->");
        Graphiz_translation(node -> right, fout);
        }
    
    else fprintf(fout, ";\n");
    }



Node* Diff::Copy_tree(Node* node)
    {
    if (node)
        {
        Node* node1 = Create_node(node -> lexemm);
        if (node -> left)
            node1 -> left  = Copy_tree(node -> left);
        if (node -> right)
            node1 -> right = Copy_tree(node -> right);
        return node1;
        }
    return NULL;   
    }



void Diff::Degree_handler(Node* node, Node** node_res)
    {
    char bufer[word_size];
    assert(node);
    if (node -> left -> lexemm[0] < '0' || node -> left -> lexemm[0] > '9')
            {
            (*node_res) = Create_node("*");
            (*node_res) -> left = Create_node("*");
            (*node_res) -> left -> left = Copy_tree(node -> right);
            (*node_res) -> left -> right = Finding_df(node -> left);
            (*node_res) -> right = Create_node("^");
            (*node_res) -> right -> left = Copy_tree(node -> left);
            int deg = atoi((node -> right) -> lexemm) - 1;
            sprintf(bufer, "%d", deg);
            (*node_res) -> right -> right = Create_node(bufer);
            }
        else if (atoi(node -> left -> lexemm) != 0 || node -> left -> lexemm[0] == '0')
            {
            (*node_res) = Create_node("*");
            (*node_res) -> left = Create_node("ln");
            (*node_res) -> left -> left = Copy_tree(node -> left);
            (*node_res) -> right = Create_node("*");
            (*node_res) -> right -> left = Finding_df(node -> right);
            (*node_res) -> right -> right = Copy_tree(node);
            }
    }



void Diff::Multiplication_handler(Node* node, Node** node_res)
    {
    assert(node);
    (*node_res) = Create_node("+");
    (*node_res) -> left = Create_node("*");
    (*node_res) -> left -> left  = Finding_df(node -> left);
    (*node_res) -> left -> right = Copy_tree(node -> right);
    (*node_res) -> right = Create_node("*");
    (*node_res) -> right -> left   = Copy_tree(node -> left);
    (*node_res) -> right -> right = Finding_df(node -> right);
    }



void Diff::Subtraction_handler(Node* node, Node** node_res)
    {
    assert(node);
    (*node_res) = Create_node("-");
    (*node_res) -> left  = Finding_df(node -> left);
    (*node_res) -> right = Finding_df(node -> right);
    }



void Diff::Addition_handler(Node* node, Node** node_res)
    {
    assert(node);
    (*node_res) = Create_node("+");
    (*node_res) -> left  = Finding_df(node -> left);
    (*node_res) -> right = Finding_df(node -> right);
    }



void Diff::Sin_handler(Node* node, Node** node_res)
    {
    assert(node);
    (*node_res) = Create_node("*");
    (*node_res) -> left = Create_node("cos");
    (*node_res) -> right = Finding_df(node -> left);
    (*node_res) -> left -> left = Copy_tree(node -> left);
    }



void Diff::Cos_handler(Node* node, Node** node_res)
    {
    assert(node);
    (*node_res) = Create_node("*");
    (*node_res) -> left = Create_node("*");
    (*node_res) -> right = Finding_df(node -> left);
    (*node_res) -> left -> left = Create_node("-1");
    (*node_res) -> left -> right = Create_node("sin");
    (*node_res) -> left -> right -> left = Copy_tree(node -> left);
    }



Node* Diff::Finding_df(Node* node)
    {
    assert(node);
    Node* node_res = NULL;
    if (strcmp(node -> lexemm, "x") == 0)
        node_res = Create_node("1");

    else if (atoi(node -> lexemm) != 0 || node -> lexemm[0] == '0')
        node_res = Create_node("0");

    else if (strncmp(node -> lexemm, "+", 1) == 0)
        Addition_handler(node, &node_res);

    else if (strcmp(node -> lexemm, "-") == 0)
        Subtraction_handler(node, &node_res);

    else if (strcmp(node -> lexemm, "*") == 0)
        Multiplication_handler(node, &node_res);

    else if (strcmp(node -> lexemm, "^") == 0)
        Degree_handler(node, &node_res);
    
    else if (strcmp(node -> lexemm, "sin") == 0)
        Sin_handler(node, &node_res);
    
    else if (strcmp(node -> lexemm, "cos") == 0)
        Cos_handler(node, &node_res);
    
    Visit_Nodes(node_res, Simpificator);
    return node_res;
    }



void Calculator(Node*& node)
    {
    
        char bufer[word_size];
        if (strncmp(node -> lexemm, "+", 1) == 0)
            sprintf(node -> lexemm, "%d", atoi(node -> left -> lexemm) + atoi(node -> right -> lexemm));

        if (strncmp(node -> lexemm, "*", 1) == 0)
            sprintf(node -> lexemm, "%d", atoi(node -> left -> lexemm) * atoi(node -> right -> lexemm));

        if (strncmp(node -> lexemm, "-", 1) == 0)
            sprintf(node -> lexemm, "%d", atoi(node -> left -> lexemm) - atoi(node -> right -> lexemm));

        if (strncmp(node -> lexemm, "^", 1) == 0)
            sprintf(node -> lexemm, "%d", (int)pow(atoi(node -> left -> lexemm), atoi(node -> right -> lexemm)));
        node -> right = NULL;
        node -> left = NULL;
        free(node -> left);
        free(node -> right);
        
    }



void math_reduction_left(Node*& node)   
    {
    Node* node_buf = node;
    node = node -> right;
    free(node_buf -> left);
    free(node_buf);
    }



void math_reduction_right(Node*& node)
    {
    Node* node_buf = node;
    node = node -> left;
    free(node_buf -> right);
    free(node_buf);
    }



void Simpificator(Node*& node)
    {
    if (node -> left)
        {
        if ((atoi(node -> left -> lexemm) != 0  || (node -> left -> lexemm)[0] == '0')
            && (atoi(node -> right -> lexemm) != 0 || (node -> right -> lexemm)[0] == '0'))
            Calculator(node);
            
        else if (strcmp(node -> lexemm, "*") == 0 && ((node -> left -> lexemm)[0] == '0' || (node -> right -> lexemm)[0] == '0'))
            {
            sprintf(node -> lexemm, "%d", 0);
            node -> right = NULL;
            node -> left = NULL;
            free(node -> left);
            free(node -> right);
            }

        else if (strcmp(node -> lexemm, "+") == 0 && (node -> left -> lexemm)[0] == '0')
            math_reduction_left(node);
            
        else if (strcmp(node -> lexemm, "+") == 0 && (node -> right -> lexemm)[0] == '0')
            math_reduction_right(node);

        else if (strcmp(node -> lexemm, "*") == 0 && (node -> left -> lexemm)[0] == '1')
            math_reduction_left(node);

        else if (strcmp(node -> lexemm, "*") == 0 && (node -> right -> lexemm)[0] == '1')
            math_reduction_right(node);
        }
    }



int main()
    {
    Diff tree("Tree_input.c");
    printf("Reading Input_size = %d\n", tree.Input_size);
    
    tree.Reading_tree(tree.root);
    tree.df_root = tree.Finding_df(tree.root);
    printf("df_root = %p\n", tree.df_root);
    tree.Visit_Nodes(tree.df_root, Print_tree);
    tree.Visit_Nodes(tree.df_root, Simpificator);
        printf("df_root = %p\n", tree.df_root);
    tree.Visit_Nodes(tree.df_root, Print_tree);
    }