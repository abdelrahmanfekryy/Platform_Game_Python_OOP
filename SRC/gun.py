import love
from myengine import newShape,SAT_Collide,renderShape,updateShape,isBetween,destroyShape
from math import sin,cos,floor,pi
import data
import bullet
gun = []
for i in range(0,360):
    gun.append(love.graphics.newImage(f"graphics/gun/({i}).png"))
class gn:
    def __init__(self):
        self.x = 0 
        self.y = 0 
        self.dx = 0 
        self.dy = 0 
        self.angle = 0

    def update(self,angle,x,y,dx,dy):
        self.x = x
        self.y = y
        self.angle = angle
        if love.mouse.isDown(3,True):
            #for item in data.renderorder :
            #    if item.id == 'p':
            data.renderorder.append(bullet.blt(self.angle,self.x + 60*cos((self.angle +23)*pi/180),(self.y + 60*sin((self.angle + 23)*pi/180))*sin(pi/4),dx,dy))
        for item in data.renderorder :
            if item.id == 'bt':
                if item.time < 0:
                    data.renderorder.remove(item)
                    destroyShape(item.box)

    def render(self):
        #love.graphics.ellipse('line',self.x,self.y*sin(pi/4),60,60*sin(pi/4))
        love.graphics.draw2(gun[self.angle],self.x - 60,self.y*sin(pi/4) - 97)