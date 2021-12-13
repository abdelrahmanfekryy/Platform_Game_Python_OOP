import love
from myengine import newShape,SAT_Collide,renderShape,updateShape,isBetween
from math import sin,cos,floor,pi
import data
bullet = love.graphics.newImage(f"graphics/bullet/bullet.png")
class blt:
    def __init__(self,angle,x,y,dx,dy):
        self.id = 'bt'
        self.box = newShape([[0,0],[10,0],[10,10],[0,10]],0,10,0.1,0.1)
        self.box.center.x = x
        self.box.center.y = y/sin(pi/4)
        updateShape(self.box)
        self.priority = 0
        self.xmin = 0
        self.xmax = 0
        self.downlist = []
        self.angle = angle*pi/180
        self.time = 100
        self.dx = dx
        self.dy = dy
       
      
    def update(self):
        self.box.dx = 10*cos(self.angle)# + self.dx
        self.box.dy = 10*sin(self.angle)# + self.dy
        updateShape(self.box)
        self.time -= 1

    def render(self):
        #love.graphics.polygon2('line',[self.box.pnt[0].loc.x,self.box.pnt[0].loc.y*sin(pi/4)],[self.box.pnt[1].loc.x,self.box.pnt[1].loc.y*sin(pi/4)],[self.box.pnt[2].loc.x,self.box.pnt[2].loc.y*sin(pi/4)],[self.box.pnt[3].loc.x,self.box.pnt[3].loc.y*sin(pi/4)])
        love.graphics.draw2(bullet,self.box.center.x - 60,self.box.center.y*sin(pi/4) - 97)


