import engine
import love

def max(a,b):
    return engine.lib.maximum(a,b)

def min(a,b):
    return engine.lib.minimum(a,b)

def midpoint(points):
    return engine.lib.midpoint(*points)

def intersection(x1,y1,x2,y2,x3,y3,x4,y4):
    d = engine.lib.intersection([x1,y1],[x2,y2],[x3,y3],[x4,y4])
    return [d.pnt[0],d.bl[0]]

def distance2p(point1,point2):
    return engine.lib.distance2p(point1,point2)

def angle(point1,point2):
    return engine.lib.angle(point1,point2)

def projection(x1,y1,x2,y2,x3,y3):
    return engine.lib.projection([x1,y1],[x2,y2],[x3,y3])

def Lengthening(x1,y1,x2,y2,v,h):
    return engine.lib.Lengthening([x1,y1],[x2,y2],v,h)

def Centroid(points):
    return engine.lib.Centroid([points,len(points)])

def isBetween(point1,point2,point3,ref):
        return engine.lib.isBetween(point1,point2,point3,ref)

def point_polygon(points1,points2):
    return engine.lib.point_polygon(points1,points2)

def point_circle(points1,points2):
    return engine.lib.point_circle(points1,points2)

def circle_circle(points1,points2):
    return engine.lib.circle_circle(points1,points2)

def polygon_polygon(points1,points2):
    return engine.lib.polygon_polygon(points1,points2)

def circle_polygon(points1,points2):
    return engine.lib.circle_polygon(points1,points2)

def SAT_Collide(shape1,shape2,enCollision,enPhysics):
    return engine.lib.SAT_Collide(shape1,shape2,enCollision,enPhysics)

def getaxis(points,center):
    return engine.lib.getaxis([points,len(points)],center)

def newShape(points,inertia,mass,restitution,friction):
    return engine.lib.newShape([points,len(points)],inertia,mass,restitution,friction)

def renderShape(shape):
    love.graphics.setColor(255,255,0)
    if shape[0].no > 2:
        fafa = []
        for i in range(0,shape[0].no):
            fafa.append([shape[0].pnt[i].loc.x,shape[0].pnt[i].loc.y])
        love.graphics.polygon2('fill',*fafa)
        love.graphics.setColor(255,0,0)
        love.graphics.polygon2('line',*fafa)
    elif shape[0].no == 2:
        love.graphics.circle('fill',shape[0].center.x,shape[0].center.y,shape[0].pnt[0].r)
        love.graphics.setColor(255,0,0)
        love.graphics.circle('line',shape[0].center.x,shape[0].center.y,shape[0].pnt[0].r)
        love.graphics.line(shape[0].center.x,shape[0].center.y,shape[0].pnt[0].loc.x,shape[0].pnt[0].loc.y)

def updateShape(shape):
    return engine.lib.updateShape(shape)

def destroyShape(shape):
    engine.lib.destroyShape(shape)

def wait():
    return engine.lib.wait()