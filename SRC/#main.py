import sys
sys.path.append('C:/Users/admin/Desktop/cattle drive/assests')
from myengine import *
import pygame
import random
from datetime import datetime
import math
import love
import data

love.graphics.display([data.gameWidth, data.gameHeight],'my game')

import numbers
import screen
import alian
import mymap
import player
import fence
import bomb
import coin
import food

def main():
    clock = pygame.time.Clock()
    run = True
    while run:
        clock.tick(60)
        #fps = clock.get_fps()
        dt = clock.get_time()/1000
        love.keyboard.update()
        love.mouse.update(-player.camX,-player.camY)
        update(dt)
        render(dt)
        love.graphics.setColor(0,0,0)
        love.graphics.print(f'{clock}',data.gameWidth - 300,5)
        love.graphics.update()
        for event in pygame.event.get():
            if event.type == pygame.QUIT or love.keyboard.isDown('ESCAPE'):
                run = False

#////////////////////
screen = screen.scn(0,0)
foo = food.fd(2200,700)
mps = mymap.mp(850,800,math.pi/4)
fences = [fence.fnc(1810,200,45),fence.fnc(1810,470,90 + 45),fence.fnc(2180,200,270 + 45)]
player = player.plr(2000,300)
bombs = [bomb.bmb(2000,1000),bomb.bmb(2000,1200),bomb.bmb(2200,1000),bomb.bmb(2200,1200)]

data.renderorder.append(player)
for i in range(6):
    data.renderorder.append(alian.aln(2000 + 50*i,500,player.range))
for i in range(0,len(fences)):
    data.renderorder.append(fences[i])
for i in range(0,len(bombs)):
    data.renderorder.append(bombs[i])

def update(dt):
    pass
        

def render(dt):
    love.graphics.clear(255/3,255/3,255/3)
    love.graphics.translate(-player.camX,-player.camY)
    ##################################################################
 
    mps.render()
    foo.update()
    foo.render()
    for i in data.renderorder:
        data.priorityclear(i)

    for i in data.renderorder:
        i.update()
    
    for i in data.renderorder:
        data.computeX(i)

    for i in range(0,len(data.renderorder)):
        for j in range(i+1,len(data.renderorder)):
            data.prioritycheck(data.renderorder[i],data.renderorder[j])

    for k in range(5):
        for i in data.renderorder:
            data.iterate(i)

    for i in range(0,len(data.renderorder)):
        for j in range(i+1,len(data.renderorder)):
            if data.renderorder[j].priority > data.renderorder[i].priority:
                temp = data.renderorder[j]
                data.renderorder[j] = data.renderorder[i]
                data.renderorder[i] = temp
    
    for i in data.renderorder:
        i.render()
    #######################################################################
    love.graphics.translate(0,0)
    screen.render()
    #if love.keyboard.isDown('r'):
    current_time = datetime.utcnow().strftime('%H_%M_%S.%f')
    pygame.image.save(pygame.transform.scale(love.graphics.screen,(1280/2,720/2)), f"gif/screenshot{current_time}.png")

    love.graphics.print(f'x = {love.mouse.x}, y = {love.mouse.y}',10,10)


if __name__ == '__main__':
    main()