struct Queue* createQueue(unsigned capacity);
int isFull(struct Queue* queue);
void enqueue(struct Queue* queue, int item);
int dequeue(struct Queue* queue);
int front(struct Queue* queue);
int rear(struct Queue* queue);

char * getInput();
void display();
void eventHandler();
int * elevator(int f, int s, int g, int u, int d);
void user_I(int f, int s, int g, int u, int d);
void user_X();

int visited(int n, int vis[100], int visIndex);
int** matrix(int floors, int up, int down);










