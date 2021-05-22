#include "akinator.h"


Node* Akinator::Add_elem(char* word)
    {
    assert(this);
    Node* tmp = (Node*) calloc(1, sizeof(Node));
    assert(tmp);
    strcpy(tmp -> lexemm, word);
    tmp -> left   = NULL;
    tmp -> right  = NULL;
    return tmp;
    }



Akinator::Akinator(const char* Input_file_name) : root(NULL),  read_index (0)
    {
    stack = new Stack<Node*>(30);
    char lexemm_buf[word_size];

    tree_file = fopen (Input_file_name, "r");
    struct stat statistica;
    int stat_error = stat (Input_file_name, &statistica);
    assert(stat_error == 0);
    Input = (char*) calloc (statistica.st_size + 1, sizeof(char));
    Input_size = statistica.st_size + 1;
    fread ((void*) Input, sizeof(char), statistica.st_size, tree_file);
    if (get_lexemm(lexemm_buf))
        root = Add_elem(lexemm_buf);
    else fclose(tree_file);
    }



Akinator::~Akinator()
    {
    FILE* fout = fopen ("Tree_input.c", "w");
    Visit_Nodes(root, fout, print_tree_to_file);
    fclose (fout);
    delete stack;
    free(Input);
    Visit_Nodes(root, free);
    }

void Akinator::Visit_Nodes(Node* node, void (*action) (Node* Node))
    {
    assert(node);
    action(node);
    if (node -> right) 
        {
        Visit_Nodes(node -> right, action);
        }
    if (node -> left)
        {
        Visit_Nodes(node -> left, action);
        }
    }



void Akinator::Visit_Nodes(Node* node, void (*action) (void* ptrmem))
    {
    assert(node);
    if (node -> left) 
        Visit_Nodes(node -> left, action);

    if (node -> right)
        Visit_Nodes(node -> right, action);

    action(node);
    }



void Akinator::Visit_Nodes(Node* node, FILE* fout, void (*action) (Node* node, FILE* fout))
    {
    assert(node);
    action(node, fout);
    if (node -> right) 
        {
        Visit_Nodes(node -> right, fout, action);
        }

    if (node -> left)
        {
        Visit_Nodes(node -> left, fout, action);
        fprintf(fout, "}");
        }
    }



void Akinator::Game_process(Node* node)
    {
    char name[word_size] = {0};
    char answer[5] = {0};
    if (node == NULL)
        {
        printf("Data base is empty, say name of your character\n");
        scanf("%s", name);
        root = Add_elem(name);
        return; 
        }
    printf("%s ?\nchoose (yes|no)\n", node -> lexemm);
    scanf("%s", answer);
    if (strcmp(answer, "yes") == 0)
        {
        if (node -> right)
            Game_process(node -> right);
        else 
            {
            printf("I am the best, I found it\n");
            return;
            }
        }

    else if (strcmp(answer, "no") == 0)
        {
        if (node -> left)
            Game_process(node -> left);
        else
            {
            Create_new_obj(node);
            return;
            }
        }

    else 
        {
        printf("incorrect input try again\n");
        Game_process(node);
        }
    }



void Akinator::Create_new_obj(Node* node)
    {
    assert(node);
    char name[word_size] = {0};
    char difference[word_size] = {0};
    printf("there's your character in out data base, please tell us name of you character\n");
    scanf("%s", name);
    printf("what differ %s from %s\n", name, node -> lexemm);
    scanf("%s", difference);
    node -> right = Add_elem(name);
    node -> left  = Add_elem(node -> lexemm);
    strcpy(node -> lexemm, difference);
    }



void Akinator::menu()
    {
    char object[word_size];
    int action_number = 0;
    while (1)
        {
        printf("\nchoose action\n1) Play game\n2) Searching object\n3) Comparing objects\n4) Exit\n");
        scanf("%d", &action_number);
        switch (action_number)
            {
            case 1:
                printf("choose a character\n");
                Game_process(root);
                break;
            case 2:
                printf("write name of your character\n");
                scanf("%s", object);
                object_description(root, object);
                break;
            case 3:
                printf("write name of comparing characters\n");
                object_comparing();
                break;
            case 4:
                {
                FILE* fout = fopen ("Tree_output.c", "w");
                Visit_Nodes(root, fout, print_tree_to_file);
                fclose (fout);
                return;
                break;
                }
            default:
                printf("error input try again\n");
            }
        }
    }


void Akinator::reading_tree(Node* node)
    {
    if (read_index >= Input_size)
        return;
    char lexemm_buf[word_size];
    char symb = get_bracket('}');
    if (symb == '}' || symb == 0)
        return;

    node -> right = Add_elem(get_lexemm(lexemm_buf));
    reading_tree(node -> right);

    node -> left = Add_elem(get_lexemm(lexemm_buf));
    reading_tree(node -> left);
    }



char Akinator::get_bracket(char type_of_bracket)
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



char* Akinator::get_lexemm(char a[word_size])
    {
    for (; Input[read_index] != '"'; read_index++)
        if (read_index >= Input_size)
            return NULL;
    read_index++;
    int length = strchr(Input + read_index, '"') - (Input + read_index);
    strncpy(a, Input + read_index, length);
    a[length] = '\0';
    read_index += length + 1;
        return a;
    }



void print_tree(Node* node)
    {
    assert(node);
    printf("%s\n  ", node -> lexemm);
    if (node -> left)
        printf("left = %s, ", (node -> left) -> lexemm);
    if (node -> right)
        printf("right = %s ", (node -> right) -> lexemm);
    printf("\n");
    }



void print_tree_to_file(Node* node, FILE* fout)
    {
    assert(node);
    fprintf(fout, "{\n\"%s\"\n", node -> lexemm);
    if (node -> right == NULL && node -> left == NULL) 
        fprintf(fout, "}");
    }



void Akinator::print_tree_to_graphiz()
    {
    FILE* fout = fopen("graph.txt", "w");
    fprintf(fout, "digraph G{\n");
    graphiz_translation(root, fout);
    fprintf(fout, "}");
    fclose(fout);
    system("dot graph.txt -T png -o graph_visual.png");
    exit (0);
    }



void Akinator::graphiz_translation(Node* node, FILE* fout)
    {
    fprintf(fout, "%s", node -> lexemm);
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

    fprintf(fout, "%s", node -> lexemm);
    if (node -> right)
        {
        fprintf(fout, "->");
        graphiz_translation(node -> right, fout);
        }
    
    else fprintf(fout, ";\n");
    }



void Akinator::object_description(Node* node, char object[word_size])
    {
    if (object_searching(node, object) == 1)
        {
        Node* node2 = stack -> pop();
        Node* node1 = NULL;
        while (node2 != node)
            {
            node1 = node2;
            node2 = stack -> pop();
            if (node2 -> left == node1)
                printf("Not %s\n", node2 -> lexemm);
            else if (node2 -> right == node1)
                printf("%s\n", node2 -> lexemm);
            else 
                {
                printf("programm error in object_description\n");
                stack -> clear();
                exit (1);
                }
            }
        }

    else printf("there's no such object in data base\n");
    stack -> clear();
    }



void Akinator::printing_part_of_tree(int first, int end)
    {
    while (end != first)
        {
        end--;
        if ((*stack)[end] -> left == (*stack)[end + 1])
            printf("Not %s\n", (*stack)[end] -> lexemm);
        else if ((*stack)[end] -> right == (*stack)[end + 1])
            printf("%s\n", (*stack)[end] -> lexemm);
        else 
            {
            printf("programm error in object_description\n");
            stack -> clear();
            exit (1);
            }
        }
    }



int Akinator::object_searching(Node* node, const char object[word_size])
    {
    stack -> push(node);
    if (node -> right)
        {
        if (object_searching(node -> right, object) == 1)
            return 1;
        }
    if (node -> left)
        {
        if (object_searching(node -> left, object) == 1)
            return 1;
        }
    if (strcmp(node -> lexemm, object) == 0)
        {
        return 1;
        }
    stack -> pop();
    return 0;
    }



void aligment_of_cmd(int n)
    {
    for (int i = 0; i < 25 - n; i++)
        printf(" ");
    }



void Akinator::printing_of_appereance(int i)
    {
    assert(i >= 0 && i < stack -> Top());
    if (((*stack)[i]) -> left == (*stack)[i + 1])
        {
        printf("Not %s", ((*stack)[i]) -> lexemm);
        aligment_of_cmd(4 + strlen(((*stack)[i]) -> lexemm));
        } 
    else if (((*stack)[i]) -> right == (*stack)[i + 1])
        {
        printf("%s", ((*stack)[i]) -> lexemm);
        aligment_of_cmd(strlen(((*stack)[i]) -> lexemm));
        }
    else 
        {
        printf("programm error in object_description\n");
        stack -> clear();
        exit (1);
        }
    }



void Akinator::object_comparing()
    {
    int index_of_descr_2 = 0;
    int index_of_descr_1 = 0;
    int first_descr_edge = 0;
    char obj_1[word_size];
    char obj_2[word_size];
    scanf("%s", obj_1);
    scanf("%s", obj_2);
    if (object_searching(root, obj_1))
        {
        index_of_descr_2 = stack -> Top() + 1;
        first_descr_edge = index_of_descr_2 - 1;
        }
    else 
        {
        printf("there's no first object in data base\n");
        return;
        }

    if (object_searching(root, obj_2))
        {
        printf("mutual properties:\n");
        while ((*stack)[index_of_descr_1] == (*stack)[index_of_descr_2])
            {
            index_of_descr_1++;
            index_of_descr_2++;
            }
        index_of_descr_1--;
        index_of_descr_2--;
        printing_part_of_tree(0, index_of_descr_1);

        printf("difference:\n%s:", obj_1);
        aligment_of_cmd(strlen(obj_1) + 1);
        printf("%s:\n", obj_2); 
        while ((index_of_descr_1 < first_descr_edge) || (index_of_descr_2 < stack -> Top()))
            {
            if (index_of_descr_1 < first_descr_edge)
                printing_of_appereance(index_of_descr_1);
            if (index_of_descr_2 < stack -> Top())
                printing_of_appereance(index_of_descr_2);
            printf("\n");
            index_of_descr_1++;
            index_of_descr_2++;
            }
        }
    else printf("there's no second object in data base\n");
    stack -> clear();
    }



int main()
    {
    Akinator tree("Tree_input.c");

    tree.reading_tree(tree.root);
    tree.menu();
    tree.print_tree_to_graphiz();
    }