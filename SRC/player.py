import love
from myengine import newShape,SAT_Collide,renderShape,updateShape,isBetween,destroyShape,angle
from math import sin,cos,floor,pi
import coin
import data
import health
import gun
playerride = []
playerbody = []
playerleg = []
bound = love.graphics.newImage(f"graphics/player/bound.png")
for i in range(0,360):
    playerride.append(love.graphics.newImage(f"graphics/player/ride/({i}).png"))
    playerbody.append(love.graphics.newImage(f"graphics/player/body/({i}).png"))
    playerleg.append(love.graphics.newImage(f"graphics/player/leg/({i}).png"))
class plr:
    def __init__(self,x,y):
        self.id = 'p'
        self.box = newShape([[0,0],[110,0],[110,55],[0,55]],0,10,0.1,0.1)
        self.box.center.x = x
        self.box.center.y = y
        self.range  = newShape([[0,0],[500,0]],0,10,0.1,0.1)
        self.ctrl = 0
        self.c = 0
        self.ctrl2 = 0
        '''self.time = 0
        self.count = 0'''
        self.move = False
        self.priority = 0
        self.xmin = 0
        self.xmax = 0
        self.downlist = []
        self.camX = 0
        self.camY = 0
        self.hp = health.hp(1000)
        self.gun = gun.gn()




    def update(self):
        self.box.dy = 0
        self.box.dx = 0
        self.move = False

        if love.keyboard.isDown('w'):
            self.ctrl = 270
            self.move = True
        if love.keyboard.isDown('s'):
            self.ctrl = 90
            self.move = True
        if love.keyboard.isDown('d'):
            self.ctrl = 0
            self.move = True
        if love.keyboard.isDown('a'):
            self.ctrl = 180
            self.move = True
        if love.keyboard.isDown('a') and love.keyboard.isDown('w'):
            self.ctrl = 180 + 45
            self.move = True
        if love.keyboard.isDown('a') and love.keyboard.isDown('s'):
            self.ctrl = 90 + 45
            self.move = True
        if love.keyboard.isDown('d') and love.keyboard.isDown('w'):
            self.ctrl = 270 + 45
            self.move = True
        if love.keyboard.isDown('d') and love.keyboard.isDown('s'):
            self.ctrl = 45
            self.move = True
        
        if self.move:
            for i in range(0,5):
                if self.c != self.ctrl:
                    if isBetween([self.box.center.x + cos((self.c + 1)*pi/180),self.box.center.y + sin((self.c + 1)*pi/180)],[self.box.center.x + cos(self.ctrl*pi/180),self.box.center.y + sin(self.ctrl*pi/180)],[self.box.center.x + cos(self.c*pi/180),self.box.center.y + sin(self.c*pi/180)],self.box.center):
                        self.c +=1
                    else:
                        self.c -=1
            self.c = data.normalizeangle(self.c)
            self.box.angle = self.c*pi/180

        if self.move:
            self.box.dx = 5*cos(self.c*pi/180)
            self.box.dy = 5*sin(self.c*pi/180)
        
        '''self.time = self.time == 0 and 4 or self.time - 1
        if self.time == 0:
            self.count = self.count != 7 and self.count + 1 or 0'''
        self.ctrl2 = floor(angle([self.box.center.x,self.box.center.y],[love.mouse.x,love.mouse.y/sin(pi/4)])*180/pi)

        updateShape(self.box)
        self.range.center.x = self.box.center.x
        self.range.center.y = self.box.center.y
        updateShape(self.range)

        data.npcno = 0
        for item in data.renderorder :
            if item.id == 'c':
                if SAT_Collide(item.box,self.box,False,False).check:
                    data.renderorder.remove(item)
                    destroyShape(item.box)
                    data.coinno += 1
                   
            if item.id == 'n':
                SAT_Collide(item.box,self.box,True,False)
                data.npcno += 1

            if item.id == 'b':
                SAT_Collide(item.box,self.box,True,False)

        if love.mouse.isDown(1,True):
            cn = coin.cn(love.mouse.x,love.mouse.y)
            data.renderorder.append(cn)


        mx = max(0, min( self.box.center.x - data.gameWidth / 2,
        min(4000 - data.gameWidth, self.box.center.x)))
        self.camX += (mx - self.camX)/10

        my = max(0, min( self.box.center.y*sin(pi/4) - data.gameHeight / 2,
        min(4000 - data.gameHeight, self.box.center.y)))
        self.camY += (my - self.camY)/10

        self.gun.update(self.ctrl2,self.box.center.x,self.box.center.y,self.box.dx,self.box.dy)

        
    def render(self):
        #love.graphics.draw2(bound,self.box.center.x - 60,self.box.center.y*sin(pi/4) - 97)
        #love.graphics.polygon2('line',[self.box.pnt[0].loc.x,self.box.pnt[0].loc.y*sin(pi/4)],[self.box.pnt[1].loc.x,self.box.pnt[1].loc.y*sin(pi/4)],[self.box.pnt[2].loc.x,self.box.pnt[2].loc.y*sin(pi/4)],[self.box.pnt[3].loc.x,self.box.pnt[3].loc.y*sin(pi/4)])
        #love.graphics.ellipse('line',self.range.center.x,self.range.center.y*sin(pi/4),500/2,500/2*sin(pi/4))
        love.graphics.draw2(playerride[self.c],self.box.center.x - 60,self.box.center.y*sin(pi/4) - 97)
        love.graphics.draw2(playerleg[self.c],self.box.center.x - 60,self.box.center.y*sin(pi/4) - 97)
        love.graphics.draw2(playerbody[self.ctrl2],self.box.center.x - 60,self.box.center.y*sin(pi/4) - 97)
        #love.graphics.print(f'{len(self.downlist)}',self.box.center.x,self.box.center.y*sin(pi/4)-50)
        #love.graphics.line(self.xmin.x,self.xmin.y*sin(pi/4),self.xmax.x,self.xmax.y*sin(pi/4))
        self.hp.render(self.box.center.x - 35,self.box.center.y*sin(pi/4) - 100)
        self.gun.render()
