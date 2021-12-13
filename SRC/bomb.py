import love
from myengine import newShape,SAT_Collide,renderShape,updateShape,isBetween,circle_polygon,destroyShape
from math import sin,cos,floor,pi
import data
bombanime = []
bombsize = []
for i in range(0,2):
    bombanime.append(love.graphics.newImage(f"graphics/bomb/({i}).png"))
    bombsize.append(love.graphics.getSize(bombanime[i]))
class bmb:
    def __init__(self,x,y):
        self.id = 'e'
        #self.box = newShape([[0,0],[50,0]],0,0,0.1,0.1)
        self.box = newShape([[0,0],[50,0],[50,50],[0,50]],0,10,0.1,0.1)
        self.box.angle = pi/4
        self.box.center.x = x
        self.box.center.y = y/sin(pi/4)
        updateShape(self.box)
        self.ctrl = 0
        self.downlist = []
        self.xmin = self.box.pnt[3].loc
        self.xmax = self.box.pnt[1].loc
        self.priority = 100
       

    def update(self):
        for item in data.renderorder :
            if item.id == 'n' and self.ctrl == 0:
                if SAT_Collide(item.box,self.box,False,False).check:
                    self.ctrl = 1
                    item.hp.update(-500)
                    #data.renderorder.remove(item)
                    #destroyShape(item.box)

    def render(self):
        love.graphics.draw2(bombanime[self.ctrl],self.box.center.x - bombsize[self.ctrl][0]/2,self.box.center.y*sin(pi/4) - bombsize[self.ctrl][1]/2)
        #love.graphics.ellipse('line',self.box.center.x,self.box.center.y*sin(pi/4),25,25*sin(pi/4))
        #love.graphics.line(self.xmin.x,self.xmin.y*sin(pi/4),self.xmax.x,self.xmax.y*sin(pi/4))
        #love.graphics.print(f'{len(self.downlist)}',self.box.center.x,self.box.center.y*sin(pi/4)-50)