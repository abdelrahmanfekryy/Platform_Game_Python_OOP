import love
from myengine import newShape,SAT_Collide,renderShape,updateShape,isBetween
from math import sin,cos,floor,pi
import data
fenceanime = []
for i in range(0,360):
    fenceanime.append(love.graphics.newImage(f"graphics/fence 500/({i}).png"))
class fnc:
    def __init__(self,x,y,angle):
        self.id = 'b'
        self.box = newShape([[0,0],[0,500],[15,500],[15,0]],0,0,0.1,0.1)
        self.box.angle = angle*pi/180
        self.box.center.x = x
        self.box.center.y = y/sin(pi/4)
        updateShape(self.box)
        self.ctrl = angle
        self.priority = 0
        self.xmin = 0
        self.xmax = 0
        self.downlist = []

    def update(self):
        pass

    def render(self):
        #love.graphics.polygon2('line',[self.box.pnt[0].loc.x,self.box.pnt[0].loc.y*sin(pi/4)],[self.box.pnt[1].loc.x,self.box.pnt[1].loc.y*sin(pi/4)],[self.box.pnt[2].loc.x,self.box.pnt[2].loc.y*sin(pi/4)],[self.box.pnt[3].loc.x,self.box.pnt[3].loc.y*sin(pi/4)])
        love.graphics.draw2(fenceanime[self.ctrl],self.box.center.x - 500/2,self.box.center.y*sin(pi/4) - 250 - 40)
        #love.graphics.print(f'{len(self.downlist)}',self.box.center.x,self.box.center.y*sin(pi/4) - 50)
        #love.graphics.line(self.xmin.x,self.xmin.y*sin(pi/4),self.xmax.x,self.xmax.y*sin(pi/4))

