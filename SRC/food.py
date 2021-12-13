import love
from myengine import newShape,SAT_Collide,renderShape,updateShape,isBetween
from math import sin,cos,floor,pi,ceil
import data
import health
foodanime = []
for i in range(0,6):
    foodanime.append(love.graphics.newImage(f"graphics/food/({i}).png"))
class fd:
    def __init__(self,x,y):
        self.box = newShape([[0,0],[400,0],[400,400],[0,400]],0,10,0.1,0.1)
        self.box.center.x = x
        self.box.center.y = y/sin(pi/4)
        updateShape(self.box)
        self.sv = health.sv(5000)
        self.sv.num = 5000
        self.ctrl = 5
    
    def update(self):
        for item in data.renderorder :
            if item.id == 'n':
                if not item.sv.full and not self.sv.null:
                    if SAT_Collide(item.box,self.box,False,False).check:
                        item.sv.update(1)
                        self.sv.update(-1)
                        self.ctrl = ceil(self.sv.num/1000)
                        
    
    def render(self):
        love.graphics.draw2(foodanime[self.ctrl],self.box.center.x - 400/2,self.box.center.y*sin(pi/4) - 290/2)
        #self.sv.render(self.box.center.x  - 35,self.box.center.y*sin(pi/4) - 10)