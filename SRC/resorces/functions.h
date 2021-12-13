typedef enum { false, true } bool;
typedef struct {
    float x;
    float y;
} point;
typedef struct {
    float flt[10];
    bool bl[10];
    point pnt[10];
} array;
typedef struct {
    float th;
    float r;
    point loc;
} polar;
typedef struct {
    bool check;
    polar mtv;
    struct { 
                point pnt[2];
                int no;
            }   contacts;
} collision;
typedef struct {
    point pnt[10];
    int no; 
} array2;
typedef struct {
    point pnt;
    bool check; 
} checkpoint;
//################################################################################
typedef struct  {
                    polar a[10];
                    polar b[10];
                } lines;
//#################################################################################
typedef struct  {
                polar mtv;
                polar *pnt;
                int no;
                point center;
                lines axis;
                struct  {
                            struct  {
                                        polar prj[10];
                                        bool con;
                                        polar minimum;
                                        polar dist;
                                    }   p[2];
                        }   prj[10];
            }   gg;
//##################################################################################
typedef struct  {
                    float dx;
                    float dy;
                    float dw;
                    float inv_mass;
                    float inv_inertia;
                    float restitution;
                    float friction;
                    polar *pnt;
                    point center;
                    float angle;
                    lines axis;
                    int no;
                } shape ;
//################################################################################
typedef struct  {
                    polar p1;
                    polar p2;
                } line;
//#################################################################################
typedef struct  {
                    polar p1[100];
                    polar p2[100];
                    int no;
                } lined;
//##################################################################################
typedef struct {
            shape *ptr[50];
            int no;
            }inrng;
//##################################################################################
 typedef struct {
        struct {
                polar pnt[10];
                int no;
                bool sorted;
                point center;
                } shaped[20];
        int no;
    } ff;
//##################################################################################
 typedef struct {
        line pnt[50];
        int no;
    } nn;
//##################################################################################
 typedef struct {
        polar *pnt;
        int no;
    } dd;
//##################################################################################
float distance2p(point p1,point p2);
float maximum(float a,float b);
float minimum(float a,float b);
float angle(point p1,point p2);
point midpoint(point p1,point p2);
checkpoint intersection(point p1,point p2,point p3,point p4);
checkpoint projection(point p1,point p2,point p3);
point Lengthening(point p1,point p2,float v,float h);
point Centroid(array2 p);
lines getaxis(array2 p,point center);
bool isBetween(point p1,point p2,point p3,point ref);
collision point_polygon(shape *shape1,shape *shape2);
collision point_circle(shape *shape1,shape *shape2);
collision circle_circle(shape *shape1,shape *shape2);
collision polygon_polygon(shape *shape1,shape *shape2);
collision circle_polygon(shape *shape1,shape *shape2);
collision SAT_Collide(shape *points1,shape *points2,bool resolveC,bool resolveP);
void resolveCollision(shape *points1,shape *points2,collision cld);
void resolvePhysics(shape *shape1,shape *shape2,collision sat);
shape *newShape(array2 points,float inertia,float mass,float restitution,float friction);
void destroyShape(shape *ptr);
void updateShape(shape *ptr);
typedef struct {
            int rgb[800][500][3];
} xx;
xx *light(point p,int r);
void destroylight(xx *ptr);

dd *lights(shape * shapes[],int no,point source,float r);
void destroylights(dd *ptr);