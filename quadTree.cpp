#include "quadTree.h"
#include "quadTreeSettings.h"
#include <cstddef>

quadTree::quadTree()
{
	
	nw = NULL;
	ne = NULL;
	sw = NULL;
	se = NULL;
	
	parent = NULL;
	
	filled = false;
	
	size = quad_max_size;
	
	xpos = quad_max_size;
	ypos = quad_max_size;

}

void quadTree::split()
{
	if (size < quad_min_size) return;

	nw = new quadTree;
	ne = new quadTree;
	sw = new quadTree;
	se = new quadTree;
	
	nw->xpos = xpos - size/2;
	sw->xpos = xpos - size/2;
	
	ne->xpos = xpos + size/2;
	se->xpos = xpos + size/2;
	
	nw->ypos = ypos - size/2;
	ne->ypos = ypos - size/2;
	
	sw->ypos = ypos + size/2;
	se->ypos = ypos + size/2;
	
	nw->size = size/2;
	ne->size = size/2;
	sw->size = size/2;
	se->size = size/2;
	
	nw->parent = ne->parent = sw->parent = se->parent = this;
}

bool quadTree::isLast()
{
	return (nw == NULL)&&(ne == NULL)&&(sw == NULL)&&(se == NULL);
}

quadTree* quadTree::collisionCheck(int x, int y)
{
	//Out of bounds detection
	if (x < 0 || x >= quad_max_size*2 || y < 0 || y >= quad_max_size*2) return NULL;	
	
	quadTree* collisionTree = collision(x,y);
	return collisionTree;
}

quadTree* quadTree::collision(int x, int y)
{
	bool collision_here = ((x <= xpos+size) && (x >= xpos-size) && (y <= ypos+size) && (y >= ypos-size));
	printSubTreeLimits();
	
	if (!isLast())
	{
		quadTree* result = NULL;
		
		if (y < ypos)
		{
			if (x < xpos)
			{
				result = nw->collision(x,y);
				if (result != NULL) return result;
			}
			else
			{
				result = ne->collision(x,y);
				if (result != NULL) return result;
			}
		}
		else
		{
			if (x < xpos)
			{
				result = sw->collision(x,y);
				if (result != NULL) return result;
			}
			else
			{
				result = se->collision(x,y);
				if (result != NULL) return result;
			}
		}
		
		return NULL;
	} 

	if (collision_here)
	{
		return this;
	}
	else return NULL;
	
}

void quadTree::deleteSubTree()
{
	if (parent != NULL)
	{
		delete parent->nw;
		delete parent->sw;
		delete parent->ne;
		delete parent->se;
		        	
		parent->nw = NULL;
		parent->sw = NULL;
		parent->ne = NULL;
		parent->se = NULL;
	}
}

void quadTree::reset(quadTree* self)
{
	self->filled = false;
	if (!self->isLast())
	{
		reset(self->nw);
		reset(self->ne);
		reset(self->sw);
		reset(self->se);
	}
}

quadTree::~quadTree()
{
	delete nw;
	delete ne;
	delete sw;
	delete se;
}
