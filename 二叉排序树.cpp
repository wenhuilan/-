#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//�����������ṹ��
typedef struct Tree //������
{
    int data;           //������
    struct Tree *left;  //���ӽڵ�ָ��
    struct Tree *right; //���ӽڵ�ָ��
} Tree;

//�ڵ㴴������
Tree *createBinarySortTreeNode(int data)
{
    Tree *node = (Tree *)malloc(sizeof(Tree));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}


//����ջ
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
          printf("������\n");
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
   void UnRecPreTravresal(Tree *root) //ǰ������ǵݹ��
   {
       if(root==NULL) return;
       //����ջ
       Stack *pStack =NULL;
       s_Init(&pStack);
       //����
       while(1)
       {
           while(root)
           {
               //��ӡ
 			  printf("%d ",root->data);
              //����
             s_Push(pStack,root);//��ջ
              //������
              root=root->left;
          }
          if(pStack->nCount==0) break;
          //����ջ
          root=s_Pop(pStack);
          // ����
          root=root->right;
      }
      printf("\n");
  }
 
 

  void UnRecinOrderList(Tree *root) //��������ǵݹ��
     {
         if(root==NULL) return;
         //����ջ
         Stack *pStack =NULL;
         s_Init(&pStack);
     do{
	 	while(root){
//		 	if(pStack->nCount==0) break;
		 	 s_Push(pStack,root);//��ջ
		 	   //������
			root=root->left;
		 }
		 //ѭ��������ʾ��ջ��Ԫ�ص�ָ��Ϊ�����Ķ�����
		           //����������������
		           if(pStack->nCount!=0){
				   	//����ջ
					  root=s_Pop(pStack);
					   //��ӡ
					  printf("%d ",root->data);
					   // ����
					root=root->right;
				   }
	 	
	 }while(root||pStack->nCount);
	 printf("\n");
     }

    
 void PostOrderlist(Tree *root)               //��������ǵݹ��
{
	    	Tree *s1[100],*p=root; 
	   	//ջs1������еĽ��
	    	int s2[100],b,top=0;  //ջs2��Ž�ջ��־
	    	do
	    	{
	     		while(p!=NULL) //����������
	        	{
	        		s1[top]=p;
					s2[top++]=0;
	   			//��һ�ν�ջ��־Ϊ0
	         		p=p->left;}
	    			if(top>0)
	    			{
	     				b=s2[--top]; p=s1[top];
	     				if(b==0)
	     				{
	     					s1[top]=p;s2[top++]=1;
	   					//�ڶ��ν�ջ��־Ϊ1
	      					p=p->right;
	      				} //����������
	   			else {printf("%d ",p->data); p=NULL;} 
	   			//������
	   		}
	   	}while(top>0);
 }






//�����������Ľڵ����
void insertBinarySortTreeNode(Tree *dataNode, Tree **root) //��������������ڵ㣬��Ϊ���ڵ���ܸı䣬���Դ�����ָ��
{
    if (*root == NULL || dataNode == NULL)
    {
        *root = dataNode;
        return;
    }
    if (dataNode->data > (*root)->data)//�������ڵ����ԭ�ڵ��data������ڵ���Ҫ����root��������
    {
        if ((*root)->right == NULL)//�ҵ�����λ��
        {
            (*root)->right = dataNode;
            return;
        }
        if ((*root)->right)
            insertBinarySortTreeNode(dataNode, &(*root)->right);//�ݹ���dataNode�Ĳ���λ��
    }
    if (dataNode->data <= (*root)->data)//���ȥ�����ںţ���ʾ��������ͬdata�Ľڵ�
    {
        if ((*root)->left == NULL)//�ҵ�����λ��
        {
            (*root)->left = dataNode;
            return;
        }
        if ((*root)->left)
            insertBinarySortTreeNode(dataNode, &(*root)->left); //�ݹ���dataNode�Ĳ���λ��
    }
}

//��������������ֵ�ڵ��ȡ
Tree *maxValueOfBinaryTree(Tree *root)
{
    if (root == NULL)//��ָ���ж�
        return NULL;
    Tree *pointer = root;
    while (pointer->right)//����ѭ����pointerָ�����һ�����ӽڵ�
        pointer = pointer->right;
    return pointer;
}

//������������С��ֵ�ڵ��ȡ
Tree *minValueOfBinaryTree(Tree *root)
{
    if (root == NULL)
        return NULL;
    Tree *pointer = root;
    while (pointer->left)
        pointer = pointer->left;
    return pointer;
}

// ��������������ָ���ڵ�ĸ��ڵ�
Tree *parentNodeOfBinaryTreeNode(Tree *dataNode, Tree *root) //��ȡdataNode�ڵ�ĸ��ڵ�
{
    if (dataNode == NULL || root == NULL || root == dataNode) //��ָ���жϣ��Լ�root�����޸��ڵ�
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
	//ÿһ��ѭ����parentNode����pointer�ĸ��ڵ�
    //ѭ��������Ҫô�ҵ���dataNode��ҪôpointerΪNULL��
    if (pointer == NULL)
    {
        printf("�ڵ�dataNode������\n");
        return NULL;
    }
    return parentNode;
}

//����������ɾ���ڵ�
void deleteBinarySortTreeNode(Tree *deleteNode, Tree **root) //ɾ���������е�ĳһ���ڵ�
{
    Tree *parentOfDeleteNode = parentNodeOfBinaryTreeNode(deleteNode, *root); //ɾ���ڵ�ĸ��ڵ�
    if (deleteNode == NULL || root == NULL)                                   //��ָ���ж�
        return;
    if (deleteNode != *root && parentOfDeleteNode == NULL) //ɾ���ڵ㲻��root��parentOfDeleteNode==NULL˵��û���ҵ�deleteNode��������root�ڵ�ΪNULL,ֱ�ӽ���;
        return;
    if (deleteNode->left == NULL && deleteNode->right == NULL) // ɾ���ڵ�ΪҶ�ӽڵ�����
    {
        if (*root == deleteNode) //ɾ���Ľڵ���root�ڵ�
        {
            *root = NULL;
            return;
        }
        if (parentOfDeleteNode->left == deleteNode)
            parentOfDeleteNode->left = NULL;
        if (parentOfDeleteNode->right == deleteNode)
            parentOfDeleteNode->right = NULL;
    }
    else if (deleteNode->left == NULL || deleteNode->right == NULL) // case��2 ɾ���ڵ�ֻ����������������������֮һ
    {
        if (*root == deleteNode)
        {
            if ((*root)->left != NULL) //ɾ���ڵ�Ϊroot�ڵ㣬��root�ڵ�ֻ��������
                (*root) = (*root)->left;
            else if ((*root)->right != NULL)
                (*root) = (*root)->right; //ɾ���ڵ�Ϊroot�ڵ㣬��root�ڵ�ֻ��������
        }
        else if (deleteNode->left != NULL) //ɾ���ڵ�ֻ��������
        {
            if (parentOfDeleteNode->left == deleteNode)      //ɾ���ڵ��Ǹ��ڵ�����ӽڵ㣬��ɾ���ڵ�ֻ��������
                parentOfDeleteNode->left = deleteNode->left; //�Ѹ��ڵ��leftָ��deleteNode�����ӽڵ�
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
    else if (deleteNode->left != NULL || deleteNode->right != NULL) // case��3 ɾ���ڵ�����������������
    {
        Tree *replaceNode = maxValueOfBinaryTree(deleteNode->left);
        //�ҵ�ɾ���ڵ�������������ҽڵ㣨��Ӧ������������ֵ����Ϊ����ڵ㣬����ڵ�ļ�ֵ��ɾ���ڵ�ļ�ֵ�����ڵģ�
        Tree *parentOfReplaceNode = parentNodeOfBinaryTreeNode(replaceNode, *root); //��ȡ����ڵ�ĸ��ڵ�
        if (*root == deleteNode)
        {
            parentOfReplaceNode->right = replaceNode->left;
            replaceNode->left = (*root)->left;
            replaceNode->right = (*root)->right;
            (*root) = replaceNode;
        }
        else if (parentOfDeleteNode->left == deleteNode) //ɾ���ڵ����丸�ڵ�����ӽڵ�
        {
            parentOfDeleteNode->left = replaceNode; //ɾ���ڵ�ĸ��ڵ�leftָ������ڵ�
            replaceNode->left = deleteNode->left;
            if (parentOfReplaceNode != deleteNode)
            {
                replaceNode->right = deleteNode->right;
                //����ڵ�������ָ��ɾ���ڵ����������������ڵ㸸�ڵ����ɾ���ڵ㣬deleteNode->right���Ǹ�����ڵ㣬��ɺ���������ʧ��parentOfReplaceNode->rightҲû�����壩
                parentOfReplaceNode->right = replaceNode->left;
            }
            else if (parentOfReplaceNode == deleteNode)
                replaceNode->right = deleteNode->right->left; //�滻�ڵ��������ָ�����滻�ڵ��������������ͼ���������
        }
        else if (parentOfDeleteNode->right == deleteNode) //ɾ���ڵ��Ǹ��ڵ�����ӽڵ�
        {
            parentOfDeleteNode->right = replaceNode; //ɾ���ڵ�ĸ��ڵ�rightָ������������ֵ��Ӧ�ڵ�
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

//����ָ���ڵ����
Tree *searchTreeNode(Tree *root, int value) //����������������ָ�����ݵĽڵ�
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

void Preorderlist(Tree *root)  //�ݹ��������
   {
       if(root == NULL) return;
       
       printf("%d ",root->data);
       Preorderlist(root->left);
       Preorderlist(root->right);
  
  }


void inOrderList(Tree *root)//�ݹ��������
{
    if (root == NULL) return;
    
    inOrderList(root->left);
    printf("%d ", root->data);
    inOrderList(root->right);
}


void lastOrderList(Tree *root)//�ݹ�������
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
        insertBinarySortTreeNode(node, &pointer);//����ڵ�
    }
   printf("����ڵ����!\n\n");
    printf("�ݹ����������");
    Preorderlist(&root);
     printf("\n");
     printf("�ݹ����������");
    inOrderList(&root); 
     printf("\n");
     printf("�ݹ�������: ");
     lastOrderList(&root);
     printf("\n\n");
     printf("�ǵݹ��������У�");
      UnRecPreTravresal(&root);
      printf("�ǵݹ��������У�");
      UnRecinOrderList(&root);
      printf("�ǵݹ��������: ");
      PostOrderlist(&root);
      printf("\n\n");
    Tree *maxNode = maxValueOfBinaryTree(&root);//���ڵ����
    printf("���ڵ�:{data:%d left:%p right:%p}\n", maxNode->data, maxNode->left, maxNode->right);
    Tree *minNode = minValueOfBinaryTree(&root);//��С�ڵ����
    printf("��С�ڵ�:{data:%d left:%p right:%p}\n\n", minNode->data, minNode->left, minNode->right);
    
    Tree *searchNode = searchTreeNode(&root, 6);//����ָ���ڵ�
    printf("����ָ���ڵ�6:{data:%d left:%p right:%p}\n", searchNode->data, searchNode->left, searchNode->right);
    Tree *parentNode = parentNodeOfBinaryTreeNode(searchNode, &root);//ָ���ڵ�ĸ��ڵ����
    printf("����ָ���ڵ�6�ĸ��ڵ�:{data:%d left:%p right:%p} \n\n", parentNode->data, parentNode->left, parentNode->right);
    
    //�������ɾ��root�ڵ㣬��Ҫ������printf�����parentNode��dataȥ������Ϊ��NULL���޷�������
    Tree *pointer2 = &root;
    deleteBinarySortTreeNode(searchNode, &pointer2);//ɾ��ָ���ڵ�
    printf("ɾ��ָ���ڵ�6:\n");
    printf("ɾ��������������:  ");
    inOrderList(pointer2);//�������
    return 0;
}
