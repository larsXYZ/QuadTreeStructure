struct quadTree
{

	//Children
	quadTree *nw;
	quadTree *ne;
	quadTree *sw;
	quadTree *se;
	
	//Parent
	quadTree *parent;
	
	//Data carrier (INSERT WANTED THING HERE)
	
	//Half size in pixels
	int size;
	
	//Position
	int xpos;
	int ypos;
	
	//Constructor
	quadTree();
	
	//Looks through entire tree return NULL if no collision
	quadTree* collisionCheck(int x, int y);
	
	//Recursive function to look through tree
	quadTree* collision(int x, int y);
	
	//Delete subtrees, deletes the four subtrees it is a part of
	void deleteSubTree();
	
	//Resets fillstate
	void reset(quadTree* self);
	
	//Split into other quadTrees
	void split();
	
	//Checks if it is last node
	bool isLast();
	
	//Destructor
	~quadTree();

};
