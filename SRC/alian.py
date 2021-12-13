import love
from myengine import newShape,SAT_Collide,renderShape,updateShape,isBetween
from math import sin,cos,floor,pi
import data
import health
aliananime = []
for i in range(0,360):
    aliananime.append(love.graphics.newImage(f"graphics/alian 100/({i}).png"))
class aln:
    def __init__(self,x,y,playerrng):
        self.id = 'n'
        self.count = 0
        self.time = 4
        self.base =  newShape([[0,0],[100,0]],0,10,0.1,0.1)
        self.box = newShape([[0,0],[0,50],[50,50],[50,0]],0,10,0.1,0.1)
        self.box.center.x = x
        self.box.center.y = y
        self.collide = 0
        self.priority = 0
        self.xmin = 0
        self.xmax = 0
        self.downlist = []
        self.playerrng = playerrng
        self.hp = health.hp(1000)
        self.sv = health.sv(1000)


    def update(self):
        self.collide = SAT_Collide(self.playerrng,self.base,False,False)
        if self.collide.check:
            for i in range(0,5):
                if self.count != floor(self.collide.mtv.th*180/pi):
                    if isBetween([self.box.center.x + cos((self.count + 1)*pi/180),self.box.center.y + sin((self.count + 1)*pi/180)],[self.box.center.x + cos(self.collide.mtv.th),self.box.center.y + sin(self.collide.mtv.th)],[self.box.center.x + cos(self.count*pi/180),self.box.center.y + sin(self.count*pi/180)],self.box.center):
                        self.count +=1
                    else:
                        self.count -=1
            self.count = data.normalizeangle(self.count)
            self.box.center.x += 2*cos(self.count*pi/180)
            self.box.center.y += 2*sin(self.count*pi/180)
            self.box.angle = self.count*pi/180
            
        self.base.center = self.box.center
        updateShape(self.base)
        updateShape(self.box)

        for item in data.renderorder :
            if item.id == 'n' or item.id == 'b':
                SAT_Collide(item.box,self.box,True,False)

    def render(self):
        #love.graphics.polygon2('line',[self.box.pnt[0].loc.x,self.box.pnt[0].loc.y*sin(pi/4)],[self.box.pnt[1].loc.x,self.box.pnt[1].loc.y*sin(pi/4)],[self.box.pnt[2].loc.x,self.box.pnt[2].loc.y*sin(pi/4)],[self.box.pnt[3].loc.x,self.box.pnt[3].loc.y*sin(pi/4)])
        love.graphics.draw2(aliananime[self.count],self.box.center.x - 50,self.box.center.y*sin(pi/4) - 100 + 20)
        #love.graphics.print(f'x = {self.count}',self.base.center.x,self.base.center.y*sin(pi/4) - 200)
        #love.graphics.print(f'{len(self.downlist)}',self.box.center.x,self.box.center.y*sin(pi/4)-50)
        #love.graphics.line(self.xmin.x,self.xmin.y*sin(pi/4),self.xmax.x,self.xmax.y*sin(pi/4))
        #love.graphics.rectangle('line',self.box.center.x - 25,self.box.center.y*sin(pi/4) - 100,50,10)
        self.hp.render(self.box.center.x - 35,self.box.center.y*sin(pi/4) - 110)
        self.sv.render(self.box.center.x - 35,self.box.center.y*sin(pi/4) - 90)