//----------------------------------------------

//pct fata de un poligon varianta gresita

//#include <iostream>
//#include <vector>
//
//long long viraj(long long ax, long long ay, long long bx, long long by, std::pair<long long, long long> c) {
//    long long viraj =
//            bx * c.second + ax * by + c.first * ay - (bx * ay + c.first * by + ax * c.second);
//    if (viraj > 0)
//        return 1;
//    else {
//        if (viraj < 0)
//            return -1;
//        else
//            return 0;
//    }
//}
//
//int isSupremum(std::pair<long long, long long> a, std::pair<long long, long long> b) {
//    if (a.second > b.second)
//        return 1;
//    if (a.second == b.second)
//        return 2;
//    return 0;
//}
//
//
//bool q_is_on_frontiere(std::pair<long long, long long> a, std::pair<long long, long long> b, int qx, int qy) {
//    if (viraj(a.first, a.second, b.first, b.second, std::make_pair(qx, qy)) == 0) {
//        if (qx >= std::min(a.first, b.first) and qx <= std::max(a.first, b.first) and qy >= std::min(a.second, b.second) and qy <= std::max(a.second, b.second))
//            return true;
//    }
//    return false;
//}
//
//int main() {
//    std::vector<std::pair<long long, long long>> polygon;
//    int n, m;
//    long long x, y, m_x = -(1 << 25), m_y = -(1 << 25);
//
//    std::cin >> n;
//
//    for (int i = 0; i < n; i++) {
//        std::cin >> x >> y;
//        polygon.emplace_back(std::make_pair(x, y));
//
//        m_x = std::max(m_x, x);
//        m_y = std::max(m_y, y);
//    }
//
//    m_x += rand() % 100000;
//    m_y += rand() % 100000;
//
//    std::cin >> m;
//
//    for (int p = 0; p < m; p++) {
//        std::cin >> x >> y;
//
//        int counter = 0;
//
//        //acum numar cate muchii intersecteaza muchia MQ
//
//        for (int i = 0; i < n - 1; i++) {
//            // verific daca intersecteaza muchia normal
//            int viraje = viraj(m_x, m_y, x, y, polygon[i]) * viraj(m_x, m_y, x, y, polygon[(i + 1) % (n - 1)]);
//
//            if (q_is_on_frontiere(polygon[i], polygon[(i + 1)/ (n - 1)], x, y)) {
//                std::cout << "BOUNDARY\n";
//                counter = -1;
//                break;
//            }
//
//            if (viraje == -1) {
//                counter ++;
//            } else {
//                if (viraje == 0 )
//                    counter += isSupremum(polygon[i], polygon[(i + 1) % (n - 1)]);
//                }
//        }
//
//        if (counter >= 0) {
//            if (counter % 2 == 0)
//                std::cout << "OUTSIDE\n";
//            else
//                std::cout << "INSIDE\n";
//        }
//    }
//
//    return 0;
//}


//--------------------------------------------

//pct fata de un poligon varianta buna

#include <iostream>
#include <vector>

using std::vector;

struct Point {
    int64_t x;
    int64_t y;
};

int doesIntersect(Point const &source, Point const &_a, Point const &_b) {

    // A is the lower point on the y axis
    Point a = _a.y < _b.y ? _a : _b;
    Point b = _a.y < _b.y ? _b : _a;

    // Check to see if a horizontal ray cast from the source intersects the line formed from this vertex and the next
    // a) AB is horizontal
    // b) AB is to the right
    // c) The ray intersects A or B
    // d) Simple intersection


    // We'll ignore the line from the beginning if it doesn't intersect our ray at all
    if ((a.y > source.y && b.y > source.y) || (a.y < source.y && b.y < source.y)) {
        return 0;
    }

    if (a.y == b.y && a.y == source.y) {
        if ((a.x < source.x && b.x > source.x) ||
            (b.x < source.x && a.x > source.x)) {
            // The point is on an edge
            return -1;
        } else {
            // It's the a) case,  ignore the intersection
            return 0;
        }
    }

    int64_t crossProduct = (source.x - a.x) * (b.y - a.y) - (source.y - a.y) * (b.x - a.x);

    if(crossProduct == 0){
        // The point is on an edge
        return -1;
    }

    if (crossProduct > 0) {
        // It's case b), ignore the intersection
        return 0;
    }

    if ( b.y == source.y ) {
        // The ray intersects the higher point of the edge
        return 1;
    }
    if ((a.y > source.y && b.y < source.y) || (a.y < source.y && b.y > source.y)) {
        // Regular intersection
        return 1;
    }


    return 0;
}

int getIntersectionCount(Point const &source, const vector<Point> &vertexes) {
    int intersectionCount = 0;
    for (int i = 0; i < vertexes.size() - 1; i++) {
        Point a = vertexes[i];
        Point b = vertexes[i + 1];

        int intersects = doesIntersect(source, a, b);
        if (intersects == -1) {
            // Point is on a line
            return -1;
        }

        intersectionCount += intersects;
    }

    // Repeat the calculation for the first and last points
    int intersects = doesIntersect(source, vertexes[vertexes.size() - 1], vertexes[0]);
    if (intersects == -1) {
        // Point is on a line
        return -1;
    }

    intersectionCount += intersects;

    return intersectionCount;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<Point> vertexes;
    for (int i = 0; i < n; i++) {
        Point newPoint{};
        std::cin >> newPoint.x >> newPoint.y;
        vertexes.push_back(newPoint);
    }

    int m;
    std::cin >> m;
    for (int i = 0; i < m; i++) {
        Point newPoint{};
        std::cin >> newPoint.x >> newPoint.y;
        auto intersectionCount = getIntersectionCount(newPoint, vertexes);
        if (intersectionCount == -1) {
            std::cout << "BOUNDARY" << std::endl;
        } else if (intersectionCount % 2 == 1) {
            std::cout << "INSIDE" << std::endl;
        } else {
            std::cout << "OUTSIDE" << std::endl;
        }
    }
    return 0;
}


//------------------------------------------------------------

// monotonia unui poligon
//points = []
//# citesc punctele
//n = int(input())
//for i in range(n):
//a, b = (int(x) for x in input().split())
//points.append((a, b))
//
//
//def check_monoton_x(points):
//
//inf = float("inf")
//start = -1, (inf, inf)
//
//# caut cel mai din stanga (la egalitate cel mai de jos) punct
//for i, (a, b) in enumerate(points):
//if (a < start[1][0]):
//start = i, (a, b)
//elif a == start[1][0] and b < start[1][1]:
//start = i, (a, b)
//
//# realizez o rotire circulara a listei a.i. acel punct sa fie primul
//points = points[start[0]:] + points[:start[0]]
//points.append(points[0])
//
//order = "increasing"
//
//last = start[1][0]
//# verific daca exista vero inconsistenta in ordine
//for a, _ in points:
//if a > last and order == "decreasing":
//print("NO")
//return
//
//if a < last and order == "increasing":
//order = "decreasing"
//
//last = a
//
//print("YES")
//
//
//def check_monoton_y(points):
//
//# asemanator cu rezolvarea pentru x-monotonie
//inf = float("inf")
//start = -1, (inf, inf)
//
//for i, (a, b) in enumerate(points):
//if (b < start[1][1]):
//start = i, (a, b)
//elif b == start[1][1] and a < start[1][0]:
//start = i, (a, b)
//
//points = points[start[0]:] + points[:start[0]]
//points.append(points[0])
//
//order = "increasing"
//
//last = start[1][1]
//for _, b in points:
//if b > last and order == "decreasing":
//print("NO")
//return
//
//if b < last and order == "increasing":
//order = "decreasing"
//
//last = b
//
//print("YES")
//
//
//check_monoton_x(points)
//check_monoton_y(points)



//--------------------------------------------------------

//pozitia unui punct fata de cerc

//#include <iostream>
//#include <vector>
//using namespace std;
//long long ax,bx,cx,ay,by,cy,dx,dy,d,x1,x2,y1,y2,z1,z2,t1,t2,t3,s1,s2;
//int m;
//
//int main()
//{
//    cin>>ax>>ay;
//    cin>>bx>>by;
//    cin>>cx>>cy;
//    vector <long long> v;
//    cin>>m;
//    for (int i=0;i<m;++i)
//    {
//        cin>>dx>>dy;
//        v.push_back(dx);
//        v.push_back(dy);
//    }
//    for (int i=0;i<2*m;i=i+2)
//    {
//        dx=v[i];
//        dy=v[i+1];
//        x1=bx-ax;
//        x2=by-ay;
//        y1=cx-ax;
//        y2=cy-ay;
//        z1=dx-ax;
//        z2=dy-ay;
//        t1=bx*bx-ax*ax+by*by-ay*ay;
//        t2=cx*cx-ax*ax+cy*cy-ay*ay;
//        t3=dx*dx-ax*ax+dy*dy-ay*ay;
//        s1=x1*y2*t3+y1*z2*t1+x2*t2*z1;
//        s2=z1*y2*t1+z2*t2*x1+x2*y1*t3;
//        d=s2-s1;
//        if(d>0)
//            cout<<"INSIDE"<<"\n";
//        else
//        if(d==0)
//            cout<<"BOUNDARY"<<"\n";
//        else
//            cout<<"OUTSIDE"<<"\n";
//
//    }
//}






//------------------------------------------------------

// muchii ilegale

//#include <iostream>
//#include <vector>
//using namespace std;
//long long ax,bx,cx,ay,by,cy,dx,dy,d,x1,x2,y1,y2,z1,z2,t1,t2,t3,s1,s2;
//int m;
//
//int main()
//{
//    cin>>ax>>ay;
//    cin>>bx>>by;
//    cin>>cx>>cy;
//
//    cin>>dx>>dy;
//
//
//    x1=bx-ax;
//    x2=by-ay;
//    y1=cx-ax;
//    y2=cy-ay;
//    z1=dx-ax;
//    z2=dy-ay;
//    t1=bx*bx-ax*ax+by*by-ay*ay;
//    t2=cx*cx-ax*ax+cy*cy-ay*ay;
//    t3=dx*dx-ax*ax+dy*dy-ay*ay;
//    s1=x1*y2*t3+y1*z2*t1+x2*t2*z1;
//    s2=z1*y2*t1+z2*t2*x1+x2*y1*t3;
//    d=s2-s1;
//    if(d>0)
//        cout << "AC: ILLEGAL" << '\n';
//
//
//
//    else
//        cout << "AC: LEGAL" << '\n';
//    x1=cx-bx;
//    x2=cy-by;
//    y1=dx-bx;
//    y2=dy-by;
//    z1=ax-bx;
//    z2=ay-by;
//    t1=cx*cx-bx*bx+cy*cy-by*by;
//    t2=dx*dx-bx*bx+dy*dy-by*by;
//    t3=ax*ax-bx*bx+ay*ay-by*by;
//    s1=x1*y2*t3+y1*z2*t1+x2*t2*z1;
//    s2=z1*y2*t1+z2*t2*x1+x2*y1*t3;
//    d=s2-s1;
//    d=s2-s1;
//    if(d>0)
//        cout << "BD: ILLEGAL" << '\n';
//    else
//        cout << "BD: LEGAL" << '\n';
//
//}

























