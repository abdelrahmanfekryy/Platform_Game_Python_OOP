import love
from myengine import newShape,SAT_Collide,renderShape,updateShape,isBetween
from math import sin,cos,floor,pi
hltanime = []
for i in range(0,5):
    hltanime.append(love.graphics.newImage(f"graphics/health bar/({i}).png"))
class hp:
    def __init__(self,value):
        self.num = value
        self.value = value
        self.img = love.graphics.scale(hltanime[2],floor(self.num/self.value*62),12)
        self.full = False
        self.null = False
        
    def update(self,x):
        if x < 0:
            self.num += max(x,-self.num)
        if x > 0:
            self.num += min(x,self.value - self.num)
        self.img = love.graphics.scale(hltanime[2],floor(self.num/self.value*62),12)
        self.full = self.num == self.value
        self.null = self.num == 0

    def render(self,x,y):
        love.graphics.draw2(hltanime[1],x,y)
        love.graphics.draw2(self.img,x + 6,y + 4)
        love.graphics.draw2(hltanime[0],x,y)

class sv:
    def __init__(self,value):
        self.num = 0
        self.value = value
        self.img = love.graphics.scale(hltanime[4],floor(self.num/self.value*62),12)
        self.full = False
        self.null = False
    
    def update(self,x):
        if x < 0:
            self.num += max(x,-self.num)
        if x > 0:
            self.num += min(x,self.value - self.num)
        self.img = love.graphics.scale(hltanime[4],floor(self.num/self.value*62),12)
        self.full = self.num == self.value
        self.null = self.num == 0

    def render(self,x,y):
        love.graphics.draw2(hltanime[1],x,y)
        love.graphics.draw2(self.img,x + 6,y + 4)
        love.graphics.draw2(hltanime[3],x,y)
        #love.graphics.print(f'{self.num}',x,y)