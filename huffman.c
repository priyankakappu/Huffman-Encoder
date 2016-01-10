
/* Huffman encoder*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
	char symbol;
	int frequency;
	char huff[100];
	struct node *tailptr;
	struct node *rightptr;
	struct node *leftptr;
	};


struct node* makenode (char symbol, int frequency);
struct node* attachnode (struct node * tol, struct node * nptr);
void displaylist (struct node * tol);
struct node* findnode (struct node * tol, char symbol);
void sortlist (struct node * nptr);
void deletenode (struct node *nptr);
struct node* copylist (struct node* tolptr);
void displaytree(struct node *htree);
void printree(struct node *tree);
void makehuff(struct node *tree, char *hstring);

main()
{
	char s[] = "ABCD"; 
	struct node *nptr, *tol, *sptr, *tolptr;
	struct node *copy_list, *tree;
	int i = 0;
	tol=NULL;
	
// Test makenode and attachnode
	
	printf("Test makenode\n");
	sptr = makenode('A',100);
	tol = attachnode(tol,sptr);
	sptr = makenode('B',200);
	tol = attachnode(tol,sptr);
	sptr = makenode('C',10);
	tol = attachnode(tol,sptr);
	sptr = makenode('D',50);
	tol = attachnode(tol,sptr);
	displaylist (tol);
	tolptr = tol;
	
// Copy list
	printf("Copy of the list\n");
	copy_list = copylist(tolptr);
	displaylist(copy_list);
	
// Test findnode
	printf("Find a node\n");
	nptr = findnode(tol,'C');
	displaylist(nptr);
	
	
// Test sortlist
	sortlist(tolptr);
	printf("Sorted list\n");
	displaylist(tolptr);
	
	
	
//	while(s[i] != '\0')
//	{
//		nptr = findnode (tol,s[i]);			/* To check if the node for the character s[i] is already created */
//		if(nptr == NULL) 
//		{
//			sptr = makenode (s[i],1);		/* Make a node for s[i] and assign it to sptr */
//			tol = attachnode (tol,sptr);	/* Attach sptr to the linked list */
//		}
//		else
//			nptr->frequency++;				/* Increment frequency of nptr if the node for the character s[i] already exists */
//	}
//	i++;  
	
//Huffman tree
/*
	A: 100
	B: 200
	C: 10
	D: 50	*/
	printf("Begin Huffman code...\n\n");
	struct node *huff_sym, *huff_freq;
	struct node *h1, *h2, *hnew, *hnew_copy;
	struct node *htree;
	
	huff_freq = copylist(tolptr);
	huff_sym = copylist(tolptr);
	
	printf("Iter 1..............................\n");
	h1 = huff_freq;											//h1 is assigned node with least freq
	h2 = huff_freq->tailptr;								//h2 is the next lowest freq
	hnew = makenode('*',h1->frequency + h2->frequency);		//new node with freq as sum of h1 and h2
	hnew->leftptr = h1;
	hnew->rightptr = h2;				
	huff_freq = h2->tailptr;								// h1, h2 removed from list
//	printf("Hnew leftptr: %c %d\n", hnew->symbol, hnew->frequency);
	
	huff_freq = attachnode(huff_freq,hnew);					//attach new node to the list
	sortlist(huff_freq);									//sort the list after attaching new node
	displaylist(huff_freq);
	printf("\n");
	
	tree = hnew;
	printf("Huffman tree\n");								
	displaytree(tree);
	printf("\n");
	
	printf("Iter 2..............................\n");
	h1 = huff_freq;
	h2 = huff_freq->tailptr;
	hnew = makenode('*',h1->frequency + h2->frequency);
	hnew->leftptr = h1;
	hnew->rightptr = h2;
	huff_freq = h2->tailptr;
	
	huff_freq = attachnode(huff_freq,hnew);
	sortlist(huff_freq);
	displaylist(huff_freq);
	printf("\n");
	
	tree = hnew;
	printf("Huffman tree\n");
	displaytree(tree);
	printf("\n");
	
	printf("Iter 3..............................\n");
	h1 = huff_freq;
	h2 = huff_freq->tailptr;
	hnew = makenode('*',h1->frequency + h2->frequency);
	hnew->leftptr = h1;
	hnew->rightptr = h2;
	huff_freq = h2->tailptr;
	
	huff_freq = attachnode(huff_freq,hnew);
	sortlist(huff_freq);
	displaylist(huff_freq);
	
	tree = hnew;
	printf("Huffman tree\n");
	displaytree(tree);
	printf("\n");
	
	char hstring[100];
	hstring[0]='\0';
	makehuff(tree, hstring);
	printf("\n");
	
	printf("HUFFMAN ENCODER FINAL\n");
	printf("\n");
	printree(tree);
	
}

/* To make node */
struct node * makenode (char symbol, int frequency)
{
	struct node * nptr;
	nptr = (struct node *) malloc (sizeof(struct node));
	nptr->symbol=symbol;
	nptr->frequency=frequency;
	nptr->huff[0]='\0';
	nptr->tailptr=NULL;
	nptr->rightptr = NULL;
	nptr->leftptr = NULL;
	
	return nptr;
}

/* To attach node */
struct node * attachnode (struct node * tol, struct node * nptr)
{
	struct node * cptr;
	if(tol == NULL)
		return (nptr);
	else
	{
		cptr = tol;
		while(cptr->tailptr != NULL)
			cptr = cptr->tailptr;
		cptr->tailptr = nptr;
	}
	return tol;			
}


/* To delete node */
void deletenode(struct node *nptr)
{
	free(nptr);
}

/*To display list */
void displaylist (struct node * tol)
{
	struct node * nptr;
	nptr = tol;
	while (nptr != NULL)
	{
		if(nptr->tailptr!=NULL)
		{
			printf(" Node:%p  symbol: %c  frequency:%d  huff:%s  tailptr->symbol:%c\n", 
				nptr, nptr->symbol, nptr->frequency, nptr->huff, nptr->tailptr->symbol);
		}
		else
			printf(" Node:%p  symbol: %c  frequency:%d  huff:%s  tailptr:%p\n", 
				nptr, nptr->symbol, nptr->frequency, nptr->huff, nptr->tailptr);
		nptr = nptr->tailptr;
	}
}

/* To find node */
struct node * findnode (struct node * tol, char symbol)
{
	struct node * nptr;
	nptr = tol;		//nptr points to top of list
	while (nptr != NULL)
	{
		if(nptr->symbol == symbol)	
			return nptr;
		else
			nptr = nptr->tailptr;			
	}
	return NULL;
}

/* To sort list */
void sortlist (struct node * nptr)
{
	struct node * iptr, *jptr;
	char temp_symbol;
	int temp_frequency;
	struct node *temp_rightptr, *temp_leftptr;
	iptr = nptr;
	while (iptr->tailptr != NULL)
	{
		jptr = nptr;
		while (jptr->tailptr != NULL)
		{
			if(jptr->frequency > jptr->tailptr->frequency)
			{
				temp_symbol = jptr->tailptr->symbol;
				temp_frequency = jptr->tailptr->frequency;
				temp_rightptr = jptr->tailptr->rightptr;
				temp_leftptr = jptr->tailptr->leftptr;
				
				jptr->tailptr->symbol = jptr->symbol;
				jptr->tailptr->frequency = jptr->frequency;
				jptr->tailptr->rightptr = jptr->rightptr;
				jptr->tailptr->leftptr = jptr->leftptr;
				
				jptr->symbol = temp_symbol;
				jptr->frequency = temp_frequency;
				jptr->rightptr = temp_rightptr;
				jptr->leftptr = temp_leftptr;				
			}
			jptr = jptr->tailptr;
		}
		iptr = iptr->tailptr;
	}
	
}

// copy list

struct node* copylist (struct node* tolptr)
{
	struct node *srcptr, *destptr, *nptr, *copy_list;
	srcptr = tolptr;
	while(srcptr!=NULL)
	{
		nptr = makenode(srcptr->symbol, srcptr->frequency);
		if(srcptr == tolptr)	
		{
			destptr = nptr;
			copy_list = destptr;
		}
		else
		{
			destptr->tailptr = nptr;
			destptr = nptr;
		}
		srcptr = srcptr->tailptr;
	}
	return(copy_list);
}

// To displaytree

void displaytree(struct node *tree)
{
	struct node *htree;
	htree = tree;
	while(htree!=NULL)
	{
		printf("Node:%c	Frequency:%d\n", htree->symbol,htree->frequency);
		if(htree->leftptr!=NULL)
			printf("left Node:%c Frequency:%d\n", htree->leftptr->symbol,htree->leftptr->frequency);
		
		if(htree->rightptr!=NULL)
			printf("Right Node:%c Frequency:%d\n", htree->rightptr->symbol,htree->rightptr->frequency);
		
		htree = htree->leftptr;
	}
	
} 

void printree(struct node *tree)
{
	if(tree!=NULL)
	{
		printf("Node:%c	huff:%s\n", tree->symbol,tree->huff);
		printree(tree->leftptr);
		printree(tree->rightptr);		
	}
		
} 

void makehuff(struct node *tree, char *hstring)
{
	char leftstr[100], rightstr[100];
	if(tree!=NULL)
	{
		strcpy(tree->huff, hstring); //Initially assign null to huff
		strcpy(leftstr, hstring);
		strcat(leftstr,"0");	//concatenate left node with 0
		strcpy(rightstr, hstring);
		strcat(rightstr,"1");	//concatenate right node with 1
		
		printf("Makehuff node: %c %d huff = %s\n", tree->symbol, tree->frequency, tree->huff);
						
		printf("Huff encode:tree->leftptr = %p, hstring=%s\n",tree->leftptr, leftstr );
		makehuff(tree->leftptr,leftstr);
		printf("Huff encode:tree->rightptr = %p, hstring = %s\n",tree->rightptr, rightstr);
		makehuff(tree->rightptr,rightstr);

	}
} 

