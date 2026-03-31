#include <bits/stdc++.h>

using namespace std;
typedef long double ld;
typedef long long int ll;
const ld INF = 1e18;
const ld EPS = 0.000000001;
const ld pi = 3.1415926535;

struct Point {
    ld x, y;

    explicit Point(ld x1 = 0, ld y1 = 0) {
        x = x1;
        y = y1;
    }
};

struct Vector {
    ld x = 0, y = 0;

    explicit Vector(){

    }

    explicit Vector(Point A, Point B) {
        x = B.x - A.x;
        y = B.y - A.y;
    }

    explicit Vector(ld x1, ld y1){
        x = x1;
        y = y1;
    }

    ld len() {
        return hypot(x, y);
    }

    Vector get_unite_vector() {
        return Vector(x / len(), y / len());
    }

    Vector turn(ld cos, ld sin) {
        return Vector(x * cos - y * sin, x * sin + y * cos);
    }

    Vector turn(ld a){
        return turn(cos(a), sin(a));
    }
};

Point operator+(Point A, Vector a) {
    return Point(A.x + a.x, A.y + a.y);
}

Vector operator+(Vector a, Vector b) {
    return Vector(a.x + b.x, a.y + b.y);
}

Point operator-(Point A, Vector a){
    return Point(A.x - a.x, A.y - a.y);
}

Vector operator*(Vector a, ld n) {
    return Vector(a.x * n, a.y * n);
}

ld operator*(Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

ld operator%(Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

Vector operator/(Vector a, ld n){
    return Vector(a.x / n, a.y / n);
}

istream &operator>>(istream &in, Point &A) {
    in >> A.x >> A.y;
    return in;
}

ostream &operator<<(ostream &out, Point A) {
    out << A.x << ' ' << A.y;
    return out;
}

bool operator<(Point a, Point b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool operator>(Point a, Point b) {
    return a.x > b.x || (a.x == b.x && a.y > b.y);
}

bool operator==(Point a, Point b) {
    return a.x == b.x && a.y == b.y;
}

struct segment {
    Point A, B;

    explicit segment(Point A1 = Point(), Point B1 = Point()) {
        A = min(A1, B1);
        B = max(A1, B1);
    }

    bool is_point_in_segment(Point X) {
        return Vector(X, A) % Vector(X, B) == 0 && Vector(A, B) * Vector(A, X) >= 0 && Vector(B, A) * Vector(B, X) >= 0;
    }

    Point get_middle(){
        return Point((A.x + B.x) / 2, (A.y + B.y) / 2);
    }
};

struct ray {
    Point A, B;

    explicit ray(){

    }

    explicit ray(Point A1, Point B1) {
        A = A1;
        B = B1;
    }

    explicit ray(Point A1, Vector V){
        A = A1;
        B = A + V;
    }

    bool is_point_in_ray(Point X) {
        return Vector(X, A) % Vector(X, B) == 0 && Vector(A, B) * Vector(A, X) >= 0;
    }
};

struct line {
    Vector v;
    Point A, B;
    ld a, b, c;

    explicit line(){

    }

    explicit line(Point A1, Point B1) {
        A = A1;
        B = B1;
        v = Vector(A, B);
        a = -v.y;
        b = v.x;
        c = -(A.x * a + A.y * b);
    }

    explicit line(ld a1, ld b1, ld c1){
        a = a1;
        b = b1;
        c = c1;
        v = Vector(b, -a);
        A = Point(-(a * c) / (a * a + b * b), -(b * c) / (a * a + b * b));
        B = A + v;
    }

    line get_perpendicular(Point X) {
        return line(-b, a, -(X.x * (-b) + X.y * a));
    }
};

struct angle {
    Point O;
    Vector a, b;

    explicit angle(){

    }

    explicit angle(Point O1, Point A, Point B) {
        O = O1;
        a = Vector(O1, A);
        b = Vector(O1, B);
    }

    explicit angle(Point O1, Vector a1, Vector b1){
        O = O1;
        a = a1;
        b = b1;
    }

    ld size() {
        return atan2(a % b, a * b) / pi * 180;
    }

    line get_bisector() {
        segment temp = segment(O + a.get_unite_vector(), O + b.get_unite_vector());
        line bisect = line(O, temp.get_middle());
        return bisect;
    }

    bool is_vector_in_angle(Vector x) {
        return (a % x) * (a % b) >= 0 && (b % x) * (b % a) >= 0;
    }

    bool is_point_in_angle(Point X) {
        return is_vector_in_angle(Vector(O, X));
    }
};

bool is_two_lines_intersect(line a, line b) {
    if (Vector(a.A, a.B) % Vector(b.A, b.B) != 0) {
        return true;
    }
    return Vector(a.A, a.B) % Vector(a.A, b.A) == 0;
}

bool is_two_rays_intersect(ray a, ray b) {
    angle a1, a2;
    a1.a = Vector(a.A, a.B);
    a1.b = Vector(b.A, a.A);
    a2.a = Vector(b.A, b.B);
    a2.b = Vector(a.A, b.A);
    if (a.A == b.A) {
        return true;
    }
    if (Vector(a.A, a.B) % Vector(b.A, b.B) == 0) {
        if (Vector(a.A, a.B) % Vector(a.A, b.A) != 0) {
            return false;
        } else if (Vector(a.A, a.B) * Vector(b.A, b.B) > 0) {
            return true;
        } else if (Vector(a.A, a.B) * Vector(a.A, b.A) > 0) {
            return true;
        }
        return false;
    }
    if ((a1.is_vector_in_angle(Vector(b.A, b.B)) && a2.is_vector_in_angle(Vector(a.A, a.B)))) {
        return true;
    }
    return false;
}

bool is_two_segments_intersect(segment a, segment b) {
    if (a.is_point_in_segment(b.A) || a.is_point_in_segment(b.B) || b.is_point_in_segment(a.A) ||
    b.is_point_in_segment(a.B)) {
        return true;
    }
    if ((Vector(a.A, a.B) % Vector(a.A, b.A)) * (Vector(a.A, a.B) % Vector(a.A, b.B)) > 0) {
        return false;
    }
    return (Vector(b.A, b.B) % Vector(b.A, a.A)) * (Vector(b.A, b.B) % Vector(b.A, a.B)) < 0;
}

bool is_segment_and_line_intersect(segment a, line b) {
    if (!is_two_lines_intersect(line(a.A, a.B), b)) {
        return false;
    }
    return (Vector(b.A, b.B) % Vector(b.A, a.A)) * (Vector(b.A, b.B) % Vector(b.A, a.B)) <= 0;
}

bool is_segment_and_ray_intersect(segment a, ray b) {
    return is_two_rays_intersect(ray(a.A, a.B), b) && is_two_rays_intersect(ray(a.B, a.A), b);
}

bool is_ray_and_line_intersect(ray a, line b) {
    return is_two_rays_intersect(a, ray(b.A, b.B)) || is_two_rays_intersect(a, ray(b.B, b.A));
}

pair<int, Point> get_intersection(line a, line b) {
    if (a.a * b.b == a.b * b.a && a.a * b.c == b.a * a.c){
        return {INF, Point()};
    }
    if (a.a * b.b == a.b * b.a && a.a * b.c != b.a * a.c){
        return {0, Point()};
    }
    ld temp = b.b * a.a - a.b * b.a;
    return {1, Point(-(a.c * b.b - b.c * a.b) / temp,(a.c * b.a - b.c * a.a) / temp)};
}

ld dist(Point A, Point B) {
    return Vector(A, B).len();
}

ld dist(Point A, segment a) {
    if (Vector(a.A, A) * Vector(a.A, a.B) > 0 && Vector(a.B, A) * Vector(a.B, a.A) > 0) {
        return abs(Vector(A, a.A) % Vector(A, a.B)) / dist(a.A, a.B);
    }
    return min(dist(A, a.A), dist(A, a.B));
}

ld dist(segment a, segment b) {
    if (is_two_segments_intersect(a, b)) {
        return 0;
    }
    return min(min(dist(a.A, b), dist(a.B, b)), min(dist(b.A, a), dist(b.B, a)));
}

ld dist(Point A, ray l) {
    if (Vector(l.A, l.B) * Vector(l.A, A) > 0) {
        return abs(ld(Vector(A, l.A) % Vector(A, l.B)) / dist(l.A, l.B));
    }
    return dist(A, l.A);
}

ld dist(Point A, line a) {
    return abs(ld(Vector(A, a.A) % Vector(A, a.B)) / dist(a.A, a.B));
}

ld dist(segment a, ray b) {
    if (is_segment_and_ray_intersect(a, b)) {
        return 0.0;
    } else {
        ld dist_1 = dist(a.A, b);
        ld dist_2 = dist(a.B, b);
        ld dist_3 = dist(b.A, a);
        ld dist_4 = dist(b.B, a);
        return min(min(dist_1, dist_2), min(dist_3, dist_4));
    }
}

ld dist(segment a, line b) {
    if (is_segment_and_line_intersect(a, b)) {
        return 0.0;
    } else {
        ld dist_1 = dist(a.A, b);
        ld dist_2 = dist(a.B, b);
        ld dist_3 = dist(b.A, a);
        ld dist_4 = dist(b.B, a);
        return min(min(dist_1, dist_2), min(dist_3, dist_4));
    }
}

ld dist(ray a, ray b) {
    if (is_two_rays_intersect(a, b)) {
        return 0.0;
    } else {
        ld dist_1 = dist(a.A, b);
        ld dist_2 = dist(a.B, b);
        ld dist_3 = dist(b.A, a);
        ld dist_4 = dist(b.B, a);
        return min(min(dist_1, dist_2), min(dist_3, dist_4));
    }
}

ld dist(ray a, line b) {
    if (is_ray_and_line_intersect(a, b)) {
        return 0.0;
    } else {
        ld dist_1 = dist(a.A, b);
        ld dist_2 = dist(a.B, b);
        ld dist_3 = dist(b.A, a);
        ld dist_4 = dist(b.B, a);
        return min(min(dist_1, dist_2), min(dist_3, dist_4));
    }
}

ld dist(line a, line b) {
    if (is_two_lines_intersect(a, b)) {
        return 0.0;
    } else {
        ld dist_1 = dist(a.A, b);
        ld dist_2 = dist(a.B, b);
        ld dist_3 = dist(b.A, a);
        ld dist_4 = dist(b.B, a);
        return min(min(dist_1, dist_2), min(dist_3, dist_4));
    }
}

struct circle {
    Point O;
    ld r;

    explicit circle(Point A = Point(), ld x = 0) {
        O = A;
        r = x;
    }
};

pair<int, vector<Point>> get_intersection(circle w1, circle w2) {
    if (w1.O == w2.O && w1.r == w2.r) {
        return {3, {}};
    }
    if (w1.r < w2.r) {
        swap(w1, w2);
    }
    Vector center_line = Vector(w1.O, w2.O);
    if (center_line.len() > w1.r + w2.r || w1.r > center_line.len() + w2.r) {
        return {0, {}};
    }
    if (center_line.len() == w1.r + w2.r || w1.r == center_line.len() + w2.r) {
        return {1, {w1.O + center_line.get_unite_vector() * w1.r}};
    }
    ld cos = (pow(w1.r, 2) + pow(center_line.len(), 2) - pow(w2.r, 2)) / (2 * w1.r * center_line.len());
    ld sin = sqrt(1 - cos * cos);
    Vector temp = center_line.get_unite_vector() * w1.r;
    return {2, {w1.O + temp.turn(cos, sin), w1.O + temp.turn(cos, -sin)}};
}

pair<int, vector<Point>> get_intersection(line a, circle w) {
    if (dist(w.O, a) > w.r && abs(dist(w.O, a) - w.r) > EPS) {
        return {0, {}};
    }
    if (abs(dist(w.O, a) - w.r) <= EPS) {
        return {1, {get_intersection(a, a.get_perpendicular(w.O)).second}};
    }
    ld h = dist(w.O, a);
    ld d = sqrt(w.r * w.r - h * h);
    Point H = get_intersection(a, a.get_perpendicular(w.O)).second;
    Vector temp = a.v.get_unite_vector() * d;
    return {2, {H + temp, H - temp}};
}

pair<int, vector<Point>> get_tangents(Point X, circle w){
    if (dist(X, w.O) < w.r){
        return {0, {}};
    }
    if (dist(X, w.O) == w.r){
        return {1, {X}};
    }
    return get_intersection(circle(segment(X, w.O).get_middle(), dist(X, w.O) / 2), w);
}

