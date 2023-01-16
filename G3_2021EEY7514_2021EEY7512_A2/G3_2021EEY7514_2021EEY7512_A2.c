#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<malloc.h>
#include<stdlib.h>

/**
 * @brief Structure for each state 
 * and their link to NEXT_STATES & PREVIOUS_STATE
 * 
 */
struct state_node
{
    int left [4];
    int right [4];
    struct state_node *parent_state;
    struct state_node *child_state_1;
    struct state_node *child_state_2;
    struct state_node *child_state_3;
    struct state_node *child4;
};

/**
 * @brief LINKED LIST CONTAINING ALL THE SOLUTION NODES
 * 
 */
typedef struct solutions_list
{
    int n;
    struct state_node *sol;
    struct solutions_list* next;
}SOLUTION_LIST;

SOLUTION_LIST *ans;
//ans =  malloc(sizeof(struct solution_list));
//ans=NULL;

/**
 * @brief STACK implementation to STORE STATES 
 * when travelling from LEAF to ROOT node in the tree structure
 * 
 */
typedef struct stack
{
        struct state_node *state;
        struct stack *next;
}STACK;

STACK *pp;

/**
 * @brief Create a next child object
 * 
 * @param x 
 * @param L 
 * @param R 
 */
void create_next_child_state(struct state_node* x, int* L, int* R)
{
    struct state_node * N;
    N = malloc(sizeof(struct state_node));
    //Default_initialization
    N->child_state_1=NULL;
    N->child_state_2=NULL;
    N->child_state_3=NULL;
    N->child4=NULL;
    N->parent_state=NULL;

    int i;
    for (i=0; i<4; i++)
        {
            N->left[i] = L[i];
            N->right[i] = R[i];
        }

    N->parent_state = x;
    //To check if priority list of child nodes are occupied or not
    if (x->child_state_1 == NULL)
        x->child_state_1 = N;

    else if (x->child_state_1!=NULL && x->child_state_2 == NULL)
            x->child_state_2 = N;

    else if (x->child_state_1!=NULL && x->child_state_2 != NULL && x->child_state_3 == NULL)
            x->child_state_3 = N;

        else 
        x->child4 = N;
}

/**
 * @brief Check if a particular MOVE/STATE is VALID
 * 
 * @param L 
 * @return int 
 */
int check_validity(int *L)
{
    if ((L[0]==L[2]) || ((L[1]!=L[2]) && (L[2]!=L[3]))) 
    return 1;
    else 
    return 0;
}

/**
 * @brief To compare if two state instances are the same or not
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int compare_states(struct state_node* a, struct state_node* b)
{
    if((a==NULL)||(b==NULL))
        return 0;
    int i, flag = 1;
    for(i=0;i<4;i++)
    {
        if(a->left[i]!=b->left[i])
        {
            flag = 0;
            break;
        }
    }
    
    return flag;
}
/**
 * @brief Display the notations used in this program
 * 
 */
void print_notations()
{
    printf("\n####################  NOTATIONS USED ###############################");
    printf("\nM : Man");
    printf("\nW : Wolf");
    printf("\nG : Goat");
    printf("\nC : Cabbage sack");
    printf("\n1 = Entity  PRESENT (in that river bank)");
    printf("\n0 = Entity  ABSENT  (in that river bank)");
    printf("\n######################################################################");
    printf("\n#####################################################################");
}

/**
 * @brief Function to update the child list of a 
 * particular state
 * 
 * @param x 
 */
void generate_next_states (struct state_node* x)
{   
    if (x->left[0] != 0)/*checking whether man is on left side*/
    {   
        int L[4], R[4], k, l;
        
        for (k=0; k<4; k++)
        {   /*storing array content into array L & R*/
            for (l=0; l<4; l++)
            {
                L[l] = x->left[l];
                R[l] = x->right[l];
            }

            //ONLY MAN moves to RIGHT
            if (k==0)
            {   
                L[0]=0;
                R[0]=1;
                int a, q=0;
                a = check_validity(L);
                if (a==1 && x->parent_state!=NULL)
                        {
                        for (int p=0; p<4; p++)
                            {
                                if (L[p] == x->parent_state->left[p])
                                    q=q+1;
                            }
                         
                        if (q!=4)
                        {
                            create_next_child_state(x, L, R);
                            //break;
                        }
                        
                        }
            }
            else 
            {   
                if (L[k]!=0)
                {   
                    L[0]=0;
                    R[0]=1;
                    L[k]=0;
                    R[k]=1;
                    int b,c, q=0;

                    b = check_validity(L);
                    if (b==1 && x->parent_state==NULL)
                        create_next_child_state(x, L, R);
                    else
                    {  if (b==1 && x->parent_state!=NULL)
                        {
                        for (int p=0; p<4; p++)
                            {
                                if (L[p] == x->parent_state->left[p])
                                q=q+1;
                            }
                            
                        if (q!=4)
                        create_next_child_state(x, L, R);   
                        }
                    }  
                    
                }
            }
    }
}

    else /*checking whether man is on right side*/
    {   
        int L[4], R[4], k, l;
        /*storing array content into array L & R*/
       
        for (k=0; k<4; k++)
        {   
            for (l=0; l<4; l++)
            {
            L[l] = x->left[l];
            R[l] = x->right[l];
            }

            if (k==0)
            {   
                L[0]=1;
                R[0]=0;
                int a,q=0;
                a = check_validity(R);

                    if (a==1 && x->parent_state!=NULL)
                        {
                        for (int p=0; p<4; p++)
                            {
                            if (L[p] == x->parent_state->left[p])
                            q=q+1;
                            }
                        
                            if (q!=4)
                            {
                            create_next_child_state(x, L, R);
                            break;
                            }
                            
                        }
            }   
            else 
            {   
                if (R[k]!=0)
                {   
                    L[0]=1;
                    R[0]=0;
                    L[k]=1;
                    R[k]=0;
                    int b,c, q=0;

                    b = check_validity(R);
                    
                    if (b==1 && x->parent_state==NULL)
                        create_next_child_state(x, L, R);
                    else
                    {  if (b==1 && x->parent_state!=NULL)
                        {
                        for (int p=0; p<4; p++)
                            {
                                if (L[p] == x->parent_state->left[p])
                                    q=q+1;
                            }
                            
                        if (q!=4)
                        create_next_child_state(x, L, R);   
                        
                        }
                            
                    } 
                    
                }
            }
        }
  
    }
}

/**
 * @brief PRINT THE CURRENT STATE
 * 
 * @param current_state 
 */
void print_state(struct state_node *current_state)
{
        printf("\n");
        printf("\n             M W G C");
        printf("\nLEFT BANK:  ");
        for (int m=0; m<4; m++)
            printf(" %d", current_state->left[m]);
        printf("\nRIGHT BANK: ");
        for (int m=0; m<4; m++)
            printf(" %d", current_state->right[m]);
}

/**
 * @brief Explore all possible OPTIMAL solutions
 * 
 * @param current_state 
 * @param end 
 * @return int 
 */
int solutions(struct state_node *current_state, struct state_node *end)
{   
    int count_solution = 1;    
    if (compare_states(current_state,end))
    {
        //printf("\n\n#####################################################");

        //printf("\nans is : %d", ans==NULL);
        if(ans==NULL)
        {
            ans = malloc(sizeof(SOLUTION_LIST));
            ans->next = NULL;
            ans->sol = current_state;
            //printf("\nSOLUTION %d, IF condition satisfied", count_solution);
        }
        else
        {
            SOLUTION_LIST *new_soln, *temp1, *temp2;
            new_soln = (SOLUTION_LIST*) malloc(sizeof(SOLUTION_LIST));
            new_soln->next = NULL;
            new_soln->sol = current_state;
            temp1 = ans;
            while(temp1!=NULL)
            {
                temp2 = temp1;
                temp1=temp1->next;
            }
            //printf("\nlast element or not = %d",temp2->next==NULL);
            //print_state(temp2->sol);
            temp2->next = new_soln;
            //printf("\nSOLUTION %d", count_solution);
        }
        count_solution++;
        print_state(current_state);
        printf("\n\n#########  FINAL STATE REACHED!!! ###########");
        return 0;
    }

    if (current_state==NULL)
        return 0;
        
    //PRINT CURRENT STATE
    print_state(current_state);
    
    //UPDATED CHILDREN STATES
    generate_next_states (current_state);

    if(current_state->child_state_2!=NULL)
    {
        printf("\nCHILD_STATE_2 present,\n PROCEEDING WITH CHILD_STATE_1");
        //print_state(current_state->child_state_2);
    }

    if(current_state->child4!=NULL)
    {
        printf("\nCHILD 3 PRESENT");
        print_state(current_state->child_state_3);
    }


    solutions(current_state->child_state_1, end);

    if(current_state->child_state_2!=NULL)
        printf("\n\nBuilding NEXT_STATE based on CHILD_STATE_2");
    solutions(current_state->child_state_2, end);

    if(current_state->child_state_3!=NULL)
        printf("\n\nBuilding NEXT_STATE based on CHILD_STATE_3");
    solutions(current_state->child_state_3, end);

}

/**
 * @brief To print the operation or movement that gives us the NEXT_STATE
 * 
 * @param from_state 
 * @param to_state 
 */
void print_operation(struct state_node *from_state, struct state_node *to_state)
{
    if(to_state==NULL)
        return;
    printf("\nOPERATION");
    if(from_state->left[0]==1)
    {
        printf("\nMoving RIGHT ( ----> ): Man");
        if((from_state->left[1]!=to_state->left[1]))
            printf(" & Wolf");
        if((from_state->left[2]!=to_state->left[2]))
            printf(" & Goat");
        if((from_state->left[3]!=to_state->left[3]))
            printf(" & Cabbage");
    }
    else
    {
        printf("\nMoving LEFT ( <---- ): Man");
        if((from_state->left[1]!=to_state->left[1]))
            printf(" & Wolf");
        if((from_state->left[2]!=to_state->left[2]))
            printf(" & Goat");
        if((from_state->left[3]!=to_state->left[3]))
            printf(" & Cabbage");
    }
}


int main ()
{
    int L [4]= {1,1,1,1};
    int R [4] = {0,0,0,0}; 
    int i;
    printf("\n#############################################");
    struct state_node *start_state, *end_state;
    start_state = malloc(sizeof(struct state_node));
    for (i=0; i<4; i++)
        start_state->left [i]= 1;
    for (i=0; i<4; i++)
        start_state->right [i]= 0;
    start_state->parent_state = NULL;
    start_state->child_state_1 = NULL;
    start_state->child_state_2 = NULL;
    start_state->child_state_3 = NULL;
    start_state->child4 = NULL;
    
    end_state = malloc(sizeof(struct state_node));
    for (i=0; i<4; i++)
        end_state->left [i]= 0;
    for (i=0; i<4; i++)
        end_state->right [i]= 1;
    end_state->parent_state = NULL;
    end_state->child_state_1 = NULL;
    end_state->child_state_2 = NULL;
    end_state->child_state_3 = NULL;
    end_state->child4 = NULL;

    ans = NULL;

    struct state_node *current_state;
    current_state = start_state;
    print_notations();

    solutions(current_state, end_state);

    printf("\n\n#############################################\n\n");
    SOLUTION_LIST *temp;
    struct state_node *t;
    temp = ans;
    int steps, count = 0;
    while(temp!=NULL)
    {
        printf("\n############## SOLUTION %d ###########", count+1);
        print_notations();

        //ITERATING THROUGH THE SOLUTION LIST
        t = temp->sol;
        steps = 0;
        pp=NULL;
        //BUILDING STACK
        while(t!=NULL)
        {
            if(pp==NULL)
            {
                    pp = malloc(sizeof(STACK));
                    pp->state = t;
                    pp->next = NULL;
            }
            else
            {
                    STACK *g;
                    g = malloc(sizeof(STACK));
                    g->state = t;
                    g->next = pp;
                    pp = g;
            }
            t=t->parent_state;
        }
        
        //PRINTING STACK
        printf("\n\n####### INITIAL STATE ##########");
        while(pp!=NULL)
        {
                print_state(pp->state);
                
                
                if(pp->next!=NULL)
                {
                    printf("\n\n\nSTEP #%d", ++steps);
                    print_operation(pp->state, pp->next->state);
                } 
                else
                {
                    printf("\n######     FINAL STATE REACHED!!!    ########\n\n\n\n");
                    print_operation(pp, NULL);
                }
                    
                
                pp = pp->next;
        }
        
        temp = temp->next;
        count++;
    }

    printf("\n\n\t\t There are %d optimal solutions present for the given problem.\n\n\n", count);
}