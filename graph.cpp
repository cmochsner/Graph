//Program by Christina Ochsner

#include<iostream> 

using namespace std;

struct node
{
	int vertex;
	bool visited=false;
	node* next = {};
};
class queue
{
	node* front = {};
	public:
		queue()
		{
			front = {};
		}
		int getFront();
		bool isEmpty();
		void enqueue(int v);
		void dequeue();
};
int queue::getFront()
{
	if (front == NULL)
	{
		return 0;
	}

	return front->vertex;
}
bool queue::isEmpty()
{
	if (front == NULL)
	{
		return true;
	}

	return false;
}
void queue::enqueue(int v)
{
	node* newnode = new node;
	newnode->vertex = v;

	if (isEmpty())
	{
		front = newnode;
		return;
	}
	node* curr = front;

	while (curr->next != NULL)
	{
		curr = curr->next;
	}

	curr->next = newnode;
}
void queue::dequeue()
{
	if (isEmpty())
	{
		return;
	}

	node* temp = front;

	front = front->next;

	free(temp);
}

class graph
{
	private:
		int size;
		node **g = {};

	public:
		graph(int s = 10)
		{
			size = s;
			g = new node*[s];
		}
		void createGraph();
		void print(int s);
		void printAdj();
		bool isEmpty();
};

void graph::createGraph()
{
	for (int i = 0; i < size; i++)
	{
		g[i] = new node;
		g[i]->vertex = i;
		g[i]->next = {};
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			int num = rand() % 2;

			if (i == j)
			{
				num = 0;
			}

			if (num == 1)
			{
				node* prev = g[i];

				while (prev->next != NULL)
				{
					prev = prev->next;
				}

				node* newnode = new node;
				newnode->vertex = g[j]->vertex;

				prev->next = newnode;
			}
		}
	}
}
void graph::printAdj()
{
	for (int i = 0; i < size; i++)
	{
		cout << "Vertex " << i << ": ";
		node *current = g[i]->next;

		while (current != NULL)
		{
			cout << current->vertex <<" ";
			current = current->next;
		}
		cout << endl;
	}
}
void graph::print(int s)
{
	queue q;

	g[s]->visited = true;
	q.enqueue(g[s]->vertex);


	while (!q.isEmpty())
	{
		s = q.getFront();
		cout << s << " ";
		q.dequeue();

		node* current = g[s];

		while(current!=NULL)
		{
			int x = current->vertex;
			if (!g[x]->visited)
			{
				g[x]->visited = true;
				q.enqueue(x);
			}
			current = current->next;
		}
	}
	cout << endl;

	for (int u = 0; u < size; u++)
	{
		g[u]->visited = false;
	}
}
bool graph::isEmpty()
{
	if (g == NULL)
	{
		return true;
	}

	return false;
}
int main()
{
	int size=10;
	int vertex;
	int choice = 0;

	cout << "Welcome to the Graph Program! Enter a number for the size of your graph." << endl;
	cin >> size;
	if (size < 1)
	{
		size = 10;
	}

	graph g(size);
	g.createGraph();
	
	while (choice != 3)
	{
		cout << "\n1. Print the all adjancency matrices of your graph." << endl;
		cout << "2. Print a breadth first traversal of your graph." << endl;
		cout << "3. Exit the program." << endl;
		cin >> choice;

		switch (choice)
		{
			case 1:
			{
				g.printAdj();
			}
				break;
			case 2:
			{
				cout << "Enter the number of the vertex you'd like to start from." << endl;
				cin >> vertex;
				if (0 <= vertex < size)
				{
					g.print(vertex);
				}
				else
				{
					cout << "Invalid vertex." << endl;
				}
			}
			case 3:
				break;
			default:
			{
				cout << "Invalid choice. Try again." << endl;
				cin >> choice;
				break;
			}
		}
	}

	return 0;
}
