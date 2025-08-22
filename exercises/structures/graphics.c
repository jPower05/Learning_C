
// define structures
#include <stdio.h>
typedef struct {
    int x;
    int y;
} Point;

// nested struct without using typedef
struct Rectangle{
    Point pt1;
    Point pt2;
};

Point make_point(int x, int y);
Point add_two_points(Point a, Point b);

int main(){
    Point p;
    p.x = 20; 
    p.y = 25;

    Point pt = {10,10};

    struct Rectangle rec = {p,pt};

    // make struct using function
    Point a = make_point(5,5);

    // pointers to structures
    Point origin = {10,10};
    Point *p_ptr;
    p_ptr = &origin;

    // use the " -> " notation to access the pointers membersq
    printf("origin is (%d, %d)", p_ptr->x, p_ptr->y);

}

// make a struct in a function
Point make_point(int x, int y){
    Point temp = {x,y};
    return temp;
}

// add the values of two structs
Point add_two_points(Point a, Point b){
    a.x += b.x;
    a.y += b.y;
    return a;
}