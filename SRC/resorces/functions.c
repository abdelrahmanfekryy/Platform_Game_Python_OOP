/*#include <stdio.h>
int d = 0;
void main() 
{
    d = addme(5, 6);
    printf("%d",d);
}*/
#include "functions.h"
#include <math.h>
#include <cfloat>
#include <stdlib.h>
#include <Python.h>
//#include <Python.h>
#define NELEMS(x)  (sizeof(x) / sizeof(x.pnt[0]))
#define PI (float)acos(-1.0)
//###################################################################
point sum(array points,int no)
{
    point sum = {0,0};
    for(int i=0;i<no;i++)
    {
        sum.x += points.pnt[i].x;
        sum.y += points.pnt[i].y;    
    }
    return sum;
}
//###################################################################
point svcross(float s,point vec)
{
   return (point){-s*vec.y,s*vec.x};
}
//############################################################
point vscross(point vec,float s)
{
   return (point){s*vec.y,-s*vec.x};
}
//##################################################################
point normalize(float vecx,float vecy)
{
   float det = (float)sqrt(pow(vecx,2)+pow(vecy,2));
   point normal;
   normal = det == 0 ? (point){0,0} : (point){vecx/det,vecy/det};
   return normal;
}
//##################################################################
float minimum(float a,float b)
{
    return a < b ? a : b;
}
//#####################################################################
float maximum(float a,float b)
{
    return a > b ? a : b;
}
//##################################################################
point midpoint(point p1,point p2)
{
    point p3;
    p3.x = (p1.x + p2.x)/2;
    p3.y = (p1.y + p2.y)/2;
    return p3;
}
//##################################################################
checkpoint intersection(point p1,point p2,point p3,point p4)
{
   checkpoint re;
   float ua = ((p4.x-p3.x)*(p1.y-p3.y)-(p4.y-p3.y)*(p1.x-p3.x))/((p4.y-p3.y)*(p2.x-p1.x)-(p4.x-p3.x)*(p2.y-p1.y));
   float ub = ((p2.x-p1.x)*(p1.y-p3.y)-(p2.y-p1.y)*(p1.x-p3.x))/((p4.y-p3.y)*(p2.x-p1.x)-(p4.x-p3.x)*(p2.y-p1.y));
   re.pnt.x = p1.x + ua*(p2.x-p1.x);
   re.pnt.y = p1.y + ua*(p2.y-p1.y);
   re.check = ua>=0 && ua<=1 && ub>=0 && ub<=1;
   return re;
}
//###################################################################
float distance2p(point p1,point p2)
{
    return (float)sqrt(pow(p2.x - p1.x,2) + pow(p2.y - p1.y,2));
}
//###################################################################
checkpoint projection(point p1,point p2,point p3)
{
    checkpoint p4;
    p4.pnt.x = p3.x - ((p2.x-p1.x)*(p3.y-p2.y)-(p2.y-p1.y)*(p3.x-p2.x))/(float)(pow(p2.x-p1.x,2) + pow(p2.y-p1.y,2))*(p1.y-p2.y);
    p4.pnt.y = p3.y - ((p2.x-p1.x)*(p3.y-p2.y)-(p2.y-p1.y)*(p3.x-p2.x))/(float)(pow(p2.x-p1.x,2) + pow(p2.y-p1.y,2))*(p2.x-p1.x);
    p4.check = distance2p(p4.pnt,p2) <= distance2p(p2,p3) && distance2p(p4.pnt,p3) <= distance2p(p2,p3);
    return p4;
}
//###################################################################
point Lengthening(point p1,point p2,float v,float h)
{
    point p3;
    point p4;
    p3.x = p2.x + v * (p2.x - p1.x)/ (float)sqrt(pow(p2.x - p1.x,2) + pow(p2.y - p1.y,2) + 0.00000001);
    p3.y = p2.y + v * (p2.y - p1.y)/ (float)sqrt(pow(p2.x - p1.x,2) + pow(p2.y - p1.y,2) + 0.00000001);
    p4.x = p3.x + h * (p3.y - p1.y)/ (float)sqrt(pow(p1.y - p3.y,2) + pow(p3.x - p1.x,2) + 0.00000001);
    p4.y = p3.y + h * (p1.x - p3.x)/ (float)sqrt(pow(p1.y - p3.y,2) + pow(p3.x - p1.x,2) + 0.00000001);
    return p4;
}
//##########################################################################
point Centroid(array2 p)
{
    point c;
    float det = 0;
    float detsum = 0;
    float centroidX = 0;
    float centroidY = 0;
    int j = 0;
    for(int i=0;i<p.no;i++)
    {
       j = i == p.no - 1? 0:i + 1;
       det = p.pnt[i].x * p.pnt[j].y - p.pnt[j].x * p.pnt[i].y;
       detsum += det;
       centroidX += (p.pnt[i].x + p.pnt[j].x)*det;
       centroidY += (p.pnt[i].y + p.pnt[j].y)*det;
    }
    c.x = centroidX/(3*detsum);
    c.y = centroidY/(3*detsum);
    return (point){centroidX/(3*detsum),centroidY/(3*detsum)};
}
//##########################################################################
point subv(point p1,point p2)
{
    point p3 = {p1.x - p2.x,p1.y - p2.y};
    return p3;
}
//##########################################################################
point addv(point p1,point p2)
{
    point p3 = {p1.x + p2.x,p1.y + p2.y};
    return p3;
}
//###########################################################################
float dot(point p1,point p2)
{
   return p1.x*p2.x + p1.y*p2.y;
}
//###########################################################################
float angle(point p1,point p2)
{
    float th = atan2((p2.y - p1.y),(p2.x - p1.x)) >= 0? (float)atan2((p2.y - p1.y),(p2.x - p1.x)):(float)atan2((p2.y - p1.y),(p2.x - p1.x)) + 2*PI;
    return th;
}
//############################################################################
point rotate(point vec,float theta)
{
    return (point){vec.x*cos(theta) - vec.y*sin(theta),vec.y*cos(theta) + vec.x*sin(theta)};
}
//############################################################################
float vvcross(point vec1,point vec2)
{
    return vec1.x*vec2.y - vec2.x*vec1.y;
}
//###########################################################################
bool isBetween(point p1,point p2,point p3,point ref)
{   
    point A = subv(p2,ref);
    point B = subv(p1,ref);
    point C = subv(p3,ref);
    return (vvcross(A,B) * vvcross(A,C) >= 0) && (vvcross(C,B) * vvcross(C,A) >=0);
}
//############################################################################
collision point_polygon(shape *shape1,shape *shape2)
{
    collision data;
    struct  {
                polar *pnt;
                int no;
                point center;
                lines axis;
                polar prj[10];
                polar dist[10];
            } p[2];
    bool con1;
    bool con2;
    data.contacts.no = 0;
    data.check = true;
    int k;
    p[0].pnt = shape1[0].no == 1 ? shape2[0].pnt : shape1[0].pnt;
    p[1].pnt = shape1[0].no == 1 ? shape1[0].pnt : shape2[0].pnt;
    p[0].no = shape1[0].no == 1 ? shape2[0].no : shape1[0].no;
    p[0].center = shape1[0].no == 1 ? shape2[0].center : shape1[0].center;
    p[0].axis = shape1[0].no == 1 ? shape2[0].axis : shape1[0].axis;
    for(int i=0;i < p[0].no;i++)
    {
        p[0].prj[i].loc = projection(p[0].axis.a[i].loc,p[0].center,p[1].pnt[0].loc).pnt;
        p[0].prj[i].th = angle(p[0].center,p[0].prj[i].loc);
        p[0].prj[i].r = distance2p(p[0].center,p[0].prj[i].loc);
        k = i == p[0].no - 1 ? 0 : i + 1;
        con1 = p[0].prj[i].r < p[0].axis.a[i].r && isBetween(p[0].prj[i].loc,p[0].pnt[i].loc,p[0].pnt[k].loc,p[0].center);
        if(con1)
        {
            p[0].dist[i].r =  p[0].axis.a[i].r - p[0].prj[i].r;
            p[0].dist[i].th = p[0].prj[i].th;
        }
        con2 = p[0].prj[i].r < p[0].axis.b[i].r && !isBetween(p[0].prj[i].loc,p[0].pnt[i].loc,p[0].pnt[k].loc,p[0].center);
        if(con2)
        {
            p[0].dist[i].r =  p[0].axis.b[i].r - p[0].prj[i].r;
            p[0].dist[i].th = p[0].prj[i].th;
        }
        data.check &= con1 || con2;
    }
    if(data.check)
    {
        data.mtv = p[0].dist[0];
        for(int i=0;i < p[0].no;i++)
        {
            if(p[0].dist[i].r <= data.mtv.r)
            {
                data.mtv = p[0].dist[i];
            }
        }
        data.contacts.no = 1;
        data.contacts.pnt[0] =  p[1].pnt[0].loc;
        if(shape1[0].no == 1)
            data.mtv.r = -data.mtv.r;
    }
    return data;
}
//############################################################################
/*collision point_polygon(array2 points1,array2 points2)
{
    collision data;
    array2 p[2];
    p[0] = points1.no == 1 ? points2 : points1;
    p[1] = points1.no == 1 ? points1 : points2;
    point v0,v1,v2; 
    float invDenom = 0,u =0,v = 0;
    //--Barycentric Technique
    data.check = false;
    for(int i=1;i < p[0].no - 1;i++)
    {
        v0 = subv(p[0].pnt[i],p[0].pnt[0]);
        v1 = subv(p[0].pnt[i+1],p[0].pnt[0]);
        v2 = subv(p[1].pnt[0],p[0].pnt[0]);
        
        invDenom = 1 / (dot(v0, v0) * dot(v1, v1) - dot(v0, v1) * dot(v0, v1));
        u = (dot(v1, v1) * dot(v0, v2) - dot(v0, v1) * dot(v1, v2)) * invDenom;
        v = (dot(v0, v0) * dot(v1, v2) - dot(v0, v1) * dot(v0, v2)) * invDenom;
        data.check |= ((u >= 0) && (v >= 0) && (u + v < 1));
    }
    return data;
}*/
//########################################################################
collision point_circle(shape *shape1,shape *shape2)
{
    collision data;
    shape *p[2];
    p[0] = shape1[0].no == 1 ? shape2 : shape1;
    p[1] = shape1[0].no == 1 ? shape1 : shape2;
    float rp = distance2p(p[0][0].center,p[1][0].pnt[0].loc);
    data.check = rp <= p[0][0].pnt[0].r;
    if(data.check)
    {
        data.mtv.th = angle(p[0][0].center,p[1][0].pnt[0].loc);
        data.mtv.r = p[0][0].pnt[0].r - rp;
        data.contacts.no = 1;
        data.contacts.pnt[0].x = p[0][0].pnt[0].r*(float)cos(data.mtv.th) + p[0][0].center.x;
        data.contacts.pnt[0].y = p[0][0].pnt[0].r*(float)sin(data.mtv.th) + p[0][0].center.y;
        if(shape1[0].no == 1)
            data.mtv.r = -data.mtv.r;
    }
    return data;
}
//########################################################################
collision circle_circle(shape *shape1,shape *shape2)
{
    collision data;
    data.contacts.no = 0;
    data.check = distance2p(shape1[0].center,shape2[0].center) <= shape1[0].pnt[0].r + shape2[0].pnt[0].r;
    if(data.check)
    {
        data.mtv.th = angle(shape1[0].center,shape2[0].center);
        data.mtv.r = shape1[0].pnt[0].r + shape2[0].pnt[0].r - distance2p(shape1[0].center,shape2[0].center);
        data.contacts.no = 1;
        data.contacts.pnt[0].x = shape1[0].center.x + shape1[0].pnt[0].r*(float)cos(data.mtv.th);
        data.contacts.pnt[0].y = shape1[0].center.y + shape1[0].pnt[0].r*(float)sin(data.mtv.th);
    }
    return data;
}
//########################################################################
collision polygon_polygon(shape *shape1,shape *shape2)
{
    collision data;
    gg p[2];
    p[0].pnt = shape1[0].pnt;
    p[1].pnt = shape2[0].pnt;
    p[0].no = shape1[0].no;
    p[1].no = shape2[0].no;
    p[0].center = shape1[0].center;
    p[1].center = shape2[0].center;
    p[0].axis = shape1[0].axis;
    p[1].axis = shape2[0].axis;
    int k;
    float min;
    bool con[3];
    for(int a=0;a < 2;a++)
    {
        for(int b=0;b < p[a].no;b++)
        {
            for(int i=0;i < 2;i++)
            {
                for(int c=0;c < 2;c++)
                    con[c] = true;
                for(int j=0;j < p[i].no;j++)
                {
                    k = b == p[a].no - 1? 0 : b + 1;
                    p[a].prj[b].p[i].prj[j].loc = projection(p[a].axis.a[b].loc,p[a].center,p[i].pnt[j].loc).pnt;
                    p[a].prj[b].p[i].prj[j].th = angle(p[a].center,p[a].prj[b].p[i].prj[j].loc);
                    p[a].prj[b].p[i].prj[j].r = distance2p(p[a].center,p[a].prj[b].p[i].prj[j].loc);
                    con[0] &= isBetween(p[a].prj[b].p[i].prj[j].loc, p[a].pnt[b].loc, p[a].pnt[k].loc, p[a].center);
                    con[1] &= !isBetween(p[a].prj[b].p[i].prj[j].loc, p[a].pnt[b].loc, p[a].pnt[k].loc, p[a].center);
                }
                p[a].prj[b].p[i].con = con[0] || con[1];
            }
        }
    }
    for(int a=0;a < 2;a++)
    {
        for(int b=0;b < p[a].no;b++)
        {
            k = a == 1 ? 0 : 1;
            p[a].prj[b].p[k].minimum.r = 0;
            p[a].prj[b].p[k].minimum.loc = (point){0,0};
            min = p[a].prj[b].p[k].prj[0].r;
            if(p[a].prj[b].p[k].con)
            {
                for(int j=0;j < p[k].no;j++)
                {
                    if(p[a].prj[b].p[k].prj[j].r <= min)
                    {
                        min = p[a].prj[b].p[k].prj[j].r;
                        p[a].prj[b].p[k].minimum = p[a].prj[b].p[k].prj[j];
                    }
                }
            }
        }
    }
    data.check = true;
    int i;
    for(int a=0;a < 2;a++)
    {
        for(int b=0;b < p[a].no;b++)
        {
            k = b == p[a].no - 1? 0 : b + 1;
            i = a == 1 ? 0 : 1;
            con[0] = p[a].prj[b].p[i].minimum.r == 0;
            con[1] = isBetween(p[a].prj[b].p[i].minimum.loc,p[a].pnt[b].loc,p[a].pnt[k].loc,p[a].center) && (p[a].prj[b].p[i].minimum.r < p[a].axis.a[b].r);
            con[2] = !isBetween(p[a].prj[b].p[i].minimum.loc,p[a].pnt[b].loc,p[a].pnt[k].loc,p[a].center) && (p[a].prj[b].p[i].minimum.r < p[a].axis.b[b].r);
            data.check &= con[0] || con[1] || con[2];
        } 
    }
    
    if(data.check)
    {
        for(int a=0;a < 2;a++)
        {
            for(int b=0;b < p[a].no;b++)
            {
                k = b == p[a].no - 1? 0 : b + 1;
                i = a == 1 ? 0 : 1;
                p[a].prj[b].p[i].dist = p[a].prj[b].p[i].minimum;
                if(isBetween(p[a].prj[b].p[i].minimum.loc,p[a].pnt[b].loc,p[a].pnt[k].loc,p[a].center))
                    p[a].prj[b].p[i].dist.r = p[a].axis.a[b].r - p[a].prj[b].p[i].minimum.r;
                else
                    p[a].prj[b].p[i].dist.r = p[a].axis.b[b].r - p[a].prj[b].p[i].minimum.r;
            }
        }
        for(int a=0;a < 2;a++)
        {
            i = a == 1 ? 0 : 1;
            min = p[a].prj[0].p[i].dist.r;
            for(int b=0;b < p[a].no;b++)
            {
                if(p[a].prj[b].p[i].dist.r <= min)
                {
                    min = p[a].prj[b].p[i].dist.r;
                    p[a].mtv = p[a].prj[b].p[i].dist;
                }
            }
        }
        p[1].mtv.r = -p[1].mtv.r;
        data.mtv = fabs(p[0].mtv.r) <= fabs(p[1].mtv.r) ? p[0].mtv : p[1].mtv;
    }
    data.contacts.no = 0;
    int c = 0;
    if(data.check)
    {
        for(int a=0;a < 2;a++)
        {
            for(int b=0;b < p[0].no;b++)
            {
                con[2] = true;
                for(int j=0;j < p[1].no;j++)
                {
                    i = a == 1 ? 0 : 1;
                    k = j == p[1].no - 1 ? 0 : j + 1;
                    con[0] = p[i].prj[j].p[a].prj[b].r < p[i].axis.a[j].r && isBetween(p[i].prj[j].p[a].prj[b].loc, p[i].pnt[j].loc, p[i].pnt[k].loc, p[i].center);
                    con[1] = p[i].prj[j].p[a].prj[b].r < p[i].axis.b[j].r && !isBetween(p[i].prj[j].p[a].prj[b].loc, p[i].pnt[j].loc, p[i].pnt[k].loc, p[i].center);
                    con[2] &= con[0] || con[1];
                }
                if(con[2] && c < 2)
                {
                    data.contacts.pnt[c] = p[a].pnt[b].loc;
                    c++;
                }
            }
        }
        data.contacts.no = c;
    }
    return data;
}
//########################################################################
collision circle_polygon(shape *shape1,shape *shape2)
{
    collision data;
    polar closest;
    gg p[2];
    p[0].pnt = shape1[0].no == 2 ? shape1[0].pnt :shape2[0].pnt;
    p[1].pnt = shape1[0].no == 2 ? shape2[0].pnt :shape1[0].pnt;
    p[0].center = shape1[0].no == 2 ? shape1[0].center :shape2[0].center;
    p[1].center = shape1[0].no == 2 ? shape2[0].center :shape1[0].center;
    p[1].axis = shape1[0].no == 2 ? shape2[0].axis :shape1[0].axis;
    float c_radius = p[0].pnt[0].r;
    int k;
    bool con[3];
    float min;
    closest.r = distance2p(p[0].center,p[1].pnt[0].loc);
    for(int i=0;i < p[1].no;i++)
    {
        if(distance2p(p[0].center,p[1].pnt[i].loc) <= closest.r)
        {
            closest.r = distance2p(p[0].center,p[1].pnt[i].loc);
            closest.th = angle(p[0].center,p[1].pnt[i].loc);
            closest.loc = p[1].pnt[i].loc;
        }
    }
  

    for(int i=0;i < p[1].no;i++)
    {
        point centerc = projection(p[1].center,p[1].axis.a[i].loc,p[0].center).pnt;
        for(int j = 0;j < p[0].no;j++)
        {
            k = j == 0 ? -1 : 1;
            p[1].prj[i].p[0].prj[j].loc = Lengthening(p[0].center,centerc,0,k*c_radius);
            p[1].prj[i].p[0].prj[j].th = angle(p[1].center,p[1].prj[i].p[0].prj[j].loc);
            p[1].prj[i].p[0].prj[j].r = distance2p(p[1].center,p[1].prj[i].p[0].prj[j].loc);
        }
        p[0].prj[0].p[1].prj[i].loc = projection(closest.loc,p[0].center,p[1].pnt[i].loc).pnt;
        p[0].prj[0].p[1].prj[i].th = angle(p[0].prj[0].p[1].prj[i].loc,p[0].center);
        p[0].prj[0].p[1].prj[i].r = distance2p(p[0].prj[0].p[1].prj[i].loc,p[0].center);
    }

    for(int i=0;i < p[1].no;i++)
    {
        for(int c=0;c < 2;c++)
            con[c] = true;
        k = i == p[1].no - 1? 0 : i + 1;
        for(int j=0;j < p[0].no;j++)
        {   
            con[0] &= isBetween(p[1].prj[i].p[0].prj[j].loc,p[1].pnt[i].loc,p[1].pnt[k].loc,p[1].center);
            con[1] &= !isBetween(p[1].prj[i].p[0].prj[j].loc,p[1].pnt[i].loc,p[1].pnt[k].loc,p[1].center);
        }
        p[1].prj[i].p[0].con = con[0] || con[1];
    }
    for(int i=0;i < p[1].no;i++)
    {
        p[1].prj[i].p[0].minimum.r = 0;
        min = p[1].prj[i].p[0].prj[0].r;
        if(p[1].prj[i].p[0].con)
        {
            for(int j=0;j < p[0].no;j++)
            {
                if(p[1].prj[i].p[0].prj[j].r <= min)
                {
                    min = p[1].prj[i].p[0].prj[j].r;
                    p[1].prj[i].p[0].minimum = p[1].prj[i].p[0].prj[j];
                }
            }
        }
    }
    //____________________________________________________________________
    p[0].prj[0].p[1].con = true;
    for(int i=0;i < p[1].no;i++)
    {
       p[0].prj[0].p[1].con &= isBetween(p[0].prj[0].p[1].prj[i].loc,addv(rotate(subv(closest.loc,p[0].center),PI/4),p[0].center),addv(rotate(subv(closest.loc,p[0].center),-PI/4),p[0].center),p[0].center);
    }
    //____________________________________________________________________
    p[0].prj[0].p[1].minimum.r = 0;
    if(p[0].prj[0].p[1].con) 
    {
        p[0].prj[0].p[1].minimum.r = p[0].prj[0].p[1].prj[0].r;
        for(int i=0;i < p[1].no;i++)
        { 
            if(p[0].prj[0].p[1].prj[i].r <= p[0].prj[0].p[1].minimum.r)
            {
                p[0].prj[0].p[1].minimum = p[0].prj[0].p[1].prj[i];
            }
        }
    }
    data.check = p[0].prj[0].p[1].minimum.r <= c_radius;
    for(int i=0;i < p[1].no;i++)
    {
        k = i == p[1].no - 1? 0 : i + 1;
        con[0] = p[1].prj[i].p[0].minimum.r == 0;
        con[1] = isBetween(p[1].prj[i].p[0].minimum.loc,p[1].pnt[i].loc,p[1].pnt[k].loc,p[1].center) && (p[1].prj[i].p[0].minimum.r < p[1].axis.a[i].r);
        con[2] = !isBetween(p[1].prj[i].p[0].minimum.loc,p[1].pnt[i].loc,p[1].pnt[k].loc,p[1].center) && (p[1].prj[i].p[0].minimum.r < p[1].axis.b[i].r);
        data.check &= (con[0] || con[1] || con[2]);
    }
    data.contacts.no = 0;
    if(data.check)
    {
        for(int i=0;i < p[1].no;i++)
        {
            k = i == p[1].no - 1? 0 : i + 1;
            p[1].prj[i].p[0].dist = p[1].prj[i].p[0].minimum;
            if(isBetween(p[1].prj[i].p[0].minimum.loc,p[1].pnt[i].loc,p[1].pnt[k].loc,p[1].center))
                p[1].prj[i].p[0].dist.r = p[1].axis.a[i].r - p[1].prj[i].p[0].minimum.r;
            else
                p[1].prj[i].p[0].dist.r = p[1].axis.b[i].r - p[1].prj[i].p[0].minimum.r;
        }
        data.mtv.r = c_radius - p[0].prj[0].p[1].minimum.r;
        data.mtv.th = p[0].prj[0].p[1].minimum.th;
        for(int i=0;i < p[1].no;i++)
        {
            if(p[1].prj[i].p[0].dist.r <= data.mtv.r)
            {
                data.mtv = p[1].prj[i].p[0].dist;
            }
        }
        if(shape1[0].no == 2)
            data.mtv.r = -data.mtv.r;
        data.contacts.no = 1;
        data.contacts.pnt[0].x = p[0].center.x - c_radius*(float)cos(data.mtv.th);
        data.contacts.pnt[0].y = p[0].center.y - c_radius*(float)sin(data.mtv.th);
    }
    return data; 
}
//##################################################################################
collision SAT_Collide(shape *points1,shape *points2,bool resolveC,bool resolveP)
{
    bool circle,polygon,point;
    circle = (points1[0].no == 2) || (points2[0].no == 2);
    point = (points1[0].no == 1) || (points2[0].no == 1);
    polygon = (points1[0].no > 2) || (points2[0].no > 2);

    collision cld;
    if(circle && point)
        cld = point_circle(points1,points2);
    else if(point && polygon)
        cld = point_polygon(points1,points2);
    else if(polygon && circle)
        cld = circle_polygon(points1,points2);
    else if(circle)
        cld = circle_circle(points1,points2);
    else if(polygon)
        cld = polygon_polygon(points1,points2);

    if(resolveC)
        resolveCollision(points1,points2,cld);
    if(resolveP)
        resolvePhysics(points1,points2,cld);

    return cld;
}
//###########################################################################################
lines getaxis(array2 p,point center)
{
    lines axs;
    int k;
    float max;
    struct  {
                polar pnt[10];
            } axies[10];
    for(int j=0;j < p.no;j++)
    {
        k = j == p.no - 1? 0 : j + 1;
        axs.a[j].loc = projection(p.pnt[j],p.pnt[k],center).pnt;
        axs.a[j].th = angle(center,axs.a[j].loc);
        axs.a[j].r = distance2p(center,axs.a[j].loc);
    }
    for(int b=0;b < p.no;b++)
    {
        max = 0;
        for(int j=0;j < p.no;j++)
        {
            axies[b].pnt[j].loc = projection(axs.a[b].loc,center,p.pnt[j]).pnt;
            axies[b].pnt[j].th = angle(center,axies[b].pnt[j].loc);
            axies[b].pnt[j].r = distance2p(center,axies[b].pnt[j].loc);
            k = b == p.no - 1? 0 : b + 1;
            if(axies[b].pnt[j].r >= max && !isBetween(axies[b].pnt[j].loc,p.pnt[b],p.pnt[k],center))
            {
                max = axies[b].pnt[j].r;
                axs.b[b] = axies[b].pnt[j];
            }
        }
    }
    return axs;
}
//#########################################################
shape *newShape(array2 points,float inertia,float mass,float restitution,float friction)
{
    shape *ptr;
    ptr = (shape *) calloc(sizeof(shape),1);
    ptr[0].pnt = (polar *) calloc(sizeof(polar),points.no);
    ptr[0].dx = 0;
    ptr[0].dy = 0;
    ptr[0].dw = 0;
    ptr[0].no = points.no;
    ptr[0].inv_inertia = inertia == 0 ? 0 : (1 / inertia);
    ptr[0].restitution = restitution;
    ptr[0].friction = friction;
    ptr[0].inv_mass = mass == 0 ? 0 : (1 / mass);
    if(points.no > 2)
    {
        ptr[0].center = Centroid(points);
        ptr[0].axis = getaxis(points,ptr[0].center);
    }
    else if(points.no == 2)
    {
        ptr[0].center = midpoint(points.pnt[0],points.pnt[1]);
    }
    else if(points.no == 1)
    {
        ptr[0].center = points.pnt[0];
    }
    for(int i=0;i < points.no;i++)
    {
        ptr[0].pnt[i].loc = points.pnt[i];
        ptr[0].pnt[i].r = distance2p(ptr[0].center,points.pnt[i]);
        ptr[0].pnt[i].th = angle(ptr[0].center,points.pnt[i]);
    }
    return ptr; 
}
//###########################################################
void updateShape(shape *ptr)
{
    ptr[0].center.x += ptr[0].dx;
    ptr[0].center.y += ptr[0].dy;
    ptr[0].angle += ptr[0].dw;
    for(int i=0;i < ptr[0].no;i++)
    {
        ptr[0].pnt[i].loc.x = ptr[0].pnt[i].r*(float)cos(ptr[0].angle + ptr[0].pnt[i].th) + ptr[0].center.x;
        ptr[0].pnt[i].loc.y = ptr[0].pnt[i].r*(float)sin(ptr[0].angle + ptr[0].pnt[i].th) + ptr[0].center.y;
        if(ptr[0].no > 2)
        {
            ptr[0].axis.a[i].loc.x = ptr[0].axis.a[i].r*(float)cos(ptr[0].angle + ptr[0].axis.a[i].th) + ptr[0].center.x;
            ptr[0].axis.a[i].loc.y = ptr[0].axis.a[i].r*(float)sin(ptr[0].angle + ptr[0].axis.a[i].th) + ptr[0].center.y;
            ptr[0].axis.b[i].loc.x = ptr[0].axis.b[i].r*(float)cos(ptr[0].angle + ptr[0].axis.b[i].th) + ptr[0].center.x;
            ptr[0].axis.b[i].loc.y = ptr[0].axis.b[i].r*(float)sin(ptr[0].angle + ptr[0].axis.b[i].th) + ptr[0].center.y;
        }
    }
}
//###########################################################
void destroyShape(shape *ptr)
{
    free(ptr[0].pnt);
    free(ptr);
}
//###########################################################
void resolveCollision(shape *points1,shape *points2,collision cld)
{
    if(cld.check)
    {
        points1[0].center.x -= cld.mtv.r*(float)cos(cld.mtv.th)*points1[0].inv_mass/(points1[0].inv_mass + points2[0].inv_mass);
        points1[0].center.y -= cld.mtv.r*(float)sin(cld.mtv.th)*points1[0].inv_mass/(points1[0].inv_mass + points2[0].inv_mass);
        points2[0].center.x += cld.mtv.r*(float)cos(cld.mtv.th)*points2[0].inv_mass/(points1[0].inv_mass + points2[0].inv_mass);
        points2[0].center.y += cld.mtv.r*(float)sin(cld.mtv.th)*points2[0].inv_mass/(points1[0].inv_mass + points2[0].inv_mass);
    }
}
//###################################################################################
void resolvePhysics(shape *shape1,shape *shape2,collision sat)
{
   point rv,ra,rb,impulse,frictionimpulse,normal,tangent;
   float velAlongNormal,velAlongTangent;
   float e,uk,j,jt;

    if(sat.check)
    {
        for(int i=0;i < sat.contacts.no;i++)
        {
            ra = subv(sat.contacts.pnt[i],shape1[0].center);
            rb = subv(sat.contacts.pnt[i],shape2[0].center);
            normal = normalize(sat.mtv.r*(float)cos(sat.mtv.th),sat.mtv.r*(float)sin(sat.mtv.th));

            rv.x = (shape2[0].dx + svcross(shape2[0].dw,rb).x) - (shape1[0].dx + svcross(shape1[0].dw,ra).x);
            rv.y = (shape2[0].dy + svcross(shape2[0].dw,rb).y) - (shape1[0].dy + svcross(shape1[0].dw,ra).y);
            velAlongNormal = dot(rv,normal);
            if(velAlongNormal > 0)
                return;

            e = minimum(shape1[0].restitution, shape2[0].restitution);
            j = (-(1 + e) * velAlongNormal)/(float)(shape1[0].inv_mass + shape2[0].inv_mass + shape1[0].inv_inertia*pow(vvcross(ra,normal),2) + shape2[0].inv_inertia*pow(vvcross(rb,normal),2));
            j /= sat.contacts.no;
            impulse.x = j * normal.x;
            impulse.y = j * normal.y;

            shape1[0].dx -= shape1[0].inv_mass * impulse.x;
            shape1[0].dy -= shape1[0].inv_mass * impulse.y;
            shape1[0].dw -= shape1[0].inv_inertia * vvcross(ra,impulse);
            shape2[0].dx += shape2[0].inv_mass * impulse.x;
            shape2[0].dy += shape2[0].inv_mass * impulse.y;
            shape2[0].dw += shape2[0].inv_inertia * vvcross(rb,impulse);

            rv.x = (shape2[0].dx + svcross(shape2[0].dw,rb).x) - (shape1[0].dx + svcross(shape1[0].dw,ra).x);
            rv.y = (shape2[0].dy + svcross(shape2[0].dw,rb).y) - (shape1[0].dy + svcross(shape1[0].dw,ra).y);
            velAlongNormal = dot(rv,normal);
            
            tangent = vscross(normal,1);
            velAlongTangent = -dot( rv, tangent );
            uk = (float)sqrt(pow(shape1[0].friction,2) + pow(shape2[0].friction,2));
            jt = (uk * velAlongTangent)/(float)(shape1[0].inv_mass + shape2[0].inv_mass + shape1[0].inv_inertia*pow(vvcross(ra,normal),2) + shape2[0].inv_inertia*pow(vvcross(rb,normal),2));
            jt /= sat.contacts.no;

            frictionimpulse.x = jt * tangent.x;
            frictionimpulse.y = jt * tangent.y;

            shape1[0].dx -= shape1[0].inv_mass * frictionimpulse.x;
            shape1[0].dy -= shape1[0].inv_mass * frictionimpulse.y;
            shape1[0].dw -= shape1[0].inv_inertia * vvcross(ra,frictionimpulse);
            shape2[0].dx += shape2[0].inv_mass * frictionimpulse.x;
            shape2[0].dy += shape2[0].inv_mass * frictionimpulse.y;
            shape2[0].dw += shape2[0].inv_inertia * vvcross(rb,frictionimpulse);
        }
    }
}
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
xx *light(point p,int r)
{
    xx *c;
    int d;
    c = (xx *) calloc(sizeof(xx),1);
    for(int i=0;i< 800;i++)
        for(int j=0;j< 500;j++)
        {
            d = (int)sqrt(pow(i - p.x,2) + pow(j - p.y,2));
            for(int k=0;k < 3;k++)
            { 
                c[0].rgb[i][j][k] = d < r ? d*(255*3/4)/r : 255*3/4;
            }
        }
    return c;
}
//#################################################################################
void destroylight(xx *ptr)
{
    free(ptr);
}
//#################################################################################
/*bool quicpolygon_polygon(array2 shape1,array2 shape2)
{
    for
}*/
//#################################################################################
dd *lights(shape * shapes[],int no,point source,float r)
{
    array2 box;
    box.no = 4;
    box.pnt[0].x = source.x - r;
    box.pnt[0].y = source.y - r;
    box.pnt[1].x = source.x - r;
    box.pnt[1].y = source.y + r;
    box.pnt[2].x = source.x + r;
    box.pnt[2].y = source.y + r;
    box.pnt[3].x = source.x + r;
    box.pnt[3].y = source.y - r;
    ff ptr;
    ptr.no = 0;
    for(int i=0;i<no;i++)
    {   
       
        bool col3 = false;
        ptr.shaped[ptr.no].no = 0;
        ptr.shaped[ptr.no].sorted = true;
        for(int j=0;j<shapes[i][0].no;j++)
        {
            bool col1 = true;
            for(int k = 0;k<box.no;k++)
            {   
                int kk = k == box.no -1 ? 0 : k + 1;
                int kkk = kk == box.no - 1 ? 0 : kk + 1;     
                col1 &= isBetween(shapes[i][0].pnt[j].loc,box.pnt[k],box.pnt[kkk],box.pnt[kk]);
            }
            if(col1)
            {
                ptr.shaped[ptr.no].pnt[ptr.shaped[ptr.no].no].loc = shapes[i][0].pnt[j].loc;
                ptr.shaped[ptr.no].no ++;
            }
            col3 |= col1; 
        }
        for(int k = 0;k<box.no;k++)
        {
            bool col2 = true;
            for(int j=0;j<shapes[i][0].no;j++)
            {   
                int jj = j == shapes[i][0].no - 1 ? 0 : j + 1;
                int jjj = jj == shapes[i][0].no - 1 ? 0 : jj + 1;
                col2 &= isBetween(box.pnt[k],shapes[i][0].pnt[j].loc,shapes[i][0].pnt[jjj].loc,shapes[i][0].pnt[jj].loc);
            }
            if(col2)
            {
                ptr.shaped[ptr.no].pnt[ptr.shaped[ptr.no].no].loc = box.pnt[k];
                ptr.shaped[ptr.no].no++;
            }
            col3 |= col2; 
        }
        for(int j=0;j<shapes[i][0].no;j++)
        {
            int jj = j == shapes[i][0].no - 1 ? 0 : j + 1;
            for(int k = 0;k<box.no;k++)
            {
                int kk = k == box.no - 1 ? 0 : k + 1;
                checkpoint g = intersection(shapes[i][0].pnt[j].loc,shapes[i][0].pnt[jj].loc,box.pnt[k],box.pnt[kk]);
                if(g.check)
                {
                    ptr.shaped[ptr.no].pnt[ptr.shaped[ptr.no].no].loc = g.pnt;
                    ptr.shaped[ptr.no].no++;
                    ptr.shaped[ptr.no].sorted = false;
                }
                col3 |= g.check;
            }
        }
        if(col3)
        {
            if(!ptr.shaped[ptr.no].sorted)
            {
                point center = (point){0,0};
                polar temp;
                for(int i=0;i<ptr.shaped[ptr.no].no;i++)
                {
                    center.x += ptr.shaped[ptr.no].pnt[i].loc.x;
                    center.y += ptr.shaped[ptr.no].pnt[i].loc.y;
                }
                center.x /= ptr.shaped[ptr.no].no;
                center.y /= ptr.shaped[ptr.no].no;
                ptr.shaped[ptr.no].center = center;
                for(int i=0;i<ptr.shaped[ptr.no].no;i++)
                {
                    ptr.shaped[ptr.no].pnt[i].th = angle(center,ptr.shaped[ptr.no].pnt[i].loc);
                }
                for(int i=0;i<ptr.shaped[ptr.no].no;i++)
                {
                    for(int j=i+1;j<ptr.shaped[ptr.no].no;j++)
                    {
                        if(ptr.shaped[ptr.no].pnt[j].th < ptr.shaped[ptr.no].pnt[i].th)
                        {
                            temp = ptr.shaped[ptr.no].pnt[i];
                            ptr.shaped[ptr.no].pnt[i] = ptr.shaped[ptr.no].pnt[j];
                            ptr.shaped[ptr.no].pnt[j] = temp;
                        }
                    }
                }
            }
            ptr.no++;
        }
       
    }
    ptr.shaped[ptr.no].no = box.no;
    for(int k = 0;k<box.no;k++)
    {
        ptr.shaped[ptr.no].pnt[k].loc = box.pnt[k];
    }
    ptr.no++;
    int rayno = 0;
    for(int i =0;i < ptr.no;i++)
    {
        rayno += ptr.shaped[i].no;
    }
    /*line *ray;
    line *rays1;
    line *rays2;
    ray = (line *) calloc(sizeof(line),rayno);
    rays1 = (line *) calloc(sizeof(line),rayno);
    rays2 = (line *) calloc(sizeof(line),rayno);*/
    nn ray;
    nn rays1;
    nn rays2;
    dd *dot;
    dot = (dd *)calloc(sizeof(dd),1);
    dot[0].no = 3*rayno;
    dot[0].pnt = (polar *)calloc(sizeof(polar),dot[0].no);
    ray.no = rayno;
    rays1.no = rayno;
    rays2.no = rayno;
    checkpoint g;
    float rad;
    int k = 0;
    float d = (float)sqrt(pow(r,2) + pow(r,2));
    for(int i=0;i<ptr.no;i++)
    {
        for(int j=0;j<ptr.shaped[i].no;j++)
        {
            /*ray[k].p1.loc = ptr.shaped[i].pnt[j].loc;
            ray[k].p2.loc = source;
            rays1[k].p1.loc = Lengthening(ptr.shaped[i].pnt[j].loc,source,0,1);
            rays1[k].p2.loc = Lengthening(source,ptr.shaped[i].pnt[j].loc,d,1);
            rays2[k].p1.loc = Lengthening(ptr.shaped[i].pnt[j].loc,source,0,-1);
            rays2[k].p2.loc = Lengthening(source,ptr.shaped[i].pnt[j].loc,d,-1);*/
            ray.pnt[k].p1.loc = source;
            ray.pnt[k].p2.loc = ptr.shaped[i].pnt[j].loc;
            rays1.pnt[k].p1.loc = source;
            rays1.pnt[k].p2.loc = Lengthening(source,ptr.shaped[i].pnt[j].loc,d,2);
            rays2.pnt[k].p1.loc = source;
            rays2.pnt[k].p2.loc = Lengthening(source,ptr.shaped[i].pnt[j].loc,d,-2);
            k++;
        }
    }
    for(int i=0;i<ray.no;i++)
    { 
        dot[0].pnt[i].r = (float)sqrt(pow(r,2) + pow(r,2)) + 5;
        dot[0].pnt[i].loc = ray.pnt[i].p2.loc;
        dot[0].pnt[i].th = angle(ray.pnt[i].p2.loc,source);
        dot[0].pnt[i + ray.no].r = (float)sqrt(pow(r,2) + pow(r,2)) + 5;
        dot[0].pnt[i + ray.no].loc = rays1.pnt[i].p2.loc;
        dot[0].pnt[i + ray.no].th = angle(rays1.pnt[i].p2.loc,source);
        dot[0].pnt[i + 2*ray.no].r = (float)sqrt(pow(r,2) + pow(r,2)) + 5;
        dot[0].pnt[i + 2*ray.no].loc = rays2.pnt[i].p2.loc;
        dot[0].pnt[i + 2*ray.no].th = angle(rays2.pnt[i].p2.loc,source);
        for(int j=0;j<ptr.no;j++)
        {
            for(int k=0;k<ptr.shaped[j].no;k++)
            {
                int kk = k == ptr.shaped[j].no -1 ? 0 : k+1;
                g = intersection(ray.pnt[i].p1.loc,ray.pnt[i].p2.loc,ptr.shaped[j].pnt[k].loc,ptr.shaped[j].pnt[kk].loc);
                rad = distance2p(g.pnt,ray.pnt[i].p1.loc);
                if(g.check && rad <= dot[0].pnt[i].r)
                {
                    dot[0].pnt[i].loc = g.pnt;
                    dot[0].pnt[i].r = rad;
                }
                g = intersection(rays1.pnt[i].p1.loc,rays1.pnt[i].p2.loc,ptr.shaped[j].pnt[k].loc,ptr.shaped[j].pnt[kk].loc);
                rad = distance2p(g.pnt,rays1.pnt[i].p1.loc);
                if(g.check && rad <= dot[0].pnt[i + ray.no].r)
                {
                    dot[0].pnt[i + ray.no].loc = g.pnt;
                    dot[0].pnt[i + ray.no].r = rad;
                }
                g = intersection(rays2.pnt[i].p1.loc,rays2.pnt[i].p2.loc,ptr.shaped[j].pnt[k].loc,ptr.shaped[j].pnt[kk].loc);
                rad = distance2p(g.pnt,rays2.pnt[i].p1.loc);
                if(g.check && rad <= dot[0].pnt[i + 2*ray.no].r)
                {
                    dot[0].pnt[i + 2*ray.no].loc = g.pnt;
                    dot[0].pnt[i + 2*ray.no].r = rad;
                }
            }
        }
    }
    polar temp;
    for(int i=0;i<dot[0].no;i++)
    {
        for(int j=i+1;j<dot[0].no;j++)
        {
            if(dot[0].pnt[j].th < dot[0].pnt[i].th)
            {
                temp = dot[0].pnt[i];
                dot[0].pnt[i] = dot[0].pnt[j];
                dot[0].pnt[j] = temp;
            }
        }
    }

  
    /*free(ray);
    free(rays1);
    free(rays2);*/
    //return ptr;
    return dot;
}
void destroylights(dd *ptr)
{
    free(ptr[0].pnt);
    free(ptr);
}