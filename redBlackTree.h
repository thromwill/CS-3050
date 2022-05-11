struct rbNode *createNode(int data);
void insertion(int data);
void inorderTraversal(struct rbNode *node, char output[256]);
int maxDepth(struct rbNode* node);
char * getInput();
int * readFile(char * filename);
int * getValues();
void buildTree(int arr[256], int arrLen);
char * inorderOutput();
void printTree();
int secondMax(struct rbNode * root);
int blackHeight(struct rbNode * root);
void display();
void eventHandler();
void user_F(char * filename);
void user_E();


