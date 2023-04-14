#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//二叉排序树结构体
typedef struct Tree //二叉树
{
    int data;           //数据域
    struct Tree *left;  //左子节点指针
    struct Tree *right; //右子节点指针
} Tree;

//节点创建函数
Tree *createBinarySortTreeNode(int data)
{
    Tree *node = (Tree *)malloc(sizeof(Tree));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}


//辅助栈
typedef struct data
  {   
      Tree* nValue;
      struct data *pNext;
  }MyStack;
  
  typedef struct stack
  {   
      int nCount;
      MyStack *pTop;
  }Stack;
  
  void s_Init(Stack **pStack)
  {   
      *pStack=(Stack*)malloc(sizeof(Stack));
      (*pStack)->nCount=0;
      (*pStack)->pTop=NULL;
  }
  void s_Push(Stack *pStack,Tree* nNum)
  {   
      if(pStack==NULL)
      {
          printf("不存在\n");
          return;
      }
       
       MyStack *pTemp=NULL;
       pTemp=(MyStack*)malloc(sizeof(MyStack));
       pTemp->nValue=nNum;
       pTemp->pNext=pStack->pTop;
       pStack->pTop=pTemp;
       pStack->nCount++;
   }
   
  Tree* s_Pop(Stack *pStack)
   {   
       if(pStack==NULL) exit(1);
       if(pStack->pTop==NULL) return NULL;
       
       MyStack *pDel=pStack->pTop;
       Tree* nNum=pDel->nValue;
   
       pStack->pTop=pStack->pTop->pNext;
       free(pDel);
       pDel=NULL;
       pStack->nCount--;
       return nNum;

   }
   void UnRecPreTravresal(Tree *root) //前序遍历非递归版
   {
       if(root==NULL) return;
       //辅助栈
       Stack *pStack =NULL;
       s_Init(&pStack);
       //遍历
       while(1)
       {
           while(root)
           {
               //打印
 			  printf("%d ",root->data);
              //保存
             s_Push(pStack,root);//入栈
              //向左走
              root=root->left;
          }
          if(pStack->nCount==0) break;
          //弹出栈
          root=s_Pop(pStack);
          // 找右
          root=root->right;
      }
      printf("\n");
  }
 
 

  void UnRecinOrderList(Tree *root) //中序遍历非递归版
     {
         if(root==NULL) return;
         //辅助栈
         Stack *pStack =NULL;
         s_Init(&pStack);
     do{
	 	while(root){
//		 	if(pStack->nCount==0) break;
		 	 s_Push(pStack,root);//入栈
		 	   //向左走
			root=root->left;
		 }
		 //循环结束表示以栈顶元素的指向为根结点的二叉树
		           //的左子树遍历结束
		           if(pStack->nCount!=0){
				   	//弹出栈
					  root=s_Pop(pStack);
					   //打印
					  printf("%d ",root->data);
					   // 找右
					root=root->right;
				   }
	 	
	 }while(root||pStack->nCount);
	 printf("\n");
     }

    
 void PostOrderlist(Tree *root)               //后序遍历非递归版
{
	    	Tree *s1[100],*p=root; 
	   	//栈s1存放树中的结点
	    	int s2[100],b,top=0;  //栈s2存放进栈标志
	    	do
	    	{
	     		while(p!=NULL) //遍历左子树
	        	{
	        		s1[top]=p;
					s2[top++]=0;
	   			//第一次进栈标志为0
	         		p=p->left;}
	    			if(top>0)
	    			{
	     				b=s2[--top]; p=s1[top];
	     				if(b==0)
	     				{
	     					s1[top]=p;s2[top++]=1;
	   					//第二次进栈标志为1
	      					p=p->right;
	      				} //遍历右子树
	   			else {printf("%d ",p->data); p=NULL;} 
	   			//遍历根
	   		}
	   	}while(top>0);
 }






//二叉排序树的节点插入
void insertBinarySortTreeNode(Tree *dataNode, Tree **root) //二叉排序树插入节点，因为根节点可能改变，所以传二级指针
{
    if (*root == NULL || dataNode == NULL)
    {
        *root = dataNode;
        return;
    }
    if (dataNode->data > (*root)->data)//如果插入节点大于原节点的data，插入节点需要放在root的右子树
    {
        if ((*root)->right == NULL)//找到插入位置
        {
            (*root)->right = dataNode;
            return;
        }
        if ((*root)->right)
            insertBinarySortTreeNode(dataNode, &(*root)->right);//递归找dataNode的插入位置
    }
    if (dataNode->data <= (*root)->data)//如果去掉等于号，表示不插入相同data的节点
    {
        if ((*root)->left == NULL)//找到插入位置
        {
            (*root)->left = dataNode;
            return;
        }
        if ((*root)->left)
            insertBinarySortTreeNode(dataNode, &(*root)->left); //递归找dataNode的插入位置
    }
}

//二叉排序树最大键值节点获取
Tree *maxValueOfBinaryTree(Tree *root)
{
    if (root == NULL)//空指针判断
        return NULL;
    Tree *pointer = root;
    while (pointer->right)//跳出循环后，pointer指向最后一个右子节点
        pointer = pointer->right;
    return pointer;
}

//二叉排序树最小键值节点获取
Tree *minValueOfBinaryTree(Tree *root)
{
    if (root == NULL)
        return NULL;
    Tree *pointer = root;
    while (pointer->left)
        pointer = pointer->left;
    return pointer;
}

// 二叉排序树查找指定节点的父节点
Tree *parentNodeOfBinaryTreeNode(Tree *dataNode, Tree *root) //获取dataNode节点的父节点
{
    if (dataNode == NULL || root == NULL || root == dataNode) //空指针判断，以及root自身无父节点
        return NULL;
    Tree *pointer = root;
    Tree *parentNode = pointer;
    while (pointer != NULL && pointer->data != dataNode->data)
    {
        parentNode = pointer;
        if (dataNode->data > pointer->data)
            pointer = pointer->right;
        else
            pointer = pointer->left;
    } 
	//每一次循环后parentNode总是pointer的父节点
    //循环跳出后，要么找到了dataNode，要么pointer为NULL了
    if (pointer == NULL)
    {
        printf("节点dataNode不存在\n");
        return NULL;
    }
    return parentNode;
}

//二叉排序树删除节点
void deleteBinarySortTreeNode(Tree *deleteNode, Tree **root) //删除二叉树中的某一个节点
{
    Tree *parentOfDeleteNode = parentNodeOfBinaryTreeNode(deleteNode, *root); //删除节点的父节点
    if (deleteNode == NULL || root == NULL)                                   //空指针判断
        return;
    if (deleteNode != *root && parentOfDeleteNode == NULL) //删除节点不是root，parentOfDeleteNode==NULL说明没有找到deleteNode或者树的root节点为NULL,直接结束;
        return;
    if (deleteNode->left == NULL && deleteNode->right == NULL) // 删除节点为叶子节点的情况
    {
        if (*root == deleteNode) //删除的节点是root节点
        {
            *root = NULL;
            return;
        }
        if (parentOfDeleteNode->left == deleteNode)
            parentOfDeleteNode->left = NULL;
        if (parentOfDeleteNode->right == deleteNode)
            parentOfDeleteNode->right = NULL;
    }
    else if (deleteNode->left == NULL || deleteNode->right == NULL) // case：2 删除节点只有左子树或右子树，其中之一
    {
        if (*root == deleteNode)
        {
            if ((*root)->left != NULL) //删除节点为root节点，且root节点只有左子树
                (*root) = (*root)->left;
            else if ((*root)->right != NULL)
                (*root) = (*root)->right; //删除节点为root节点，且root节点只有右子树
        }
        else if (deleteNode->left != NULL) //删除节点只有左子树
        {
            if (parentOfDeleteNode->left == deleteNode)      //删除节点是父节点的左子节点，且删除节点只有左子树
                parentOfDeleteNode->left = deleteNode->left; //把父节点的left指向deleteNode的左子节点
            if (parentOfDeleteNode->right == deleteNode)
                parentOfDeleteNode->right = deleteNode->left;
        }
        else if (deleteNode->right != NULL)
        {
            if (parentOfDeleteNode->left == deleteNode) //
                parentOfDeleteNode->left = deleteNode->right;
            if (parentOfDeleteNode->right == deleteNode)
                parentOfDeleteNode->right = deleteNode->right;
        }
    }
    else if (deleteNode->left != NULL || deleteNode->right != NULL) // case：3 删除节点有左子树和右子树
    {
        Tree *replaceNode = maxValueOfBinaryTree(deleteNode->left);
        //找到删除节点的左子树的最右节点（对应左子树的最大键值）作为替代节点，替代节点的键值与删除节点的键值是相邻的，
        Tree *parentOfReplaceNode = parentNodeOfBinaryTreeNode(replaceNode, *root); //获取替代节点的父节点
        if (*root == deleteNode)
        {
            parentOfReplaceNode->right = replaceNode->left;
            replaceNode->left = (*root)->left;
            replaceNode->right = (*root)->right;
            (*root) = replaceNode;
        }
        else if (parentOfDeleteNode->left == deleteNode) //删除节点是其父节点的左子节点
        {
            parentOfDeleteNode->left = replaceNode; //删除节点的父节点left指向替代节点
            replaceNode->left = deleteNode->left;
            if (parentOfReplaceNode != deleteNode)
            {
                replaceNode->right = deleteNode->right;
                //替代节点右子树指向删除节点右子树（如果替代节点父节点就是删除节点，deleteNode->right就是该替代节点，造成后面子树丢失；parentOfReplaceNode->right也没有意义）
                parentOfReplaceNode->right = replaceNode->left;
            }
            else if (parentOfReplaceNode == deleteNode)
                replaceNode->right = deleteNode->right->left; //替换节点的右子树指向了替换节点的左子树，看树图很容易理解
        }
        else if (parentOfDeleteNode->right == deleteNode) //删除节点是父节点的右子节点
        {
            parentOfDeleteNode->right = replaceNode; //删除节点的父节点right指向左子树最大键值对应节点
            replaceNode->right = deleteNode->right;
            if (parentOfReplaceNode != deleteNode)
            {
                replaceNode->left = replaceNode->left;
                parentOfReplaceNode->right = replaceNode->left;
            }
            else if (parentOfReplaceNode == deleteNode)
                replaceNode->left = replaceNode->left->left;
        }
    }
    free(deleteNode);
}

//查找指定节点代码
Tree *searchTreeNode(Tree *root, int value) //搜索二叉排序树含指定数据的节点
{
    if (root == NULL)
        return NULL;
    if (root->data > value)
        return searchTreeNode(root->left, value);
    if (root->data < value)
        return searchTreeNode(root->right, value);
    else
        return root;
}

void Preorderlist(Tree *root)  //递归先序遍历
   {
       if(root == NULL) return;
       
       printf("%d ",root->data);
       Preorderlist(root->left);
       Preorderlist(root->right);
  
  }


void inOrderList(Tree *root)//递归中序遍历
{
    if (root == NULL) return;
    
    inOrderList(root->left);
    printf("%d ", root->data);
    inOrderList(root->right);
}


void lastOrderList(Tree *root)//递归后序遍历
{
    if (root == NULL)  return;
    
    lastOrderList(root->left);
    lastOrderList(root->right);
     printf("%d ", root->data);
}



int main()
{
  int array[] = {2, 6, 9, 8, 12, 3, 5, 4, 0, -66, 1, -88};
    Tree root = {2, NULL, NULL};
    Tree *pointer = &root;
    for (int i = 1; i <12; i++)
    {
        Tree *node = createBinarySortTreeNode(array[i]);
        insertBinarySortTreeNode(node, &pointer);//插入节点
    }
   printf("插入节点完成!\n\n");
    printf("递归先序遍历：");
    Preorderlist(&root);
     printf("\n");
     printf("递归中序遍历：");
    inOrderList(&root); 
     printf("\n");
     printf("递归后序遍历: ");
     lastOrderList(&root);
     printf("\n\n");
     printf("非递归先序排列：");
      UnRecPreTravresal(&root);
      printf("非递归中序排列：");
      UnRecinOrderList(&root);
      printf("非递归后序排列: ");
      PostOrderlist(&root);
      printf("\n\n");
    Tree *maxNode = maxValueOfBinaryTree(&root);//最大节点查找
    printf("最大节点:{data:%d left:%p right:%p}\n", maxNode->data, maxNode->left, maxNode->right);
    Tree *minNode = minValueOfBinaryTree(&root);//最小节点查找
    printf("最小节点:{data:%d left:%p right:%p}\n\n", minNode->data, minNode->left, minNode->right);
    
    Tree *searchNode = searchTreeNode(&root, 6);//查找指定节点
    printf("查找指定节点6:{data:%d left:%p right:%p}\n", searchNode->data, searchNode->left, searchNode->right);
    Tree *parentNode = parentNodeOfBinaryTreeNode(searchNode, &root);//指定节点的父节点查找
    printf("查找指定节点6的父节点:{data:%d left:%p right:%p} \n\n", parentNode->data, parentNode->left, parentNode->right);
    
    //如果测试删除root节点，需要把上行printf里面的parentNode的data去掉，因为是NULL，无法解引用
    Tree *pointer2 = &root;
    deleteBinarySortTreeNode(searchNode, &pointer2);//删除指定节点
    printf("删除指定节点6:\n");
    printf("删除后中序遍历输出:  ");
    inOrderList(pointer2);//中序遍历
    return 0;
}
