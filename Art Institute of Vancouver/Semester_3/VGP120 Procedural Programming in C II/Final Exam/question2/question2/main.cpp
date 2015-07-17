/* Fig. 12.19: fig12_19.c
   Create a binary tree and traverse it 
   preorder, inorder, and postorder */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* self-referential structure */
struct treeNode { 
   struct treeNode *leftPtr;  /* pointer to left subtree */
   int data; /* node value */
   struct treeNode *rightPtr; /* pointer to right subtree */
}; /* end structure treeNode */

typedef struct treeNode TreeNode; /* synonym for struct treeNode */
typedef TreeNode *TreeNodePtr; /* synonym for TreeNode* */

/* prototypes */
void insertNode( TreeNodePtr *treePtr, int value );
void inOrder( TreeNodePtr treePtr );
void preOrder( TreeNodePtr treePtr );
void postOrder( TreeNodePtr treePtr );

int main( void )
{
	int i;	//counter
	char item;//variable to hold random values
	TreeNodePtr rootPtrA = NULL;//tree initially empty
	insertNode( &rootPtrA, 'M');
	TreeNodePtr rootPtrB = NULL;//tree initially empty
	insertNode( &rootPtrB, 'M');

	srand((unsigned)time(NULL));

	printf("The numbers being placed in the tree are:\n"	);

	for( i = 1; i <= 5; i++ )
	{
		item = rand() % 65 + 26;
		printf( "%c", item );
		insertNode( &rootPtrA, item );
	}

	printf("The numbers being placed in the tree are:\n");

	for(i = 1; i <= 5; i++)
	{
		item = rand() % 65 + 26;
		printf( "%c", item );
		insertNode( &rootPtrB, item );
	}

	//traverse the tree preOrder
	printf( "\n\nThe preOrder traversal is:\n" );
	preOrder( rootPtr );

	//traverse the tree inOrder
	printf( "\n\nThe inOrder traversal is:\n" );
	inOrder( rootPtr );

	//traverse the tree postOrder
	printf( "\n\nThe postOrder traversal is:\n" );
	postOrder( rootPtr );

	return 0;

}

/* insert node into tree */
void insertNode( TreeNodePtr *treePtr, int value )
{ 
   
   /* if tree is empty */
   if ( *treePtr == NULL ) {   
      *treePtr = malloc( sizeof( TreeNode ) );

      /* if memory was allocated then assign data */
      if ( *treePtr != NULL ) { 
         ( *treePtr )->data = value;
         ( *treePtr )->leftPtr = NULL;
         ( *treePtr )->rightPtr = NULL;
      }
      else {
         printf( "%d not inserted. No memory available.\n", value );
      }

   }
   else { /* tree is not empty */

      /* data to insert is less than data in current node */
      if ( value < ( *treePtr )->data ) {
         insertNode( &( ( *treePtr )->leftPtr ), value );
      } /* end if */

      /* data to insert is greater than data in current node */
      else if ( value > ( *treePtr )->data ) {
         insertNode( &( ( *treePtr )->rightPtr ), value );
      } /* end else if */
      else { /* duplicate data value ignored */
         printf( "dup" );
      }

   }

}

/* begin inorder traversal of tree */
void inOrder( TreeNodePtr treePtr )
{ 

   /* if tree is not empty then traverse */
   if ( treePtr != NULL ) { 
      inOrder( treePtr->leftPtr );
      printf( "%3d", treePtr->data );
      inOrder( treePtr->rightPtr );
   }

}

/* begin preorder traversal of tree */
void preOrder( TreeNodePtr treePtr )
{ 

   /* if tree is not empty then traverse */
   if ( treePtr != NULL ) { 
      printf( "%3d", treePtr->data );
      preOrder( treePtr->leftPtr );
      preOrder( treePtr->rightPtr );
   }

}

/* begin postorder traversal of tree */
void postOrder( TreeNodePtr treePtr )
{ 

   /* if tree is not empty then traverse */
   if ( treePtr != NULL ) { 
      postOrder( treePtr->leftPtr );
      postOrder( treePtr->rightPtr );
      printf( "%3d", treePtr->data );
   }

}