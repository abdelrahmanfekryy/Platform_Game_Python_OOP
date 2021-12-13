import love
from myengine import newShape,SAT_Collide,renderShape,updateShape
from math import sin,cos,floor,pi

class mp:
    def __init__(self,x,y,w):
        self.map = love.graphics.newImage(f"graphics/landscape.png")
        self.box = newShape([[0,0],[100,0],[100,3000],[0,3000]],0,10,0.1,0.1)
        self.box.angle = w
        self.box.center.x = x
        self.box.center.y = y/sin(pi/4)
        updateShape(self.box)

    def render(self):
        love.graphics.draw2(self.map,-500,-600)
        love.graphics.polygon2('line',[self.box.pnt[0].loc.x,self.box.pnt[0].loc.y*sin(pi/4)],[self.box.pnt[1].loc.x,self.box.pnt[1].loc.y*sin(pi/4)],[self.box.pnt[2].loc.x,self.box.pnt[2].loc.y*sin(pi/4)],[self.box.pnt[3].loc.x,self.box.pnt[3].loc.y*sin(pi/4)])
