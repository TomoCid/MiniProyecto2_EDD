    #ifndef _STRUCTS
    #define _STRUCTS
    class Point
    {
    public:
        int x;
        int y;
        Point(int _x, int _y)
        {
            x = _x;
            y = _y;
        }
        Point()
        {
            x = 0;
            y = 0;
        }

    };
    class Node
    {   
    public:
        Point pos;
        int data;
        bool collisions; //IDEA

        Node(Point _pos, int _data)
        {
            pos = _pos;
            data = _data;
        }
        Node() { data = 0; }

        bool collision(){ //IDEA
            return collisions;
        }
        
    };
    #endif