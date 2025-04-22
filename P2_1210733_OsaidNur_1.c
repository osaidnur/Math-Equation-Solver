/* Name    : Osaid Hasan Nur
 * ID      : 1210733
 * Section : 1
 * Instructor : Ahmad Abusnaina
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
typedef struct nodeS *Stack;
typedef struct nodell *linked_list;
// two types of nodes , one for stack and the other is for linked list
struct nodeS
{
    double data;
    Stack next;
};
struct nodell
{
    char s[10000];
    // this field to save the validity of the equation without need to call the function again
    int valid;
    linked_list next;
    linked_list prev;
};

// linked list functions
linked_list new_linked_list(linked_list);
void insert_First(char[], linked_list);
void insert_Pos(char[], linked_list, linked_list);
void insert_Last(char[], linked_list);
int isLast(linked_list, linked_list);
int isEmptyll(linked_list);
linked_list findPrevious(char[], linked_list);
linked_list find(char[], linked_list);
void deleteList(linked_list);
void delete(char[], linked_list);
void deleteFirst(linked_list);
int sizell(linked_list);
void fprint_List(linked_list);
void print_List(linked_list);
void reverse(linked_list);

// Stack functions
int isEmptyS(Stack s);
Stack new_Stack();
int sizeS(Stack s);
void deleteStack(Stack s);
void push(double x, Stack s);
double pop(Stack s);
double top(Stack s);
void fprint_Stack(Stack s);
void print_Stack(Stack s);
int isValid(char s[]);
double evaluate(char[]);
double performOperation(double op1, char a, double op2);
void InfixToPostfix(char[], char[]);
int priority(char);
void InfixToPrefix(char[], char res[]);
void modify(char[], char[]);

FILE *input, *output;

int main()
{
    printf("************ Welcome **************\n");
    // linked list to save the equations in , the linked list has the type array of characters that stores strings
    linked_list equations = new_linked_list(equations);
    // array for the answers of equations 
    double values[100000];
    int pos = 0;
    while (1)
    {
        int choice = 0;
        printf("choose the operation (1-5) \n");
        printf("1- Read the equations from the file  \n");
        printf("2- Check the validity of the equations \n");
        printf("3- Convert valid equations from infix to prefix  \n");
        printf("4- Evaluate the equations \n");
        printf("5- Print invalid equations\n");
        printf("6- Print equations to the file \n");
        printf("7- Exit\n");
        scanf("%d", &choice);

        // read the file 
        if (choice == 1)
        {
            char name[50];
            printf("Enter the name of source file : ");
            scanf("%s", name);
            input = fopen(name, "r");
            char c = 'a';
            char s[10000] = {'0'};
            int i = 0;
            while (1)
            {
                c = getc(input);
                if (c == '\n' || c == ' ' || c == EOF)
                {
                    i = 0;
                    insert_Last(s, equations);
                    memset(s, 0, sizeof(s));
                    if (c == EOF)
                        break;
                    continue;
                }
                s[i] = c;
                i++;
            }
            printf("All equations from the file are stored \n");
        }
    // check the validity of the equations , the print process is in the function 
        else if (choice == 2)
        {
            int counter = 1;
            linked_list pointer = equations;
            while (pointer->next != NULL)
            {
                printf("Equation (%d) -> ", counter);
                if (isValid(pointer->next->s))
                    pointer->next->valid = 1;
                pointer = pointer->next;
                counter++;
                printf("\n");
            }
        }
        // print the prefix form
        else if (choice == 3)
        {
            int counter = 1;
            linked_list pointer = equations;
            while (pointer->next != NULL)
            {
                char prefix[10000];
                // in my program , I'm dealing with string that have a symbol '|' between every character
                char modified[10000];
                memset(prefix, 0, sizeof(prefix));
                memset(modified, 0, sizeof(modified));
                if (pointer->next->valid)
                {
                    modify(pointer->next->s, modified);
                    InfixToPrefix(modified, prefix);
                    printf("Equation (%d) Prefix form >>>  ", counter);
                    //this for loop to print the prefix sum without the symbol '|'
                    for (int i = 0; i < strlen(prefix); i++)
                    {
                        if (prefix[i] != '|')
                            printf("%c", prefix[i]);
                    }
                    printf("\n");
                }
                pointer = pointer->next;
                counter++;
            }
        }
        // evaluate the equations by passing the prefix form to the function 
        else if (choice == 4)
        {
            int counter = 1;
            linked_list pointer = equations;
            while (pointer->next != NULL)
            {
                char pre[10000];
                char modified[10000];
                // to initialize the arrays with zero value 
                memset(modified, 0, sizeof(modified));
                memset(pre, 0, sizeof(pre));
                if (pointer->next->valid)
                {
                    modify(pointer->next->s, modified);
                    InfixToPrefix(modified, pre);
                    printf("Equation (%d) result = %lf\n", counter, evaluate(pre));
                    values[pos] = evaluate(pre);
                    pos++;
                }
                pointer = pointer->next;
                counter++;
            }
        }
        // print the invalid equations , I do this operation without calling the function isValid 
        // I use a value inside the node that decide the validation of the equation
        else if (choice == 5)
        {
            int counter = 0;
            linked_list point = equations;
            while (point->next != NULL)
            {
                if (!(point->next->valid))
                {
                    printf("Equation (%d) : %s\n", counter, point->next->s);
                }
                point = point->next;
                counter++;
            }
        }
        // print all information about equation to the file 
        else if (choice == 6)
        {
            output = fopen("output.txt", "w");
            int counter = 1;
            pos = 0;
            linked_list pointer = equations;
            while (pointer->next != NULL)
            {
                char pre[10000];
                char modified[10000];
                memset(pre, 0, sizeof(pre));
                memset(modified, 0, sizeof(modified));
                if (pointer->next->valid)
                {
                    modify(pointer->next->s, modified);
                    InfixToPrefix(modified, pre);
                    fprintf(output, "Equation (%d) : prefix form -->> ", counter);
                    // print the prefix form without the symbol '|'
                    for (int i = 0; i < strlen(pre); i++)
                    {
                        if (pre[i] != '|')
                            fprintf(output, "%c", pre[i]);
                    }
                    fprintf(output, "\n");
                    fprintf(output, "                   result --->>> %f\n", values[pos]);
                    pos++;
                }
                else
                {
                    fprintf(output, "Equation (%d) : invalid !\n", counter);
                }
                counter++;
                pointer = pointer->next;
            }
            printf("Data stored in the file ...\n");
        }
        // Exit the program
        else if (choice == 7)
        {
            printf("********** Thank you for using My Program  ************ \n");
            printf("-------------------- Good By -------------------------");
            break;
        }
        else
            printf("Invalid Input ! try again \n");
    }
    fclose(input);
    fclose(output);
    return 0;
}
// ----------->>>>>>>>>> For Stack
//****************************************************************************************************************************

// to check if the stack is empty 
int isEmptyS(Stack s)
{
    return s->next == NULL;
}

// create a new stack 
Stack new_Stack()
{
    Stack s = (Stack)malloc(sizeof(struct nodeS));
    if (s == NULL)
        printf("Out of memory !");
    s->next = NULL;
    s->data = 0;
    deleteStack(s);
    return s;
}

// the size of stack (number of nodes)
int sizeS(Stack s)
{
    Stack p = s->next;
    int count = 0;
    while (p != NULL)
    {
        count++;
        p = p->next;
    }
    return count;
}

// to make the stack empty
void deleteStack(Stack s)
{
    if (s == NULL)
        printf("Out of memeory !");
    else
        while (!isEmptyS(s))
        {
            pop(s);
        }
}

// push elements to the stack 
void push(double x, Stack s)
{
    Stack newnode = new_Stack();

    if (newnode == NULL)
    {
        printf("Out of memory !");
    }
    else
    {
        newnode->data = x;
        newnode->next = s->next;
        s->next = newnode;
    }
}

// to delete the top element of the stack 
double pop(Stack s)
{
    double elem = 0;
    if (isEmptyS(s))
    {
        printf("The Stack is Empty !");
    }
    else
    {
        Stack temp = s->next;
        elem = temp->data;
        s->next = temp->next;
        free(temp);
    }
    return elem;
}

// returns the top element of the stack 
double top(Stack s)
{
    if (!isEmptyS(s))
    {
        return s->next->data;
    }
    return 0;
}

// print the content of the stack to the file 
void fprint_Stack(Stack s)
{
    Stack p = s->next;
    while (p != NULL)
    {
        fprintf(output, "%c", p->data + '0');
        p = p->next;
    }
    fprintf(output, " \n");
}

// print the content of the stack to the terminal
void print_Stack(Stack s)
{
    Stack p = s->next;
    while (p != NULL)
    {
        printf("%c", p->data + '0');
        p = p->next;
    }
    printf(" \n");
}

//******************************************************************************************************************************

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// ----------------->>>>>  For linked list
//*******************************************************************************************************************************

// Function to make a new linked_list
linked_list new_linked_list(linked_list L)
{
    L = (linked_list)malloc(sizeof(struct nodell));
    memset(L->s, 0, sizeof(L->s));
    L->valid = 0;
    L->next = NULL;
    L->prev = NULL;
    return L;
}

// Insert linked_lists at the first of the linked list
void insert_First(char x[], linked_list L)
{
    linked_list newlist = new_linked_list(newlist);
    strcpy(newlist->s, x);
    newlist->next = L->next;
    newlist->prev = L;
    L->next = newlist;
    L->next->prev = newlist;
}

// Insert linked_lists at specific loacation
void insert_Pos(char x[], linked_list P, linked_list L)
{
    linked_list newlinked_list = new_linked_list(newlinked_list);
    strcpy(newlinked_list->s, x);
    newlinked_list->next = P->next;
    newlinked_list->prev = P;
    P->next->prev = newlinked_list;
    P->next = newlinked_list;
}

// Insert linked_lists at the last of the linked list
void insert_Last(char x[], linked_list L)
{
    linked_list newlinked_list = new_linked_list(newlinked_list);
    strcpy(newlinked_list->s, x);
    linked_list lst = L;
    while (lst->next != NULL)
    {
        lst = lst->next;
    }
    lst->next = newlinked_list;
    newlinked_list->prev = lst;
    newlinked_list->next = NULL;
}

// To check if the linked_list p is the last linked_list in linked list L
int isLast(linked_list P, linked_list L)
{
    return P->next == NULL;
}

// To check if the list is empty
int isEmptyll(linked_list L)
{
    return L->next == NULL && L->prev == NULL;
}

// Delete the linked list and free all linked_lists except the head
void deleteList(linked_list L)
{
    linked_list p, temp;
    p = L->next;
    L->next = NULL;
    while (p != NULL)
    {
        temp = p->next;
        free(p);
        p = temp;
    }
}

// To delete linked_lists with specific data value
void delete(char x[], linked_list L)
{
    linked_list temp = findPrevious(x, L);
    if (!isLast(temp, L))
    {
        linked_list temp2 = temp->next;
        temp2->next->prev = temp;
        temp->next = temp2->next;
        temp2->prev = NULL;
        temp2->next = NULL;
        free(temp2);
    }
}

// To delete the first linked_list of the linked list(I used this function to delete the sign of the negative numbers)
void deleteFirst(linked_list L)
{
    linked_list temp = L;
    if (!isLast(temp->next, L))
    {
        linked_list temp2 = temp->next;
        temp2->next->prev = temp;
        temp->next = temp2->next;
        temp2->prev = NULL;
        temp2->next = NULL;
        free(temp2);
    }
    else
    {
        linked_list temp2 = temp->next;
        temp->next = NULL;
        free(temp2);
    }
}

// To find the previous linked_list of a linked_list containing desired value
linked_list findPrevious(char x[], linked_list L)
{
    linked_list p = L;

    while (strcmp(p->next->s, x) != 0 && p->next != NULL)
    {
        p = p->next;
    }
    return p;
}

// To find a linked_list with specific data value
linked_list find(char x[], linked_list L)
{
    linked_list p = L->next;
    while (strcmp(p->s, x) != 0 && p != NULL)
    {
        p = p->next;
    }
    return p;
}

// calculates the size of the linked list ( the number of linked_lists)
int sizell(linked_list L)
{
    linked_list p = L->next;
    int count = 0;
    while (p != NULL)
    {
        count++;
        p = p->next;
    }
    return count;
}

// To print the content of the linked list on the file
void fprint_List(linked_list L)
{
    linked_list p = L->next;
    while (p != NULL)
    {
        fprintf(output, "%s", p->s);
        p = p->next;
    }
    fprintf(output, " \n");
}

// To print the content of the linked list on the screen (terminal)
void print_List(linked_list L)
{
    linked_list p = L->next;
    while (p != NULL)
    {
        printf("%s\n", p->s);
        p = p->next;
    }
}
//  Reverse the linked_lists of a linked list
void reverse(linked_list L)
{
    linked_list curr = L->next;
    linked_list prev = NULL;
    linked_list nxt = curr->next;

    while (curr != NULL)
    {
        curr->next = prev;
        curr->prev = nxt;
        prev = curr;
        curr = nxt;
        if (nxt != NULL)
            nxt = nxt->next;
    }
    L->next = prev;
    prev->prev = L;
}

//*************************************************************************************************************************

// function to modify the equation form , by adding a symbol '|' between every characters
void modify(char old[], char new[])
{
    int flag = 0;
    for (int i = 0; i < strlen(old); i++)
    {
        if (!flag)
        {
            new[strlen(new)] = '|';
            new[strlen(new)] = old[i];
        }
        else
            new[strlen(new)] = old[i];

        if (old[i] >= '0' && old[i] <= '9' && old[i + 1] >= '0' && old[i + 1] <= '9')
        {
            flag = 1;
        }
        else
            flag = 0;
    }
    new[strlen(new)] = '|';
}

// check if the equation is valid or not ( I used the brute force solution , there is a huge number of if statements )
int isValid(char s[])
{
    int n = strlen(s);
    int isBalanced = 1; // checks the Parentheses
    Stack check = new_Stack();
    for (int i = 0; i < n; i++)
    {
        if (s[i] == '(' || s[i] == '{' || s[i] == '[')
            push(s[i], check);
        else if (s[i] == ')' || s[i] == '}' || s[i] == ']')
        {
            if (isEmptyS(check))
            {
                isBalanced = 0;
                break;
            }
            if (s[i] == ')' && top(check) == '(')
                pop(check);
            else if (s[i] == '}' && top(check) == '{')
                pop(check);
            else if (s[i] == ']' && top(check) == '[')
                pop(check);
            else
            {
                isBalanced = 0;
                break;
            }
        }
    }
    if (!isEmptyS(check))
        isBalanced = 0;
    deleteStack(check);
    if (!isBalanced)
    {
        printf("Invalid ! , there is a bracket not closed");
        return 0;
    }

    for (int i = 0; i < n - 1; i++)
    {
        if (s[i] == '+' && s[i + 1] == '*')
        {
            printf("Invalid! , there is two consecutive operators , %c  then %c", s[i], s[i + 1]);
            return 0;
        }
        else if (s[i] == '+' && s[i + 1] == '/')
        {
            printf("Invalid! , there is two consecutive operators , %c  then %c", s[i], s[i + 1]);
            return 0;
        }
        else if (s[i] == '+' && s[i + 1] == '^')
        {
            printf("Invalid! , there is two consecutive operators , %c  then %c", s[i], s[i + 1]);
            return 0;
        }

        else if (s[i] == '-' && s[i + 1] == '*')
        {
            printf("Invalid! , there is two consecutive operators , %c  then %c", s[i], s[i + 1]);
            return 0;
        }
        else if (s[i] == '-' && s[i + 1] == '/')
        {
            printf("Invalid! , there is two consecutive operators , %c  then %c", s[i], s[i + 1]);
            return 0;
        }
        else if (s[i] == '-' && s[i + 1] == '^')
        {
            printf("Invalid! , there is two consecutive operators , %c  then %c", s[i], s[i + 1]);
            return 0;
        }

        else if (s[i] == '*' && s[i + 1] == '*')
        {
            printf("Invalid! , there is two consecutive operators , %c  then %c", s[i], s[i + 1]);
            return 0;
        }
        else if (s[i] == '*' && s[i + 1] == '/')
        {
            printf("Invalid! , there is two consecutive operators , %c  then %c", s[i], s[i + 1]);
            return 0;
        }
        else if (s[i] == '*' && s[i + 1] == '^')
        {
            printf("Invalid! , there is two consecutive operators , %c  then %c", s[i], s[i + 1]);
            return 0;
        }

        else if (s[i] == '/' && s[i + 1] == '/')
        {
            printf("Invalid! , there is two consecutive operators , %c  then %c", s[i], s[i + 1]);
            return 0;
        }
        else if (s[i] == '/' && s[i + 1] == '*')
        {
            printf("Invalid! , there is two consecutive operators , %c  then %c", s[i], s[i + 1]);
            return 0;
        }
        else if (s[i] == '/' && s[i + 1] == '^')
        {
            printf("Invalid! , there is two consecutive operators , %c  then %c", s[i], s[i + 1]);
            return 0;
        }

        else if (s[i] == '^' && s[i + 1] == '^')
        {
            printf("Invalid! , there is two consecutive operators , %c  then %c", s[i], s[i + 1]);
            return 0;
        }
        else if (s[i] == '^' && s[i + 1] == '*')
        {
            printf("Invalid! , there is two consecutive operators , %c  then %c", s[i], s[i + 1]);
            return 0;
        }
        else if (s[i] == '^' && s[i + 1] == '/')
        {
            printf("Invalid! , there is two consecutive operators , %c  then %c", s[i], s[i + 1]);
            return 0;
        }
        else if (s[i] >= 'a' && s[i] <= 'z' || s[i] >= 'A' && s[i] <= 'Z' || s[i + 1] >= 'a' && s[i + 1] <= 'z' || s[i + 1] >= 'A' && s[i + 1] <= 'Z')
        {
            printf("Invalid! ,the equation contains letters !!");
            return 0;
        }

        else if ((s[i] == '^' || s[i] == '/' || s[i] == '*' || s[i] == '+' || s[i] == '-') && (s[i + 1] == ')' || s[i + 1] == '}' || s[i + 1] == ']'))
        {
            printf("Invalid! ,the equation contains operator then a parentheses !!");
            return 0;
        }
        else if ((s[i] == '(' || s[i] == '{' || s[i] == '[') && (s[i + 1] == '*' || s[i + 1] == '/' || s[i + 1] == '^'))
        {
            printf("Invalid! ,the equation contains parentheses then operator !!");
            return 0;
        }

        else if ((s[i] >= '0' && s[i] <= '9') && (s[i + 1] == '(' || s[i + 1] == '{' || s[i + 1] == '['))
        {
            printf("Invalid! ,There is no operator between %c and %c ", s[i], s[i + 1]);
            return 0;
        }
        else if ((s[i] == ')' || s[i] == '}' || s[i] == ']') && (s[i + 1] >= '0' && s[i + 1] <= '9'))
        {
            printf("Invalid! ,There is no operator between %c and %c ", s[i], s[i + 1]);
            return 0;
        }
    }
    if (s[n - 1] == '+' || s[n - 1] == '-' || s[n - 1] == '*' || s[n - 1] == '/' || s[n - 1] == '^' || s[n - 1] == '(' || s[n - 1] == '{' || s[n - 1] == '[')
    {
        printf("Invalid! , there is an operator %c at the end of equation !!", s[n - 1]);
        return 0;
    }
    printf("Valid..");
    return 1;
}

// evaluate the prefix form of the equation
double evaluate(char s[])
{
    Stack stack = new_Stack();
    double x = 0;
    int p = 0;
    int flag = 0;
    for (int i = strlen(s) - 1; i >= 0; i--)
    {
        if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^')
        {
            p = 0;
            x = 0;
            double x2 = pop(stack);
            double x1 = pop(stack);
            double answer = performOperation(x2, s[i], x1);
            push(answer, stack);
        }
        else if (s[i] == '|')
        {
            if (x > 0)
                push(x, stack);
            p = 0;
            x = 0;
            continue;
        }
        else
        {
            // this algorithm to push a number with multiple digits 
            x += ((s[i] - '0') * pow(10, p));
            p++;
        }
    }
    return top(stack);
}

// to apply the operations on the nodes in the stack 
double performOperation(double op1, char a, double op2)
{
    if (a == '+')
        return op1 + op2;
    if (a == '-')
        return op1 - op2;
    if (a == '*')
        return op1 * op2;
    if (a == '/')
        return (op1 / op2);
    if (a == '^')
        return pow(op1, op2);
}

// returns the priority of the operation
int priority(char a)
{
    if (a == '^')
        return 3;
    if (a == '*' || a == '/')
        return 2;
    if (a == '+' || a == '-')
        return 1;
    if (a == '(' || a == '{' || a == '[')
        return 0;
}

// convert from infix to postfix form 
void InfixToPostfix(char s[], char res[])
{
    Stack op = new_Stack();
    char ans[10000];
    memset(ans, 0, sizeof(ans));
    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            ans[strlen(ans)] = s[i];
        }
        else if (s[i] == '|')
        {
            if (strlen(ans) == 0)
            {
                ans[strlen(ans)] = s[i];
            }
            else
            {
                if (ans[strlen(ans) - 1] != '|')
                {
                    ans[strlen(ans)] = s[i];
                }
            }
        }
        else if (s[i] == '(' || s[i] == '{' || s[i] == '[')
            push(s[i], op);
        else if (s[i] == ')')
        {
            int x;
            while ((x = pop(op)) != '(')
            {
                ans[strlen(ans)] = x;
                if (ans[strlen(ans) - 1] != '|')
                    ans[strlen(ans)] = '|';
            }
        }
        else if (s[i] == '}')
        {
            int x;
            while ((x = pop(op)) != '{')
            {
                ans[strlen(ans)] = x;
                if (ans[strlen(ans) - 1] != '|')
                    ans[strlen(ans)] = '|';
            }
        }
        else if (s[i] == ']')
        {
            int x;
            while ((x = pop(op)) != '[')
            {
                ans[strlen(ans)] = x;
                if (ans[strlen(ans) - 1] != '|')
                    ans[strlen(ans)] = '|';
            }
        }
        else
        {
            if (!isEmptyS(op))
            {
                while (priority(top(op)) >= priority(s[i]))
                {
                    ans[strlen(ans)] = pop(op);
                    if (ans[strlen(ans) - 1] != '|')
                        ans[strlen(ans)] = '|';
                }
            }
            push(s[i], op);
        }
    }
    while (!isEmptyS(op))
    {
        if (ans[strlen(ans) - 1] != '|')
            ans[strlen(ans)] = '|';
        ans[strlen(ans)] = pop(op);
    }
    if (ans[strlen(ans) - 1] != '|')
        ans[strlen(ans)] = '|';
    strcpy(res, ans);
}

// convert from infix to postfix , then to prefix 
void InfixToPrefix(char s[], char res[])
{
    char postfix[10000];
    char infix[10000];
    strcpy(infix, s);
    for (int i = 0; i < strlen(infix); i++)
    {
        if (infix[i] == '(')
            infix[i] = ')';
        else if (infix[i] == ')')
            infix[i] = '(';
        else if (infix[i] == '{')
            infix[i] = '}';
        else if (infix[i] == '}')
            infix[i] = '{';
        else if (infix[i] == '[')
            infix[i] = ']';
        else if (infix[i] == ']')
            infix[i] = '[';
    }
    strrev(infix);
    InfixToPostfix(infix, postfix);
    strrev(postfix);
    strcpy(res, postfix);
}
