// Mehmet Selman Yilmaz 31158 CS300 Homework1

#ifndef CS300THE1_2_DSTACK_H
#define CS300THE1_2_DSTACK_H

// Node struct in order to make dynamic stack
// (The code will not navigate through the stack using the next pointer, next pointer will only be used to keep its size dynamic.)
template<class T>
struct sNode {
public:
    T element;
    sNode<T>* next;

    // Constructor to initialize the node
    sNode() : element(T()), next(nullptr) {}

    // Constructor with an element
    sNode(const T& elem, sNode *n) : element(elem), next(n) {}
};

// Struct to store maze information
struct cell {
    int xCoordinate;
    int yCoordinate;
    bool left;
    bool right;
    bool up;
    bool down;
    bool isVisited;
    int unbreakable; // 1 for unbreakable left wall, 2 for unbreakable right wall, 3 for unbreakable up wall, 4 for unbreakable down wall,
    // 5 for left and up, 6 for left and down, 7 for right and up, 8 for right and down.
    // Default constructor
    cell() : xCoordinate(), yCoordinate(), left(), right(), up(), down(), isVisited(), unbreakable() {}

    // Parameterized constructor
    cell(int x, int y, bool l, bool r, bool u, bool d, bool iV, int unB) : xCoordinate(x), yCoordinate(y), left(l), right(r), up(u), down(d), isVisited(iV), unbreakable(unB) {}
};

// Class for stack
template<class T>
class dStack {
private:
    sNode<T>* top;

public:
    // Default Constructor (with Implementation)
    dStack() { top = nullptr; }

    // Assignment operator
    dStack<T>& operator=(const dStack& rhs) {
        if (this == &rhs) {
            return *this; // Avoid self-assignment
        }

        // Clean the left-hand side
        while (!isEmpty()) {
            T x;
            pop(x);
        }

        // Copy and paste every element
        sNode<T>* current = rhs.top;
        while (current != nullptr) {
            push(current->element);
            current = current->next;
        }

        return *this;
    }

    // Destructor
    ~dStack() {
        T x;
        while (!isEmpty()) {
            pop(x);
        }
    }

    // Push function
    void push(T value) {
        sNode<T>* newNode = new sNode<T>(value, top);
        top = newNode;
    }

    // Push function and store the node
    void pushGet(T value, sNode<T>*& valueNode) {
        sNode<T>* newNode = new sNode<T>(value, top);
        top = newNode;
        valueNode = newNode;
    }

    // Pop function
    void pop(T& value) {
        sNode<T>* temp;
        temp = top->next;
        value = top->element;
        delete top;
        top = temp;
    }

    // Check whether the stack is empty or not
    bool isEmpty() {
        return top == nullptr;
    }

    // Getter for top
    sNode<T>* getTop() {
        return top;
    }
};

#endif //CS300THE1_2_DSTACK_H
