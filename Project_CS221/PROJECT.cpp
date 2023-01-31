//#include <SDL.h>
#undef main

#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include<cmath>
using namespace std;
float pi = 3.14159;
struct node {
    string data;
    float x, y;
};
/*void circle(node array[], int no_of_vertices)
{
    float radius, theta;
    radius = 100;
    theta = 0;
    for (int i = 0; i < no_of_vertices; i++)
    {
        if (theta + 0.0174533 > 2 * pi)
        {
            theta = 0;
            radius = radius + 25;
        }
        array[i].x = 300 + radius * cos(theta);
        array[i].y = 300 + radius * sin(theta);
        theta = theta + (0.0174533 * 12);
    }

    // ------------

    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_Init(SDL_INIT_VIDEO);

    //create window
    window = SDL_CreateWindow("Graph", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, 0);
    //create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool displayingGraph = true;
    while (displayingGraph)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                displayingGraph = false;
            }
        }

        // set canvas color
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        // set dot color
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

        float x_correction = 300, y_correction = 300;

        for (int i = 0; i < no_of_vertices; i++)
        {

            SDL_RenderDrawPointF(renderer, array[i].x, array[i].y);

        }

        // shows what we have drawn on canvas
        SDL_RenderPresent(renderer);

    }

    SDL_DestroyWindow(window);
    SDL_Quit();
}*/

void printMST(int parent_ind[], float** adj, int src_index, int size){
	int start_ind;
	int count = 0;
	bool found;
	cout<<"Edge \t\tWeight\n";
		for(int i=0; i<size; i++){
			if(src_index == parent_ind[i]){
				start_ind = i;
				found = true;
				break;
			}	
		}
		for(int i=0; i<size-1; i++){
			if(parent_ind[start_ind] != -1){
				cout<<parent_ind[start_ind]<<"  -  "<<start_ind<<" \t "<<adj[parent_ind[start_ind]][start_ind]<<" \n";	
			}
			start_ind++;
		}
}

int minIndex(int key[], bool mstSet[], int size){
	int min = INT_MAX;
	int min_index;
	for(int i=0; i<size; i++){
		if(mstSet[i] == false && key[i] < min){
			min = key[i];
			min_index = i;
		}
	}
	if(min == INT_MAX){
		return -1;
	}
	return min_index;
}

void MST_Prims(float** adj, int size, int src_index){
	int parent_ind[size];
	int key[size];
	bool mstSet[size];
	for(int i=0; i<size; i++){
		key[i] = INT_MAX;
		mstSet[i] = false;
		parent_ind[i] = -1;
	}
	key[src_index] = 0;
	for(int count = 0; count < size - 1;count++){
		int u = minIndex(key, mstSet, size);
		if(u == -1){
			break;
		}
		mstSet[u] = true;
		for(int v=0; v<size; v++){
			if(adj[u][v] != 9 && mstSet[v] == false && adj[u][v] < key[v]){
				parent_ind[v] = u;
				key[v] = adj[u][v];
			}
		}
	}
	printMST(parent_ind, adj, src_index, size);
}

void display_list(vector<string> vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << " ";
    }
    cout << endl;
}

int findIndex(vector<string> vertex_list, string protein)
{
    int index = -1;
    bool found;
    found = false;
    for (int i = 0; i < vertex_list.size(); i++)
    {
        if (protein == vertex_list[i])
        {
            found = true;
            index = i;
            break;
        }
    }
    return index;
}

void display_matrix(float** adj, int size)
{
    size = 97;
    for (int i = 0; i < size; i++)
    {
        cout << i << "->      ";
        for (int j = 0; j < size; j++)
        {
            cout << adj[i][j] << "  ";
        }
        cout << endl
            << endl;
    }
}

int find_degree(float* list, int size)
{
    int degree = 0;
    for (int i = 0; i < size; i++)
    {
        if (list[i] != 9)
        {
            degree += 1;
        }
    }
    return degree;
}

int main()
{
    vector<string> vertex_list;
    ifstream input;
    string proteins;
    string protein1, protein2;
    float weight;
    bool repetition;
    int index1, index2, degree, choice;
    int max_degree, min_degree;
    input.open("info.txt");
    vertex_list.push_back("VERTICES");
    for (int i = 1; i <= 300; i++)
    {
        repetition = false;
        input >> proteins;
        if (i % 3 == 0)
        {
            continue;
        }
        for (int j = 0; j < vertex_list.size(); j++)
        {
            if (proteins.compare(vertex_list[j]) == 0)
            {
                repetition = true;
                break;
            }
        }
        if (repetition == false)
        {
            vertex_list.push_back(proteins);
        }
    }
    vertex_list.erase(vertex_list.begin());
    input.close();
    int matrix_size = vertex_list.size();
    display_list(vertex_list);
    float** adj = new float* [matrix_size];
    for (int i = 0; i < matrix_size; i++)
    {
        adj[i] = new float[matrix_size];
    }
    for (int i = 0; i < matrix_size; i++)
    {
        for (int j = 0; j < matrix_size; j++)
        {
            adj[i][j] = 9;
        }
    }
    input.open("info.txt");
    for (int j = 0; j < 100; j++)
    {
        input >> protein1;
        input >> protein2;
        input >> weight;
        index1 = findIndex(vertex_list, protein1);
        index2 = findIndex(vertex_list, protein2);
        adj[index1][index2] = weight;
    }
    node* vertexList = new node[matrix_size];
    for (int i = 0; i < matrix_size; i++) {
        vertexList->data = vertex_list[i];
    }
    int* degree_list = new int[matrix_size];
    for (int i = 0; i < matrix_size; i++) {
        degree_list[i] = find_degree(adj[i], matrix_size);
    }
    cout << "Enter from the following choices: " << endl;
    cout << "1) Find the degree of a node" << endl;
    cout << "2) Find the node with maximum degree" << endl;
    cout << "3) Find the node with minimum degree" << endl;
    cout << "4) Display the raw adjacency matrix" << endl;
    cout << "5) Find the neighbours of a node" << endl;
    cout << "6) Print circle" << endl;
    cout << "7) Display MST"<<endl;
    cin >> choice;
    switch (choice)
    {
    case 1:
        cout << "Enter the node to find it's degree = ";
        cin >> proteins;
        index1 = findIndex(vertex_list, proteins);
        degree = find_degree(adj[index1], matrix_size);
        cout << "The degree of " << proteins << " is " << degree << endl;
        break;
    case 2:
        max_degree = 0;
        for (int i = 0; i < matrix_size; i++) {
            if (degree_list[i] > max_degree) {
                max_degree = degree_list[i];
                index1 = i;
            }
        }
        cout << "The maximum degree is of node " << vertex_list[index1] << " which is " << max_degree << endl;
        break;
    case 3:
        min_degree = 99999;
        for (int i = 0; i < matrix_size; i++) {
            if (degree_list[i] < min_degree) {
                min_degree = degree_list[i];
                index1 = i;
            }
        }
        cout << "The minimum degree is of nodes ";
        for (int i = 0; i < matrix_size; i++) {
            if (min_degree == degree_list[i]) {
                cout << vertex_list[i] << " ";
            }
        }
        cout << " which is " << min_degree << endl;
        break;
    case 4:
        display_matrix(adj, matrix_size);
        break;
    case 5:
        cout << "Enter the node to find it's neighbours = ";
        cin >> proteins;
        index1 = findIndex(vertex_list, proteins);
        cout << "The neighbours are ";
        for (int i = 0; i < matrix_size; i++) {
            if (adj[index1][i] != 9) {
                cout << vertex_list[i] << " ";
            }
        }
        break;
    case 6:

        //circle(vertexList, matrix_size);

        break;
    case 7:
    	cout<<"Enter the name of the source node of MST = ";
    	cin >> proteins;
    	index1 = findIndex(vertex_list, proteins);
    	MST_Prims(adj, matrix_size, index1);
    	break;
    }
    return 0;
}