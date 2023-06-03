#include <iostream>
#include <vector>

#include <GL/freeglut.h>

using namespace std;

vector<int> arr; // the array to be sorted
int winWidth = 800, winHeight = 600; // window size

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, winWidth, 0, winHeight);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    int n = arr.size();
    int barWidth = winWidth / n;
    int x = 0;

    // draw bars
    for (int i = 0; i < n; i++)
    {
        glColor3f(1.0, 1.0, 1.0);
        glRecti(x, 0, x + barWidth, arr[i]);
        x += barWidth;
    }

    glutSwapBuffers();
}

void swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

int partition(int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);

    return (i + 1);
}
void merge( int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    int L[500];
    int R[500];
    for (int i = 0; i < n1; i++)
    {
        L[i] = arr[p + i];
    }
    for (int j = 0; j < n2; j++)
    {
        R[j] = arr[q + j + 1];
    }
    L[n1] = INT_MAX;
    R[n2] = INT_MAX;
    int i = 0;
    int j = 0;
    for (int k = p; k <= r; k++)
    {
        if (L[i] < R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
    }
}

void merge_sort( int p, int r)
{
    if (p < r) {
        int q = (p + r) / 2;
        glutPostRedisplay();
        glutMainLoopEvent();
        merge_sort( p, q);
        
        merge_sort( q + 1, r);
        glutPostRedisplay();
        glutMainLoopEvent();
        merge( p, q, r);
    }

}
void quicksort(int low, int high)
{
    if (low < high)
    {
        int pivot = partition(low, high);
        glutPostRedisplay();
        glutMainLoopEvent();
        quicksort(low, pivot - 1);
        quicksort(pivot + 1, high);
    }
}

int main(int argc, char** argv)
{
    int a;
    std::cout << "1->QuickSort\n2->MergeSort" << std::endl;
    std::cin >> a;
    // create an array of random integers
    srand(time(NULL));
    int count = 0;
    for (int i = 0; i < 400; i++)
    {
        arr.push_back(rand() % 500);
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("Algorithm Visualizer");
    glutDisplayFunc(display);
    init();
    
    switch (a) {
    case 1:
        quicksort(0, arr.size() - 1);
    case 2:
        merge_sort(0, arr.size() - 1);
    }

    glutMainLoop();

    return 0;
}
