#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <map>
#include <time.h>
#include <windows.h>

using namespace std;

// Global Variables
map<int, map<int, char>> frame; // 2d map
float speed = 8.0;				// Speed of snake

int i, j;					 // Counter variables
int width = 50, height = 20; // Map dimensions

int score; // Score

bool game_over; // Bool variable for Game over variable

// Directions for the Snake movement
bool dir1;
bool dir2;

// Class Node
class Node
{
public:
	int xPosition, yPosition;
	char symbol;
	Node *nextNodeAddress;

	Node(char symbol = 'o', int xPos = 0, int yPos = 0)
	{
		xPosition = xPos;
		yPosition = yPos;
		this->symbol = symbol;
		nextNodeAddress = NULL;
	}
};

// Class Snake
class Snake
{
private:
	Node *head;
	Node *body;
	Node *fruit;
	Node *front;
	Node *rear;
	float snakeSpeed;
	int bodyXPosition, bodyYPosition;
	int headXPosition, headYPosition;
	int fruitXPosition, fruitYPosition;
	int score;
	char fruitSymbol;

public:
	Snake(int headX = 0, int headY = 0, int bodyX = 0, int bodyY = 0, int foodX = 0, int foodY = 0)
	{
		headXPosition = headX;
		fruitXPosition = foodX;
		headYPosition = headY;
		fruitYPosition = foodY;
		bodyXPosition = bodyX;
		bodyYPosition = bodyY;
		snakeSpeed = 7.0;
		head = new Node('O');
		body = new Node('o');
		fruit = new Node('\242');
		front = new Node();
		rear = new Node();
		front = NULL;
		rear = NULL;
		score = 0;
		fruitSymbol = '\242';
	}
	// Enqueue body
	void enqueue(int xPos, int yPos)
	{
		Node *newNode = new Node();
		newNode->xPosition = xPos;
		newNode->yPosition = yPos;
		newNode->nextNodeAddress = NULL;

		if (rear == NULL)
		{
			rear = newNode;
			front = newNode;
		}
		else
		{
			rear->nextNodeAddress = newNode;
			rear = newNode;
		}
	}

	void dequeue(int &x, int &y)
	{
		// It will directly put data in given variables
		if (!(this->isEmpty()))
		{
			x = front->xPosition;
			y = front->yPosition;

			Node *temp = front;
			front = front->nextNodeAddress;

			delete temp;

			if (this->isEmpty())
			{
				rear = NULL;
			}
		}
		else
			cout << "Queue is Empty.\n";
	}

	void generateFruit()
	{
		fruitXPosition = (rand() % (width - 7)) + 3;
		fruitYPosition = (rand() % (height - 6)) + 3;
		if (frame[fruitYPosition][fruitXPosition] == ' ') // fruit will not be generated
		{
			frame[fruitYPosition][fruitXPosition] = fruitSymbol; // where snake body is
		}
		else
			generateFruit();
	}

	// Getting the front
	void getFront(int &x, int &y)
	{
		// only return the node data from front of queue
		if (!(this->isEmpty()))
		{
			x = front->xPosition;
			y = front->yPosition;
		}

		else
			cout << "Queue is empty.\n";
	}

	bool isEmpty()
	{
		return (front == NULL);
	}

	// Initializing
	void draw()
	{
		// score = 0;
		//  outerbox
		for (i = 0; i < width; i++)
		{
			frame[0][i] = '\262';
		}
		for (i = 1; i < height - 1; i++)
		{
			frame[i][0] = '\262';
			for (j = 1; j < width - 1; j++)
			{
				frame[i][j] = ' ';
			}
			frame[i][j] = '\262';
		}
		for (i = 0; i < width; i++)
		{
			frame[height - 1][i] = '\262';
		}

		// innerbox
		frame[1][1] = '\311';
		for (i = 2; i < width - 2; i++)
		{
			frame[1][i] = frame[height - 2][i] = '\315';
		}
		frame[1][i] = '\273';
		for (i = 2; i < height - 2; i++)
		{
			frame[i][1] = frame[i][width - 2] = '\272';
		}
		frame[i][1] = '\310';
		frame[i][width - 2] = '\274';

		// Placing head at random position in start
		srand(time(NULL));

		headXPosition = (rand() % (width - 4)) + 4;
		headYPosition = (rand() % (height - 5)) + 2;

		frame[headYPosition][headXPosition] = head->symbol;

		enqueue(headXPosition - 2, headYPosition);
		frame[headYPosition][headXPosition - 2] = body->symbol;
		enqueue(headXPosition - 1, headYPosition);
		frame[headYPosition][headXPosition - 1] = body->symbol;

		printMap();

		// initializing snake direction to vertical and right
		dir1 = 0;
		dir2 = 0;

		game_over = false;

		Sleep(1000 / speed);
	}
	void addBody()
	{ // Add a new body part (this is called when a fruit is eaten)
		move();

		printMap();

		Sleep(1000 / speed);
	}
	void update()
	{ // Show next frame
		move();

		dequeue(bodyXPosition, bodyYPosition);
		frame[bodyYPosition][bodyXPosition] = ' ';

		printMap();

		Sleep(1000 / speed);
	}

	void reLocate(char dir)
	{
		// Case for Vertical Direction
		if ((dir == 72 || dir == 80) && dir1 == 0)
		{
			if (dir == 72)
			{
				dir2 = 0;
			}
			else
			{
				dir2 = 1;
			}

			dir1 = 1;
		}
		else if ((dir == 75 || dir == 77) && dir1 == 1) // Case for Horizontal Direction
		{
			if (dir == 75)
			{
				dir2 = 1;
			}
			else
			{
				dir2 = 0;
			}

			dir1 = 0;
		}
	}
	void move()
	{ // Move head to its next node
		enqueue(headXPosition, headYPosition);
		frame[headYPosition][headXPosition] = body->symbol;

		// For Vertical and Right
		if (dir1 == 0 && dir2 == 0)
		{
			headXPosition++;
		}
		else if (dir1 == 0 && dir2 == 1) // For Vertical and Left
		{
			headXPosition--;
		}
		else if (dir1 == 1 && dir2 == 0) // For Horizontal and Right
		{
			headYPosition--;
		}
		else if (dir1 == 1 && dir2 == 1) // For Horizontal and Left
		{
			headYPosition++;
		}

		// Add body if head reaches the fruit
		if (headXPosition == fruitXPosition && headYPosition == fruitYPosition)
		{
			// Increasing the Scores and Adding body and Fruit
			score++;
			addBody();
			generateFruit();
		}

		// gameover if head touches the wall or body
		if (frame[headYPosition][headXPosition] == '\262' || frame[headYPosition][headXPosition] == '\311' || frame[headYPosition][headXPosition] == body->symbol)
		{
			game_over = true;
		}

		frame[headYPosition][headXPosition] = head->symbol;
	}

	void displayScore()
	{
		cout << "\t\tScore : " << score << " ";
	}

	// Function to print the Boundary and Score
	void printMap()
	{
		// print the frame
		system("cls");
		for (i = 0; i < height; i++)
		{
			for (j = 0; j < width; j++)
			{
				cout << frame[i][j];
			}
			if (i == 8)
			{
				displayScore();
			}
			cout << endl;
		}
	}

	int getScore()
	{
		return score;
	}
};

void display()
{
	// Creating the snake object
	Snake snake;
	string name;
	char get;
	cout << "\t\t\t\t  _________\n\n";
	cout << "\t\t\t\t  -----------------------\n";
	cout << "\t\t\t\t\tSNAKE GAME\n";
	cout << "\t\t\t\t  -----------------------\n";
	cout << "\t\t\t\t  _________\n";
	cout << "\n\n\n\n\n";

	cout << "Enter Your Name: ";
	cin >> name;
	cin.get(get);
	system("cls");
	// Iniatilizing the variables
	speed = 10;
	width = 50, height = 20;

	// Initializing the snake
	snake.draw();

	// generateFruit()
	snake.generateFruit();

	do
	{
		// update the position of the snake
		snake.update();

		if (_kbhit()) // If user presses any key
		{
			// Changing the direction of Snake
			snake.reLocate(_getch());
		}
	} while (game_over == false);

	cout << "\n\nName : " << name << "\t\tYour Score : " << snake.getScore() << endl;
	cout << "\nGAME OVER...\n\n";

	system("pause");
}
int main()
{
	display();
}