import love
from myengine import newShape,SAT_Collide,renderShape,updateShape,isBetween,circle_polygon
from math import sin,cos,floor,pi
import data
coinanime = []
for i in range(0,180):
    coinanime.append(love.graphics.newImage(f"graphics/coin/({i}).png"))
class cn:
    def __init__(self,x,y):
        self.id = 'c'
        self.box = newShape([[0,0],[20,0],[20,20],[0,20]],0,10,0.1,0.1)
        self.box.center.x = x
        self.box.center.y = y/sin(pi/4)
        updateShape(self.box)
        self.ctrl = 0
        self.priority = 0
        self.xmin = 0
        self.xmax = 0
        self.downlist = []

    def update(self):
        self.ctrl = self.ctrl != 179 and self.ctrl + 1 or 0


    def render(self):
        for i in range(2):
            self.ctrl = self.ctrl != 179 and self.ctrl + 1 or 0
        love.graphics.draw2(coinanime[self.ctrl],self.box.center.x - 25,self.box.center.y*sin(pi/4) - 37)
        #love.graphics.ellipse('line',self.box.center.x,self.box.center.y*sin(pi/4),25,25*sin(pi/4))
        #love.graphics.polygon2('line',[self.box.pnt[0].loc.x,self.box.pnt[0].loc.y*sin(pi/4)],[self.box.pnt[1].loc.x,self.box.pnt[1].loc.y*sin(pi/4)],[self.box.pnt[2].loc.x,self.box.pnt[2].loc.y*sin(pi/4)],[self.box.pnt[3].loc.x,self.box.pnt[3].loc.y*sin(pi/4)])