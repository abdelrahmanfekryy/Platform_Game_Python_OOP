import love
from myengine import newShape,SAT_Collide,renderShape,updateShape,isBetween,destroyShape
from math import sin,cos,floor,pi
import data
numbers = []
for i in range(0,10):
    numbers.append(love.graphics.newImage(f"graphics/numbers0/{i}.png"))
    
class pp:
    def __init__(self,x,y,size):
        self.num = 0
        self.space = 0
        self.x = x
        self.y = y
        self.index = 1
        self.size = size

    def render(self):
        self.index = 1
        while 10**self.index <= self.num:
            self.index += 1

        #love.graphics.print(f'{self.index}',50 + self.x,0)
        for i in range(self.index):
            love.graphics.draw2(numbers[floor((self.num%(10**(i+1)))/10**i)],self.x + (self.index - i - 1)*self.size,self.y)
