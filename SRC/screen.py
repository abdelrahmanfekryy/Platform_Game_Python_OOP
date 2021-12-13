import love
from math import sin,cos,floor,pi
import data
import numbers
a = love.graphics.newImage(f"graphics/alian.png")
c = love.graphics.newImage(f"graphics/coin.png")
class scn:
    def __init__(self,x,y):
        self.x = x
        self.y = y
        self.coinCounter = numbers.pp(data.gameWidth/2 + 50,0,35)
        self.NPCCounter = numbers.pp(data.gameWidth/2 - 200 + 50,0,35)
    
    def render(self):
        love.graphics.draw2(a,data.gameWidth/2 - 200 + self.x,0 + self.y)
        love.graphics.draw2(c,data.gameWidth/2 + self.x,0 + self.y)
        self.coinCounter.num = data.coinno
        self.NPCCounter.num = data.npcno
        self.coinCounter.render()
        self.NPCCounter.render()

        
