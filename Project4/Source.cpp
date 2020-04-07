//
//  main.cpp
//  project3
//
//  Created by Eliseo Garcia on 3/21/20.
//  Copyright © 2020 Eliseo Garcia. All rights reserved.
//

#include <iostream>
using namespace std;


template <class DT>
class GLRow; //class prototype
template <class DT>
ostream& operator << (ostream& s, GLRow<DT>& oneGLRow);


template <class DT>
class GLRow {
    friend ostream& operator << <DT>(ostream& s, GLRow<DT>& oneGLRow);
protected:
    DT* _Info;
    int _Next;
    int _Down;
public:
    GLRow(); //defualt constructor
    GLRow(DT newInfo); //non-default constructor : takes in input
    GLRow(GLRow<DT>& anotherOne); //copy constructor
    GLRow<DT>& operator= (GLRow<DT>& anotherOne); //overloaded "=" operator to perform deep copy
    void copy(GLRow<DT>& anotherOne); //copy method
    int getNext(); //getter for next
    int getDown(); //getter for down
    DT* getInfo(); //getter for info
    void setNext(int n); //set the value of next
    void setDown(int d); //set the value of down
    void setInfo(DT x);
    ~GLRow(); //destructor

};


template <class DT>
GLRow<DT>::GLRow() //default constructor
{
    _Info = nullptr;
    _Next = NULL;
    _Down = NULL;
}


template <class DT>
GLRow<DT>::GLRow(DT newInfo) { //non-default constructor
    _Info = new DT(newInfo);
    _Next = -1;
    _Down = -1;
}


template <class DT>
GLRow<DT>::GLRow(GLRow<DT>& anotherOne) {//copy contructor
    copy(anotherOne); //calling helper method to perform deep copy
}


template<class DT>
GLRow<DT>& GLRow<DT>::operator=(GLRow<DT>& anotherOne)
{
    if (_Info != NULL) delete _Info; //if not null then delete
    copy(anotherOne); // calling helper method to perform deep copy

    return *this;
}


template <class DT>
void GLRow<DT>::copy(GLRow<DT>& anotherOne) {
    if (anotherOne._Info == nullptr) _Info = nullptr; //leaving null if already null
    else {
        _Info = anotherOne.getInfo(); // passing a pointer
    }
    if (anotherOne._Next == -1) _Next = -1; //leaving out of bounds if out of bounds
    else {
        _Next = anotherOne.getNext(); //setting to anotherOne's next value
    }
    if (anotherOne._Down == -1) _Down = -1;
    else {
        _Down = anotherOne.getDown(); //setting to anotherOne's down value
    }

}


template <class DT>
int GLRow<DT>::getNext() { //getter for next
    return _Next;
}


template <class DT>
int GLRow<DT>::getDown() { //getter for down
    return _Down;
}


template <class DT>
DT* GLRow<DT>::getInfo() { //getter for info
    return _Info;
}


template <class DT>
void GLRow<DT>::setNext(int n) { // setter for next
    _Next = n;
}


template <class DT>
void GLRow<DT>::setDown(int d) { //setter for down
    _Down = d;

}


template <class DT>
void GLRow<DT>::setInfo(DT x) { //setter for info
    _Info = new DT(x);
}


template <class DT>
ostream& operator << (ostream& s, GLRow<DT>& oneGLRow) { //overloaded << operator
    if (oneGLRow.getInfo() != nullptr) {
        s << *oneGLRow.getInfo(); // printing out in parathesis
    }
    return s;
}

template <class DT>
GLRow<DT>::~GLRow<DT>() { //destructor method
    if (_Info != nullptr)
    {
        delete _Info;
    }
}







template <class DT>
class ArrayGLL; //class prototype
template <class DT>
ostream& operator << (ostream& s, ArrayGLL<DT>& oneGLL);

template <class DT>
class ArrayGLL {
    friend ostream& operator << <DT>(ostream& s, ArrayGLL<DT>& oneGLL);
protected:
    GLRow<DT>* myGLL = new GLRow<DT>[0];
    int maxSize; //maximum size of the array
    int firstElement;
    int firstFree;
public:
    ArrayGLL();
    ArrayGLL(int size);
    ArrayGLL(ArrayGLL<DT>& anotherOne);
    void copy(ArrayGLL<DT>& anotherOne); //copy method
    ArrayGLL<DT>& operator = (ArrayGLL<DT>& anotherOne);
    void display(); //display in parenthesis format
    int display(int l);
    int _find(DT& key, int i);
    int _findDP(DT& key, int i);
    int find(DT& key); //return the index position of found key
    void findDisplayPath(DT& Key);
    void insertAChild(DT& parent, DT& child);
    int findFree();
    int noFree();
    int _size(int i);
    int size();
    // int parenPos(DT& key);
    GLRow<DT>& operator[](int pos);
    int getMaxSize();
    int getFirstFree();
    int getFirstElement();
    void setFirstFree(int pos);
    void setFirstElement(int pos);

    ~ArrayGLL();

};


template <class DT>
ArrayGLL<DT>::ArrayGLL() { //default constructor
    myGLL = nullptr;
    maxSize = NULL;
    firstElement = NULL;
    firstFree = NULL;
}


template <class DT>
ArrayGLL<DT>::ArrayGLL(int size) { //non-default constructor
    myGLL = new GLRow<DT>[size];
    maxSize = size;
    firstElement = -1;
    firstFree = -1;
}



template <class DT>
void ArrayGLL<DT>::copy(ArrayGLL<DT>& anotherOne) { // helper constructor to copy
    myGLL = anotherOne.myGLL;
    maxSize = anotherOne.getMaxSize();
    firstElement = anotherOne.getFirstElement();
    firstFree = anotherOne.getFirstFree();
}


template <class DT>
ArrayGLL<DT>::ArrayGLL(ArrayGLL<DT>& anotherOne) { // copy constructor
    copy(anotherOne);
}


template<class DT>
ArrayGLL<DT>& ArrayGLL<DT>::operator=(ArrayGLL<DT>& anotherOne) //overloaded = operator
{
    copy(anotherOne);

    return *this;
}



template <class DT>
int ArrayGLL<DT>::_find(DT& key, int i) { //given helper method
    if (i == -1) return -1;

    else if ((*myGLL[i].getInfo()) == key) return i;

    else {
        int t = _find(key, myGLL[i].getNext());
        if (t > -1) return t;
        else return (_find(key, myGLL[i].getDown()));
    }
}

template <class DT>
int ArrayGLL<DT>::_findDP(DT& key, int i) { //modified given helper method to display find path
    cout << myGLL[i];

    if (i == -1) return -1;

    else if (*myGLL[i].getInfo() == key)
    {

        return i;
    }

    else {
        int t = _findDP(key, myGLL[i].getNext());

        if (t > -1)
        {
            return t;
        }

        else
        {
            return (_findDP(key, myGLL[i].getDown()));
        }
    }
}

template <class DT>
int ArrayGLL<DT>::find(DT& key) { //given find method
    return _find(key, firstElement);
}

template <class DT>
void ArrayGLL<DT>::findDisplayPath(DT& Key) { //method to display how the gll searches for a value
    cout << "[";
    _findDP(Key, firstElement);
    cout << "]" << endl;;
}


template <class DT>
void ArrayGLL<DT>::insertAChild(DT& parent, DT& child) {
    int locationOfParent = find(parent);
    int insertAt = findFree();

    (*this)[insertAt].setInfo(child);

    int tempDown = (*this)[locationOfParent].getDown();
    (*this)[locationOfParent].setDown(insertAt);

    (*this)[insertAt].setDown(tempDown);
    (*this)[insertAt].setDown(-1);
}


template<class DT>
int ArrayGLL<DT>::findFree() {

    int free = getFirstFree();
    int nextFree = (*this)[free].getNext();
    firstFree = nextFree;
    return free;
}


template <class DT>
int ArrayGLL<DT>::noFree() { //method to search for the number of free elements

    int count = 0;
    while (firstFree != -1) {

        if (myGLL[firstFree].getInfo() != nullptr) {
            count++;
            firstFree = myGLL[firstFree].getNext();
        }
    }
    return count;
}



template <class DT>
int ArrayGLL<DT>::_size(int i) { //given helper method to find the size of gll

    if (i == -1) return 0;
    if (myGLL[i].getInfo() == nullptr) return 0;
    return (1 + _size(myGLL[i].getNext()) + _size(myGLL[i].getDown()));
}

template <class DT>
int ArrayGLL<DT>::size() { //given size method
    return _size(firstElement);
}


template <class DT>
GLRow<DT>& ArrayGLL<DT> :: operator[](int pos) { //overloaded bracket operator

    return myGLL[pos];

}

template <class DT>
int ArrayGLL<DT>::getMaxSize() { //getter for maxSize
    return maxSize;
}

template <class DT>
int ArrayGLL<DT>::getFirstFree() { //getter for first free
    return firstFree;
}

template <class DT>
int ArrayGLL<DT>::getFirstElement() { //getter for first element
    return firstElement;
}

template <class DT>
void ArrayGLL<DT>::setFirstFree(int pos) { //setter for first free
    firstFree = pos;
}

template <class DT>
void ArrayGLL<DT>::setFirstElement(int pos) { //setter for first element
    firstElement = pos;
}


template <class DT>
ostream& operator << (ostream& s, ArrayGLL<DT>& oneGLL) { // overloaded << operator
    for (int i = 0; i < oneGLL.getMaxSize(); i++) {
        if (oneGLL[i].getInfo() != nullptr)
            s << oneGLL[i];
        if (i != (oneGLL.getMaxSize() - 1) )
            cout << " ";
    }
    return s;
}


template <class DT>
int ArrayGLL<DT>::display(int l) {

    if (myGLL[l].getInfo() == nullptr) return -1;
    cout << myGLL[l]; 


    if ((myGLL[l].getNext() == -1) && (myGLL[l].getDown() == -1)) {
        cout << ")) ";
        return -1;
    }
    
    int t = -1;

    if (myGLL[l].getDown() != -1) {
        int t = display(myGLL[l].getDown());
    }
    if (t > -1) 
        return t;

    else {
        if (myGLL[myGLL[l].getNext()].getInfo() != nullptr)
            cout << "( ";
        return display(myGLL[l].getNext());
    }
}

template <class DT>
void ArrayGLL<DT>::display() {
    
    cout << myGLL[getFirstElement()] << " ";

    if (myGLL[getFirstElement()].getDown() > -1) {
        display(myGLL[getFirstElement()].getDown());

        //int z = myGLL[myGLL[getFirstElement()].getDown()].getNext();

       // while (z != -1)
       // {
        //    display(z);
       // }
    }
}

template <class DT>
ArrayGLL<DT>::~ArrayGLL<DT>() {
}



int main() {

    ArrayGLL<int> firstGLL(20);
    int noElements, value, next, down; //parentPos;
    int pos = -1;
    //int keyValue;
    //int tempValue = 0;
    GLRow<int> oneRow; //note that this statically defined make sure you define all the variables first line of input contains the number of segments
    cin >> noElements;
    for (int i = 0; i < noElements; i++) {
        cin >> value >> next >> down;
        oneRow.setInfo(value);
        oneRow.setNext(next);
        oneRow.setDown(down);
        firstGLL[i] = oneRow;
    }
    firstGLL.setFirstFree(8);
    firstGLL.setFirstElement(2);
    cout << firstGLL << endl;
    //firstGLL.display();
    ArrayGLL<int>* secondGLL = new ArrayGLL<int>(firstGLL);



    firstGLL.display();

}
