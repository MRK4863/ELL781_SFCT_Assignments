#include <iostream>
#include <cmath>

using namespace std;
/**
 * @brief DONE BY
 * 1. NAMAN DWIVEDI	-> EEY217514
 * 2. M. RUPESH KUMAR	-> EEY217512 
 */
/**
 * @brief Structure of a node
 * @param parent pointer to parent of a node
 * @param left pointer to left of current node
 * @param right pointer to the right of current node
 * @param child pointer to the child of current node
 * @param degree number children in child list of current node
 * @param mark indicates whether
 */
struct FH_node
{
  struct FH_node *parent;
  struct FH_node *left;
  struct FH_node *right;
  struct FH_node *child;
  int degree;
  int mark;
  int key; 
};


/**
 * @brief Default NODE settings for a fibanocci heap
 * 
 * @return FH_node* 
 */
FH_node *default_node()
{
	FH_node *x;
	x = new FH_node;
	x->left = x;
	x->right = x;
	x->child = NULL;
	x->parent = NULL;
	x->key = 0;
	x->degree=0;
	x->mark=0;

	return x;
}

void display_node(FH_node *temp)
{
	std::cout<<"\nKey "<<temp->key;
	std::cout<<"\tmark "<<temp->mark;
	std::cout<<"\tdegree "<<temp->degree;
}

class fib_heap
{
	public:
		int N;
		FH_node *min;

	void make_fib_heap()
	{
		min = NULL;
		N = 0;
	}

	fib_heap()
	{
		make_fib_heap();
	}

	void disp_N_min()
	{
		std::cout<<"\nNumber of nodes in the Heap: "<<N;
		if(min!=NULL)
			std::cout<<"\nmin value:"<<min->key<<endl;
	}

	void disp_roots()
	{
		FH_node *temp;
		temp = min;
		if(temp ==NULL)
		{
			std::cout<<"\n The fibanocci heap is empty.";
			return;
		}
		
		std::cout<<endl;

		std::cout<<temp->key<<"<--->";
		temp = temp->right;
		while(temp!=min)
		{
			std::cout<<temp->key<<"<-->";
			temp = temp->right;
		}
		std::cout<<endl;

		
	}

	void display_root_nodes_properties()
	{
		FH_node *t;
		std::cout<<"\nDISPLAYING PROPERTIES OF ROOT NODES";
		do
		{
			
			display_node(t);
			if(t->right!=NULL)
				std::cout<<"\nRight value: "<<t->right->key;
			if(t->left!=NULL)
				std::cout<<"\nLeft value: "<<t->left->key;
			t=t->right;
		} while (t!=min);
	}

	/**
	 * @brief Insert a tree to the Heap object
	 * 
	 * @param x pointer to root of the min_heap
	 * @param n number of node in min_heap
	 */
	void insert_tree(FH_node *x, int n)
	{
		if(min==NULL)
		{
			min = x;
		}
		else
		{
			std::cout<<"\nFib heap NOT empty.\nInserting a new node to the left of min node";
			FH_node *left_node;
			left_node = min->left;

			x->right = min;
			x->left = left_node;

			left_node->right = x;
			min->left = x;
			
			if(x->key<min->key)
			{
				std::cout<<"\naddress of min: "<<&min;
				min = x;
				std::cout<<"\naddress of min: "<<&min;
			}
		}
		N=N+n;
	}

	/**
	 * @brief Insert a new node to the heap object
	 * 
	 */
	void fib_heap_insert_node()
	{
		FH_node *x;
		x = default_node();
		std::cout<<"\nEnter the key value of the new node: ";
		std::cin>>x->key;

		std::cout<<"\nInserting a new node";
		if(min==NULL)
		{
			std::cout<<"\nFib heap is empty";
			std::cout<<"\naddress of min: "<<&min;
			min = x;
			std::cout<<"\naddress of min: "<<&min;
		}
		else
		{
			std::cout<<"\nFib heap NOT empty.\nInserting a new node to the left of min node";
			FH_node *left_node;
			left_node = min->left;

			x->right = min;
			x->left = left_node;

			left_node->right = x;
			min->left = x;
			
			if(x->key<min->key)
			{
				std::cout<<"\naddress of min: "<<&min;
				min = x;
				std::cout<<"\naddress of min: "<<&min;
			}
		}
		N++;
	}

	/**
	 * @brief Function to find the minimum of the fibanocci heap and return the value
	 * 
	 * @return int 
	 */
	void find_min()
	{
		int temp;
		temp = min->key;
		std::cout<<"\nThe min. value: "<<temp;
		std::cout<<"\nProperties";
		display_node(min);
	}


	/**
	 * @brief Function CUT to cut node x from the child list of node y
	 * 
	 * @param x 
	 * @param y 
	 */
	void cut(FH_node *x, FH_node *y)
	{
		std::cout<<"\nCUT in progress";
		FH_node *rnode, *lnode;
		rnode = x->right;
		lnode = x->left;
		if(x==rnode)
			y->child = NULL;

		lnode->right = rnode;
		rnode->left = lnode;
		
		if(x==x->parent->child)
			y->child = rnode;


		x->parent = NULL;

		// S#2
		//y->mark=1;
		y->degree=y->degree-1;

		// S#3
		x->left = min;
		x->right = min->right;
		(min->right)->left = x;
		min->right = x;
		
		x->parent = NULL;
		x->mark = 0;
	}

	/**
	 * @brief Function to recursively apply CUT operation on parent node if they are already marked.
	 * Base case: Mark the parent node and terminate operation
	 * @param y 
	 */
	void cascading_cut(FH_node *y)
	{
		std::cout<<"\nCascading cut in progress";

		FH_node *z;
		z = y->parent;
		

		if(z!=NULL)
		{
			std::cout<<"\nNode key"<<y->key;
			std::cout<<"\nParent key"<<z->key;
			std::cout<<"\ny->mark = "<<y->mark;
			if((y->mark) ==0)
			{
				y->mark = 1;
				std::cout<<"\nY is marked....End of Story"<<endl;
			}
			else
			{
				std::cout<<"\nAgain cut"<<endl;
				cut(y,z);
				cascading_cut(z);
			}
		}
	}
	/**
	 * @brief DECREASE KEY function to decrease the key of particular node
	 * 
	 * @param x 
	 * @param new_key 
	 * @return int 
	 */
	int decrease_key()
	{
		FH_node *x;
		int k, new_key;

		if(N==0)
		{
			std::cout<<"\nNO ELEMENTS AVAILABLE IN HEAP!\n";
			return 0;
		}

		std::cout<<"\nEnter the key of the node that has to be searched: ";
		std::cin>>k;

		
		x = search_node_given_key(k);
		if(x==NULL)
		{
			std::cout<<"TRY AGAIN";
			return 0;
		}

		std::cout<<"\nEnter the NEW KEY: ";
		std::cin>>new_key;

			
		std::cout<<"\n Decreasing key"<<x->key<<" to "<< new_key;
		//CASE 1
		if(new_key>x->key)
		{
			std::cout<<"\nThe new key for this node is higher than its original key. Cancelling decrease_key operation";
			return 0;
		}

		FH_node *y;
		x->key = new_key;
		y = x->parent;

		if((y!=NULL) && (x->key<y->key))
		{
			cut(x,y);
			cascading_cut(y);		
		}

		if(x->key<min->key)
		{
			min = x;
			return 0;
		}
	}

	/**
	 * @brief Remove node Y from the root-list and make it a child of node X
	 * 
	 * @param y 
	 * @param x 
	 */
	void fib_heap_link(FH_node *y, FH_node *x)
	{
		
		std::cout<<"\nEntering FIB_HEAP_LINK: ";

		//if(y->key==x->key)
		//	return;


		// S#1 remove y from root list of H (Bypassing)
		FH_node *lnode, *rnode;
		lnode = y->left;
		rnode = y->right;
		lnode->right = rnode;
		rnode->left = lnode;

		//self linking
		y->left = y;
		y->right = y;

		if(x->right == x)
		{
			min =x;
		}

		y->parent = x;

		if(x->child ==NULL)
		{
			x->child = y;
		} 
		else
		{
			lnode = x->child;
			rnode = x->child->right;

			y->left = lnode;
			y->right = rnode;

			rnode->left = y;
			lnode->right = y;

			if(y->key < x->child->key)
				x->child =y;
		}
		x->degree +=1;
		y->mark = 0;
	}

	/**
	 * @brief A fucntion to rearrange the trees in root list so that, 
	 * each node in the root list have a unique degree
	 * 
	 */
	void consolidate()
	{
		//assuming max. degree to be 5
		int d, i;

		//Maximun degree calculation
		float f = (log(N))/(log(2));
		std::cout<<"\nEntering CONSOLIDATE: "<<"\nthe value of D is : "<<int(f);
		int D;
		D = f+1;

		//array of pointers.
		FH_node *A[D];

		//intializing the array to NULL
		for(i=0;i<=D;i++)
			A[i] = NULL;
		
		//w to iterate through each node in the child list
		FH_node *w, *x, *y, *temp, *temp_min;
		temp_min = min;
		w = min;
	
		do
		{
			x = w;
			w = w->right;

			display_node(x);
			display_node(w);
			d = x->degree;
			std::cout<<"\nkey and degree of root node UNDER CONSIDERATION = "<<x->key<<" "<<d;
			while(A[d]!=NULL)
			{
				y = A[d];

				std::cout<<"\nkey and degree of CONFLICT root node = "<<y->key<<" "<<d;
					
				if(x->key == y->key)
				{
					std::cout<<"\n\nERROR!!!\tERROR!!!\tERROR!!!\n";
				}

				if (x->key>y->key)
				{
					//Exchange x and y
					temp = x;
					x = y;
					y = temp;
				}
				

				if(y==min)
				{
					min =x;
				}

				std::cout<<"\nSUPERIOR NODE";
				display_node(x);
				std::cout<<"\nINFERIOR NODE";
				display_node(y);
				fib_heap_link(y,x);

				if(x->right ==x)
					min = x;

				A[d] = NULL;
				d++;
			}
			A[d] = x;
		} while (w!=temp_min);
		
		//each index in A[] points to a root node
		min = NULL;

		for(i=0; i<=D; i++)
		{
			if(A[i]!=NULL)
			{
				A[i] ->right = A[i];
				A[i] ->left = A[i];

				if(min ==NULL)
				{
					//create root list for H just containing A[i]
					min = A[i];
				}
				else 
				{
					//insert_tree(A[i]);
					min->left->right=A[i];
					A[i]->right = min;
					A[i]->left = min->left;
					min->left = A[i];

					if(A[i]->key<min->key)
						min = A[i];
				}
			}
		}
	}

	/**
	 * @brief Extract the minimum node from the Fib-Heap
	 * 
	 * @return FH_node* 
	 */
	FH_node* fib_heap_extract_min()
	{
		FH_node *p, *ptr, *x, *pp, *lnode, *rnode, *t;
		FH_node *z;
		z = min;
		
		if(N==0)
		{
			std::cout<<"\nNO ELEMENTS AVAILABLE IN HEAP!\n";
			return 0;
		}

		std::cout<<"\nExtracting min...........\n";
		if (z==NULL)
			return z;

		

		if(N==1)
		{
			p = min;
			min = NULL;
			N=0;
			return p;
		}

		x = z->child;

		if(x==NULL && N>1)
		{
			FH_node *temp;
			
			//remove z from the root list of H
			z->left->right = z->right;
			z->right->left = z->left;

			//setting MIN pointer to the RIGHT node in the root list
			min = z->right;

			temp = min;
			//updating min pointer to the next smallest root node
			do
			{
				if(temp->key<min->key)
				{
					min = temp;
				}					
				temp =temp->right;
			} while(temp!=min);
			N--;
			return z;
		}

		

		if(x!=NULL && N>1)
		{
			//refernce child
			ptr = x;
			pp = x;
			do
			{
				//iterating through the child list of z
				std::cout<<"\nChild list promotd to the root list\n";
				std::cout<<x->key<<endl;

				//storing right neibhour of current child
				pp = x->right;

				//attatching x to the root list to the left of min
				lnode = min->left;
				lnode->right = x;
				x->right = min;
				x->left = min->left;
				min->left = x;
				x->parent = NULL;

				//updating min pointer
				if(x->key < min->key)
					min = x;
				
				x = pp;

			} while (pp!=ptr);
			//remove z from the root list of H
			z->left->right = z->right;
			z->right->left = z->left;
			z->child = NULL;

			//setting MIN pointer to the RIGHT node in the root list
			min = z->right;
			
			std::cout<<"\n The roots after promotion are: ";
			disp_roots();
			display_root_nodes_properties();


			if(z==z->right)
				min = NULL;
			else
			{
				min = z->right;
				disp_roots();
				t = min;
			//updating min pointer to the next smallest root node
				do
				{
					if(t->key<min->key)
					{
						min = t;
					}					
					t =t->right;
				} while(t!=min);
				disp_roots();
				consolidate();
			}
			N--;
			return z;
		}
		
		std::cout<<"BYPASS";
		N--;
		return z;

	}

	FH_node* search_node_given_key(int k)
	{
		FH_node *temp, *child_l1, *child_l2, *child_l3, *child_l4;
		temp = min;
		//std::cout<<"\n\nPRINTING THE ENTIRE FIBONACCI HEAP";
		do
		{
			//std::cout<<"\n\n\nROOT NODE:";
			if (k == temp->key)
				return temp;
			if(temp->degree>0)
			{

				//std::cout<<"\nPrinting the children(LEVEL 1)";
				child_l1 = temp->child;
				
				do
				{
					if (k == child_l1->key)
						return child_l1;
					if(child_l1->degree>0)
					{

						child_l2 = child_l1->child;
						
						do
						{
							//std::cout<<"\nLEVEL 1 CHILD";
							if (k == child_l2->key)
								return child_l2;

							if(child_l2->degree>0)
							{
								child_l3 = child_l2->child;
								do
								{
									if (k == child_l3->key)
										return child_l3;
									if(child_l3->degree>0)
									{
										child_l4 = child_l3->child;
										do
										{
											if (k == child_l4->key)
												return child_l4;
										} while (child_l4!=child_l4->right);
									}
											
									child_l3=child_l3->right;
								}while(child_l3!=child_l2->child);
							}
							child_l2=child_l2->right;
						} while (child_l2!=child_l1->child);
						
					}
					child_l1 = child_l1->right;
				} while (child_l1!=temp->child);
			}
			temp = temp->left;
		}while(temp!=min);

		std::cout<<"\nTHE KEY DOES NOT EXIST IN THE GIVEN TREE\n";
		return NULL;
	}

	
};

/**
 * @brief Function to print the entire heap
 * 
 * @param H 
 */
int print_fib_heap(fib_heap H)
{
	FH_node *temp, *child_l1, *child_l2, *child_l3;
	temp = H.min;
	std::cout<<"\n\nPRINTING THE ENTIRE FIBONACCI HEAP";
	if(H.N==0)
	{
		std::cout<<"\nThe Fibonacci Heap is Empty.";
		return 0;
	}

	do
	{
		std::cout<<"\n\n\nROOT NODE:";
		display_node(temp);
		if(temp->degree>0)
		{
			std::cout<<"\nPrinting the children(LEVEL 1)";
			child_l1 = temp->child;
			do
			{
				std::cout<<"\nLEVEL 1 CHILD";
				display_node(child_l1);
				if(child_l1->degree>0)
				{
					std::cout<<"\nPrinting the children(LEVEL 2)";
					child_l2 = child_l1->child;
					do
					{
						std::cout<<"\nLEVEL 2 CHILD";
						display_node(child_l2);
						if(child_l2->degree>0)
						{
							child_l3 = child_l2->child;
							do
							{
								std::cout<<"\nLEVEL 3 CHILD";
								display_node(child_l3);	
								child_l3=child_l3->right;
							}while(child_l3!=child_l2->child);
						}
						child_l2=child_l2->right;
					} while (child_l2!=child_l1->child);
					
				}
				child_l1 = child_l1->right;
			} while (child_l1!=temp->child);
			std::cout<<endl;
		}
		temp = temp->left;
	}while(temp!=H.min);
	return 0;
}


/**
 * @brief Hard coded values for a sample fibanocci heap
 * 
 * @param H1 fibanocci heap object
 * @return fib_heap 
 */
fib_heap hard_coded_value(fib_heap H1)
{
	FH_node *x, *temp, *c1, *c2, *c3;
	// inserting 7
	
	//min-heap - 1
	x = default_node();
	temp = default_node();

	x->key = 7;
	x->degree = 1;
	x->child = temp;

	temp->key = 9;
	temp->parent = x;

	H1.insert_tree(x, 2);

	//min-heap - 2
	x = default_node();
	c1 = default_node();
	c2 = default_node();
	c3 = default_node();

	x->key = 2;
	x->degree = 2;
	x->child = c2;
	
	c1->key = 4;
	c1->degree = 1;
	c1->right = c2;
	c1->left = c2;
	c1->child = c3;
	c1->parent = x;

	c2->key = 3;
	c2->right = c1;
	c2->left = c1;
	c2->parent = x;

	c3->key = 6;
	c3->parent = c1;

	H1.insert_tree(x,4);
	return H1;
}

/**
 * @brief Hard coded fib-heap from textbook example
 * 
 * @param H1 
 * @return fib_heap 
 */
fib_heap hard_coded_value_2(fib_heap H1)
{
	FH_node *x_3, *x_17, *x_24, *x_23, *x_7, *c1, *c2, *c3, *cc1, *cc3;
	//min_heap PRIME
	x_3 = default_node();
	c1 = default_node();
	c2 = default_node();
	c3 = default_node();
	cc1 = default_node();
	cc3 =  default_node();

	x_3->key = 3;
	x_3->degree = 3;
	x_3->child = c1;
	//x_3->right = x_17;
	//x_3->left = x_7;

	c1->key = 18;
	c1->degree = 1;
	c1->right = c2;
	c1->left = c3;
	c1->child = cc1;
	c1->parent = x_3;
	c1->mark = 1;

	c2->key = 52;
	c2->left = c1;
	c2->right = c3;
	c2->parent = x_3;

	c3->key = 38;
	c3->degree = 1;
	c3->left = c2;
	c3->right = c1;
	c3->parent = x_3;
	c3->child = cc3;

	cc1->key = 39;
	cc1->mark = 1;
	cc1->parent = c1;

	cc3->key = 41;
	cc3->parent = c3;
	H1.insert_tree(x_3, 6);

	//Min heap - 2
	x_7 = default_node();
	
	x_7->key = 7;

	H1.insert_tree(x_7,1);

	//min heap - 3

	x_23 = default_node();
	
	x_23->key = 23;

	H1.insert_tree(x_23,1);

	//min-heap 4
	x_24 = default_node();
	c1 = default_node();
	c2 = default_node();
	cc1 = default_node();

	x_24->key = 24;
	x_24->child = c1;
	x_24->degree = 2;

	c1->key = 26;
	c1->degree = 1;
	c1->right = c2;
	c1->left = c2;
	c1->child = cc1;
	c1->parent = x_24;
	c1->mark = 1;

	c2->key = 46;
	c2->left = c1;
	c2->right = c1;
	c2->parent = x_24;

	cc1->key = 35;
	cc1->parent = c1;

	H1.insert_tree(x_24,4);

	//min_heap 5
	x_17 = default_node();
	c1 = default_node();

	x_17->key = 17;
	x_17->degree = 1;
	x_17->child = c1;

	c1->key = 30;
	c1->parent = x_17;

	H1.insert_tree(x_17,2);

	return H1;
}

int main()
{
	fib_heap H;
	FH_node *temp, *min_pointer, *show;
	int c;
	do
	{
		std::cout<<"\n\nEnter your choice:";
		std::cout<<"\n1. DEMO HEAP FROM TEXT_BOOK";
		std::cout<<"\n2. INSERT NEW NODE";
		std::cout<<"\n3. FIND MIN";
		std::cout<<"\n4. EXTRACT MIN";
		std::cout<<"\n5. DECREASE KEY";
		std::cout<<"\n6. PRINT ENTIRE HEAP";
		std::cout<<"\n7. PRINT ROOT NODES";
		std::cout<<"\n8. EXIT\n";
		std::cin>>c;
		switch(c)
		{
			case 1: std:cout<<"\n######### DEMO HEAP FROM THE CLRS TEXT_BOOK ##############\n";
				H = hard_coded_value_2(H);
				H.disp_roots();
				H.disp_N_min();
				break;
			case 2: std::cout<<"\n\n################   INSERTION NEW NODE    ###################";
				H.fib_heap_insert_node();
				H.disp_roots();
				H.disp_N_min();
				break;
			case 3: std::cout<<"\n\n################   FIND MIN    ###################";
				H.find_min();
				//H.disp_roots();
				//H.disp_N_min();
				break;
			case 4: std::cout<<"\n\n\n################   EXTRACT_MIN OPERATION    ###################";
				show = H.fib_heap_extract_min();
				if(show!=NULL)
					std::cout<<"\nThe value extracted is: "<<show->key;
				else
					std::cout<<"\nNO ELEMENTS FOUND";
				H.disp_roots();
				H.disp_N_min();
				break;
			case 5: std::cout<<"\n\n\n################   DECREASE_KEY OPERATION   ###################";
				H.decrease_key();
				H.disp_roots();
				H.disp_N_min();
				break;
			case 6: print_fib_heap(H);
				break;
			case 7: H.disp_roots();
				break;
			deafult: continue;
		}
	} while (c!=8);
	

	


	
/*	

	H.fib_heap_insert_node();

	H.disp_roots();
	H.disp_N_min();

	

	std::cout<<"\n\n\n################   DECREASE_KEY OPERATION(NODE(46)->15)    ###################";
	temp=H.min->child->right;
	display_node(temp);

	temp = H.min->child->right->child->right;
	display_node(temp);

	H.decrease_key(temp, 15);
	H.disp_roots();
	H.disp_N_min();

	temp = H.min->child->right->child->child;
	display_node(temp);

	print_fib_heap(H);

	std::cout<<"\n\n\n################   DECREASE_KEY OPERATION(NODE(35)->5)    ###################";
	H.decrease_key(temp, 5);
	H.disp_roots();
	H.disp_N_min();
	std::cout<<"\nFINAL VERIFICATION\nROOT NODES LIST AND THEIR PROPERTIES\n";
	
	print_fib_heap(H);
*/

}