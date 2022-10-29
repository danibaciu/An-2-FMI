from sympy.geometry import Point, Line, Polygon


def check_position(polygon: Polygon, start: Point):
    end = Point(999999, 9999999)
    intersections = 0

    for i in range(polygon.size):
        p1 = polygon.edges[i]
        p2 = polygon.edges[(i + 1) % polygon.size]
        if Point.compute_turn(p1, p2, start) == 0:
            return 0
        if Line(p1, p2).intersect(Line(start, end)):
            intersections += 1

    if intersections % 2 == 0:
        return -1
    return 1


def main():

    points_list = []

    n = int(input())

    for i in range(n):
        x, y = input().split()
        x, y = int(x), int(y)

        points_list.append({x, y})

    polygon = Polygon(points_list)

    m = int(input())

    for i in range(m):
        x, y = input().split()
        x, y = int(x), int(y)
        q = Point(x, y)

        pos = check_position(polygon, q)
        if pos == 1:
            print("INSIDE")
            return
        if pos == -1:
            print("OUTSIDE")
            return
        print("BOUNDARY")


if __name__ == '__main__':
    main()